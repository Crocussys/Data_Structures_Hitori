#include <iostream>
#include <fstream>
#include "grid.h"

using namespace std;


bool Grid::search_3_in_row()
{
    Cell*** array = options.top();
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
    Cell*** array = options.top();
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
    Cell*** array = options.top();
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
bool Grid::search_squares()
{
    Cell*** array = options.top();
    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - 1; j++){
            Cell* top_left = array[i][j];
            int num = top_left->get_number();
            Cell* top_right = array[i][j + 1];
            Cell* bottom_left = array[i + 1][j];
            Cell* bottom_right = array[i + 1][j + 1];
            if (top_right->get_number() == num and
                    bottom_left->get_number() == num and
                    bottom_right->get_number() == num){
                if (top_left->is_frozen()){
                    if (top_left->is_shaded()){
                        if (!bottom_right->to_shade()) return false;
                        bottom_right->to_freeze();
                        if (!top_right->to_lighten()) return false;
                        top_right->to_freeze();
                        if (!bottom_left->to_lighten()) return false;
                        bottom_left->to_freeze();
                        continue;
                    }else{
                        if (!bottom_right->to_lighten()) return false;
                        bottom_right->to_freeze();
                        if (!top_right->to_shade()) return false;
                        top_right->to_freeze();
                        if (!bottom_left->to_shade()) return false;
                        bottom_left->to_freeze();
                        continue;
                    }
                }
                if (top_right->is_frozen()){
                    if (top_right->is_shaded()){
                        if (!bottom_right->to_lighten()) return false;
                        bottom_right->to_freeze();
                        if (!top_left->to_lighten()) return false;
                        top_left->to_freeze();
                        if (!bottom_left->is_shaded()) return false;
                        bottom_left->to_freeze();
                        continue;
                    }else{
                        if (!bottom_right->to_shade()) return false;
                        bottom_right->to_freeze();
                        if (!top_left->to_shade()) return false;
                        top_left->to_freeze();
                        if (!bottom_left->to_lighten()) return false;
                        bottom_left->to_freeze();
                        continue;
                    }
                }
                if (bottom_left->is_frozen()){
                    if (bottom_left->is_shaded()){
                        if (!bottom_right->to_lighten()) return false;
                        bottom_right->to_freeze();
                        if (!top_right->to_shade()) return false;
                        top_right->to_freeze();
                        if (!top_left->to_lighten()) return false;
                        top_left->to_freeze();
                        continue;
                    }else{
                        if (!bottom_right->to_shade()) return false;
                        bottom_right->to_freeze();
                        if (!top_right->to_lighten()) return false;
                        top_right->to_freeze();
                        if (!top_left->to_shade()) return false;
                        top_left->to_freeze();
                        continue;
                    }
                }
                if (bottom_right->is_frozen()){
                    if (bottom_right->is_shaded()){
                        if (!top_right->to_lighten()) return false;
                        top_right->to_freeze();
                        if (!top_left->is_shaded()) return false;
                        top_left->to_freeze();
                        if (!bottom_left->to_lighten()) return false;
                        bottom_left->to_freeze();
                        continue;
                    }else{
                        if (!top_right->to_shade()) return false;
                        top_right->to_freeze();
                        if (!top_left->to_lighten()) return false;
                        top_left->to_freeze();
                        if (!bottom_left->to_shade()) return false;
                        bottom_left->to_freeze();
                        continue;
                    }
                }
                top_left->to_shade();
                top_left->to_freeze();
                top_right->to_lighten();
                top_right->to_freeze();
                bottom_left->to_lighten();
                bottom_left->to_freeze();
                bottom_right->to_shade();
                bottom_right->to_freeze();
                Cell*** new_option = new Cell** [size];
                for (int k = 0; k < size; k++){
                    new_option[k] = new Cell* [size];
                    for (int l = 0; l < size; l++){
                        new_option[k][l] = array[k][l];
                    }
                }
                new_option[i][j]->to_lighten();
                new_option[i][j]->to_freeze();
                new_option[i][j + 1]->to_shade();
                new_option[i][j + 1]->to_freeze();
                new_option[i + 1][j]->to_shade();
                new_option[i + 1][j]->to_freeze();
                new_option[i + 1][j + 1]->to_lighten();
                new_option[i + 1][j + 1]->to_freeze();
                options.push(new_option);
                array = new_option;
            }
        }
    }
    return true;
}
bool Grid::freezing_light()
{
    Cell*** array = options.top();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            Cell* cll = array[i][j];
            Cell* adjacent;
            if (cll->is_frozen() and cll->is_shaded()){
                if (i + 1 < size){
                    adjacent = array[i + 1][j];
                    if (!adjacent->to_lighten()) return false;
                    adjacent->to_freeze();
                }
                if (i - 1 >= 0){
                    adjacent = array[i - 1][j];
                    if (!adjacent->to_lighten()) return false;
                    adjacent->to_freeze();
                }
                if (j + 1 < size){
                    adjacent = array[i][j + 1];
                    if (!adjacent->to_lighten()) return false;
                    adjacent->to_freeze();
                }
                if (j - 1 >= 0){
                    adjacent = array[i][j - 1];
                    if (!adjacent->to_lighten()) return false;
                    adjacent->to_freeze();
                }
            }
        }
    }
    return true;
}
bool Grid::shading(bool* flag)
{
    Cell*** array = options.top();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            Cell* cll = array[i][j];
            if (cll->is_frozen() and !cll->is_shaded()){
                int num = cll->get_number();
                for (int k = 0; k < size; k++){
                    if (k != i){
                        Cell* cll2 = array[k][j];
                        if (cll2->get_number() == num){
                            bool temp = cll2->is_shaded();
                            if (!cll2->to_shade()) return false;
                            cll2->to_freeze();
                            if (cll2->is_shaded() == temp)
                                *flag = true;
                        }
                    }
                }
                for (int k = 0; k < size; k++){
                    if (k != j){
                        Cell* cll2 = array[i][k];
                        if (cll2->get_number() == num){
                            bool temp = cll2->is_shaded();
                            if (!cll2->to_shade()) return false;
                            cll2->to_freeze();
                            if (cll2->is_shaded() == temp)
                                *flag = true;
                        }
                    }
                }
            }
        }
     }
    return true;
}
bool Grid::main_move(){
    Cell*** array = options.top();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            Cell* cll = array[i][j];
            if (!cll->is_frozen() and !cll->is_shaded()){
                int num = cll->get_number();
                for (int k = 0; k < size; k++){
                    if (k != i){
                        Cell* cll2 = array[k][j];
                        if (!cll2->is_frozen() and
                                !cll2->is_shaded() and
                                cll2->get_number() == num){
                            Cell*** new_option = new Cell** [size];
                            for (int m = 0; m < size; m++){
                                new_option[m] = new Cell* [size];
                                for (int l = 0; l < size; l++){
                                    new_option[m][l] = array[m][l];
                                }
                            }
                            new_option[i][j]->to_shade();
                            new_option[i][j]->to_freeze();
                            options.push(new_option);
                            cll2->to_shade();
                            cll2->to_freeze();
                            return true;
                        }
                    }
                }
                for (int k = 0; k < size; k++){
                    if (k != j){
                        Cell* cll2 = array[i][k];
                        if (!cll2->is_frozen() and
                                !cll2->is_shaded() and
                                cll2->get_number() == num){
                            Cell*** new_option = new Cell** [size];
                            for (int m = 0; m < size; m++){
                                new_option[m] = new Cell* [size];
                                for (int l = 0; l < size; l++){
                                    new_option[m][l] = array[m][l];
                                }
                            }
                            new_option[i][j]->to_shade();
                            new_option[i][j]->to_freeze();
                            options.push(new_option);
                            cll2->to_shade();
                            cll2->to_freeze();
                            return true;
                        }
                    }
                }
            }
        }
     }
    return false;
}
bool Grid::is_completely_frozen()
{
    Cell*** array = options.top();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (!array[i][j]->is_frozen())
                return false;
        }
     }
    return true;
}
Grid::Grid()
{
    size = 0;
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
    Cell*** array = new Cell** [size];
    for (int i = 0; i < size; i++){
        array[i] = new Cell* [size];
        for (int j = 0; j < size; j++){
            int num;
            if (!(file >> num)){
                delete [] array;
                return 2;
            }
            array[i][j] = new Cell(num, i * size + j);
        }
    }
    file.close();
    options.push(array);
    return 0;
}
void Grid::print()
{
    Cell*** array = options.top();
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            Cell* cll = array[i][j];
            if (cll->is_frozen()){
                cout << "$";
            }else{
                cout << " ";
            }
            if (cll->is_shaded()){
                cout << "#";
            }else{
                cout << " ";
            }
            cout << cll->get_number() << "|";
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
    if (!search_squares()) return false;
    while (!options.empty()){
        bool is_change = false;
        if (!freezing_light()){
            options.pop();
            continue;
        }
        if (!shading(&is_change)){
            options.pop();
            continue;
        }
        if (!is_change){
            if (!main_move()){
                return true;
            }
            print();
        }
    }
    return false;
}
