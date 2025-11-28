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
        try {
            std::ifstream file(FILE_NAME);
            json data;
            file >> data;

            record = data.value("record", 0);
            points = data.value("points", 0);
            games = data.value("gamesPlayed", 0);
            wins = data.value("wins", 0);
            winningPercentage = data.value("winningPercentage", 0);
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка чтения " << FILE_NAME << ": " << e.what()
                      << ". Создаём новый файл.\n";
            record = points = games = wins = winningPercentage = 0;
            save();
        }
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