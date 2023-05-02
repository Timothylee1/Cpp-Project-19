/*!*****************************************************************************
\File spelling.hpp
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
#include <string>
#include <vector>
#include <fstream>

namespace hlp2 {

class string_utils {
    public:
    // Converts lower-case Latin characters in a string to upper-case.
    static std::string upper_case(std::string const& str);

    // Split a string into words. A word is any character but a space.
    // Return the word in a vector.
    static std::vector<std::string> split(std::string const& words);
};

class spell_checker {
    public: 
        enum SCResult {
            scrFILE_OK = -1, //File opened successfully
            scrFILE_ERR_OPEN = -2, //File unable to be opened
            scrWORD_OK = 1, //word found in lexicon
            scrWORD_BAD = 2 //word not found in lexicon
        };

        struct lexicon_info {
            size_t shortest; //shortest word in lexicon
            size_t longest;  //longest word in lexicon
            size_t count;    //number of words in lexicon
        };

    // Constructor. A lexicon filename must be supplied to initialize
    // private data member but not open the lexicon!!!
    spell_checker(const std::string &lexicon);

    // Count number of words that start with letter. If file can't be
    // opened, return scrFILE_ERR_OPEN. If successful, return scrFILE_OK.
    // The count is returned in the reference parameter count.
    SCResult words_starting_with(char letter, size_t& count) const;

    // Count the number of words that have length 1 to count and store
    // them in lengths at appropriate index. If the file can't be
    // opened, return scrFILE_ERR_OPEN, otherwise return scrFILE_OK.
    SCResult word_lengths(std::vector<size_t>& lengths, size_t count) const;

    // Return some information about lexicon using reference
    // parameter. If the file can't be opened, return scrFILE_ERR_OPEN,
    // otherwise return scrFILE_OK.
    SCResult get_info(lexicon_info& info) const;

    // Lookup the word in lexicon. If the word was found, return
    // scrWORD_OK. If the word was not found, return scrWORD_BAD. If the
    // lexicon file can't be opened, return scrFILE_ERR_OPEN.
    SCResult spellcheck(std::string const& word) const;

    // Given a string, find words in the lexicon that are composed of
    // letters in the same order. If the lexicon can't be opened,
    // return scrFILE_ERR_OPEN. If successful, return scrFILE_OK.
    SCResult acronym_to_word(std::string const& acronym,
                std::vector<std::string>& words, size_t maxlen = 0) const;

    private:
        std::string dictionary;
};

} // end namespace hlp2
