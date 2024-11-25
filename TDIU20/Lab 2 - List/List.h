#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <iostream> // Inkludera för std::ostream

// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   Malte.Nilsson@liu.se


// Komplettering: Funktionen för utskrift ska göra utskriften på en given utström.

// Kommentar: Privata medlemar bör läggas längst ner i klassdeklarationen.
// Kommentar: Node bör vara en struct. Vi behöver inte skapa en konstruktor och kan fortfarande initiera Node på samma sätt.

class List {
public:

  struct Node { // Ändrad från class till struct
    int data;     // Node data
    Node* prev;   // Prev node pointer
    Node* next;   // Next node pointer
    
    Node(const int value = 0, Node* prev = nullptr, Node* next = nullptr);
  };
  
  
    List();   // Default constructor
    ~List();  // Destructor

    List(const std::initializer_list<int>& list);  // Initializer list constructor

    List(const List& other);             // Copy constructor
    List& operator=(const List& other);  // Copy assignment

    List(List&& other) noexcept;             // Move constructor
    List& operator=(List&& other) noexcept;  // Move assignment

    void insert(int value);    // Insert value into the list
    void remove(int value);    // Remove value from the list
    void clear();              // Clear the list
    int get(int index) const;  // Get the value at index
    int size() const;          // Get the size of the list
    bool isEmpty() const;      // Check if the list is empty
    void print(std::ostream& os) const;  // Print the list to a given stream

    List sub(std::initializer_list<int> indexes) const;  // Returns a sub list

private:

    Node* first;   // Pointer to first node in the list
    Node* last;    // Pointer to last node in the list
    int listSize;  // Size of the list

    void insertFromOtherList(const List& other);  // Internal function
    void resetOtherList(List& other) const;       // Internal function
};

#endif  // LIST_H

