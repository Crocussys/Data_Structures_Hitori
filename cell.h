#ifndef CELL_H
#define CELL_H


class Cell
{
private:
    int id;
    int number;
    bool shaded;
    bool frozen;
public:
    Cell();
    Cell(int num, int idnt);
    int get_number();
    bool to_shade();
    bool to_lighten();
    void to_freeze();
    bool is_shaded();
    bool is_frozen();
};

#endif // CELL_H
