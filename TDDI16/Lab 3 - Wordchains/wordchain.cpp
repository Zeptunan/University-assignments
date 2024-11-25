#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <unordered_map>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::unordered_set;
using std::queue; 
using std::unordered_map; 

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef unordered_set<string> Dictionary;

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */

vector<string> generate_neighbors(const string &from, const Dictionary &dict) {
    vector<string> neighbors; 
    for (int i = 0; i < from.size(); ++i){
        for(char c = 'a'; c <= 'z'; ++c) {
            string generate_string = from; 
            generate_string[i] = c; 
            if (dict.find(generate_string) != dict.end())
                neighbors.push_back(generate_string);
        }
    }
    return neighbors;
}

vector<string> find_shortest(const Dictionary &dict, const string &from, const string &to) {
    unordered_set<string> visited; // Håller koll på de ord vi besökt
    unordered_map<string, string> parent; // Sparar varifrån varje ord kommer
    queue<string> q; // Kö för BFS

    q.push(from); // Lägg startordet i kön
    visited.insert(from); // Markerar startordet som besökt

    while (!q.empty()) { // Fortsätt sålänge kön inte är tom
        string current_word = q.front(); // Ta ut första ordet i kön
        q.pop(); // Ta bort det från kön

        if (current_word == to) { // Om vi har nått slutordet, avsluta loopen
            break;
        }

        // Gå igenom alla grannar
        for (const auto& neighbor : generate_neighbors(current_word, dict)) { 
            if (visited.find(neighbor) == visited.end()) { // Om granne inte är besökt
                visited.insert(neighbor); // Markera grannen som besökt
                parent[neighbor] = current_word; // Spara varifrån vi kom
                q.push(neighbor); // Lägg till granne i kön
            }
        }
    }


    vector<string> result; // Resultat för ordkedja 
    if (parent.find(to) != parent.end() || from == to) { // Om vi hittat en väg eller om from = to
        string current = to; // Börjar med slutordet 
        while (true) { // Gå baklänges från slutordet till startordet
            result.push_back(current); 
            if (current == from) break; // Om vi når startordet, avsluta
            current = parent[current]; // Flytta till föregående ord i kedjan
        }
        reverse(result.begin(), result.end()); // Vänd ordningen så vi får from -> to
    }

    return result;
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const Dictionary &dict, const string &word) {
    unordered_set<string> visited;
    unordered_map<string, string> parent;
    queue<string> q;

    q.push(word);
    visited.insert(word);

    string furthest_word = word; // För att hålla reda på ordet längst bort
    int max_distance = 0; // Längsta avståndet hittills 
    unordered_map<string, int> distance;  // Lagrar avståndet från startordet
    distance[word] = 0; // Avståndet till målordet är 0 

    while (!q.empty()) {
        string current_word = q.front();
        q.pop();

        int current_distance = distance[current_word]; // Hämta avståndet till nuvarande ord 

        for (const auto& neighbor : generate_neighbors(current_word, dict)) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current_word;
                distance[neighbor] = current_distance + 1; // Uppdatera avståndet till grannen
                q.push(neighbor); 

                // Om det nya avståndet är längre än det tidigare längsta avståndet
                if (distance[neighbor] > max_distance) { 
                    max_distance = distance[neighbor]; // Uppdatera längsta avståndet
                    furthest_word = neighbor; // Uppdatera ordet längst bort
                }
            }
        }
    }

    vector<string> result;
    string current = furthest_word; // Börja med ordet längst bort 
    while (true) {
        result.push_back(current);
        if (current == word) break;
        current = parent[current];
    }
    return result;
}




/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
Dictionary read_dictionary() {
    string line;
    unordered_set<string> result;
    while (std::getline(std::cin, line)) {
        if (line == "#")
            break;

        result.insert(line);
    }

    return Dictionary(result.begin(), result.end());
}

/**
 * Skriv ut en ordkedja på en rad.
 */
void print_chain(const vector<string> &chain) {
    if (chain.empty())
        return;

    vector<string>::const_iterator i = chain.begin();
    cout << *i;

    for (++i; i != chain.end(); ++i)
        cout << " -> " << *i;

    cout << endl;
}

/**
 * Skriv ut ": X ord" och sedan en ordkedja om det behövs. Om ordkedjan är tom, skriv "ingen lösning".
 */
void print_answer(const vector<string> &chain) {
    if (chain.empty()) {
        cout << "ingen lösning" << endl;
    } else {
        cout << chain.size() << " ord" << endl;
        print_chain(chain);
    }
}

/**
 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions(const Dictionary &dict) {
    string line;
    while (std::getline(std::cin, line)) {
        size_t space = line.find(' ');
        if (space != string::npos) {
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second);

            cout << first << " " << second << ": ";
            print_answer(chain);
        } else {
            vector<string> chain = find_longest(dict, line);

            cout << line << ": ";
            print_answer(chain);
        }
    }
}

int main() {
    Dictionary dict = read_dictionary();
    read_questions(dict);

    return 0;
}
