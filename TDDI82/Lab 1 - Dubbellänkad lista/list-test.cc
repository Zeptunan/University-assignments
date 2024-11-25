#include "List.h"
#include <iostream>
#include "catch.hpp"
#include <string>
#include <sstream>

TEST_CASE( "Create list" )
{
  List_NS::List<int> lst{1,4,2,6,8,9};
  CHECK(lst.at(2) == 2);
  CHECK(lst.size() == 6);
  List_NS::List<int> l2;
  l2 = lst;
  CHECK(l2.size() == lst.size());
  CHECK(l2.front() == lst.front());
  CHECK(l2.back() == lst.back());
  
}

TEST_CASE( "Swap" )
{
  List_NS::List<int> l1{1,4,2,6,8,9};
  List_NS::List l2{5,9,1,4,6};
  l2.swap(l1);
  CHECK(l1.at(2) == 1);
  CHECK(l2.at(4) == 8);
  CHECK(l1.size() == 5);
  CHECK(l2.size() == 6);
  
}

TEST_CASE( "Push front and push back" )
{
  List_NS::List<int> l1{1,4,2,6,8,9};
  l1.push_front(4);
  CHECK(l1.at(0) == 4);
  CHECK(l1.size() == 7);
  l1.push_back(5);
  CHECK(l1.at(7) == 5);
  CHECK(l1.size() == 8);
}



TEST_CASE ("ITERATOR")
{
  List_NS::List<int> lst{2,3,1,5};
 auto rb { std::make_reverse_iterator(lst.end()) };
 auto re { std::make_reverse_iterator(lst.begin()) };
for ( auto it = rb; it != re; ++it )
{
  std::cout << *it << ' ';
}
}

TEST_CASE("Iterator")
{
  List_NS::List<int> l1{1,7,3,4,5};
  auto rb {l1.begin()};
  auto re {l1.end()};
  
  int size{0};
  for( auto it{rb}; it != re; ++it )
    {
      CHECK(*it == l1.at(size));
      ++size;
    }
}

TEST_CASE("Iterator preincrement")
{
  List_NS::List<int> l1{1,5,3,8};
  auto it1{l1.begin()};
  auto it2{it1};
  
  it2 = ++it1;
  CHECK(*it1 == 5);
  CHECK(*it2 == 5);
  
  it2 = ++it1;
  CHECK(*it1 == 3);
  CHECK(*it2 == 3);
}


TEST_CASE("Iterator postincrement")
{
  List_NS::List<int> l1{1, 5, 3, 8};
  auto it1 = l1.begin();
  auto it2 = it1;

  CHECK(*it1 == 1);   
  auto old_it1 = it1++;
  CHECK(*old_it1 == 1);  
  CHECK(*it1 == 5);   

  CHECK(*it2 == 1);  
  auto old_it2 = it2++;
  CHECK(*old_it2 == 1);  
  CHECK(*it2 == 5);   

  
}


TEST_CASE("Iterator predecrement")
{
  List_NS::List<int> l1{1,5,3,8};
  auto it1{l1.end()};
  
  CHECK(*it1 == 0);
  --it1;
  CHECK(*it1 == 8);
  
  CHECK(*it1 == 8);
  --it1;
  CHECK(*it1 == 3);
}

TEST_CASE("Iterator postdecrement")
{
  List_NS::List<int> l1{1, 5, 3, 8};
  auto it1 = l1.end(); 
  
  
  --it1;
  CHECK(*it1 == 8);   

  
  auto old_it1 = it1--;   
  CHECK(*old_it1 == 8);   
  CHECK(*it1 == 3);       
  
  
  old_it1 = it1--;   
  CHECK(*old_it1 == 3);   
  CHECK(*it1 == 5);       

  
  old_it1 = it1--;
  CHECK(*old_it1 == 5);
  CHECK(*it1 == 1);
}


TEST_CASE("Iterator operator ==")
{
  List_NS::List<int> l1{1,5,3,8};
  auto rb{l1.begin()};
  auto re{l1.end()};
  
  auto it1{rb};
  auto it2{rb};
  
  CHECK(*it1 == *it2);
}

TEST_CASE("Iterator operator !=")
{
  List_NS::List<int> l1{1,5,3,8};
  auto rb{l1.begin()};
  auto re{l1.end()};
  
  auto it1{rb};
  auto it2{re};
  
  CHECK(*it1 != *it2);
}

TEST_CASE("Iterator operator *")
{
  List_NS::List<int> l1{1,5,3,8};
  List_NS::List<std::string> l2{"Tjena","Tjo"};
  auto rb = l1.begin(); 
  auto sb = l2.begin(); 
  
  CHECK(*rb == 1);
  ++rb;
  CHECK(*rb == 5);
  
  CHECK(*sb == "Tjena");
  ++sb;
  CHECK(*sb == "Tjo");
  
}


TEST_CASE("Other datatypes")
{
  List_NS::List<std::string> l1{"hola","hello"};
  CHECK(l1.at(0) == "hola");
  CHECK(l1.at(1) == "hello");
  CHECK(l1.size() == 2);
  
  List_NS::List<char> l2{'a','b','c'};
  CHECK(l2.at(1) == 'b');
  CHECK(l2.size() == 3);
}

struct List
{
  int add_two(int a)
  {
    return a + 2;
  }
};

TEST_CASE("Namespaces")
{
  List l1;
  List_NS::List<int> l2;
  CHECK(l1.add_two(2) == 4);
  CHECK(l2.size() == 0);
}

TEST_CASE( "Operator ->" ) {
  {
    std::stringstream ss;
    List_NS::List<std::string> lst{"hej","svej","dej"};
    for ( auto it = lst.begin(); it != lst.end(); ++it )
      {
	ss << it->size() << ' ';
      }
    CHECK(ss.str() == "3 4 3 ");
  }
  {
    std::stringstream ss;
    struct Person{int age;};
    List_NS::List<Person> lst{Person{10}, Person{15}};
    for ( auto it = lst.begin(); it != lst.end(); ++it )
      {
	ss << it->age + 5 << ' ';
      }
    CHECK(ss.str() == "15 20 ");
  }
}


