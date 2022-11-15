#ifndef STACK_H
#define STACK_H
#include "cell.h"


class Stack
{
private:
    int size;
    Cell**** array;
public:
    Stack();
    bool empty();
    void pop();
    void push(Cell*** element);
    Cell*** top();
};

#endif // STACK_H
