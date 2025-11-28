#ifndef FIELD_H
#define FIELD_H
#include "list.h"
#include "parameters.h"

class Field:public List {
public:
    Field copy();
    void draw();
};

#endif
