#ifndef RECORDS_H
#define RECORDS_H
#include "statistics.h"
#include "parameters.h"
#include "button.h"

class Records {
public:
    Statistics statistics;
    Button exit;

    Records();
    void manage(State& state, Result& res);
    void draw(Result& res);
};

#endif
