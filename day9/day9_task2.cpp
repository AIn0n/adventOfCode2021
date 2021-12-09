#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>

bool checkNeighbor(const std::vector<int> heatmap, int mx, int my, int x, int y, int curr) {
    if (x >= mx || y >= my || y < 0 || x < 0) return true;
    return curr < heatmap[x + y * mx];
}

template<typename T, typename E>
bool contain(const T &c, E e)
{
    return std::find(c.begin(), c.end(), e) != c.end();
}

int checkBasin(
 const std::vector<int> heatmap, 
 int mx,    int my, 
 int x,     int y, 
 int prev,  std::vector<std::pair<int, int>> &checked) {
    const int curr = heatmap[x + y * mx];
    if (x >= mx || y >= my || y < 0 || x < 0 || curr > 8 || contain(checked, std::pair<int,int>{x, y}))
        return 0;
    if (prev != -1 && prev >= curr)
        return 0;
    checked.push_back(std::pair<int, int>{x, y});
    return 1 +
        checkBasin(heatmap, mx, my, x-1, y, curr, checked) +
        checkBasin(heatmap, mx, my, x+1, y, curr, checked) +
        checkBasin(heatmap, mx, my, x, y-1, curr, checked) +
        checkBasin(heatmap, mx, my, x, y+1, curr, checked);
}

int GetBasin(std::vector<int> heatmap, int mx, int my, int x, int y)
{
    std::vector<std::pair<int, int>> checked;
    return checkBasin(heatmap, mx, my, x, y, -1, checked);
}

bool isLowest(const std::vector<int> heatmap, int mx, int my, int x, int y) {
    int curr = heatmap[x + y * mx];
    return
        checkNeighbor(heatmap, mx, my, x-1, y, curr) &&
        checkNeighbor(heatmap, mx, my, x+1, y, curr) &&
        checkNeighbor(heatmap, mx, my, x, y-1, curr) &&
        checkNeighbor(heatmap, mx, my, x, y+1, curr);
}

int main (void)
{
    std::fstream file("input.txt");
    std::vector<int> heatmap;
    int max_x = 0, max_y = 0;
    for (std::string line; getline(file, line);) {
        max_x = line.size();
        max_y ++;
        for (const char c : line)
            if (c >= '0' && c <= '9')
                heatmap.push_back((int)(c - '0'));
    }
    std::vector<int> basins;
    for (int y = 0; y < max_y; ++y)
        for (int x = 0; x < max_x; ++x)
            if (isLowest(heatmap, max_x, max_y, x, y))
                basins.push_back(GetBasin(heatmap, max_x, max_y, x, y));
    
    std::sort(basins.begin(), basins.end());
    const int result = std::accumulate(basins.end() - 3, basins.end(), 1, 
    [](int x, int y){
        return x * y;
    });
    std::cout << result << '\n';
}