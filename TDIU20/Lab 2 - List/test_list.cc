#include <iostream>

#include "List.h"
#include "catch.hpp"
using namespace std;

TEST_CASE("DOUBLE LINKED LIST TEST") {
  SECTION("Default constructor") {
    List empty{};
    CHECK(empty.size() == 0);
    CHECK(empty.isEmpty());
  }
  
  SECTION("Initializer list constructor") {
    List list{3, 2, 1};
    CHECK(list.size() == 3);
    CHECK(!list.isEmpty());
    CHECK(list.get(0) == 1);
    CHECK(list.get(1) == 2);
    CHECK(list.get(2) == 3);
    
    /* Test doubles */
    List list2{3, 3, 2, 2, 1, 1};
    CHECK(list2.size() == 6);
    CHECK(!list2.isEmpty());
    CHECK(list2.get(0) == 1);
    CHECK(list2.get(1) == 1);
    CHECK(list2.get(2) == 2);
    CHECK(list2.get(3) == 2);
    CHECK(list2.get(4) == 3);
    CHECK(list2.get(5) == 3);
  }
  
  SECTION("Destructor") {
    List list{};
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.~List();
    CHECK(list.size() == 0);
    CHECK(list.isEmpty());
  }
  
  SECTION("Copy") {
    /* Copy constructor */
    List list{};
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    List copy{list};
    
    CHECK(copy.size() == list.size());
    CHECK(copy.size() == 3);
    
    CHECK(!copy.isEmpty());
    CHECK(!list.isEmpty());
    
    CHECK(copy.get(0) == list.get(0));
    CHECK(copy.get(0) == 1);
    
    CHECK(copy.get(1) == list.get(1));
    CHECK(copy.get(1) == 2);
    
    CHECK(copy.get(2) == list.get(2));
    CHECK(copy.get(2) == 3);
    
    /* Deep copy check */
    list.remove(1);
    CHECK(copy.size() == 3);
    CHECK(list.size() == 2);
    
    CHECK(copy.get(0) == 1);
    CHECK(copy.get(1) == 2);
    CHECK(copy.get(2) == 3);
    
    CHECK(list.get(0) == 2);
    CHECK(list.get(1) == 3);
    
    /* Copy assignment */
    List list2{};
    list2.insert(1);
    list2.insert(2);
    list2.insert(3);
    
    List copy2{};
    copy2 = list2;
    
    CHECK(copy2.size() == list2.size());
    CHECK(copy2.size() == 3);
    
    CHECK(!copy2.isEmpty());
    CHECK(!list2.isEmpty());
    
    CHECK(copy2.get(0) == list2.get(0));
    CHECK(copy2.get(0) == 1);

    CHECK(copy2.get(1) == list2.get(1));
    CHECK(copy2.get(1) == 2);
    
    CHECK(copy2.get(2) == list2.get(2));
    CHECK(copy2.get(2) == 3);
    
    /* Deep copy check */
    list2.remove(1);
    CHECK(copy2.size() == 3);
    CHECK(list2.size() == 2);
    
    CHECK(copy2.get(0) == 1);
    CHECK(copy2.get(1) == 2);
    CHECK(copy2.get(2) == 3);
    
    CHECK(list2.get(0) == 2);
    CHECK(list2.get(1) == 3);
    
  }
  
  SECTION("MOVE") {
    /* Move constructor */
    List list{};
    list.insert(1);
    list.insert(2);
    list.insert(3);
    
    List newList{std::move(list)};
    
    CHECK(newList.size() == 3);
    CHECK(list.size() == 0);
    
    CHECK(!newList.isEmpty());
    CHECK(list.isEmpty());
    
    CHECK(newList.get(0) == 1);
    CHECK(newList.get(1) == 2);
    CHECK(newList.get(2) == 3);

    /* Move assignment */
    List list2{};
    list2.insert(1);
    list2.insert(2);
    list2.insert(3);
    
    List newList2 = std::move(list2);
    
    CHECK(newList2.size() == 3);
    CHECK(list2.size() == 0);
    
    CHECK(!newList2.isEmpty());
    CHECK(list2.isEmpty());
    
    CHECK(newList2.get(0) == 1);
    CHECK(newList2.get(1) == 2);
    CHECK(newList2.get(2) == 3);
  }
  
  SECTION("Insert") {
    /* Tests sorted insert */
    List list{};
    
    list.insert(42);
    list.insert(24);
    list.insert(616);
    list.insert(-235);
    list.insert(0);
    list.insert(1);
    list.insert(-400);
    
    CHECK(list.size() == 7);
    CHECK(!list.isEmpty());
    
    CHECK(list.get(0) == -400);
    CHECK(list.get(1) == -235);
    CHECK(list.get(2) == 0);
    CHECK(list.get(3) == 1);
    CHECK(list.get(4) == 24);
    CHECK(list.get(5) == 42);
    CHECK(list.get(6) == 616);
    
    /* Test doubles */
    List list2{};
    list2.insert(42);
    list2.insert(42);
    list2.insert(44);
    list2.insert(44);
    
    CHECK(list2.size() == 4);
    CHECK(!list2.isEmpty());
    
    CHECK(list2.get(0) == 42);
    CHECK(list2.get(1) == 42);
    CHECK(list2.get(2) == 44);
    CHECK(list2.get(3) == 44);
  }
  
  SECTION("Remove") {
    /* Tests removing elements and the sorting */
    List list{};
    
    list.insert(42);
    list.insert(24);
    list.insert(616);
    list.insert(-235);
    list.insert(0);
    list.insert(1);
    list.insert(-400);
    
    CHECK(list.size() == 7);
    
    list.remove(42);
    CHECK(list.size() == 6);
    CHECK(list.get(0) == -400);
    CHECK(list.get(1) == -235);
    CHECK(list.get(2) == 0);
    CHECK(list.get(3) == 1);
    CHECK(list.get(4) == 24);
    CHECK(list.get(5) == 616);
    
    list.remove(24);
    CHECK(list.size() == 5);
    CHECK(list.get(0) == -400);
    CHECK(list.get(1) == -235);
    CHECK(list.get(2) == 0);
    CHECK(list.get(3) == 1);
    CHECK(list.get(4) == 616);
    
    list.remove(616);
    CHECK(list.size() == 4);
    CHECK(list.get(0) == -400);
    CHECK(list.get(1) == -235);
    CHECK(list.get(2) == 0);
    CHECK(list.get(3) == 1);
    
    list.remove(-235);
    CHECK(list.size() == 3);
    CHECK(list.get(0) == -400);
    CHECK(list.get(1) == 0);
    CHECK(list.get(2) == 1);
    
    list.remove(0);
    CHECK(list.size() == 2);
    CHECK(list.get(0) == -400);
    CHECK(list.get(1) == 1);
    
    list.remove(1);
    CHECK(list.size() == 1);
    CHECK(list.get(0) == -400);

    list.remove(-400);
    
    CHECK(list.size() == 0);
    CHECK(list.isEmpty());
    
        /* Test doubles */
    List list2{};
    list2.insert(42);
    list2.insert(42);
    list2.insert(44);
    list2.insert(44);
    
    list2.remove(42);
    CHECK(list2.size() == 3);
    CHECK(list2.get(0) == 42);
    CHECK(list2.get(1) == 44);
    CHECK(list2.get(2) == 44);
    
    list2.remove(44);
    CHECK(list2.size() == 2);
    CHECK(list2.get(0) == 42);
    CHECK(list2.get(1) == 44);
    
    list2.remove(44);
    CHECK(list2.size() == 1);
    CHECK(list2.get(0) == 42);
    
    list2.remove(42);
    CHECK(list2.size() == 0);
    CHECK(list2.isEmpty());
  }
  
  SECTION("Clear") {
    List list{};
    
    list.insert(42);
    list.insert(24);
    list.insert(616);
    list.insert(-235);
    list.insert(0);
    list.insert(1);
    list.insert(-400);
    
    CHECK(list.size() == 7);
    CHECK(!list.isEmpty());
    
    list.clear();
    
    CHECK(list.size() == 0);
    CHECK(list.isEmpty());
  }
  
  SECTION("Get") {
    List list{};
    
    list.insert(42);
    list.insert(24);
    list.insert(616);
    list.insert(-235);
    list.insert(0);
    list.insert(1);
    list.insert(-400);
    
    CHECK(list.get(0) == -400);
    CHECK(list.get(1) == -235);
    CHECK(list.get(2) == 0);
    CHECK(list.get(3) == 1);
    CHECK(list.get(4) == 24);
    CHECK(list.get(5) == 42);
    CHECK(list.get(6) == 616);
  }
  
  SECTION("Size") {
    List list{};
    CHECK(list.size() == 0);
    
    list.insert(42);
    list.insert(24);
    list.insert(616);
    list.insert(-235);
    list.insert(0);
    list.insert(1);
    list.insert(-400);
    
    CHECK(list.size() == 7);
  }
  
  SECTION("isEmpty") {
    List list{};
    CHECK(list.isEmpty());
    
    list.insert(42);
    list.insert(24);
    list.insert(616);
    list.insert(-235);
    list.insert(0);
    list.insert(1);
    list.insert(-400);
    
    CHECK(!list.isEmpty());
  }
  SECTION("Get with invalid index throws exception") {
    List list{1, 2, 3};
    CHECK_THROWS_AS(list.get(-1), std::out_of_range);
    CHECK_THROWS_AS(list.get(3), std::out_of_range);  // Index 3 är utanför gränserna för en lista med storlek 3.
  }
  
  SECTION("Remove from an empty list does nothing") {
    List list;
    // Uppdatera detta testfall för att förvänta sig ett specifikt undantag.
    CHECK_THROWS_WITH(list.remove(1), "Cannot remove from an empty list.");
  }
  
  SECTION("Remove a non-existing value does nothing") {
    List list{1, 2, 3};
    // Uppdatera detta testfall för att förvänta sig ett specifikt undantag.
    CHECK_THROWS_WITH(list.remove(4), "Value not found in the list.");
  }
  
  SECTION("Insert into an empty list updates both head and tail") {
    List list;
    list.insert(1);
    CHECK(list.size() == 1);
    CHECK(list.get(0) == 1);
  }
  
  
  SECTION("Removing all elements makes the list empty") {
    List list{1, 2, 3};
    list.remove(1);
    list.remove(2);
    list.remove(3);
    CHECK(list.isEmpty());
  }
  
  SECTION("Insert maintains sorted order") {
    List list;
    list.insert(2);
    list.insert(1);  // Insättning före befintligt värde.
    list.insert(3);  // Insättning efter befintligt värde.
    CHECK(list.get(0) == 1);
    CHECK(list.get(1) == 2);
    CHECK(list.get(2) == 3);
  }
  
}

TEST_CASE("Sub lists") {
  SECTION("1") {
    List list{0, 2, 4, 8};
    List sub_list{list.sub({0, 1, 2})};  // [0, 2, 4]
    CHECK(sub_list.size() == 3);
    CHECK(sub_list.get(0) == 0);
    CHECK(sub_list.get(1) == 2);
    CHECK(sub_list.get(2) == 4);
  }

  SECTION("2") {
    List list{0, 2, 4, 8};
    List sub_list{list.sub({0, 1, 1, 1, 1})};  // [0, 2, 2, 2, 2]
    CHECK(sub_list.size() == 5);
    CHECK(sub_list.get(0) == 0);
    CHECK(sub_list.get(1) == 2);
    CHECK(sub_list.get(2) == 2);
    CHECK(sub_list.get(3) == 2);
    CHECK(sub_list.get(4) == 2);
  }
  
  SECTION("3") {
    List list{1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};
    List sub_list{list.sub({0, 2, 3, 4, 6, 10})};  // [1, 2, 3, 5, 13, 89]
    CHECK(sub_list.size() == 6);
    CHECK(sub_list.get(0) == 1);
    CHECK(sub_list.get(1) == 2);
    CHECK(sub_list.get(2) == 3);
    CHECK(sub_list.get(3) == 5);
    CHECK(sub_list.get(4) == 13);
    CHECK(sub_list.get(5) == 89);
  }
  
  SECTION("4") {
    List list{0, 1, 2, 3};
    CHECK_THROWS_AS(list.sub({2, 1, 2}), std::invalid_argument);
    CHECK_THROWS_AS(list.sub({-1, 5}), std::out_of_range);
  }
}

TEST_CASE("List - More Comprehensive Tests") {
  // Återinsättning av borttaget element
  SECTION("Re-insertion of a removed element") {
    List list{1, 2, 3};
    list.remove(2);
    list.insert(2);
    CHECK(list.size() == 3);
    CHECK(list.get(1) == 2);  // Antagande: Listan sorteras om efter insättning
  }
  
  // Insertion i en lista med dubletter
  SECTION("Insertion in a list with duplicates") {
    List list{2, 2, 3, 3};
    list.insert(3);
        CHECK(list.size() == 5);
        CHECK(list.get(3) == 3);  // Den tredje 3:an ska vara på index 3 efter insättning
  }
  
  // Borttagning av alla förekomster av ett värde
  SECTION("Removal of all occurrences of a value") {
    List list{4, 4, 5, 5};
    list.remove(4);
    list.remove(4);
    CHECK(list.size() == 2);
    CHECK_THROWS_WITH(list.remove(4), "Value not found in the list.");
  }
  
  // Borttagning från en lista med bara ett element
  SECTION("Removal from a single-element list") {
    List list{9};
    list.remove(9);
    CHECK(list.isEmpty());
  }
  
  // Kontrollera listans tillstånd efter clear
  SECTION("List state after clear") {
    List list{1, 2, 3};
    list.clear();
    CHECK(list.size() == 0);
    CHECK(list.isEmpty());
  }
  
  // Försök att få ett värde från en tom lista
  SECTION("Attempt to get a value from an empty list") {
    List emptyList;
        CHECK_THROWS_AS(emptyList.get(0), std::out_of_range);
  }

  // Tillgång till element med ogiltigt index
    SECTION("Accessing elements with invalid index") {
      List list{1, 2, 3};
      CHECK_THROWS_AS(list.get(-1), std::out_of_range);
      CHECK_THROWS_AS(list.get(3), std::out_of_range);  // Index 3 är utanför listan
    }
         
    // Testa sub-metoden med icke-angränsande index
    SECTION("Sub method with an empty or single-element list") {
      List emptyList;
      // Försöker skapa en sublista från en tom lista bör kasta ett undantag
      // eftersom det inte finns några index att välja.
      CHECK_THROWS_AS(emptyList.sub({0}), std::out_of_range);
      
      List singleElementList{1};
      List subFromSingle = singleElementList.sub({0});
      CHECK(subFromSingle.size() == 1);
      CHECK(subFromSingle.get(0) == 1);
    }
    
}
