#include "List.h"

#include <utility>
#include <stdexcept>
#include <iostream>

// Standardkonstruktor som skapar en lista med en dummy-nod och initierar storleken till 0.
template <typename T>
List_NS::List<T>::List() : head{std::make_unique<Node>()}, tail{head.get()}, sz{0} {}

// Kopieringskonstruktor som kopierar innehållet från other till nya instansen av List 
template <typename T>
List_NS::List<T>::List(List const & other)
  : List{} // Anropar standardkonstruktorn för att initialisera listan
{
  for (Node *tmp{other.head.get()}; tmp != other.tail;)
    {
      push_back(tmp->value);
      tmp = tmp->next.get();
    }
} 

// Move-konstruktor som använder swap för att ta över resurser från en temporär lista.
template <typename T>
List_NS::List<T>::List(List && tmp) noexcept
  :List{}
{
  swap(tmp);
}

// Konstruktor som tar en initializer_list för att initiera listan med flera element.
template <typename T>
List_NS::List<T>::List(std::initializer_list<T> lst)
  : List{}
{
  for ( auto val : lst )
    {
      push_back(val);
    }
}

// Lägger till ett element i början av listan.
template <typename T>
void List_NS::List<T>::push_front(T value) {
  head = std::make_unique<Node>(value, nullptr, std::move(head));
  head.get()->next.get()->prev = head.get();
  if(sz == 0){
    tail->prev = head.get();
  }
  ++sz; 
}

// Lägger till element i slutet av listan.
template <typename T>
void List_NS::List<T>::push_back(T value) {
  if (empty()){
    push_front(value);
  }
  else{
    //tail->prev->next.release(); // Next släpper ägarskap av noden som next pekar på som är den sista faktiskta noden
    tail->prev->next = std::make_unique<Node>(value, tail->prev, std::move(tail->prev->next)); // Skapar en ny nod som next ska peka på
    tail->prev = tail->prev->next.get(); // uppdaterar den sista noden
    ++sz;
  }
}

// Kontrollerar om listan är tom
template <typename T>
bool List_NS::List<T>::empty() const noexcept
{
  return sz == 0;
}

// Ger åtkomst till sista elementet i listan
template <typename T>
T List_NS::List<T>::back() const noexcept
{
  return tail->prev->value;
}

// ger åtkomst till 
template <typename T>
T & List_NS::List<T>::back() noexcept
{
  return tail->prev->value;
}

// Ger åtkomst till första elementet i listan
template <typename T>
T List_NS::List<T>::front() const noexcept
{
  return head->value;
}
template <typename T>
T & List_NS::List<T>::front() noexcept
{
  return head->value;
}

// Ger åtkomst till elementet vid ett specifikt index. Kastar ett undantag om indexet är ogiltigt.
template <typename T>
T & List_NS::List<T>::at(int idx)
{
  return const_cast<T &>(static_cast<List const *>(this)->at(idx));
}

template <typename T>
T const & List_NS::List<T>::at(int idx) const
{
  if (idx >= sz)
    throw std::out_of_range{"Index not found"};
  Node * tmp {head.get()};
  while ( idx > 0 )
    {
      tmp = tmp->next.get();
      --idx;
    }
  return tmp->value;
}

// Returnerar antalet element i listan 
template <typename T>
int List_NS::List<T>::size() const noexcept
{
  return sz;
}

// Byter innehållet i en lista med en annan.
template <typename T>
void List_NS::List<T>::swap(List & other) noexcept
{
  using std::swap;
  swap(head, other.head);
  swap(tail, other.tail);
  swap(sz, other.sz);
}

// Tilldelningsoperator för kopiering.  
template <typename T>
List_NS::List<T>& List_NS::List<T>::operator=(List<T> const & rhs) &
  {
   List{rhs}.swap(*this); // Skapar en kopia av rhs och byter sedan innehåll.
   return *this;
  }
template <typename T>
List_NS::List<T>& List_NS::List<T>::operator=(List<T>&& rhs)& noexcept
{
  swap(rhs); // Byter direkt innehåll med rhs.
  return *this;
}


// Iterator funktionerna

// Skapar en iterator som initialt pekar på en specifik nod. 
template <typename T>
List_NS::List<T>::List_Iterator::List_Iterator(Node* ptr) : curr(ptr) {}

// Tillgånsoperator för iteratorn, returnerar en referens till nodens värde.
template <typename T>
T& List_NS::List<T>::List_Iterator::operator*() const {return curr->value;}

// Prefix inkrement: flyttar iteratorn till nästa nod i listan.
template <typename T>
typename List_NS::List<T>::List_Iterator& List_NS::List<T>::List_Iterator::operator++() {
  if (curr != nullptr) {
    curr = curr->next.get(); // Flyttar till nästa nod 
  }
  return *this;
}

// Postfix inkrement: returerar en kopia av nuvarande iteratorn innan den flyttas till nästa nod.
template <typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::List_Iterator::operator++(int) {
  List_Iterator tmp{*this};
  if(curr->next != nullptr) 
    {
      curr = curr->next.get(); // flyttar till nästa nod om möjligt 
    }
  return tmp; // returnerar kopia med gamla värdet
}

// Prefix dekrement: flyttar iteratorn till föregående nod. 
template <typename T> 
typename List_NS::List<T>::List_Iterator& List_NS::List<T>::List_Iterator::operator--() {
  if (curr->prev !=  nullptr) {
    curr = curr->prev;
  }
  return *this;
}

// Postfix dekrement: returnerar en kopia av nuvarande iteratorn innan den flyttas till föregående nod. 
template <typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::List_Iterator::operator--(int) {
  List_Iterator tmp{*this};
  if (curr->prev != nullptr) {
    curr = curr->prev; // flyttar till föregående nod om möjligt 
  }
  return tmp; 
}

// Jämförelseoperator som kontreollerar om två iteratorer pekar på samma nod.
template <typename T>
bool List_NS::List<T>::List_Iterator::operator==(const List_Iterator &rhs) const {
  return curr == rhs.curr;   
}

// Jämförelseoperator som kontrollerar om två iteratorer inte pekar på samma nod. 
template <typename T>
bool List_NS::List<T>::List_Iterator::operator!=(const List_Iterator &rhs) const {
  return curr != rhs.curr;  
}

// Returnerar en iterator som pekar på listans första nod. 
template <typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::begin() const {
  return List_Iterator(head.get()); 
}

// Returnerar en iterator som representerar en position efter listans sista nod. 
template <typename T>
typename List_NS::List<T>::List_Iterator List_NS::List<T>::end() const {
  return List_Iterator(tail);
}
