#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T> intersection = {};

    typename std::set<T>::iterator it;
    typename std::set<T>::iterator end;
    typename std::set<T>& other = s1;
    
    if (s1.size() < s2.size) {
        it = s1.begin();
        end = s1.end();
        other = s2;
    }
    else {
        it = s2.begin();
        end = s2.end();
        other = s1;
    }
    while(it != end) {
        if (other.contains(*it)) {
            intersection.insert(*it);
        }
        it++;

    }
    return intersection;
}

template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T> union_set = {};

    typename std::set<T>::iterator it1 = s1.begin();
    typename std::set<T>::iterator it2 = s2.begin();
    while(it1 != s1.end() || it2 != s2.end()) {
        if (it1 != s1.end()) {
            union_set.insert(*it1);
            it1++;
        }
        if (it2 != s2.end()) {
            union_set.insert(*it2);
            it2++;
        }
    }
    return union_set;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
