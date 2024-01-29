/**
 * ReadWords Interface for Assignment 1
 */

#ifndef READWORDS_H
#define READWORDS_H
/**
 * ReadWords class. Provides mechanisms to read a text file, and return
 * lower-case versions of words from that file.
 */
using namespace std;

#include <string>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <cctype>
class ReadWords
{
public:

    friend ostream& operator<<(ostream& os, const ReadWords& rw);

    /**
     * Constructor. Opens the file with the given filename and associates in
     * with the wordfile stream.
     * Initailises the other members.
     * Prints an error message then terminates the program if thr file cannot be opened.
     * Must not perform any other processing
     * @param filename - a C string naming the file to read.
     */
    ReadWords(const char *filename);

    /**
     * Closes the file.
     */
    void close();

   /**
    * Returns a string, being the next word in the file.
    * All letters should be converted to lower case
    * Leading and trailing punctuation symbols should not be included in the word
    * but punctuation elsewhere should not be removed
    * Returns an empty string if next word contains no letters
    * @return - string - next word.
    */


    string getNextWord() ;

    /**
     * Returns true if there is a further word in the file, false if we have reached the
     * end of file.
     * @return - bool - !eof
     */


    bool isNextWord() ;
    bool containsLetters(const string& str);

    /**
     * Returns true if there is a further word in the file, false if we have reached the
     * end of file.
     * @return - bool - !eof
     */
    const unordered_map<string, int>& getWordFrequencies() const {
        return wordFrequenciesMap;
    }

    //function to get the total number of words
    int getTotalWords() const {
        return totalWordsCount;
    }

    //default constructor with initialisation of 0
    ReadWords() : totalWordsCount(0) {}

    //constructor with parameters
    ReadWords(const unordered_map<string, int>& wordFrequencies, int totalWords)
            : wordFrequenciesMap(wordFrequencies), totalWordsCount(totalWords) {}


private:
    ifstream wordfile;
    string nextword;
    bool eoffound;
    unordered_map<string, int> wordFrequenciesMap;
    int totalWordsCount;
};

#endif
