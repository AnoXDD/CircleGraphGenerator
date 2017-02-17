/**
 * The file reader of the circle graph
 * 
 * By default, each line in the file represents an edge, with the format defined in `FORMAT` of the class, separated by comma
 * 
 * Author: Runjie Guan guanrunjie@gmail.com
 */

#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>

#include "Graph.h"

using namespace std;

class FileReader {
    /**
     * An enum type to determine how to read the data in each line
     */
    enum Property {Concept1, Concept2, Type1, Type2, GraphNo, Weight};

    const vector<Property> FORMAT = {Concept1, Type1, Concept2, Type2, GraphNo, Weight};
    const string STOPWORD_FILE = "stopwords.txt"; // Format: one line per stop word
    /**
     * Format: one line per group of words. The first word is the original word, and the others are the alternative forms of the first word. Separated by comma
     */
    const string ORIGINAL_WORD_FILE = "original.txt";

    unordered_set<string> stop_words;
    unordered_map<string, string> original_word;

    /**
     * A function to split the string, copied from http://stackoverflow.com/questions/236129/split-a-string-in-c
     */
    vector<string> split(const string& s) const;

    /**
     * Updates the stop word dictionary. Returns if updating is a success
     */
    bool updateStopWords();

    /**
     * Updates the original word dictionary. Returns if updating is a success
     */
    bool updateOriginalWordDictionary();

public:
    FileReader();

    vector<Graph> getGraphs(string filename);
};
