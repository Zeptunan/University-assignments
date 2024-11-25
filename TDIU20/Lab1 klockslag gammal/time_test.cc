#include "catch.hpp"
#include "Time.h"

using namespace std;

// LÄS FÖRST HELA VÄGEN TILL RAD 65. LÄS NOGA.

// I denna fil skriver ni alla testfall huvudprogrammet ska köra.
// Huvudprogrammet finns test_main.cc så det kan kompileras för sig en gång för alla.

// Ni ska arbeta med uppgiften enligt TDD (Test Driven Developement)
// Snabbintroduktion till TDD:
//  1. Lägg till ett testfall.
//  2. Gör minsta möjliga otillräckliga stub-implementation så att testfallet kompilerar.
//  3. Kör testprogrammet.
//     Du ska se att testfallet detekterar otillräcklig implementation (misslyckas).
//  4. Lägg till (minsta möjliga) korrekta implementation.
//  5. Kör testprogrammet med alla testfall.
//     Du ska se att alla testfall, tidigare och det nya, går igenom.
//  6. Refaktorera (skriv om) så att koden ser bra ut
//  7. Kör testprogrammet med alla testfall.
//     Du ska se att alla testfall, tidigare och det nya, fortfarande går igenom.

// Catch är ett ramverk som hjälper till med all logik för att gå
// igenom alla testfall, köra dem, visa tester som misslyckas, och
// sammanställa resultatet.

// Ni ska använda catch när ni skriver testfallen.
// Full dokumentation:
// https://github.com/catchorg/Catch2/tree/devel/docs#reference

// Snabbintroduktion till Catch:

TEST_CASE ( "quick introduction to catch" )
{
  // Initialization of objects you want to test
  // Changes here will be visible in eah section
  int i{};

  // a section will use objects initialize above
  SECTION ( "check default initalization of int" )
  {
    // A check evaluates a condition. The test passes if the result is "true".
    // Each "CHECK" is counted as an "assertion" in program output
    CHECK ( i == 0 );
    
    // Changes to an object in a section do not propagate to other sections
    i += 1000;
    // But we can assert the new value is correct in the section
    CHECK ( i == 1000 );
  }
  
  SECTION ( "postfix increment" )
  {
    // A failed test may be caused by a faulty test-case or a faulty implementation.
    CHECK ( i++ == 1 ); // Catch me if you can**
    CHECK ( ++i == 2 );
    // ** Understand "me" as "the bug". Unrelated: https://www.imdb.com/title/tt0264464/
  }

  // If all assertions in all sections of a TEST_CASE pass, the TEST_CASE passes.
}

TEST_CASE ( "introduce a start brace { to match the end brace } on line 126" )
{ // line 70-71 will replace this when you begin

// KÖR TESTPROGRAMMET. Ta bort ovan två TEST_CASEs när du förstått hur det fungerar.

/* ----- REMOVE THIS COMMENT WHEN YOU HAVE READ AND TRIED ABOVE -----
TEST_CASE ("Constructors and getters")
{
   SECTION("Default")
   {
      Time empty{};
      CHECK( empty.get_hour()   == 0 );
      CHECK( empty.get_minute() == 0 );
      CHECK( empty.get_second() == 0 );
   }
*/
/* ----- REMOVE THIS COMMENT WHEN PREVIOUS TEST PASSES -----

   SECTION("Integer")
   {
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS( Time{13,35,60} );
      CHECK_THROWS( Time{13,60,35} );
      CHECK_THROWS( Time{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
   }
*/
/* ----- REMOVE THIS COMMENT WHEN PREVIOUS TEST PASSES -----

   SECTION("String")
   {
      Time t0{"00:00:00"};
      Time t1{"12:30:30"};
      Time t2{"23:59:59"};

      CHECK_THROWS( Time{"13:35:60"} );
      CHECK_THROWS( Time{"13:60:35"} );
      CHECK_THROWS( Time{"24:35:35"} );

      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );  
   }
*/
}
/* ----- REMOVE THIS COMMENT WHEN PREVIOUS TEST PASSES -----
TEST_CASE ("is_am") 
{
   Time t0{"05:00:00"};
   Time t1{"14:00:00"};
   CHECK       ( t0.is_am() );
   CHECK_FALSE ( t1.is_am() );
   // Fill with extra corner cases!
}
*/
/* ----- REMOVE THIS COMMENT WHEN PREVIOUS TEST PASSES -----

TEST_CASE ("to_string")
{
   Time t0{};
   Time t1{11, 59, 59};
   Time t2{12, 0, 0};
   Time t3{13, 0, 0};
   Time t4{23, 59, 59};
   SECTION("24 hour format no argument")
   {
      CHECK( t0.to_string() == "00:00:00" );
      // Fill with more tests!
   }
   
   SECTION("24 hour format with argument")
   {
      // Fill with more tests!
   } 

   SECTION("12 hour format")
   {
      // Fill with more tests!
   }
}

// Fill with more tests of other functions and operators!

*/
