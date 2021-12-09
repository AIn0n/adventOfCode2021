#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

template<typename T, typename E>
bool contain(const T &c, E e)
{
    return std::find(c.begin(), c.end(), e) != c.end();
}

std::vector<std::string>splitBySpacesAndSort(std::string in)
{
    std::vector<std::string> ret;
    boost::split(ret, in, boost::is_any_of(" "));
    for (std::string &s : ret)
        std::sort(s.begin(), s.end());
    return ret;
}

size_t countCommon(const std::string f, const std::string s)
{
    return std::count_if(f.begin(), f.end(), 
    [&](const auto &n) { return contain(s, n); });
}

void removeAndAddMappingIfEq(
    std::vector<std::string> &in, 
    std::array<std::string, 10> &mapping, 
    size_t out_map_idx,
    size_t cmp_map_idx,
    int val)
{
    for (int i = 0; i < in.size(); ++i) {
        if (countCommon(in[i], mapping[cmp_map_idx]) == val) {
            mapping[out_map_idx] = in[i];
            in.erase(std::next(in.begin(), i));
            return;       
        }
    }
}

std::vector<std::string>
getWithLen(const std::vector<std::string> &in, const size_t len) 
{
    std::vector<std::string>ret;
    std::copy_if(in.begin(), in.end(), std::back_inserter(ret),
    [=](std::string s) { return s.size() == len; });
    return ret;
}

int main (void)
{
    std::fstream file("input.txt");
    std::vector<std::vector<std::string>> outputs, signals;
    for (std::string line; getline(file, line);) {
        std::vector<std::string> tmp;
        boost::split(tmp, line, boost::is_any_of("|"));
        signals.push_back(splitBySpacesAndSort(tmp[0]));
        outputs.push_back(splitBySpacesAndSort(tmp[1]));
    }
    std::array<std::string, 10> mapping;
    int counter = 0, sum = 0;
    for (int i = 0; i < signals.size(); ++i) {
        mapping[1] = getWithLen(signals[i], 2)[0];
        mapping[4] = getWithLen(signals[i], 4)[0];
        mapping[7] = getWithLen(signals[i], 3)[0];
        mapping[8] = getWithLen(signals[i], 7)[0];
        std::vector<std::string>lenSix = getWithLen(signals[i], 6);
        removeAndAddMappingIfEq(lenSix, mapping, 9, 4, 4);
        removeAndAddMappingIfEq(lenSix, mapping, 0, 1, 2);
        mapping[6] = lenSix[0];
        std::vector<std::string>lenFive = getWithLen(signals[i], 5);
        removeAndAddMappingIfEq(lenFive, mapping, 2, 9, 4);
        removeAndAddMappingIfEq(lenFive, mapping, 5, 1, 1);
        mapping[3] = lenFive[0];

        int counter = 0;
        for (std::string s : outputs[i]) {
            for (int j = 0; j < mapping.size(); ++j) {
                if (mapping[j] == s) {
                    counter += j;
                    counter *= 10;
                    break;
                }
            }
        }
        sum += counter/10;
    }
    std::cout << sum << '\n';
}