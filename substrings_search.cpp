//
// Created by Pavel on 11/28/2021.
//

#include "substrings_search.h"
#include <fstream>
#include <cstring>

// Aho-Corasick algorithm

BohrVertex make_bohr_vertex(int p, char c)
{
    BohrVertex v{};
    memset(v.nextVertex, 255, sizeof(v.nextVertex));
    memset(v.autoMove, 255, sizeof(v.autoMove));
    v.flag = false;
    v.suffixLink = -1;
    v.parent = p;
    v.symbol = c;
    v.suffixFineLink = -1;
    return v;
}

void Bohr::initialize()
{
    bohr.push_back(make_bohr_vertex(0, '#'));
}

void Bohr::add_string(const std::string& s)
{
    int number = 0;
    for (size_t i = 0; i < s.length(); i++)
    {
        char c = 53;
        if (s[i] >= 'a' && s[i] <= 'z')
            c = s[i] - 'a';
        if (s[i] >= 'A' && s[i] <= 'Z')
            c = s[i] - 'A' + 26;
        if (s[i] == '-')
            c = 52;
        if (bohr[number].nextVertex[c] == -1)
        {
            bohr.push_back(make_bohr_vertex(number, c));
            bohr[number].nextVertex[c] = bohr.size() - 1;
        }
        number = bohr[number].nextVertex[c];
    }
    bohr[number].flag = true;
    pattern.push_back(s);
    bohr[number].patternNumber = pattern.size() - 1;
}

void Bohr::add_strings(const std::set<std::string>& d)
{
    for (const auto& w : d)
    {
        if (!is_string_in(w))
            add_string(w);
    }
}

bool Bohr::is_string_in(const std::string& s)
{
    int number;
    for (int i = 0; i < s.length(); i++)
    {
        char c = 53;
        if (s[i] >= 'a' && s[i] <= 'z')
            c = s[i] - 'a';
        if (s[i] >= 'A' && s[i] <= 'Z')
            c = s[i] - 'A' + 26;
        if (s[i] == '-')
            c = 52;
        if (bohr[number].nextVertex[c] == -1)
        {
            return false;
        }
        number = bohr[number].nextVertex[c];
    }
    return true;
}

int Bohr::get_suffix_link(int v)
{
    if (bohr[v].suffixLink == -1)
    {
        if ((v == 0) || (bohr[v].parent == 0))
        {
            bohr[v].suffixLink = 0;
        }
        else
        {
            bohr[v].suffixLink=get_auto_move(get_suffix_link(bohr[v].parent), bohr[v].symbol);
        }
    }
    return bohr[v].suffixLink;
}

int Bohr::get_auto_move(int v, char c)
{
    if (bohr[v].autoMove[c] == -1)
    {
        if (bohr[v].nextVertex[c] != -1)
        {
            bohr[v].autoMove[c] = bohr[v].nextVertex[c];
        }
        else
        {
            if (v == 0)
            {
                bohr[v].autoMove[c] = 0;
            }
            else
            {
                bohr[v].autoMove[c] = get_auto_move(get_suffix_link(v), c);
            }
        }
    }
    return bohr[v].autoMove[c];
}

int Bohr::get_suffix_fine_link(int v)
{
    if (bohr[v].suffixFineLink == -1)
    {
        int u = get_suffix_link(v);
        if (u == 0)
        {
            bohr[v].suffixFineLink=0;
        }
        else
        {
            bohr[v].suffixFineLink = (bohr[u].flag) ? u : get_suffix_fine_link(u);
        }
    }
    return bohr[v].suffixFineLink;
}

void Bohr::check(int v, int i)
{
    for (int u = v; u != 0; u = get_suffix_link(u))
    {
        if (bohr[u].flag)
            std::cout << i - pattern[bohr[u].patternNumber].length() + 1 << ' ' << pattern[bohr[u].patternNumber] << std::endl;
    }
}

void Bohr::find_all_pos(const std::string& s)
{
    int u = 0;
    for (int i = 0; i < s.length(); i++)
    {
        char c = 53;
        if (s[i] >= 'a' && s[i] <= 'z')
            c = s[i] - 'a';
        if (s[i] >= 'A' && s[i] <= 'Z')
            c = s[i] - 'A' + 26;
        if (s[i] == '-')
            c = 52;
        u = get_auto_move(u, c);
        check(u, i + 1);
    }
}

void Bohr::find_all_pos(const std::vector<std::string>& text)
{
    size_t i = 1;
    for (const auto& line : text)
    {
        std::cout << "Line #" << i << std::endl;
        find_all_pos(line);
        i++;
    }
}

// brute force algorithm

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
            if (!word.empty())
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
}

