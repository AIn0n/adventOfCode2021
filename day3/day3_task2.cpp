#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstring>

//------------- WARNING ------------------------
//
//  Down here you can find pretty spaghetti vibin' code
//  Please don't touch this, especially if you are cpp experienced hasker
//      (for you own mental sanity)
//  I have some problem with passing lambda into the function
//
//-----------------------------------------------


int count_bits(const std::vector<std::string>lines, const int line_num) {
    int bits = 0;
    for (const auto& str : lines)
        bits += (str[line_num] == '1');
    return bits;
}

int main (void) {
    const std::string filename("input.txt");
    std::fstream file(filename);
    std::vector<std::string> lines;

    for (std::string line; getline(file, line);)
        lines.push_back(line);

    const size_t word_len = lines.front().length();

    std::vector<std::string> cpy = lines;
    for (int i = 0; i < word_len && cpy.size() > 1; ++i) {
        const int bits = count_bits(cpy, i);
        const size_t num_of_info = cpy.size();
        std::vector<std::string> tmp;
        std::copy_if(cpy.begin(), cpy.end(), std::back_inserter(tmp), 
            [=](const auto& s) {
                return ((bits >= (num_of_info - bits)) ? '1' : '0') == s[i];
            });
        cpy = tmp;
    }
    const int oxygen = stoi(cpy[0],0, 2);

    cpy = lines;
    for (int i = 0; i < word_len && cpy.size() > 1; ++i) {
        const int bits = count_bits(cpy, i);
        const size_t num_of_info = cpy.size();
        std::vector<std::string> tmp;
        std::copy_if(cpy.begin(), cpy.end(), std::back_inserter(tmp), 
            [=](const auto& s) {
                return ((bits >= (num_of_info - bits)) ? '0' : '1') == s[i];
            });
        cpy = tmp;
    }
    const int carbon = stoi(cpy[0], 0, 2);
    std::cout << carbon * oxygen << '\n';
}