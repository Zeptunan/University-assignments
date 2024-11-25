#include "image.h"
#include "window.h"
#include "load.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::unordered_map;

/**
 * Class that stores a summary of an image.
 *
 * This summary is intended to contain a high-level representation of the
 * important parts of an image. I.e. it shall contain what a human eye would
 * find relevant, while ignoring things that the human eye would find
 * irrelevant.
 */
class Image_Summary {
public:
    // Horizontal increases in brightness.
    vector<bool> horizontal;

    // Vertical increases in brightness.
    vector<bool> vertical;

    bool operator==(const Image_Summary &other) const {
        return horizontal == other.horizontal && vertical == other.vertical;
    };
};

// Definiera en typ som specialiserar std::hash för vår typ:
template <>
class std::hash<Image_Summary> { //specialiserar std::hash för vår typ "Image_Summary"
public:
    std::size_t operator()(const Image_Summary &to_hash) const { // Överlagrar call-operatorn för att generera ett hash-värde för Image_Summary
        std::size_t hash1 = std::hash<std::vector<bool>>{}(to_hash.horizontal); //Skapar ett hash-värde för horizontella vektorn
        std::size_t hash2 = std::hash<std::vector<bool>>{}(to_hash.vertical); //skapar ett hash-värde för vertikala vektorn 
        return hash1 ^ (hash2 << 1); // Skiftar hash2 ett steg till vänster (motsvarar multiplikation med 2)                                   
    }                                // och kombinerar det med hash1 med XOR för slutligt hashvärde
};

// Compute an Image_Summary from an image.
Image_Summary compute_summary(const Image &image) {
    const size_t summary_size = 8;
    Image_Summary result;

    Image shrunk_image = image.shrink(summary_size + 1, summary_size + 1); // Skalar ner bilden
    
    //horizontell jämförelse
    for (size_t y = 0; y < shrunk_image.height(); y++) { // Itererar över varje rad
        for (size_t x = 0; x < shrunk_image.width() - 1; x++){ // Itererar över varje kolumn utom den sista
            const Pixel &current = shrunk_image.pixel(x,y); // Hämtar aktuella pixel
            const Pixel &right_pixel = shrunk_image.pixel(x + 1,y); // Hämtar pixeln till höger om aktuella pixeln

            result.horizontal.push_back(current.brightness() < right_pixel.brightness()); // Jämför aktuella pixeln med pixeln till höger
        }                                                                                 // Lägger till 1 om sant och 0 om falskt
    }

    //vertikal jämförelse
    for (size_t x = 0; x < shrunk_image.width(); x++){ // Itererar över vare kolumn
        for (size_t y = 0; y < shrunk_image.height() - 1; y++){ // Itererar över varje rad utom den sista
            const Pixel &current = shrunk_image.pixel(x,y); // Hämtar aktuella pixel
            const Pixel &below_pixel = shrunk_image.pixel(x,y + 1); // Hämtar pixeln under aktuella pixeln
           
            result.vertical.push_back(current.brightness() < below_pixel.brightness()); // Jämför aktuella pixeln med pixeln under
        }                                                                               // Lägger till 1 om sant och 0 om falsk
    }
    return result;
}

int main(int argc, const char *argv[]) {
    WindowPtr window = Window::create(argc, argv);

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " [--nopause] [--nowindow] <directory>" << endl;
        cerr << "Missing directory containing files!" << endl;
        return 1;
    }

    vector<string> files = list_files(argv[1], ".jpg");
    cout << "Found " << files.size() << " image files." << endl;

    if (files.size() <= 0) {
        cerr << "No files found! Make sure you entered a proper path!" << endl;
        return 1;
    }

    // Mätning för total tid (inklusive inläsning)
    auto begin_total = std::chrono::high_resolution_clock::now();

    window->show_single("Loading images...", load_image(files[0]), false);

    // Mätning för inläsningstiden
    auto begin_inläsning = std::chrono::high_resolution_clock::now();
    
    unordered_map<Image_Summary, vector<string>> summaries; 
    // Gå igenom alla bilder och bearbeta dem
    for (const auto &file : files) {
        Image img = load_image(file);  // Ladda bilden
        Image_Summary summary = compute_summary(img);  // Beräkna sammanfattningen

        // Om denna sammanfattning redan finns, lägg till bilden i samma grupp (möjliga dubbletter)
        if (summaries.find(summary) != summaries.end()) {
            summaries[summary].push_back(file);
        } else {
            // Annars skapa en ny grupp för denna sammanfattning
            summaries[summary] = vector<string>{file};
        }
    }

    auto end_inläsning = std::chrono::high_resolution_clock::now();
    
    cout << "Inläsningstid: "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end_inläsning - begin_inläsning).count()
         << " milliseconds." << endl;

    // Nu när vi har alla sammanfattningar, visa grupper med liknande bilder (dubbletter)
    for (const auto &entry : summaries) {
        if (entry.second.size() > 1) {
            // Rapportera alla filer som är lika
            cout << "Match found: ";
            for (const auto &file : entry.second) {
                cout << file << " ";
            }
            cout << endl;
            window->report_match(entry.second);  // Visa bilderna som matchar
        }
    }

    auto end_total = std::chrono::high_resolution_clock::now();
    
    cout << "Total tid (inkl. inläsning och bearbetning): "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end_total - begin_total).count()
         << " milliseconds." << endl;

    return 0;
}