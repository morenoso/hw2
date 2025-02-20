#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> words;
    int count = 0;
    for(int i = 0; i < (int)rawWords.size(); ++i){
      int asciiCheck = (int)rawWords[i];
      //cout << asciiCheck << endl;
      if((asciiCheck < 65 || (asciiCheck>90 && asciiCheck < 97)
        || asciiCheck > 122) && count >= 2){
        //cout << rawWords.substr(i-count,count) << endl;
        words.insert(convToLower(rawWords.substr(i - count, count)));
        count = 0;
      }else if ((asciiCheck < 65 || (asciiCheck>90 && asciiCheck < 97)
      || asciiCheck > 122) && count < 2){
        count = 0;
      }else{
        count++;
      }
    }
    return words;

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
