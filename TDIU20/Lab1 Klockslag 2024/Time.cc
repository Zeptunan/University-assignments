#include "Time.h"

#include <iomanip>
#include <sstream>

Time::Time() : h{0}, m{0}, s{0} {
    // Standardkonstruktorn initierar tiden till 00:00:00
}

Time::Time(int hour, int minute, int second) : h{hour}, m{minute}, s{second} {
    validate_time(hour, minute, second);
}

// Konverterar tiden till en sträng i formatet HH:MM:SS
std::string Time::to_string(bool use_24_hour_format) const {
  std::string timeStr {
        format_component(use_24_hour_format ? h : (h % 12 == 0 ? 12 : h % 12)) +
      ":" + format_component(m) + ":" + format_component(s)};
    if (!use_24_hour_format) {
        std::string am_pm = h < 12 ? " AM" : " PM";
        timeStr += am_pm;
    }
    return timeStr;
}

// Returnerar true om tiden är förmiddag (AM), annars false.
bool Time::is_am() const { return h < 12; }

int Time::get_hour() const { return h; }
int Time::get_minute() const { return m; }
int Time::get_second() const { return s; }

Time& Time::operator++() { return *this += 1; }

Time Time::operator++(int) {
  Time temp {*this};
    ++(*this);  // Använd prefix-versionen
    return temp;
}

Time Time::operator+(int seconds) const {
  Time temp {*this};
    temp += seconds;
    return temp;
}

Time operator+(int seconds, const Time& time) { return time + seconds; }

Time& Time::operator+=(int seconds) {
  int total_seconds {h * 3600 + m * 60 + s + seconds};
    while (total_seconds < 0) {
        total_seconds +=
            24 * 3600;  // Lägg till en dag i sekunder om totalt är negativt
    }
    h = (total_seconds / 3600) % 24;
    m = (total_seconds % 3600) / 60;
    s = total_seconds % 60;
    return *this;
}

Time Time::operator-(int seconds) const {
  Time temp {*this};
    temp -= seconds;
    return temp;
}

Time& Time::operator-=(int seconds) {
    return *this +=
           -seconds;  // Använder operator+= för att subtrahera sekunder
}

bool Time::operator<(const Time& other) const {
    return std::tie(h, m, s) < std::tie(other.h, other.m, other.s);
}
bool Time::operator>(const Time& other) const { return other < *this; }
bool Time::operator==(const Time& other) const {
    return h == other.h && m == other.m && s == other.s;
}
bool Time::operator<=(const Time& other) const { return !(*this > other); }
bool Time::operator>=(const Time& other) const { return !(*this < other); }
bool Time::operator!=(const Time& other) const { return !(*this == other); }

std::istream& operator>>(std::istream& is, Time& t) {
    std::string timeStr{};
    is >> timeStr;
    try {
      t = Time{timeStr};  // Försöker skapa en Time-instans från strängen
    } catch (const std::invalid_argument&) {
        is.setstate(
            std::ios::failbit);  // Sätter failbit om konverteringen misslyckas
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Time& t) {
    return os << t.to_string();
}

// konvertera string till integer
Time::Time(const std::string& timeStr) 
  : h{std::stoi(timeStr.substr(0, 2))}, 
    m{std::stoi(timeStr.substr(3, 2))}, 
    s{std::stoi(timeStr.substr(6, 2))}
{
  
  if (timeStr.length() != 8 || timeStr[2] != ':' || timeStr[5] != ':') {
    throw std::invalid_argument("Invalid time format");
  }
  
  validate_time(h, m, s);
}


// Privata hjälpfunktioner
void Time::validate_time(int hour, int minute, int second) const {
    if (hour < 0 || hour > 23) {
        throw std::invalid_argument("Hour must be between 0 and 23.");
    }
    if (minute < 0 || minute > 59) {
        throw std::invalid_argument("Minute must be between 0 and 59.");
    }
    if (second < 0 || second > 59) {
        throw std::invalid_argument("Second must be between 0 and 59.");
    }
}

std::string Time::format_component(int component) const {
    std::ostringstream oss{};
    oss << std::setw(2) << std::setfill('0') << component;
    return oss.str();
}



