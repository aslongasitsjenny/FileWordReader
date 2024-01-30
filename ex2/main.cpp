#include "ReadWords.h"
/**
 * Converts each character in the input string to its lowercase equivalent.
 *
 * @param str - The input string to be converted to lowercase.
 * @return A new string with all characters converted to lowercase.
 */
string toLowerCase(const string& str) {
    string result;
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

//function to handle user input for file names
string getFileNameFromUser(const string& prompt) {
    string fileName;
    cout << prompt << ": " << endl;
    cin >> fileName;
    return  fileName;
}

/**
 * Generates a bar graph based on the word counts in the provided searchWordCountMap.
 * Writes the formatted output to the specified output file.
 *
 * @param searchWordCountMap - A map containing word counts for each search word.
 * @param longestSearchWord - The length of the longest search word for formatting.
 * @param totalWords - The total number of words used for percentage calculation.
 * @return A formatted string representing the bar graph content.
 */
string generateBarGraphContent(const unordered_map<string, int>& searchWordCountMap, int longestSearchWord, int totalWords) {
    stringstream output;

    //iterate through each word in the searchWordCountMap
    //format the output with left alignment and a specified width of longestSearchWord
    for (const auto& searchWordCountPair : searchWordCountMap) {
        string lowercaseWord = toLowerCase(searchWordCountPair.first);

        output << left << setw(longestSearchWord) << searchWordCountPair.first;

        //append = symbol based on the count of the current word
        stringstream remainingOutputStream;
        for (int i = 0; i < searchWordCountPair.second; i++) {
            remainingOutputStream << "=";
        }

        //calculate the percentage of occurrences relative to the total words
        double percentage = ((double)searchWordCountPair.second / (double)totalWords) * 100.0;
        remainingOutputStream << " " << searchWordCountPair.second << " (" << percentage << "%)" << endl;

        string remainingOutput = remainingOutputStream.str();
        output << remainingOutput;
    }
    return output.str();
}

int main() {

    unordered_map<string, int> searchWordCountMap;
    int totalWords = 0;

    string analysisFilePath = getFileNameFromUser("Enter the name of the text file to be analysed, please put FULL file path in: ");
    string searchWordsFilePath = getFileNameFromUser("Enter the name of the file containing search words: ");
    string outputFilePath = getFileNameFromUser("Enter the name of the output file: ");

    //use a different stream for the searchWords file
    ifstream analysisFile(analysisFilePath);
    if (!analysisFile.is_open()) {
        cerr << "Error opening analysis file: " << analysisFilePath << endl;
        return 1;
    }

    //use a different stream for the searchWords file
    ifstream searchWordsFile(searchWordsFilePath);
    if (!searchWordsFile.is_open()) {
        cerr << "Error opening search words file: " << searchWordsFilePath << endl;
        return 1;
    }

    //read search words file and store in map
    ReadWords searchWordsReader(searchWordsFilePath.c_str());
    while (searchWordsReader.isNextWord()) {
        string word = searchWordsReader.getNextWord();
        string lowercaseWord = toLowerCase(word);
        searchWordCountMap[lowercaseWord] = 0;
    }

    //read words to analyse file and update the map based on occurrences in the given file
    ReadWords wordsToAnalyseReader(analysisFilePath.c_str());
    while (wordsToAnalyseReader.isNextWord()) {
        string nextWord = wordsToAnalyseReader.getNextWord();
        string lowercaseWord = toLowerCase(nextWord);
        if (searchWordCountMap.count(lowercaseWord) > 0) {
            searchWordCountMap[lowercaseWord] += 1;
        }
        totalWords++;
    }

    //create a ReadWords object with the filled map and total word count
    ReadWords rw(searchWordCountMap, totalWords);

    //output ReadWords object using the overloaded operator<<
    cout << rw << endl;
    ofstream outputFile(outputFilePath);
    if (outputFile.is_open()) {
        outputFile << rw << endl;
        outputFile.close();
        cout << "Graph outputted to file: output.txt" << endl;
    } else {
        cerr << "Error opening file for writing." << endl;
    }

    return 0;
}

ostream& operator<<(ostream& os, const ReadWords& rw) {
    //obtain a constant reference to the word count map from the ReadWords object
    //this map holds the frequencies of each search word in the analysed text
    const unordered_map<string, int>& searchWordCountMap = rw.getWordFrequencies();
    int totalWords = rw.getTotalWords();

    //find the longest search word so it can align the output of the bar chart
    int longestSearchWord = 0;
    for (const auto& searchWordCountPair : searchWordCountMap) {
        int length = searchWordCountPair.first.length();
        if (length > longestSearchWord) {
            longestSearchWord = length;
        }
    }
    //use longestSearchWord as the padding +1 for space between
    longestSearchWord += 1;

    //generate bar graph content
    string barGraphContent = generateBarGraphContent(searchWordCountMap, longestSearchWord, totalWords);

    //output to the stream
    os << barGraphContent;

    return os;
}
