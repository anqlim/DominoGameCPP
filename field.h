#ifndef FIELD_H
#define FIELD_H
#include "list.h"

class Field {
public:
    Field();
    ~Field();
    Node* head;
    Node* tail;
    void draw();
};

#endif
