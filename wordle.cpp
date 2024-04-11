#ifndef RECCHECK
// For debugging

// For std::remove
#include <fstream>
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
#include <string>
using namespace std;


// Add prototypes of helper functions here
void floatHelp(std::set<std::string>& list, std::string word, std::string floats);

void helper(string word, std::set<std::string>& answers ,string alphabet, const set<string>& dictionary);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  set<string> dictionary;
  ifstream file;
  file.open("dict-eng.txt");
  string line;
  while(std::getline(file, line)){
    dictionary.insert(line);
  }
  file.close();
  
  set<string> list;
  if(floating.length() == 0){
    list.insert(in);
  }
  floatHelp(list, in, floating);
  set<string> answers;
  for(string word : list)
  {
    helper(word, answers, "abcdefghijklmnopqrstuvwxyz", dictionary);
  }
  return answers;
}

void floatHelp(std::set<std::string>& list, std::string word, std::string floats)
{
  if(floats.length() == 0){
    return;
  }
  

  if(floats.length() == 1){
    for(size_t i=0; i < word.length(); i++){
      if(word[i] == '-'){
        word[i] = floats[0];
        list.insert(word);
        word[i] = '-';
      }
    }
    return;
  }
  
  for(size_t i=0; i < word.length(); i++){
    if(word[i] == '-'){
      word[i] = floats[0];
      string temp = floats;
      temp.erase(0,1);
      floatHelp(list, word, temp);
      word[i] = '-';
    }
  }
}

void helper(string word, std::set<std::string>& answers,string alphabet, const set<string>& dictionary)
{
  if(word.find('-') == string::npos){
    if(dictionary.find(word) != dictionary.end()){
      answers.insert(word);
    }
    return;
  }
  
  for(size_t i=0; i < word.length(); i++){
    if(word[i] == '-'){
      for(size_t j=0; j < alphabet.length(); j++){
        word[i] = alphabet[j];
        helper(word, answers, alphabet, dictionary);
        word[i] = '-';
      }
    }
  }
}

