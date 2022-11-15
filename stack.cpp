#include "stack.h"

Stack::Stack()
{
    size = 0;
    array = nullptr;
}
bool Stack::empty()
{
    if (size == 0)
        return true;
    else
        return false;
}
void Stack::pop()
{
    if (size == 0){
        throw;
    }
    if (size == 1){
        size = 0;
        delete [] array;
        return;
    }
    Cell**** temp = new Cell*** [size - 1];
    for (int i = 0; i < size - 1; i++){
        temp[i] = array[i];
    }
    delete [] array;
    size--;
    array = new Cell*** [size];
    for (int i = 0; i < size; i++){
        array[i] = temp[i];
    }
    delete [] temp;
}
void Stack::push(Cell*** element)
{
    Cell**** temp = new Cell*** [size];
    for (int i = 0; i < size; i++){
        temp[i] = array[i];
    }
    delete [] array;
    size++;
    array = new Cell*** [size];
    for (int i = 0; i < size - 1; i++){
        array[i] = temp[i];
    }
    array[size - 1] = element;
    delete [] temp;
}
Cell*** Stack::top()
{
    if (size > 0) return array[size - 1];
    else throw;
}
