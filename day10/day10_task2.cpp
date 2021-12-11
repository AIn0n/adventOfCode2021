#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <numeric>

using namespace std;

bool is_corrupted(
    const string line, 
    const map<char, char> expected, 
    const string r_brk)
{
    vector<char> v;
    for (char c : line)
        if (v.size() > 1 && find(r_brk.begin(),r_brk.end(), c) != r_brk.end()) {
            if (v.back() != expected.at(c))
                return true;
            v.pop_back();
        } else
            v.push_back(c);
    return false;
}

vector<char> get_closing(const string line, const string r_brk)
{
    vector<char> v;
    for (char c : line)
        if(find(r_brk.begin(), r_brk.end(), c) != r_brk.end())
            v.pop_back();
        else
            v.push_back(c);
    reverse(v.begin(), v.end());
    return v;
}

int main (void) {
    fstream f("input.txt");

    const map<char, char> expected{{'}', '{'}, {']', '['}, {')', '('}, {'>', '<'}};
    const string r_brk = "})>]";
    const map<char, uint64_t> vals{{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
    vector<uint64_t> points;
    for (string s; getline(f, s);)
        if (!is_corrupted(s, expected, r_brk)) {
            vector<char> clos = get_closing(s, r_brk);
            points.push_back(accumulate(clos.begin(), clos.end(), 0, 
            [=](uint64_t x, char c){
                return x * 5 + vals.at(c);
            }));
        }
    sort(points.begin(), points.end());
    cout << points[points.size() / 2] << '\n';
    return 0;
}