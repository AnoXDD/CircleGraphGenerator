#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

vector<string> FileReader::split(const string& s) const {
    vector<string> elems;
    auto result = back_inserter(elems);
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, ',')) {
        *(result++) = item;
    }
    return elems;
}

bool FileReader::updateStopWords() {
    ifstream file(STOPWORD_FILE);
    if (!file.is_open()) {
        cout << "Unable to read the stop word dictionary" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            stop_words.insert(line);
        }
    }

    cout << "Stop words read: " << stop_words.size() << endl;
    return true;
}

bool FileReader::updateOriginalWordDictionary() {
    ifstream file(ORIGINAL_WORD_FILE);
    if (!file.is_open()) {
        cout << "Unable to read the original word dictionary" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        auto v = split(line);
        for (auto s : v) {
            original_word[s] = v[0];
        }
    }

    cout << "Original word groups read: " << original_word.size() << endl;
    return true;
}

FileReader::FileReader() {
    updateStopWords();
    updateOriginalWordDictionary();
}

vector<Graph> FileReader::getGraphs(string filename) {
    unordered_map<string, int> m;
    vector<Graph> graphs;

    cout << "Reading files" << endl;

    ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file " + filename);
    }

    string line;
    while (getline(file, line)) {
        // Convert to lower case. Comment this line for test purpose
        //        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        auto v = split(line);
        string s1, s2;
        char c1 = 0, c2 = 0;
        string id;
        float weight = 0;

        for (int i = 0; i < v.size(); ++i) {
            switch (FORMAT[i]) {
                case Concept1:
                    s1 = v[i];
                    break;
                case Concept2:
                    s2 = v[i];
                    break;
                case Type1:
                    c1 = v[i][0];
                    break;
                case Type2:
                    c2 = v[i][0];
                    break;
                case GraphNo:
                    id = v[i];
                    break;
                case Weight:
                    weight = atof(v[i].c_str());
                default: break;
            }
        }

        // Sanitize the words
        if (stop_words.count(s1) || stop_words.count(s2)) {
//            continue;
        }

        // Map to another word
        if (original_word.count(s1)) {
            s1 = original_word[s1];
        }
        if (original_word.count(s2)) {
            s2 = original_word[s2];
        }

        if (!m.count(id)) {
            // Create a new one
            m[id] = graphs.size();
            graphs.push_back(Graph());
        } 
        graphs[m[id]].add(s1, c1, s2, c2, weight);
    }

    return graphs;
}
