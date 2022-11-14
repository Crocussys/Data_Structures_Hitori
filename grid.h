#ifndef GRID_H
#define GRID_H
#include "cell.h"


class Grid
{
private:
    int size;
    Cell*** array;

    bool search_3_in_row();
    bool search_2_in_row();
    bool search_for_identical_adjacent();
public:
    Grid();
    int in_file(char* path);
    void print();
    bool solve();
};

#endif // GRID_H
