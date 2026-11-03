#include "CSVReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<PlayerPerformance> readCSV(const std::string& filePath) {
    std::vector<PlayerPerformance> performances;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: could not open " << filePath << std::endl;
        return performances;
    }

    std::string line;
    std::getline(file, line); // skip header row

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back(); // handle Windows line endings
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, playerId, gameId, team, pts, reb, ast;
        std::getline(ss, name, ',');
        std::getline(ss, playerId, ',');
        std::getline(ss, gameId, ',');
        std::getline(ss, team, ',');
        std::getline(ss, pts, ',');
        std::getline(ss, reb, ',');
        std::getline(ss, ast, ',');

        try {
            PlayerPerformance p;
            p.playerName = name;
            p.playerId = std::stoi(playerId);
            p.gameId = std::stoi(gameId);
            p.team = team;
            p.points = std::stof(pts);
            p.rebounds = std::stof(reb);
            p.assists = std::stof(ast);
            performances.push_back(p);
        } catch (const std::exception&) {
            // skip malformed rows
        }
    }

    return performances;
}
