//
// Created by Pavel on 11/28/2021.
//

#ifndef LAB2_SUBSTRINGS_SEARCH_H
#define LAB2_SUBSTRINGS_SEARCH_H

#include <iostream>
#include <vector>
#include <set>

// Aho-Corasick algorithm

const int k = 54;

struct BohrVertex
{
    int nextVertex[k];
    int patternNumber;
    int suffixLink;
    int autoMove[k];
    int parent;
    int suffixFineLink;
    bool flag;
    char symbol;
};

BohrVertex make_bohr_vertex(int p, char c);

class Bohr
{
public:
    std::vector<BohrVertex> bohr;
    std::vector<std::string> pattern;

    void initialize();
    void add_string(const std::string& s);
    void add_strings(const std::set<std::string>& d);
    bool is_string_in(const std::string& s);
    int get_auto_move(int v, char c);
    int get_suffix_link(int v);
    int get_suffix_fine_link(int v);
    void check(int v, int i);
    void find_all_pos(const std::string& s);
    void find_all_pos(const std::vector<std::string>& text);
};


// brute force algorithm

bool naive_string_matcher(std::string& word, std::string& text, std::vector<size_t>& positions);

void find_all_pos(std::set<std::string>& dictionary, std::vector<std::string>& text);

bool read_text_from_file(const std::string& fileName, std::vector<std::string>& text);

bool read_dictionary_from_file(const std::string& fileName, std::set<std::string>& dictionary);

void normalize_word(std::string& word);



#endif //LAB2_SUBSTRINGS_SEARCH_H
