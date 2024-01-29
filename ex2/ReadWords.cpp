#include   "ReadWords.h"


string removePunct(string word)
{
    //for character in word, if character isnt punctuation add to result and return
    string result;
    for (char c : word) {
        if (!ispunct(c)) {
            result += c;
        }
    }
    return result;
}

ReadWords::ReadWords(const char *fname)
{   wordfile.open(fname);
    if (!wordfile)
    {   cout << "Failed to open " << fname << endl;
        exit(1);
    }
    wordfile >> nextword;
    eoffound = false;
}


string ReadWords::getNextWord()
{
    string word = nextword;
    wordfile >> nextword;

    if (wordfile.eof())
        eoffound = true;

    word = removePunct(word);

    //check if the word contains any letters
    if (!containsLetters(word)) {
        //return an empty string if the word contains no letters
        return "";
    }

    //convert to lowercase before returning
    for (char& c : word) {
        c = std::tolower(c);
    }

    return word;
}
bool ReadWords::containsLetters(const string& str) {
    for (char c : str) {
        if (isalpha(c)) {
            return true;
        }
    }
    return false;
}

bool ReadWords::isNextWord()
{ return !eoffound;
}

void ReadWords::close()
{
    wordfile.close();

}
