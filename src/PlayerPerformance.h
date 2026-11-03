#pragma once
#include <string>

// One row of games_details.csv: a single player's stat line for one game.
struct PlayerPerformance {
    std::string playerName;
    int playerId = 0;
    int gameId = 0;
    std::string team;
    float points = 0.0f;
    float rebounds = 0.0f;
    float assists = 0.0f;
};
