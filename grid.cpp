#include <iostream>
#include <fstream>
#include "grid.h"

using namespace std;


bool Grid::search_3_in_row()
{
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            Cell* cll = array[i][j];
            int num = cll->get_number();
            bool flag = true;
            for (int k = j + 1; k < j + 3; k++){
                if (k >= size){
                    flag = false;
                    break;
                }
                if (array[i][k]->get_number() != num){
                    flag = false;
                    break;
                }
            }
            if (flag){
                if (!cll->to_shade()) return false;
                cll->to_freeze();
                Cell* adjacent = array[i][j + 1];
                if (!adjacent->to_lighten()) return false;
                adjacent->to_freeze();
                adjacent = array[i][j + 2];
                if (!adjacent->to_shade()) return false;
                adjacent->to_freeze();
            }
            flag = true;
            for (int k = i + 1; k < i + 3; k++){
                if (k >= size){
                    flag = false;
                    break;
                }
                if (array[k][j]->get_number() != num){
                    flag = false;
                    break;
                }
            }
            if (flag){
                if (!cll->to_shade()) return false;
                cll->to_freeze();
                Cell* adjacent = array[i + 1][j];
                if (!adjacent->to_lighten()) return false;
                adjacent->to_freeze();
                adjacent = array[i + 2][j];
                if (!adjacent->to_shade()) return false;
                adjacent->to_freeze();
            }
        }
    }
    return true;
}
bool Grid::search_2_in_row()
{
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            int num = array[i][j]->get_number();
            if (j + 1 < size){
                if (array[i][j + 1]->get_number() == num){
                    for (int k = 0; k < size; k++){
                        if (k < j - 1 or k > j + 2){
                            Cell* cll = array[i][k];
                            if (cll->get_number() == num){
                                if (!cll->to_shade()) return false;
                                cll->to_freeze();
                            }
                        }
                    }
                }
            }
            if (i + 1 < size){
                if (array[i + 1][j]->get_number() == num){
                    for (int k = 0; k < size; k++){
                        if (k < i - 1 or k > i + 2){
                            Cell* cll = array[k][j];
                            if (cll->get_number() == num){
                                if (!cll->to_shade()) return false;
                                cll->to_freeze();
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}
bool Grid::search_for_identical_adjacent()
{
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            Cell* cll = array[i][j];
            if (j - 1 >= 0 and j + 1 < size){
                if (array[i][j - 1]->get_number() == array[i][j + 1]->get_number()){
                    if (!cll->to_lighten()) return false;
                    cll->to_freeze();
                }
            }
            if (i - 1 >= 0 and i + 1 < size){
                if (array[i - 1][j]->get_number() == array[i + 1][j]->get_number()){
                    if (!cll->to_lighten()) return false;
                    cll->to_freeze();
                }
            }
        }
    }
    return true;
}
Grid::Grid()
{
    size = 0;
    array = nullptr;
}
int Grid::in_file(char* path)
{
    fstream file(path, ios::in);
    if (!file){
        return 1;
    }
    if (!(file >> size)){
        return 2;
    }
    array = new Cell** [size];
    for (int i = 0; i < size; i++){
        array[i] = new Cell* [size];
        for (int j = 0; j < size; j++){
            int num;
            if (!(file >> num)){
                return 2;
            }
            array[i][j] = new Cell(num, i * size + j);
        }
    }
    file.close();
    return 0;
}
void Grid::print()
{
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            Cell* cll = array[i][j];
            if (cll->is_frozen()){
                cout << "$";
            }
            if (cll->is_shaded()){
                cout << "#";
            }
            cout << cll->get_number() << " ";
        }
        cout << endl;
    }
    cout << endl;
}
bool Grid::solve()
{
    if (!search_3_in_row()) return false;
    if (!search_2_in_row()) return false;
    if (!search_for_identical_adjacent()) return false;
    return true;
}
