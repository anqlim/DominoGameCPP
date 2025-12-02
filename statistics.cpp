#include "statistics.h"

const std::string Statistics::FILE_NAME = "statistics.json";

Statistics::Statistics() {
    load();
}

void Statistics::save() {
    json data;
    data["record"] = record;
    data["points"] = points;
    data["gamesPlayed"] = games;
    data["wins"] = wins;
    data["winningPercentage"] = winningPercentage;

    std::ofstream file(FILE_NAME);
    file << data.dump(4);
}

void Statistics::load() {
    if (std::filesystem::exists(FILE_NAME)) {
        std::ifstream file(FILE_NAME);
        if (!file.is_open()) {
            record = points = games = wins = winningPercentage = 0;
            save();
            return;
        }

        json data;
        file >> data;

        if (file.fail() || data.is_discarded()) {
            std::cerr << "Ошибка чтения " << FILE_NAME << ". Создаём новый файл.\n";
            record = points = games = wins = winningPercentage = 0;
            save();
            return;
        }

        record = data.value("record", 0);
        points = data.value("points", 0);
        games = data.value("gamesPlayed", 0);
        wins = data.value("wins", 0);
        winningPercentage = data.value("winningPercentage", 0);
    }
    else {
        record = points = games = wins = winningPercentage = 0;
        save();
    }
}

void Statistics::recalculatePercentage() {
    if (games == 0)
        winningPercentage = 0;
    else
        winningPercentage = (wins * 100) / games;
}