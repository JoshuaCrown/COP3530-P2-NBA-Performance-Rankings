#pragma once
#include <string>
#include <vector>
#include "PlayerPerformance.h"

// Reads a CSV with columns:
// PLAYER_NAME,PLAYER_ID,GAME_ID,TEAM_ABBREVIATION,PTS,REB,AST
// Returns an empty vector if the file can't be opened.
std::vector<PlayerPerformance> readCSV(const std::string& filePath);
