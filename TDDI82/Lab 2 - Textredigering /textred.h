#include <string>
#include <vector>
#include <map>

#ifndef TEXTRED_H
#define TEXTRED_H

void countword(std::map<std::string, int> &words, std::string word); //ok
void countwordalgo(std::map<std::string, int> &words, std::string word);
void check(std::string word, int &longest);
int get_longest();
void removeword(std::string &word, std::string searchword, int &index); //ok
void changeword(std::string &word, std::string old, std::string nnew); //ok
void printtable(std::pair<std::string, int> word); //ok
void printfrequency(std::pair<std::string, int> word); //ok
void add_argument(char *argument, std::vector<char *> myvector);
void print(); //ok
bool compare(std::pair<std::string, int> word1, std::pair<std::string, int> word2); //ok
void frequency(); //ok
void table(); //ok
void substitute(std::string const &old, std::string const &nnew); //ok
void remove(std::string searchword); //ok
void argumentparser(std::string argument); //ok

#endif
