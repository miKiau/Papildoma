//
// Created by Žygimantas Kungelis on 2020-06-12.
// ISI 1, 2 grupė
//

#include "header.h"

int main() try {
    std::cout << "Recomendation: don't input a file with a huge number of lines.\n";
    const std::string file_name = get_file();
    svector lines, urls;

    read_file(file_name, lines);
    check_for_urls(lines, urls);
    change_all_lines(lines);

    my_map words;
    read_all_words(words, lines);

    // std::cout << "\nShould the output be printed to the file? (y/n)\n";
    // std::string tmp;
    // while (true) {
    //     std::cin >> tmp;
    //     std::cin.ignore(256, '\n');
    //     std::cin.clear();
    //     if (tmp != "y" || tmp != "n") break;
    // }
    std::cout << "\nThe output's name.";
    const std::string file_to = get_file();
    print(words, urls, file_to, lines.size());

    return 0;
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
} catch (...) {
    std::cerr << "something went wrong." << std::endl;
    return 2;
}
