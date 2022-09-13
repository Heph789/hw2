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
    set<string> parsedWords;
    string word = "";
    for (long unsigned int i = 0; i<rawWords.size(); i++) {
        char c = rawWords[i];
        if (isalpha(c)) {
            word += (char)tolower(c); // changes all keywords to lowercase
        }
        else if (isdigit(c)) {
            word += c;
        }
        else if (word.size() >= 2) { // when we encounter punctuation or on the last character
            parsedWords.insert(word);
            word.clear();
        }
        else {
            word.clear();
        }
    }
    if (word.size() >= 2) { // catches last word. redundant, can improve on later
        parsedWords.insert(word);
        word.clear();
    }
    return parsedWords;
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
