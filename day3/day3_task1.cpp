#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

int main(void) {
    const std::string filename("input.txt");
    std::fstream file(filename);
    std::vector<std::string> lines;

    for (std::string line; getline(file, line);)
        lines.push_back(line);
    
    const size_t word_len = lines.front().length();
    const size_t num_of_info = lines.size();

    std::vector<int> bit_counter(word_len, 0);
    for (const auto& str : lines)
        for (int i = 0; i < word_len; ++i)
            bit_counter[i] += (str[i] == '1') ? 1 : 0;

    std::string binary = std::accumulate(bit_counter.begin(), bit_counter.end(), std::string(""), 
    [=](std::string s, int i){
        return std::move(s) + (i > num_of_info / 2 ? '1' : '0');
    });
    const int gamma = stoi(binary, 0, 2);
// binary in string negation
    std::transform(binary.begin(), binary.end(), binary.begin(), 
    [](char a){ 
        return (a == '1') ? '0' : '1';
    });
// negated gamma is just epsilon
    std::cout << gamma * stoi(binary, 0, 2) << '\n';
}