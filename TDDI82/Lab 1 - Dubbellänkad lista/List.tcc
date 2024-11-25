#include <utility>
#include <stdexcept>
#include <iostream>

namespace List_NS {

// Standardkonstruktor som skapar en lista med en dummy-nod och initierar storleken till 0.
template <typename T>
List<T>::List() : head{std::make_unique<Node>()}, tail{head.get()}, sz{0} {}

// Kopieringskonstruktor som kopierar innehållet från other till nya instansen av List 
template <typename T>
List<T>::List(const List<T>& other) : List{} {
    for (Node* tmp = other.head.get(); tmp != other.tail;) {
        push_back(tmp->value);
        tmp = tmp->next.get();
    }
}

// Move-konstruktor som använder swap för att ta över resurser från en temporär lista.
template <typename T>
List<T>::List(List<T>&& tmp) noexcept : List{} {
    swap(tmp);
}

// Konstruktor som tar en initializer_list för att initiera listan med flera element.
template <typename T>
List<T>::List(std::initializer_list<T> lst) : List{} {
    for (const auto& val : lst) {
        push_back(val);
    }
}

// Lägger till ett element i början av listan.
template <typename T>
void List<T>::push_front(const T& value) {
    head = std::make_unique<Node>(value, nullptr, std::move(head));
    head->next->prev = head.get();
    if (sz == 0) {
        tail->prev = head.get();
    }
    ++sz;
}

// Lägger till ett element i slutet av listan.
template <typename T>
void List<T>::push_back(const T& value) {
    if (empty()) {
        push_front(value);
    } else {
        tail->prev->next = std::make_unique<Node>(value, tail->prev, std::move(tail->prev->next));
        tail->prev = tail->prev->next.get();
        ++sz;
    }
}

// Kontrollerar om listan är tom
template <typename T>
bool List<T>::empty() const noexcept {
    return sz == 0;
}

// Ger åtkomst till sista elementet i listan
template <typename T>
const T& List<T>::back() const noexcept {
    return tail->prev->value;
}

// Ger åtkomst till sista elementet i listan
template <typename T>
T& List<T>::back() noexcept {
    return tail->prev->value;
}

// Ger åtkomst till första elementet i listan
template <typename T>
const T& List<T>::front() const noexcept {
    return head->value;
}

// Ger åtkomst till första elementet i listan
template <typename T>
T& List<T>::front() noexcept {
    return head->value;
}

// Ger åtkomst till elementet vid ett specifikt index. Kastar ett undantag om indexet är ogiltigt.
template <typename T>
T& List<T>::at(int idx) {
    return const_cast<T&>(static_cast<const List*>(this)->at(idx));
}

template <typename T>
const T& List<T>::at(int idx) const {
    if (idx >= sz) throw std::out_of_range{"Index not found"};
    Node* tmp = head.get();
    while (idx > 0) {
        tmp = tmp->next.get();
        --idx;
    }
    return tmp->value;
}

// Returnerar antalet element i listan 
template <typename T>
int List<T>::size() const noexcept {
    return sz;
}

// Byter innehållet i en lista med en annan.
template <typename T>
void List<T>::swap(List& other) noexcept {
    using std::swap;
    swap(head, other.head);
    swap(tail, other.tail);
    swap(sz, other.sz);
}

// Tilldelningsoperator för kopiering.  
template <typename T>
List<T>& List<T>::operator=(const List& rhs) & {
    List{rhs}.swap(*this); // Skapar en kopia av rhs och byter sedan innehåll.
    return *this;
}

// Tilldelningsoperator för flyttning.
template <typename T>
List<T>& List<T>::operator=(List&& rhs) & noexcept {
    swap(rhs); // Byter direkt innehåll med rhs.
    return *this;
}

// Iterator-funktioner

// Skapar en iterator som initialt pekar på en specifik nod. 
template <typename T>
List<T>::List_Iterator::List_Iterator(Node* ptr) : curr(ptr) {}

// Tillgångsoperator för iteratorn, returnerar en referens till nodens värde.
template <typename T>
T& List<T>::List_Iterator::operator*() { 
    return curr->value;
}

// Tillgångsoperator för att komma åt medlemmar hos noden via iteratorn.
template <typename T>
typename List<T>::List_Iterator::pointer List<T>::List_Iterator::operator->() {
    return &(this->curr->value);
}

// Prefix inkrement: flyttar iteratorn till nästa nod i listan.
template <typename T>
typename List<T>::List_Iterator& List<T>::List_Iterator::operator++() {
    if (curr != nullptr) {
        curr = curr->next.get(); // Flyttar till nästa nod 
    }
    return *this;
}

// Postfix inkrement: returnerar en kopia av nuvarande iteratorn innan den flyttas till nästa nod.
template <typename T>
typename List<T>::List_Iterator List<T>::List_Iterator::operator++(int) {
    List_Iterator tmp{*this};
    if (curr->next != nullptr) {
        curr = curr->next.get(); // Flyttar till nästa nod om möjligt 
    }
    return tmp; // Returnerar kopia med gamla värdet
}

// Prefix dekrement: flyttar iteratorn till föregående nod. 
template <typename T>
typename List<T>::List_Iterator& List<T>::List_Iterator::operator--() {
    if (curr->prev != nullptr) {
        curr = curr->prev;
    }
    return *this;
}

// Postfix dekrement: returnerar en kopia av nuvarande iteratorn innan den flyttas till föregående nod. 
template <typename T>
typename List<T>::List_Iterator List<T>::List_Iterator::operator--(int) {
    List_Iterator tmp{*this};
    if (curr->prev != nullptr) {
        curr = curr->prev; // Flyttar till föregående nod om möjligt 
    }
    return tmp; 
}

// Jämförelseoperator som kontrollerar om två iteratorer pekar på samma nod.
template <typename T>
bool List<T>::List_Iterator::operator==(const List_Iterator& rhs) const {
    return curr == rhs.curr;   
}

// Jämförelseoperator som kontrollerar om två iteratorer inte pekar på samma nod. 
template <typename T>
bool List<T>::List_Iterator::operator!=(const List_Iterator& rhs) const {
    return curr != rhs.curr;  
}

// Returnerar en iterator som pekar på listans första nod. 
template <typename T>
typename List<T>::List_Iterator List<T>::begin() {
    return List_Iterator(head.get()); 
}

// Returnerar en iterator som representerar en position efter listans sista nod. 
template <typename T>
typename List<T>::List_Iterator List<T>::end() {
    return List_Iterator(tail);
}

} // namespace List_NS
