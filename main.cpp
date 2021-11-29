#include <iostream>
#include <chrono>
#include "substrings_search.h"

void test(const std::string& textFileName, const std::string& dictionaryFileName)
{
    std::vector<std::string> text;
    std::set<std::string> dictionary;
    read_text_from_file(textFileName, text);
    read_dictionary_from_file(dictionaryFileName, dictionary);

    Bohr test;
    test.initialize();
    test.add_strings(dictionary);

//  Dictionary search by brute force algorithm
    auto start1 = std::chrono::high_resolution_clock::now();
    find_all_pos(dictionary, text);
    auto end1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);

//  Dictionary search by Aho-Corasick algorithm
    auto start2 = std::chrono::high_resolution_clock::now();
    test.find_all_pos(text);
    auto end2 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

    std::cout << "Execution time of dictionary search by brute force algorithm: " << time1.count() << " ms" << std::endl;
    std::cout << "Execution time of dictionary search by Aho-Corasick algorithm: " << time2.count() << " ms" << std::endl;
}

int main()
{
    test("C:\\Users\\I\\Desktop\\C++\\CLion\\AlgorithmsAndComplexity\\lab2\\Text.txt",
         "C:\\Users\\I\\Desktop\\C++\\CLion\\AlgorithmsAndComplexity\\lab2\\Dictionary.txt");
    return 0;
}
