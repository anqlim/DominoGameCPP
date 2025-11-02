#ifndef RECORDS_H
#define RECORDS_H
#include "parameters.h"

class Records {
private:

public:
    Records();
    void manage(State& state, Result& res);
    void draw();
};

#endif
