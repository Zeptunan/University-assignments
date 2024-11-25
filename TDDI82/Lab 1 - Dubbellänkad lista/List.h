#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include <iterator>
#include <iostream>

// Information om komplettering: 
//   Kompletteringen kan gälla hela filen och alla filer i labben, 
//   så får ni komplettering på en sak, kan samma sak förekomma på 
//   fler ställen utan att jag skrivit det. 
// 
//   Komplettering lämnas in via sendlab efter senast en (1) vecka 
// 
//   Har ni frågor om kompletteringen kan ni maila mig på: 
//   Malte.Nilsson@liu.se 

// Komplettering:Det ska endast gå att skapa en iterator genom begin och end.
// Kolla över vilka konstruktorer vi har

// Kommentar: att sätta const på begin och end är missvisande eftersom det med en iterator går att ändra på listan.  
// Detta gäller även åtkomst-operatorer i iterator-klassen. 

namespace List_NS {

template <typename T>
class List {
private:
  struct Node {
    Node() = default;
    Node(const T& v, Node* p, std::unique_ptr<Node> n)
      : value{v}, prev{p}, next{std::move(n)} {}
    T value{};
    Node* prev{};
    std::unique_ptr<Node> next{};
    
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
    Node(Node&&) = default;
    Node& operator=(Node&&) = default;
  };
  
  std::unique_ptr<Node> head;
  Node* tail;
  int sz;
  
  friend class List_Iterator;
  
public:
  class List_Iterator {
  public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    
    reference operator*();
    pointer operator->();
    
    List_Iterator& operator++();
    List_Iterator operator++(int);
    
    List_Iterator& operator--();
    List_Iterator operator--(int);
    
    bool operator==(const List_Iterator&) const;
    bool operator!=(const List_Iterator&) const;
    
  private:
    Node* curr;
    List_Iterator(Node* ptr = nullptr); 
    friend class List<T>; 
  };
  
  List();
  List(const List&);
  List(List&&) noexcept;
  List(std::initializer_list<T>);
  
  List& operator=(const List&)&;
  List& operator=(List&&)& noexcept;
  
  void push_front(const T& value);
  void push_back(const T& value);
  
  T& back() noexcept;
  const T& back() const noexcept;
  
  T& front() noexcept;
  const T& front() const noexcept;
  
  T& at(int idx);
  const T& at(int idx) const;
  
  int size() const noexcept;
  bool empty() const noexcept;
  
  void swap(List& other) noexcept;
  
  List_Iterator begin();
  List_Iterator end();
};
  
}

#include "List.tcc"
#endif // LIST_H
