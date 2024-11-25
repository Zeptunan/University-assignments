// allsh436: Arbetat enskilt

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

//Meny
int Menu_Selection()
{
  
  int val{};
   
  cout << "1. Beräkna N-fakultet." << endl
       << "2. Multiplicera en sträng." << endl
       << "3. Byta värden på ett heltal och ett flyttal." << endl
       << "4. Beräkna totala längden samt medellängden på två strängar."<< endl
       << "5. Avsluta programmet." << endl
       << "Val: ";
  cin >> val;
  if (val < 1 or val > 5)
    {
      cout << "Fel val!" << endl;
    }  
  return val;
  
}


//Factorial
int Calculate_Factorial(int const & n)
{
  int fakultet {1};
  
  for (int i = 1; i < (n+1); i++)
    {
      fakultet = fakultet*i;
    }
  return fakultet; 
}

void Factorial_Program()
{
  int n;
  
  cout << "Mata in ett heltal: ";
  cin >> n; 
  cout << "Fakulteten av " << n << " är ";
  cout << Calculate_Factorial(n) << endl;
}


//Multiplicera sträng med heltal
string Multiply(string const & text,
                int const & multiplier)
{
  
  string multipli{};
  
  for (int i{0}; i < multiplier; i++)
    {
      multipli = (multipli + text);
    }
  
  return multipli;
  
}

void Multiply_Program()
{
  
  string text; 
  int multiplier{};
  
  cout << "Mata in en text och ett heltal: ";
  cin >> text >> multiplier;
  cout << "Den multiplicerade texten är ";
  cout << Multiply(text, multiplier) << endl; 
  
}


//Byt värde på heltal och flyttal
void Swap(int & a,
          double & b)
{
  double placeholder{b};
  b = a;
  a = static_cast<int>(ceil(placeholder));
  
}          

void Swap_Program()
{
  int a {};
  double b {};
  
  cout << "Mata in ett heltal och ett flyttal: ";
  cin >> a >> b;   
  cout << "Heltalets värde är nu ";
  Swap(a, b);
  cout << a << endl;
  cout << "Flyttalets värde är nu " << fixed << setprecision(1) << b << endl; 
  
}


//Beräkna längd och meddelängd av två strängar
void Length(string const & text_1,
            string const & text_2,
            int & total_length,
            double & mean_length)
{
  total_length = text_1.length() + text_2.length();
  mean_length = static_cast<double>(total_length) / 2;
}

void Length_Program()
{
  string text_1;
  string text_2;
  int total_length{};
  double mean_length{};
  
  cout << "Mata in två ord: ";
  cin >> text_1 >> text_2;
  cout << "Totallängd: ";
  Length(text_1, text_2, total_length, mean_length);
  cout << total_length << endl;
  cout << "Medellängd: " << fixed << setprecision(1) << mean_length << endl;
  
}


int main()
{
  
  int val{};
  bool active = true;
  
  cout << "Välkommen till huvudmenyn!" << endl;
  
  while(active) 
    {
      val = Menu_Selection();
      switch (val)
	{
	case 1:
	    Factorial_Program();
	    break;
	case 2:
	  Multiply_Program();
	  break;
	case 3:
	  Swap_Program();
	  break;
	case 4:
	  Length_Program();
	  break;
	case 5:
	  active = false;
	  cout << "Ha en bra dag!" << endl;
	  break;
	}    
    }
  
  return 0;
}
