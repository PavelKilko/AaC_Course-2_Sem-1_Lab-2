#include <iostream>
#include "substrings_search.h"

int main() {
    std::string fileName = "C:\\Users\\I\\Desktop\\C++\\CLion\\AlgorithmsAndComplexity\\lab2\\Text.txt";
    std::vector<std::string> text;
    std::set<std::string> dictionary;
    read_text_from_file(fileName, text);
    read_dictionary_from_file(fileName, dictionary);

    find_all_pos(dictionary, text);

    return 0;
}
