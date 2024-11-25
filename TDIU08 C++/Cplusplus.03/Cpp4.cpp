// allsh436: Samarbetat med saiah135, Said Ali Ahmed, samma program
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;


/////////////////////TYPER/////////////////////

struct Runner_Type
{
  string first_name{0};
  string last_name{0};
  string team{0}; 
  vector<double> time;
};

using Runner_Cloud = vector<Runner_Type>; 

//////////////////////UP///////////////////////

void store_runners(string const first,
		   Runner_Cloud & runner_database)
{
  Runner_Type Runner;
  string klubb, klubb2;
  
  Runner.first_name = first;
  cin >> Runner.last_name;
  cin >> klubb;
  cin >> klubb2;
  Runner.team = klubb + " " + klubb2;

  runner_database.push_back(Runner);
}


void store_time(Runner_Type & runner)
{
  double data;
  while (true)
  {
    cin >> data;
    if(data == -1)
    {
      break;
    }
    else
    {
      runner.time.push_back(data);
    
    }
  }
}

bool operator<(Runner_Type const & lhs,
	       Runner_Type const & rhs)
{
  if (lhs.time.at(0) < rhs.time.at(0))
  {
    return true;
  }
  else
  {
    return false;
  }
}

   void print_results(Runner_Cloud & runners)
   {
  cout << "Efternamn   Förnamn           Klubb: Tider" << endl
       << "==========================================" << endl;
    
  for (Runner_Type & runner : runners)
  {
    cout << setw(9) << right <<runner.last_name << setw(10)<< runner.first_name << setw(16)
	 << runner.team << ':';
    for (double & time: runner.time)
    {
      cout << " " << time;
    }
    cout << endl;
  }
   }

/////////////////////MAIN//////////////////////

int main() {

  cout << fixed << setprecision(2);
  
  Runner_Cloud runners; 
  string text;
  
  cout << "Mata in deltagare:" << endl;
  while(true)
  {
    cin >> text;
    if (text == "KLAR")
    {
      break;
    }
    else
    {
      store_runners(text, runners);
    }
   
  }

  for (Runner_Type & runner : runners)
  {
    cout << "Tider " << runner.first_name << ": ";
    store_time(runner);
  }

  
  for (Runner_Type & runner : runners)
  {
    sort(begin(runner.time), end(runner.time));
  }
  
  sort(begin(runners), end(runners)); 
	
  print_results(runners);
  
  return 0;
}
