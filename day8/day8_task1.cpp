#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

template<typename T, typename E>
bool contain(const T &c, E e)
{
    return std::find(c.begin(), c.end(), e) != c.end();
}

int main (void) {
    std::fstream file("input.txt");
    int counter = 0;
    for (std::string line; getline(file, line);) {
        std::vector<std::string> output;
        boost::split(output, line.substr(line.find('|') + 2), boost::is_any_of(" "));
        counter += std::count_if(output.begin(), output.end(), 
        [sizes = {2, 3, 4, 7}](std::string s) { return contain(sizes, s.size()); });
    }
    std::cout << counter << '\n';
}