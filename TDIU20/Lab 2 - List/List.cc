#include "List.h"

#include <initializer_list>
#include <iostream>
#include <map>
// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   Malte.Nilsson@liu.se

// Komplettering: Markera variabler och parametrar som inte bör ändras som const.
// Komplettering: Ta bort onödiga this-> 

// Komplttering: initiera variabler med måsvingar

// Komplettering: En testfil ska pröva de funktioner som
// ni har skapat. Det innebär att man vill pröva alla
// möjliga fall (även specialfall). Vi vill ju vara säkra
// på att vi har en funktion som fungerar. En bra fråga är:
// "Övertygar detta den som rättar att er funktion
// fungerar utan att kolla i List.cc-filen?"

// Se till att testa de undantag som kastas i de olika medlemsfunktionerna

// Kommentar: Undantag kastas inte när man försöker ta bort ett element som inte finns i listan.
// Detta behöver nödvändigtvis inte göras men bra att dokumentera "speciallfallen".

/* Node constructor */
List::Node::Node(int value, Node* prev, Node* next) 
    : data(value), prev(prev), next(next) {}

/* List constructor */
List::List() : first{nullptr}, last{nullptr}, listSize{0} {}

/* List constructor with initializer list */
List::List(const std::initializer_list<int>& list)
  : first{nullptr}, last{nullptr}, listSize{0} {
    for (const int value : list) {
      insert(value);
    }
				   }

/* List destructor */
List::~List() { clear(); }

/* Inserts values from another list to this list */
void List::insertFromOtherList(const List& other) {
  for (Node* otherCurrent = other.first; otherCurrent != nullptr; otherCurrent = otherCurrent->next) {
    insert(otherCurrent->data);
  }
}

/* List copy constructor */
List::List(const List& other) : first{nullptr}, last{nullptr}, listSize{0} {
  insertFromOtherList(other);
							       }

/* List copy assignment */
List& List::operator=(const List& other) {
  if (this != &other) {
    clear();
    insertFromOtherList(other);
  }
  return *this;
}

/* Resets the other list */
void List::resetOtherList(List& other) const {
  other.first = nullptr;
  other.last = nullptr;
  other.listSize = 0;
}

/* List move constructor */
List::List(List&& other) noexcept
  : first{other.first}, last{other.last}, listSize{other.listSize} {
    resetOtherList(other);
					  }

/* List move assignment */
List& List::operator=(List&& other) noexcept {
  if (this != &other) {
    clear();
    first = other.first;
    last = other.last;
    listSize = other.listSize;
    resetOtherList(other);
  }
  return *this;
}

/* Inserts a value into the list */
void List::insert(const int value) {
  Node* newNode = new Node{value, nullptr, nullptr};
  
  if (isEmpty()) {
    first = newNode;
    last = newNode;
  } else {
    Node* current = first;
    
    while (current != nullptr && current->data < value) {
      current = current->next;
    }
    
    if (current == first) {
      newNode->next = first;
      first->prev = newNode;
      first = newNode;
    } else if (current == nullptr) {
      last->next = newNode;
      newNode->prev = last;
      last = newNode;
    } else {
      newNode->next = current;
      newNode->prev = current->prev;
      current->prev->next = newNode;
      current->prev = newNode;
    }
  }
  listSize++;
}

/* Removes a value from the list */
void List::remove(const int value) {
  if (isEmpty()) {
    throw std::runtime_error("Cannot remove from an empty list.");
  }
  
  Node* candidateNode = first;
  
  while (candidateNode != nullptr && candidateNode->data != value) {
    candidateNode = candidateNode->next;
  }
  
  if (candidateNode == nullptr) {
    throw std::runtime_error("Value not found in the list.");
  }
  
  if (candidateNode == first) {
    first = candidateNode->next;
    if (first != nullptr) {
      first->prev = nullptr;
    } else {
      last = nullptr;
    }
  } else if (candidateNode == last) {
    last = candidateNode->prev;
    last->next = nullptr;
  } else {
    candidateNode->prev->next = candidateNode->next;
    candidateNode->next->prev = candidateNode->prev;
  }
  delete candidateNode;
  listSize--;
}


/* Clears the list */
void List::clear() {
  while (first != nullptr) {
    Node* nextNode = first->next;
    delete first;
    first = nextNode;
  }
  last = nullptr;
  listSize = 0;
}

/* Get the value at index */
int List::get(const int index) const {
  if (index < 0 || index >= listSize) {
    throw std::out_of_range{"Index out of bounds"};
  }
  
  Node* current = first;
  for (int i = 0; i < index; ++i) {
    current = current->next;
  }
  
  return current->data;
}

/* Returns the size of the list */
int List::size() const { return listSize; }

/* Returns true if the list is empty */
bool List::isEmpty() const { return listSize == 0; }

/* Prints the list for debugging */
void List::print(std::ostream& os) const {
  Node* current = first;
  while (current != nullptr) {
    os << current->data << " ";
    current = current->next;
  }
  os << std::endl;
}


/* Returns a sub list */
List List::sub(const std::initializer_list<int> indexes) const {
  /* Map of indexes and their occurences */
  std::map<int, int> indexMap{};
  
  /* Previous index */
  int prevIndex = -1;
  
  /* Add each index and its occurence to the map */
  for (int index : indexes) {
    /* Check if index is valid */
    if (index < 0 || index >= this->listSize) {
      throw std::out_of_range("Index out of bounds");
    }
    
    /* Check if the input indexes are sorted */
    if (prevIndex > 0 && prevIndex > index) {
      throw std::invalid_argument("Indexes are not sorted");
    }
    
    /* Add index to map if it didn't exist,
     * otherwise increase counter
     */
    if (indexMap.find(index) == indexMap.end()) {
      indexMap[index] = 1;
    } else {
      indexMap[index]++;
    }
    prevIndex = index;  // Update prevIndex variable
  }
  
  List newList{};
  Node* currentNode = this->first;
  
  /* Add nodes to the new list */
  for (int i = 0; i < this->listSize; i++) {
    /* If the index is in the map */
    if (indexMap.find(i) != indexMap.end()) {
      /* Add the node to the new list */
      for (int j = 0; j < indexMap[i]; j++) {
	/* Inserts happen either in the beginning or end of the list,
	 * because the list is already sorted
	 */
	if (newList.isEmpty()) {
	  newList.first =
	    new Node(currentNode->data, nullptr, nullptr);
	  newList.last = newList.first;
	} else {
	  newList.last->next =
	    new Node(currentNode->data, newList.last, nullptr);
	  newList.last = newList.last->next;
	}
	newList.listSize++;
      }
    }
    currentNode = currentNode->next;
  }
  return newList;
}
