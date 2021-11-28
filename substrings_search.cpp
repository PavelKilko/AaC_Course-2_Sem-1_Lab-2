//
// Created by Pavel on 11/28/2021.
//

#include "substrings_search.h"
#include <fstream>

bool naive_string_matcher(std::string& word, std::string& text, std::vector<size_t>& positions)
{
    bool flag = false;
    size_t wordLength = word.length();
    size_t textLength = text.length();
    if (wordLength > textLength)
        return flag;
    for (size_t i = 0; i < textLength-wordLength+1; i++)
    {
        bool is_found = true;
        for (size_t j = 0; j < wordLength; j++)
        {
            if (word[j] != text[j+i])
            {
                is_found = false;
                break;
            }
        }
        if(is_found)
        {
            flag = true;
            positions.push_back(i+1);
        }
    }
    return flag;
}

void find_all_pos(std::set<std::string>& dictionary, std::vector<std::string>& text)
{
    for (auto word : dictionary)
    {
        std::cout << "Word : " << word << "\n";
        size_t i = 1;
        for (auto line : text)
        {
            std::vector<size_t> positions;
            naive_string_matcher(word, line, positions);
            if (!positions.empty())
            {
                std::cout << "Line #" << i << " : ";
                for (auto pos : positions)
                {
                    std::cout << pos << " ";
                }
                std::cout << ";\n";
            }
            i++;
        }
    }
}

bool read_text_from_file(const std::string& fileName, std::vector<std::string>& text)
{
    std::string line;
    std::ifstream input;

    input.open(fileName);
    bool flag = input.is_open();

    if (input.is_open())
        while (std::getline(input, line, '\n'))
            text.push_back(line);

    input.close();
    return flag;
}

bool read_dictionary_from_file(const std::string& fileName, std::set<std::string>& dictionary)
{
    std::string word;
    std::ifstream input;

    input.open(fileName);
    bool flag = input.is_open();

    if (input.is_open())
        while (input >> word)
        {
            normalize_word(word);
            dictionary.insert(word);
        }


    input.close();
    return flag;
}

void normalize_word(std::string& word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z'))
            continue;
        else
        {
            if (word[i] == '-' && ((word[i - 1] >= 'a' && word[i - 1] <= 'z') || (word[i - 1] >= 'A' && word[i - 1] <= 'Z'))
                               && ((word[i + 1] >= 'a' && word[i + 1] <= 'z') || (word[i + 1] >= 'A' && word[i + 1] <= 'Z')))
                continue;
            else
            {
                word.erase(i);
                i--;
            }
        }
    }
    std::cout << word << "\n";
}

