// allsh436: Samarbetat med saiah135, Said Ali Ahmed, samma program
#include <iostream>
#include <string>
#include <cctype> 
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
  //Del1
  int startvalue {};
  int finalvalue {};
  double Fahrenheit {};
  double Reaumur {};
  double Kelvin {};

  //Del2
  char character;
  int siffra{};
  int alfa{};
  int vita{};

  //Del3
  int antal_ord {};
  double medellangd {};
  string kort_ord;
  string langt_ord;
  int min_length {100}; 
  int max_length {};
  string S;
  
  //Del1
  cout << "Del 1: Temperaturtabell" << endl;

  do
    {
      cout << "Ange startvärde: ";
      cin >> startvalue;
      
      if (startvalue < -273)
  	{
  	  cout << "Felaktigt startvärde!" << endl;
  	}
      
    } while (startvalue < -273);
  
  do
    {

      cout << "Ange slutvärde: ";
      cin >> finalvalue;

      if (startvalue > finalvalue)
  	{
  	  cout << "Felaktigt slutvärde!" << endl;
  	}
    } while (startvalue > finalvalue);

  cout << "Celsius   Kelvin   Fahrenheit   Reaumur" << endl;
  cout << "---------------------------------------" << endl;
  
  for (startvalue; startvalue <= finalvalue; startvalue++)
    {
      Kelvin = startvalue + 273.15;
      Fahrenheit = startvalue * 1.8 + 32;
      Reaumur = startvalue * 0.8;
      cout << setw(7) << startvalue;
      cout << setw(9) << Kelvin;
      cout << setw(13) << fixed << setprecision(2) << Fahrenheit;
      cout << setw(10) << Reaumur << endl;       
    }
  cout << "---------------------------------------" << endl<< endl;
  cin.ignore(100, '\n');
  
  //Del2
  cout << "Del 2: Teckenhantering" << endl;

  for(int i{}; i < 10; i++)
    {

      cin.get(character);

      if(isdigit(character))
  	{
  	  siffra++;
  	}
      if(isalpha(character))
  	{
  	  alfa++;
  	}
      if(isspace(character))
  	{
  	  vita++;
  	}
      
    }
  cin.ignore(1000, '\n');
  cout << "Texten innehöll:" << endl;
  cout << "Alfabetiska tecken:" << alfa << endl;
  cout << "Siffertecken......:" << siffra << endl;
  cout << "Vita tecken.......:" << vita << endl << endl;


  //Del3
  cout << "Del 3: Ordhantering" << endl;
  cout << "Mata in en text:\n" << endl;

  while (cin >> S)
    {
      if (S.length() > max_length)
	{
	  max_length = S.length();
	  langt_ord = S;
	}
      
      if (S.length() < min_length)
	{
	  min_length = S.length();
	  kort_ord = S;
	}
      
      medellangd+=S.length();
      antal_ord++;
      
    }
  

  if (antal_ord == 0)
    {
      cout << "Inga ord matades in." << endl;
    }
  else {
    medellangd = (medellangd / antal_ord);
    round(medellangd);
    
    cout << "Texten innehöll " << antal_ord << " ord." << endl;
    cout << "Det kortaste ordet var " << '"' << kort_ord << '"' << " med "
	 << kort_ord.length() << " tecken." << endl;
    cout << "Det längsta ordet var " << '"' << langt_ord << '"' << " med "
	 << langt_ord.length() << " tecken." << endl;
    cout << "Medelordlängden var "<< fixed << setprecision(1) << medellangd << " tecken.";
  }
  
  return 0; 
}
