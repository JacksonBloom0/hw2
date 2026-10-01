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
std::set<std::string> parseStringToWords(std::string rawWords)
{
    rawWords = convToLower(rawWords);
    std::set<std::string> word_set = {};
    std::stringstream text_stream = std::stringstream(rawWords);
    std::string word;
    while (text_stream >> word) { // O(N) N = num words
        if (word.length() < 2) {
            continue;
        }

        std::set<std::string> sub_words;
        size_t start = 0;
        for (size_t i = 0; i < word.length(); ++i) { // O(N) N = letters in word
            if (!std::isalnum(word[i]) && word[i] != ' ') {
                sub_words.insert(word.substr(start, (i - start)));
                start = i + 1;
            }
        }
        sub_words.insert(word.substr(start, (word.length() - start)));


        for (std::set<std::string>::iterator it = sub_words.begin(); it != sub_words.end(); ++it) { // O(N) sub_words in word
            if (it->length() >= 2) {
                word_set.insert(*it);
            }
        }
    }
    return word_set;

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
