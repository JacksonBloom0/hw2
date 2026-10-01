#include <set>
#include <string>
#include <sstream>
#include <iostream>

std::set<std::string> parseStringToWords(std::string rawWords)
{
    std::set<std::string> word_set = {};
    std::stringstream text_stream = std::stringstream(rawWords);
    std::string word;
    while (text_stream >> word) { // O(N) N = num words
        if (word.length() < 2) {
            continue;
        }
        std::cout << word << std::endl;
        std::set<std::string> sub_words;
        size_t start = 0;
        for (size_t i = 0; i < word.length(); ++i) { // O(N) N = letters in word
            std::cout << word[i] << std::endl;
            if (!std::isalnum(word[i]) && word[i] != ' ') {
                std::cout << "is not alphanum: " << word[i] << std::endl;
                std::cout << "word[" << i << "]: " << word[i] << std::endl;
                std::cout << "i: " << i << std::endl;
                std::cout << "start: " << start << std::endl;
                std::cout << "word.substr(start, (i - start): " << word.substr(start, (i - start)) << std::endl;
                sub_words.insert(word.substr(start, (i - start)));
                start = i + 1;
            }
        }
        sub_words.insert(word.substr(start, (word.length() - start)));
        std::cout << "subwords: " << sub_words.size() << std::endl;
        for (std::set<std::string>::iterator it = sub_words.begin(); it != sub_words.end(); ++it) { // O(N) sub_words in word
            std::cout << *it << std::endl;
            if (it->length() > 2) {
                word_set.insert(*it);
            }
        }
    }
    return word_set;

}

int main() {
    std::string rawWords = "These are mys-words.I have them here :)";
    auto s = parseStringToWords(rawWords);
    std::cout << std::endl;
    for (std::set<std::string>::iterator it = s.begin(); it != s.end(); ++it) { // O(N) sub_words in word
        std::cout << *it << std::endl;
    }
    
}