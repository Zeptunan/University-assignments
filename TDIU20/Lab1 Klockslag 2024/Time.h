#ifndef TIME_H
#define TIME_H

// Information om komplettering:
//   Siffrorna hänvisar till rättningsprotokollet som finns på
//   kurshemsidan -> läsning -> Literatur -> "Uppgruppens bedömningsprotokoll"
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   eric.ekstrom@liu.se

// Komplettering (bonus): operator+ för kommutativa fallet saknas.

#include <iostream>
#include <string>
#include <sstream>

class Time {
public:
  Time();
  Time(int hour, int minute, int second);
  Time(const std::string& timeStr);

  std::string to_string(bool use_24_hour_format = true) const;
  bool is_am() const;
  
  int get_hour() const;
  int get_minute() const;
  int get_second() const;
  
  Time& operator++();    // Prefix-inkrement
  Time operator++(int);  // Postfix-inkrement
  Time& operator+=(int seconds);
  Time operator+(int seconds) const; // Redan definierad för Time + int
  Time& operator-=(int seconds); // Subtraherar sekunder från det nuvarande objektet
  Time operator-(int seconds) const; // Skapar ett nytt Time-objekt med subtraherade sekunder
  bool operator<(const Time& other) const;
  bool operator>(const Time& other) const;
  bool operator==(const Time& other) const;
  bool operator<=(const Time& other) const;
  bool operator>=(const Time& other) const;
  bool operator!=(const Time& other) const;
  
private:
  int h, m, s;
  
  void validate_time(int hour, int minute, int second) const; // Ny privat medlemsfunktion
  std::string format_component(int component) const; // Ny privat medlemsfunktion
};

// Fri funktion för kommutativ addition
Time operator+(int seconds, const Time& time); // Ny deklaration för int + Time

std::ostream& operator<<(std::ostream& os, const Time& t);
std::istream& operator>>(std::istream& is, Time& t);

#endif // TIME_H
