#include <fstream>
#include <iostream>
#include <array>

#define MAX_X 10
#define MAX_Y 10

using namespace std;

class Octo {
public:
    uint8_t energy = 0;
    bool flashed = false;

    bool is_flashing(void) {
        flashed = energy > 9;
        return flashed;
    }
};

void
checkAndIncNeighbor(array<Octo, MAX_X * MAX_Y> &d, int x, int y)
{
    if (x > MAX_X || y > MAX_Y || x < 0 || y < 0) return;
    d[x + y * MAX_X].energy++;
}

bool
is_flashing(array<Octo, MAX_X * MAX_Y> &d, int x, int y)
{
    return d[x + y * MAX_X].energy > 9;
}

int main (void) {
    array<Octo, MAX_X * MAX_Y> d;
    fstream f("input.txt");
    Octo *ptr = d.data();
    for (string s; getline(f, s);)
        for (char c : s)
            (ptr++)->energy = c;

    for (Octo &o : d)
        o.energy++;

    for (int y = 0; y < MAX_Y; ++y)
        for (int x = 0; x < MAX_X; ++x) {
            int idx = x + y * MAX_X;
            if (d[idx].is_flashing()) {
                checkAndIncNeighbor(d, x + 1, y + 1);
                checkAndIncNeighbor(d, x - 1, y - 1);
                checkAndIncNeighbor(d, x + 1, y - 1);
                checkAndIncNeighbor(d, x - 1, y + 1);
                checkAndIncNeighbor(d, x + 1, y);
                checkAndIncNeighbor(d, x - 1, y);
                checkAndIncNeighbor(d, x, y + 1);
                checkAndIncNeighbor(d, x, y - 1);
            }
        }
    for (const Octo &o : d)
        std::cout << o.energy << ' ';
}