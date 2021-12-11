#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

int main (void) {
    const map<char, char> expected{{'}', '{'}, {']', '['}, {')', '('}, {'>', '<'}};
    const string r_brk = "})>]";
    const map<char, int> vals{{')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};

    fstream f("input.txt");
    int p = 0;
    for (string s; getline(f, s);) {
        vector<char> stack;
        for (char c : s)
            if (stack.size() > 1 && find(r_brk.begin(),r_brk.end(), c) != r_brk.end()) {
                if (stack.back() != expected.at(c)) {
                    p += vals.at(c);
                    break;
                }
                stack.pop_back();
            } else
                stack.push_back(c);
    }
    cout << p << '\n';
    return 0;
}