#include <fstream>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <map>

int main (void) {
    std::fstream f("input.txt");
    std::vector<std::string> lines;
    for (std::string line; getline(f, line);)
        lines.push_back(line);

    const std::map<char, char> m{{'}', '{'}, {']', '['}, {')', '('}, {'>', '<'}};
    const std::array<char, 4> r_brk{'}',')','>',']'};
    const std::map<char, int> vals{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
    int p = 0;
    for (std::string s : lines) {
        std::vector<char> stack;
        for (char c : s) {
            if (stack.size() > 1 && std::find(r_brk.begin(),r_brk.end(), c) != r_brk.end()) {
                if (stack.back() != m.at(c)) {
                    p += vals.at(c);
                    break;
                } else {
                    stack.pop_back();
                }
            } else {
                stack.push_back(c);
            }
        }

    }
    std::cout << p << '\n';
}