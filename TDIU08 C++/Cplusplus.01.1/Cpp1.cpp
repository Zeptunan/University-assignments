// allsh436: Arbetat enskilt
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{

  int heltal = 0;
  double flyttal;
  char tecken;
  string ord;
  

  //Del1
  cout << "Skriv in ett heltal: ";
  cin >> heltal;
  cin.ignore(1000, '\n');
  cout << "Du skrev in heltalet: " << heltal << endl << endl;
  
  
  //Del2
  cout << "Skriv in fem heltal: ";
  cin >> heltal;
  cout << "Du skrev in heltalen: ";
  cout << heltal << " ";
  cin >> heltal;
  cout << heltal << " ";
  cin >> heltal;
  cout << heltal << " ";
  cin >> heltal;
  cout << heltal << " ";
  cin >> heltal;
  cin.ignore(100, '\n');
  cout << heltal << endl << endl;
  

  //Del 3
  cout << "Skriv in ett flyttal: ";
  cin >> flyttal;
  cin.ignore(100, '\n');
  cout << "Du skrev in flyttalet: " << fixed << setprecision(3) << flyttal << endl << endl;
  
  
  //Del4
  cout << "Skriv in ett heltal och ett flyttal: ";
  cin >> heltal >> flyttal;
  cin.ignore(100, '\n');
  cout << "Du skrev in heltalet: " << setw(9) << right << heltal << endl;
  cout << "Du skrev in flyttalet:" << setw(9) << right << fixed << setprecision(4) << flyttal << endl << endl;

  
  //Del5
  cout << "Skriv in ett flyttal och ett heltal: ";
  cin >> flyttal >> heltal;
  cin.ignore(100, '\n');
  cout << "Du skrev in heltalet:" << setfill('-') << setw(10) << heltal << endl;
  cout << "Du skrev in flyttalet:" << setfill('-') << setw(9) << fixed << setprecision(4) << flyttal << endl << endl;

  
  //Del6
  cout << "Skriv in ett tecken: ";
  cin >> tecken;
  cin.ignore(100, '\n');
  cout << "Du skrev in tecknet: " << tecken << endl << endl;

  
  //Del7
  cout << "Skriv in ett ord: ";
  cin >> ord;
  cin.ignore(100, '\n');
  cout << "Du skrev in ordet: " << ord << endl << endl;

  
  //Del8
  cout << "Skriv in ett heltal och ett ord: ";
  cin >> heltal >> ord;
  cin.ignore(100, '\n');
  cout << "Du skrev in heltalet |" << heltal << "| och ordet |" << ord << "|." << endl << endl; 

  
  //Del9
  cout << "Skriv in ett tecken och ett ord: ";
  cin >> tecken >> ord;
  cin.ignore(100, '\n');
  cout << "Du skrev in " << '"' << ord << '"' << " och " << '"' << tecken << '"' << '.' << endl << endl;
  

  //Del10
  cout << "Skriv in ett ord och ett tecken: ";
  cin >> ord >> tecken;
  cin.ignore(100, '\n');
  cout << "Du skrev in " << '"' << ord << '"' << " och " << '"' << tecken << '"' << '.' << endl << endl;

  
  //Del11
  cout << "Skriv in en textrad: ";
  getline(cin, ord);
  cout << "Du skrev in " << '"' << ord << '"' << '.' << endl << endl;

  
  //Del12
  cout << "Skriv in en till rad text: ";
  getline(cin, ord);
  cout << "Du skrev in " << '"' << ord << '"' << '.' << endl << endl;

  
  //Del13
  cout << "Skriv in en rad med tre ord: ";
  cin >> ord;
  cout << "Du skrev in: ";
  cout << '"' << ord << '"' << ", "; 
  cin >> ord;
  cout << '"' << ord << '"' << " och ";
  cin >> ord;
  cin.ignore(100,'\n');
  cout << '"' << ord << '"' << '.';

  return 0; 
}