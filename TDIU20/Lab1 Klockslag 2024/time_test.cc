#include "Time.h"

#include "catch.hpp"

// Komplettering: tester för operator>> och operator<< borde testa minst två klockslag.

using namespace std;

TEST_CASE("Constructors and getters") {
  SECTION("Default") {
    Time empty{};
    CHECK(empty.get_hour() == 0);
    CHECK(empty.get_minute() == 0);
    CHECK(empty.get_second() == 0);
  }

  SECTION("Integer") {
    Time t0{0, 0, 0};
    Time t1{12, 30, 30};
    Time t2{23, 59, 59};

    CHECK_THROWS(Time{13, 35, 60});
    CHECK_THROWS(Time{13, 60, 35});
    CHECK_THROWS(Time{24, 35, 35});

    CHECK(t0.get_hour() == 0);
    CHECK(t0.get_minute() == 0);
    CHECK(t0.get_second() == 0);
    CHECK(t1.get_hour() == 12);
    CHECK(t1.get_minute() == 30);
    CHECK(t1.get_second() == 30);
    CHECK(t2.get_hour() == 23);
    CHECK(t2.get_minute() == 59);
    CHECK(t2.get_second() == 59);
  }

  SECTION("String") {
    Time t0{"00:00:00"};
    Time t1{"12:30:30"};
    Time t2{"23:59:59"};

    CHECK_THROWS(Time{"13:35:60"});
    CHECK_THROWS(Time{"13:60:35"});
    CHECK_THROWS(Time{"24:35:35"});

    CHECK(t0.get_hour() == 0);
    CHECK(t0.get_minute() == 0);
    CHECK(t0.get_second() == 0);
    CHECK(t1.get_hour() == 12);
    CHECK(t1.get_minute() == 30);
    CHECK(t1.get_second() == 30);
    CHECK(t2.get_hour() == 23);
    CHECK(t2.get_minute() == 59);
    CHECK(t2.get_second() == 59);
  }
}

TEST_CASE("is_am") {
  Time t0{"05:00:00"};
  Time t1{"14:00:00"};
  CHECK(t0.is_am());
  CHECK_FALSE(t1.is_am());
  Time t5{"00:00:00"};  // Exakt midnatt
  Time t6{"11:59:59"};  // Precis innan middag
  Time t7{"12:00:00"};  // Exakt middag
  Time t8{"12:00:01"};  // Precis efter middag

  CHECK(t5.is_am());
  CHECK(t6.is_am());
  CHECK_FALSE(t7.is_am());
  CHECK_FALSE(t8.is_am());
}

TEST_CASE("to_string") {
  Time t0{};
  Time t1{11, 59, 59};
  Time t2{12, 0, 0};
  Time t3{13, 0, 0};
  Time t4{23, 59, 59};
  
  SECTION("24 hour format no argument") {
    CHECK(t0.to_string() == "00:00:00");
    Time t5{0, 0, 0};     // Midnatt
    Time t6{12, 0, 0};    // Middag
    Time t7{23, 59, 59};  // Precis innan midnatt
    Time t8{15, 30, 45};  // Eftermiddag
    
    CHECK(t5.to_string() == "00:00:00");
    CHECK(t6.to_string() == "12:00:00");
    CHECK(t7.to_string() == "23:59:59");
    CHECK(t8.to_string() == "15:30:45");
  }
  
  SECTION("24 hour format with argument") {
    Time t9{0, 0, 0};      // Midnatt
    Time t10{12, 0, 0};    // Middag
    Time t11{23, 59, 59};  // Precis innan midnatt
    Time t12{15, 30, 45};  // Eftermiddag
    
    CHECK(t9.to_string(true) == "00:00:00");
    CHECK(t10.to_string(true) == "12:00:00");
    CHECK(t11.to_string(true) == "23:59:59");
    CHECK(t12.to_string(true) == "15:30:45");
  }

  SECTION("12 hour format") {
    Time t13{0, 0, 0};     // Midnatt
    Time t14{12, 0, 0};    // Middag
    Time t15{15, 30, 45};  // Eftermiddag
    Time t16{23, 59, 59};  // Kväll

    CHECK(t13.to_string(false) == "12:00:00 AM");
    CHECK(t14.to_string(false) == "12:00:00 PM");
    CHECK(t15.to_string(false) == "03:30:45 PM");
    CHECK(t16.to_string(false) == "11:59:59 PM");
  }
}


// Fill with more tests of other functions and operators!

TEST_CASE("OPERATORS") {
  /* ++operator & operator++ */
  SECTION("Increment operators") {
    Time t0{0, 0, 0};
    Time t1{23, 59, 59};

    /* t0 */
    CHECK((++t0).to_string() == "00:00:01");
    CHECK((t0++).to_string() == "00:00:01");

    CHECK((++t0).to_string() == "00:00:03");
    CHECK((t0++).to_string() == "00:00:03");

    CHECK((++t0).to_string() == "00:00:05");
    CHECK((t0++).to_string() == "00:00:05");

    CHECK((t0).to_string() == "00:00:06");

    /* t1 */
    CHECK((++t1).to_string() == "00:00:00");
    CHECK((t1++).to_string() == "00:00:00");

    CHECK((++t1).to_string() == "00:00:02");
    CHECK((t1++).to_string() == "00:00:02");

    CHECK((++t1).to_string() == "00:00:04");
    CHECK((t1++).to_string() == "00:00:04");

    CHECK((t1).to_string() == "00:00:05");
  }

  /* operator+ & operator+= */
  SECTION("Addition operators") {
    Time t0{0, 0, 0};
    Time t1{23, 59, 59};

    /* t0 */
    CHECK((t0 + 1).to_string() == "00:00:01");
    CHECK((t0 + 2).to_string() == "00:00:02");
    CHECK((t0 + 3).to_string() == "00:00:03");
    CHECK((t0 += 10).to_string() == "00:00:10");
    CHECK((t0 += 10).to_string() == "00:00:20");
    CHECK((t0 + 3600).to_string() == "01:00:20");

    /* t1 */
    CHECK((t1 + 1).to_string() == "00:00:00");
    CHECK((t1 + 2).to_string() == "00:00:01");
    CHECK((t1 + 3).to_string() == "00:00:02");
    CHECK((t1 += 10).to_string() == "00:00:09");
    CHECK((t1 += 10).to_string() == "00:00:19");
    CHECK((t1 + 3600).to_string() == "01:00:19");

    /* Negative addition */
    CHECK((t0 + -1).to_string() == "00:00:19");
    CHECK((t1 + -1).to_string() == "00:00:18");
    CHECK((t0 + -60).to_string() == "23:59:20");
    CHECK((t1 + -60).to_string() == "23:59:19");
  }

  /* operator- & operator-= */
  SECTION("Subtraction operators") {
    Time t0{0, 0, 0};
    Time t1{23, 59, 59};

    /* t0 */
    CHECK((t0 - 1).to_string() == "23:59:59");
    CHECK((t0 - 2).to_string() == "23:59:58");
    CHECK((t0 - 3).to_string() == "23:59:57");
    CHECK((t0 -= 3).to_string() == "23:59:57");
    CHECK((t0 -= 3).to_string() == "23:59:54");
    CHECK((t0 - 3600).to_string() == "22:59:54");

    /* t1 */
    CHECK((t1 - 1).to_string() == "23:59:58");
    CHECK((t1 - 2).to_string() == "23:59:57");
    CHECK((t1 - 3).to_string() == "23:59:56");
    CHECK((t1 -= 3).to_string() == "23:59:56");
    CHECK((t1 -= 3).to_string() == "23:59:53");
    CHECK((t1 - 3600).to_string() == "22:59:53");

    /* Positive subtraction */
    CHECK((t0 - -1).to_string() == "23:59:55");
    CHECK((t1 - -1).to_string() == "23:59:54");
    CHECK((t0 - -60).to_string() == "00:00:54");
    CHECK((t1 - -60).to_string() == "00:00:53");
  }

  /* operator< */
  SECTION("Less than operator") {
    Time t0{0, 0, 0};
    Time t1{23, 59, 59};

    CHECK((t0 < t1) == true);
    CHECK((t1 < t0) == false);
    CHECK((t0 < t0) == false);
  }

  /* operator> */
  SECTION("Greater than operator") {
    Time t0{0, 0, 0};
    Time t1{23, 59, 59};

    CHECK((t0 > t1) == false);
    CHECK((t1 > t0) == true);
    CHECK((t0 > t0) == false);
  }

  /* operator== */
  SECTION("Equal to operator") {
    Time t0{0, 0, 0};
    Time t1{23, 59, 59};

    CHECK((t0 == t1) == false);
    CHECK((t1 == t0) == false);
    CHECK((t0 == t0) == true);
  }

  /* operator<= */
  SECTION("Less than or equal to operator") {
    Time t0{0, 0, 0};
    Time t1{23, 59, 59};

    CHECK((t0 <= t1) == true);
    CHECK((t1 <= t0) == false);
    CHECK((t0 <= t0) == true);
  }

  /* operator>= */
  SECTION("Greater than or equal to operator") {
    Time t0{0, 0, 0};
    Time t1{23, 59, 59};

    CHECK((t0 >= t1) == false);
    CHECK((t1 >= t0) == true);
    CHECK((t0 >= t0) == true);
  }

  /* operator!= */
  SECTION("Not equal to operator") {
    Time t0{0, 0, 0};
    Time t1{23, 59, 59};

    CHECK((t0 != t1) == true);
    CHECK((t1 != t0) == true);
    CHECK((t0 != t0) == false);
  }

  /* operator<< */
  SECTION("Output operator") {
    stringstream ss;
    Time t0{0, 0, 0};
    Time t1{13, 14, 15};
    
    ss << t0;
    CHECK(ss.str() == "00:00:00");

    ss.str(""); // Rensa stringstream
    ss << t1;
    CHECK(ss.str() == "13:14:15"); // Kontrollera det nya klockslaget
  }
  
  /* operator>> */
  SECTION("Input operator") {
    stringstream input;
    Time t;
    

    input.str("23:59:59");
    input >> t;
    CHECK(t.to_string() == "23:59:59");
    
 
    input.clear(); 
    input.str("01:02:03");
    input >> t;
    CHECK(t.to_string() == "01:02:03");
    }
}
