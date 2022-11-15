#ifndef GRID_H
#define GRID_H
#include "cell.h"
#include "stack.h"


class Grid
{
private:
    int size;
    Stack options;

    bool search_3_in_row();
    bool search_2_in_row();
    bool search_for_identical_adjacent();
    bool search_squares();
    bool freezing_light();
    bool shading(bool* flag);
    bool main_move();

    bool is_completely_frozen();
public:
    Grid();
    int in_file(char* path);
    void print();
    bool solve();
};

#endif // GRID_H
