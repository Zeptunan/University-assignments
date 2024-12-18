#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <map>
#include <iomanip>
#include "textred.h"

using namespace std;

vector<string> text{}; //global vector "text" som kommer hålla alla ord som separata strängar

void countword(map<string, int>& words, string word){
  words[word]++;
}

//Annan version av countword som använder count algoritmen
void countwordalgo(map<string, int>& words, string word){
  if (words.find(word) == words.end()) { 
    words[word] = count(text.begin(), text.end(), word);
    } 
  }

//hjälpfunktion för att hitta det längsta ordet i texten (för att sätta width i cout)
void check(string word, int& longest){
  if (word.length() > longest){
    longest = word.length();
  }
}

//Funktion som hämtar det längsta ordet (int)
int get_longest(){
  int longest{0};
  for_each(text.begin(), text.end(), [&longest](string word) {
    check(word, longest);
    });

    return longest;
    }
  
//hjälpfunktion för remove
void removeword(string& word, string searchword, int& index){
  if (word == searchword){
    text.erase(text.begin() + index);
  }
  index++;
}

//hjälpfunktion för substitute
void changeword(string& word, string old, string nnew){
  if (word == old){
    word = nnew;
  }
}

//funktion som kallas för alla ord vid table
void printtable(pair<string, int> word){
  if (word.first != " "){
  cout << left << setw(get_longest()) << word.first << " " << word.second << endl;
  }
}

//funktion som kallas för alla ord vid frequency
void printfrequency(pair<string, int> word){
  if (word.first != " "){
  cout << right << setw(get_longest()) << word.first << " " << word.second << endl;
  }
}

//Funktion som lägger till alla argument i en vector (används inte??)
void add_argument(char* argument, vector<char*> myvector){
  myvector.push_back(argument);
}

//printfunktion
void print(){
  //for_each(text.begin(), text.end(), printword);
  copy(text.begin(), text.end(), ostream_iterator<string>(cout, " "));
}


//används för att sortera orden efter ggr de förekommer istället för alfabetet.
bool compare(pair<string, int> word1, pair<string, int> word2){
  if (word1.second > word2.second){
    return true;
  }
  else{
    return false;
  }
}

void frequency(){
  map<string, int> words{};
    for_each(text.begin(), text.end(), [&words](string word) {
    countword(words, word);
    });

    vector<pair<string, int>> entries(words.begin(), words.end());
    sort(entries.begin(), entries.end(), compare);

    for_each(entries.begin(), entries.end(), printfrequency);
}

void table(){
    map<string, int> words{};
    for_each(text.begin(), text.end(), [&words](string word) {
    countword(words, word);
    });

    for_each(words.begin(), words.end(), printtable);
}

//funktion som byter ut alla förekomster av ett ord mot ett som anges av användaren
void substitute(string const& old, string const& nnew){
  for_each(text.begin(), text.end(), [old, nnew](string& word) {
    changeword(word, old, nnew);
    });
}

//Funktion som tar bort alla förekomster av ett ord
void remove(string searchword){
  int removeindex{0};
  //text.erase(remove(text.begin(), text.end(), searchword), text.end());
  for_each(text.begin(), text.end(), [searchword, &removeindex](string& word) {
    removeword(word, searchword, removeindex);
  });
}

//funktion som används för alla argument, delar upp dem i flag och parametrar och kör seedan matchande funktion
void argumentparser(string argument){

  if (argument.find("=") != string::npos){ //Ifall argumentet innehåller '='
    int splitindex{0}; //används för att dela upp argumentet i flag och parameter
    splitindex = argument.find("=");
    string flag = argument.substr(0, splitindex); //flag = från start till '='
    string parameter = argument.substr(splitindex + 1, argument.size()); //parameter = från '=' till sista index
    pair<string, string> flagpar{flag, parameter}; //skapar pair som håller bägge

    if (flagpar.first == "--substitute"){

      splitindex = flagpar.second.find("+"); //substitutes parameter består av två värden separerade av '+'
      string old = flagpar.second.substr(0, splitindex );
      string nnew = flagpar.second.substr(splitindex + 1, flagpar.second.size()); 
      substitute(old, nnew); //kallar funktionen med bägge värden
    }

    else if (flagpar.first == "--remove"){
      remove(flagpar.second);
    }

  }
  else{
    if (argument == "--print"){
      print();
    }
    else if (argument == "--frequency"){
      frequency();
    }
    else if (argument == "--table"){
      table();
    }
  }
}

int main(int argc, char *argv[]){
  cout << setfill(' '); //fill blir permanent ' '
  fstream textfile; //skapar filestream textfile
  textfile.open(argv[1]); //öppnar filen som anges som första argument
  vector<string> arguments(argv + 2, argv + argc);

  //Fyller vectorn text med alla ord från den angivna texten
  copy(istream_iterator<string>(textfile), 
       istream_iterator<string>(), 
       back_inserter(text));

  //Kör argumentparser för varje medskickat argument
  for_each(arguments.begin(), arguments.end(), argumentparser);
  
  textfile.close();
  return 0;
}
