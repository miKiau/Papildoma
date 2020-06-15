//
// Created by Žygimantas Kungelis on 2020-06-12.
// ISI 1, 2 grupė
//

#ifndef UNTITLED1_MAIN_H
#define UNTITLED1_MAIN_H

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

// Initial size of vector
#define N 10000000
// fill symbol in the output
#define fill_symbol 'O'
// Symbols, which i'll change to ' '
const char evil[] = "–,<.>/?;:|\'\"\\[{]}=+-_)(*&^%$#@!~`0123456789";
const char evil_for_url[] = "<>;\"\'(),\\";

typedef std::map<std::string, std::vector<int>> my_map;
typedef std::vector<std::string> svector;

std::string get_file();
void read_file(const std::string& file_name, svector& vec);
void find_all_occurrences(std::vector<int>& positions, const std::string& data, const std::string& toSearch);
void erase_duplicate_url_positions(std::vector<int>& positions);
void find_url_positions(std::vector<int>& positions, const std::string& line);
void cut_string_length(std::string& line);
void get_all_urls_from_string(const std::vector<int>& positions, const std::string& line, svector& urls);
void check_for_urls(const svector& lines, svector& urls);
void change_special_symbols(std::string& line);
void change_all_lines (svector& vec);
bool count_repeats(const int& counter, const my_map& words, const std::pair<my_map::iterator, bool>& result);
void read_words(const std::string& line, my_map& words, const int& counter);
void read_all_words(my_map& words, const svector& vec);
int count_of_digits(const int& line_count);
std::string longest_keyword(const my_map& words);
void print_to(const my_map& words, const svector& urls, std::ostream& to, const int& line_count);
void print(const my_map& words, const svector& urls, const std::string& file_name, const int& line_count);

#endif //UNTITLED1_MAIN_H
