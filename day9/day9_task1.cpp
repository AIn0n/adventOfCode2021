#include <iostream>
#include <vector>
#include <fstream>

bool checkNeighbor(const std::vector<int> heatmap, int mx, int my, int x, int y, int curr) {
    if (x >= mx || y >= my || y < 0 || x < 0) return true;
    return curr < heatmap[x + y * mx];
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
    int sum = 0;
    for (int y = 0; y < max_y; ++y)
        for (int x = 0; x < max_x; ++x)
            if (isLowest(heatmap, max_x, max_y, x, y))
                sum += heatmap[x + y * max_x] + 1;
   std::cout << sum << '\n';
}