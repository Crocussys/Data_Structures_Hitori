#include <iostream>
#include "grid.h"

using namespace std;

void usage()
{
    cout << "Hitori [path]" << endl << endl;
    cout << "path - Путь до файла с головоломкой" << endl;
    cout << endl << "Not enought arguments" << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        usage();
        return 1;
    }
    Grid grid;
    int err = grid.in_file(argv[1]);
    if (err == 1){
        cout << "File open error" << endl;
        return 2;
    }
    if (err == 2){
        cout << "Value error" << endl;
        return 3;
    }
    if (!grid.solve()){
        cout << "Задача не имеет решения" << endl;
        return 4;
    }
    grid.print();
    return 0;
}
