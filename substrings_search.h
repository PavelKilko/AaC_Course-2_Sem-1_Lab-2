//
// Created by Pavel on 11/28/2021.
//

#ifndef LAB2_SUBSTRINGS_SEARCH_H
#define LAB2_SUBSTRINGS_SEARCH_H

#include <iostream>
#include <vector>
#include <set>

bool naive_string_matcher(std::string& word, std::string& text, std::vector<size_t>& positions);

void find_all_pos(std::set<std::string>& dictionary, std::vector<std::string>& text);

bool read_text_from_file(const std::string& fileName, std::vector<std::string>& text);

bool read_dictionary_from_file(const std::string& fileName, std::set<std::string>& dictionary);

void normalize_word(std::string& word);

#endif //LAB2_SUBSTRINGS_SEARCH_H
