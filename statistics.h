#ifndef STATISTICS_H
#define STATISTICS_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Statistics {
public:
    static const std::string FILE_NAME;
    int record;
    int points;
    int winningPercentage;
    int games;
    int wins;

    Statistics();
    void save();
    void load();
    void recalculatePercentage();
};

#endif
