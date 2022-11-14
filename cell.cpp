#include "cell.h"

Cell::Cell()
{
    id = -1;
    number = 0;
    shaded = false;
    frozen = false;
}
Cell::Cell(int num, int idnt)
{
    id = idnt;
    number = num;
    shaded = false;
    frozen = false;
}
int Cell::get_number()
{
    return number;
}
bool Cell::to_shade()
{
    if (shaded){
        return true;
    }
    if (frozen){
        return false;
    }else{
        shaded = true;
        return true;
    }
}
bool Cell::to_lighten()
{
    if (!shaded){
        return true;
    }
    if (frozen){
        return false;
    }else{
        shaded = false;
        return true;
    }
}
void Cell::to_freeze()
{
    frozen = true;
}
bool Cell::is_shaded()
{
    return shaded;
}
bool Cell::is_frozen()
{
    return frozen;
}
