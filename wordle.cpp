#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void func(
  string current,
  string floating, 
  const set<string>& dict, 
  set<string>& results,
  size_t index){

//base case
    if(index == current.length()){
      //floating letters test
      if(floating.empty() && dict.find(current) != dict.end()){
        results.insert(current);
       
      }

      return;
    }
  
    if(current[index] != '-'){ // for used letters
      func(current, floating, dict, results, index + 1);
        return;
    }

    for(char c = 'a'; c <= 'z'; ++c){ //start at first lowercase, loop til end
      current[index] = c;

      size_t pos = floating.find(c);
      if(pos < floating.size()){
        string newFloat = floating;
        newFloat.erase(pos,1);
        func(current, newFloat, dict, results, index + 1);
      }
      else{
        int blanksRemain = 0;
        for(size_t j = index + 1; j < current.size(); ++j){
          if(current[j] == '-'){
            ++blanksRemain;
          }
        }
        if(floating.size() <= blanksRemain){
          func(current, floating, dict, results, index + 1);
        }
      }
    }
    

    current[index] = '-';
  }
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

  set<string> results;
  func(in, floating, dict, results, 0);
  return results;
}

// Define any helper functions here
