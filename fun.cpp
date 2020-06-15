//
// Created by Žygimantas Kungelis on 2020-06-12.
// ISI 1, 2 grupė
//

#include "header.h"

std::string get_file()
{
    std::string tmp = " ";
    std::cout << "\nInput file's name (.txt format, between 5 and 20 symbols in length):\n";
    while (true) {
        std::cin >> tmp;
        std::cin.ignore(256,'\n');
        if (tmp.length() > 4 && tmp.length() < 21 && tmp.compare(tmp.length() - 4, 4, ".txt") == 0)
            return tmp;
        std::cout << "Wrong address.\n";
    }
}
void read_file(const std::string& file_name, svector& vec)
{
    std::ifstream from(file_name);
    vec.reserve(N);
    if (!from.is_open()) throw std::runtime_error("File does not exist. Please try again");
    std::string temp;
    while (!from.eof()) {
        getline(from, temp, '\n');
        if (temp.empty() || temp == " " || temp == "\n") continue;
        vec.push_back(temp);
    }
    from.close();
}
void find_all_occurrences(std::vector<int>& positions, const std::string& data, const std::string& to_search)
{
    size_t pos = data.find(to_search);
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = data.find(to_search, pos + to_search.size());
    }
}
void erase_duplicate_url_positions(std::vector<int>& positions)
{
    std::vector<size_t> erase_these;
    std::string tmp = "https://";
    erase_these.reserve(N);
    // std::size("https://") - 1 == 8
    for (int i = 0, until = positions.size(); i < until - 1; ++i)
        if (positions.at(i + 1) - positions.at(i) == tmp.size())
          erase_these.push_back(i + 1);
    for (const auto& i : erase_these)
        positions.erase(positions.begin() + i);
}
void find_url_positions(std::vector<int>& positions, const std::string& line)
{
    // Finds all positions of https// and www. substrings.
    find_all_occurrences(positions, line, "https://");
    find_all_occurrences(positions, line, "www.");
    // All of https::// will have www. address duplicate.
    if (!positions.empty()) {
      positions.shrink_to_fit();
      std::sort(positions.begin(), positions.end());
      erase_duplicate_url_positions(positions);
    }
}
void cut_string_length(std::string& line) {
    bool change = false;
    for (auto& e : line)
    {
        for (const auto& f : evil_for_url)
            if (f == e) {
                change = true;
                break;
            }
        if (change) {
            size_t from = line.find(e);
            line.erase(line.begin() + from, line.end());
            break;
        }
    }
}
void get_all_urls_from_string(const std::vector<int>& positions, const std::string& line, svector& urls)
{
    std::string tmp, url;
    for (const auto& pos : positions) {
        // I always need a full line string, because if I erase something from it, the positions in the string will change
        tmp = line;
        // erase until the first position
        tmp.erase(0, pos);
        // output the first string from tmp
        std::stringstream from(tmp);
        from >> url;
        cut_string_length(url);
        // cut url length
        urls.push_back(url);
    }
}
void check_for_urls(const svector& lines, svector& urls)
{
    std::vector<int> positions;
    urls.reserve(N);
    positions.reserve(N);
    for (const auto& line : lines) {
        find_url_positions(positions, line);
        get_all_urls_from_string(positions, line, urls);
        if (!positions.empty()) positions.clear();
    }
}
void change_special_symbols(std::string& line)
{
    bool change = false;
    for (auto& e : line)
    {
        for (const auto& f : evil)
            if (f == e) {
                change = true;
                break;
            }
        if (change) e = ' ';
        change = false;
    }
}
void change_all_lines(svector& vec)
{
    for (auto& line : vec)
        change_special_symbols(line);
}
bool count_repeats(const int& counter, const my_map& words, const std::pair<my_map::iterator, bool>& result)
{
    for (const auto& num : result.first->second)
        if (num == counter) return true;
    return false;
}
void read_words(const std::string& line, my_map& words, const int& counter)
{
    std::stringstream from(line);
    std::string temp;
    std::pair<my_map::iterator, bool> result;
    while (from >> temp) {
        result = words.insert(std::pair<std::string, std::vector<int>>(temp, {0, counter}));
        // if insertion failed, then increment the first value of vector<int> in map[result.first]
        if (!result.second) {
            ++result.first->second[0];
            if (!count_repeats(counter, words, result)) result.first->second.push_back(counter);
        }
    }
}
void read_all_words(my_map& words, const svector& vec)
{
    int counter = 1;
    for (const auto& line : vec) {
        read_words(line, words, counter);
        counter++;
    }
}
int count_of_digits(const int& line_count)
{
    int tmp = line_count;
    int count = 0;
    while (tmp != 0) {
        ++count;
        tmp /= 10;
    }
    return count;
}
std::string longest_keyword(const my_map& words)
{
    std::string tmp = " ";
    for (const auto& e : words)
        if (e.first.size() > tmp.size()) tmp = e.first;
    return tmp;
}
void print_to(const my_map& words, const svector& urls, std::ostream& to, const int& line_count)
{
    int name_size = longest_keyword(words).size(),
        number_size = count_of_digits(line_count);
    std::string table_line, fill;
    for (int i = 0, until = name_size + 1 + line_count * (number_size + 1); i < until; ++i)
        table_line += "-";
    for (int i = 0, until = number_size; i < until; ++i)
        fill += fill_symbol;
    table_line += "\n";

    to << table_line;
    to << std::setw(name_size) << std::left << " " << '|';
    for (int i = 1; i <= line_count; ++i)
        to << std::setw(number_size) << std::left << i << '|';
    to << std::endl << table_line;

    for (const auto& e : words)
        if (e.second[0] > 1) {
            to  << std::setw(name_size) << std::left << e.first << '|';
            for (int i = 1; i <= line_count; ++i) {
                if (std::find(e.second.begin(), e.second.end(), i) != e.second.end())
                    to << std::setw(number_size) << std::left << fill << '|';
                else
                    to << std::setw(number_size) << std::left << ' ' << '|';
            }
            to << std::setw(number_size) << std::left << e.second[0];
            to << std::endl << table_line;
        }
    to << std::endl;

    for (const auto& url : urls)
        to << url << '\n';
}
void print(const my_map& words, const svector& urls, const std::string& file_name, const int& line_count)
{
    if (file_name != "NULL") {
        std::ofstream to(file_name);
        print_to(words, urls, to, line_count);
        to.close();
    }
    else {
        print_to(words, urls, std::cout, line_count);
    }
}
