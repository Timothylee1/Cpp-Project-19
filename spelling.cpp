/*!*****************************************************************************
\File spelling.cpp
\Author Timothy Lee Ke Xin
\Par DP email: timothykexin.lee@digipen.edu.sg
\Par Course: RSE 1202
\Par Section: Using STL to solve real-world problems
\Par Programming Assignment #10
\Date 31-03-2022

    \brief
    The purpose of this assignment is to implement a spell checker that is not 
    case sensitive with various functions as listed.

  - upper_case
    Converts lower-case Latin characters in a string to upper-case.
  
  - split
    Split a string into words. A word is any character but a space.
    
  - spell_checker
    Non-default constructor.
    
  - words_starting_with
    Count number of words that start with letter. 
    
  - word_lengths
    Count the number of words that have length 1 to count range and store them 
    in lengths at appropriate index. E.g. 1 to 5; counts the number of words 
    with 1 char to 5 char and assigns the "count" to the respective index.
    
  - get_info
    Counts the number of words, shortest characters that make up a word, and 
    the longest number characters that make up a word in the file.
    
  - spellcheck
    Lookup the word in lexicon (the file containing the text).
    
  - acronym_to_word
    Given a string, find words in the lexicon that are composed of letters in 
    the same order. E.g. ABC -> Asnfbabkiec not Baabc. The first letter has to 
    match with the first letter of the acronym. Iterate through till the end
    of the lexicon word to see if the other acronym letters match. Repeats are
    fine, occurance prior is fine too, as long as the acronym is found within
    and follows the order.
*******************************************************************************/
#include "spelling.hpp"

namespace hlp2 {

std::string const ws = " \t\f\v\n\r";

/******************************************************************************/
/*!
    \brief
    Converts lower-case Latin characters in a string to upper-case.

    \param str
    The function param that contains the const reference to a string yet to 
    be converted.

    \param upper
    To contain the string with uppercased chars.

    \return 
    String containing the uppercased string.
*/
/******************************************************************************/
std::string string_utils::upper_case(std::string const& str) {
    std::string upper = str;
    for (size_t i{}; i < str.length(); ++i) {
        upper[i] = toupper(upper[i]);
    }
    return upper;
}

/******************************************************************************/
/*!
    \brief
    Split a string into words. A word is any character but a space.

    \param words 
    The function param that contains the const reference to a string yet to 
    be split.

    \param split_words
    A vector containing the split up words.

    \return 
    Return the word in a vector.
*/
/******************************************************************************/
std::vector<std::string> string_utils::split
                                (std::string const& words) {
    std::vector<std::string> split_words;
    size_t i{};
    while (i < words.size()) {
        i = words.find_first_not_of(ws, i);
        size_t j = words.find_first_of(ws, i);
        if (i != j) {
            split_words.push_back(words.substr(i, j-i));
            i = j;
        }
    }
    return split_words;
}

/******************************************************************************/
/*!
    \brief
    Non-default constructor.

    \param lexicon 
    The file name that is to be used as the initialized data for the private
    member, dictionary.

    \return 
    Nothing.
*/
/******************************************************************************/
spell_checker::spell_checker(const std::string &lexicon) 
                                : dictionary{lexicon} {}


/******************************************************************************/
/*!
    \brief
    Count number of words that start with letter. 

    \param letter 
    The identified letter.

    \param count
    Counter to number of words that start with the letter.

    \param ifs
    The fstream name representing the file.

    \param from_dic
    The word extracted from the file.

    \return 
    If file can't be opened, return scrFILE_ERR_OPEN. If successful, return 
    scrFILE_OK. The count is returned in the reference parameter count.
*/
/******************************************************************************/
spell_checker::SCResult spell_checker::words_starting_with(char letter, 
                                                        size_t& count) const {
    std::fstream ifs(dictionary, std::ios_base::in);
    if (!ifs.is_open()) return scrFILE_ERR_OPEN;
    
    count = 0;
    std::string from_dic;
    while (ifs) {
        std::getline(ifs, from_dic);

        if (from_dic.empty()) break;
        if (toupper(from_dic[0]) == toupper(letter)) ++count;
    }
    ifs.close();
    return scrFILE_OK;
}

/******************************************************************************/
/*!
    \brief
    Count the number of words that have length 1 to count range and store them 
    in lengths at appropriate index. E.g. 1 to 5; counts the number of words 
    with 1 char to 5 char and assigns the "count" to the respective index.

    \param lengths 
    The vector containing the range of lengths.

    \param count
    The max range for the number of chars to be appropriated. 

    \param ifs
    The fstream name representing the file.

    \param from_dic
    The word extracted from the file.

    \param length
    Represents the length of the word extracted from the file.

    \return 
    If the file can't be opened, return scrFILE_ERR_OPEN, otherwise return 
    scrFILE_OK.
*/
/******************************************************************************/
spell_checker::SCResult spell_checker::word_lengths(std::vector<size_t>& lengths
                                                        , size_t count) const {
    std::fstream ifs(dictionary, std::ios_base::in);
    if (!ifs.is_open()) return scrFILE_ERR_OPEN;

    for (size_t i{1}; i <= count; ++i) lengths[i] = 0;

    std::string from_dic;
    while (ifs) {
        std::getline(ifs, from_dic);
        if (from_dic.empty()) break;

        size_t length{from_dic.length()};
        if (length >= 1 && length <= count ) {
            ++lengths[length];
        }
    }
    ifs.close();
    return scrFILE_OK;
}

/******************************************************************************/
/*!
    \brief
    Counts the number of words, shortest characters that make up a word, and 
    the longest number characters that make up a word in the file.

    \param info
    The reference the a struct that contains the data members of count, 
    shortest, and longest.

    \param ifs
    The fstream name representing the file.

    \param from_dic
    The word extracted from the file.

    \param length
    Represents the length of the word extracted from the file.

    \return 
    If the file can't be opened, return scrFILE_ERR_OPEN, otherwise return 
    scrFILE_OK.
*/
/******************************************************************************/
spell_checker::SCResult spell_checker::get_info(lexicon_info& info) const {
    std::fstream ifs(dictionary, std::ios_base::in);
    if (!ifs.is_open()) return scrFILE_ERR_OPEN;

    info.count = 0;  info.shortest = 5;  info.longest = 5;
    std::string from_dic;
    while (ifs) {
        std::getline(ifs, from_dic);
        if (from_dic.empty()) break;
        size_t length = from_dic.length();
        if (info.shortest > length) info.shortest = length;
        if (info.longest < length) info.longest = length;
        ++(info.count);
    }
    ifs.close();
    return scrFILE_OK;
}

/******************************************************************************/
/*!
    \brief
    Lookup the word in lexicon (the file containing the text).

    \param word
    The function param that contains the const reference to a string to be 
    checked against.

    \param ifs
    The fstream name representing the file.
    
    \param from_dic
    The word extracted from the file.

    \return 
    If the word was found, return scrWORD_OK. If the word was not found, return 
    scrWORD_BAD. If the file can't be opened, return scrFILE_ERR_OPEN, otherwise 
    return scrFILE_OK.
*/
/******************************************************************************/
spell_checker::SCResult spell_checker::spellcheck(std::string const& word) const {
    std::fstream ifs(dictionary, std::ios_base::in);
    if (!ifs.is_open()) return scrFILE_ERR_OPEN;
    
    std::string from_dic;
    while (ifs) {
        std::getline(ifs, from_dic);
        if (from_dic.empty()) break;
        if (string_utils::upper_case(from_dic) == 
                string_utils::upper_case(word)) {
            ifs.close();
            return scrWORD_OK;
        }
    }
    ifs.close();
    return scrWORD_BAD;
}

/******************************************************************************/
/*!
    \brief
    Given a string, find words in the lexicon that are composed of letters in 
    the same order. E.g. ABC -> Asnfbabkiec not Baabc. The first letter has to 
    match with the first letter of the acronym. Iterate through till the end
    of the lexicon word to see if the other acronym letters match. Repeats are
    fine, occurance prior is fine too, as long as the acronym is found within
    and follows the order.

    \param acronym
    The string const reference containing the acronym.

    \param words
    Vector of strings to contain the words that match the conditions.

    \param maxlen
    Conditional max length of word that can be accepted, if not given, is 
    default to 0.

    \param ifs
    The fstream name representing the file.
    
    \param from_dic
    The word extracted from the file.

    \param pos
    The array containing the position of the letters of the acronym found in 
    the word.

    \param size
    Represents the length of the acronym.

    \param same
    Bool expression, true if the word matches, false if it doesn't.

    \return 
    If the file can't be opened, return scrFILE_ERR_OPEN, otherwise return 
    scrFILE_OK.
*/
/******************************************************************************/
spell_checker::SCResult spell_checker::acronym_to_word(std::string const& acronym,
            std::vector<std::string>& words, size_t maxlen) const {
    std::fstream ifs(dictionary, std::ios_base::in);
    if (!ifs.is_open()) return scrFILE_ERR_OPEN;
    
    std::string from_dic;
    size_t pos[8]{}, size = acronym.length();
    while (ifs) {
        std::getline(ifs, from_dic);
        std::string upp = string_utils::upper_case(from_dic);
        if (from_dic.empty()) break;
        bool same = true; 
        if (from_dic.length() >= size && 
            (from_dic.length() <= maxlen || maxlen == 0) ) {
            for (size_t i{}, j{}; i < size; ++i) {
                char ch = toupper(acronym[i]);
                pos[i] = upp.find_first_of(ch, j);

                if (pos[i] == std::string::npos || pos[0] != 0) {
                    same = false; break; 
                }
                j = pos[i]+1;
            }
            if (same == true)
                words.push_back(from_dic);
        }
    } 
    return scrFILE_OK;
}

} // end namespace hlp2
