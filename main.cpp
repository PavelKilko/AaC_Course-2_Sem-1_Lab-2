#include <iostream>
#include "substrings_search.h"

int main()
{
    std::string fileName1 = "C:\\Users\\I\\Desktop\\C++\\CLion\\AlgorithmsAndComplexity\\lab2\\Text.txt";
    std::string fileName2 = "C:\\Users\\I\\Desktop\\C++\\CLion\\AlgorithmsAndComplexity\\lab2\\Dictionary.txt";
    std::vector<std::string> text;
    std::set<std::string> dictionary;
    read_text_from_file(fileName1, text);
    read_dictionary_from_file(fileName2, dictionary);

    for (const auto& word : dictionary)
        std::cout << word << std::endl;

    find_all_pos(dictionary, text);

    Bohr test;
    test.initialize();
    test.add_strings(dictionary);
    test.find_all_pos(text);
    return 0;
}
