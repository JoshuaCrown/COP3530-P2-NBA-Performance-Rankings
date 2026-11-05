#include "MergeSort.h"

void MergeSort::mergeSort(std::vector<PlayerPerformance>& players,
                          const std::string& stat) {
    if (players.size() < 2) {
        return;
    }
    mergeHelp(players, 0, static_cast<int>(players.size()) - 1, stat);
}

void MergeSort::mergeHelp(std::vector<PlayerPerformance>& players,
                          int left, int right, const std::string& stat) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergeHelp(players, left, mid, stat);
    mergeHelp(players, mid + 1, right, stat);
    merge(players, left, mid, right, stat);
}

void MergeSort::merge(std::vector<PlayerPerformance>& players,
                      int left, int mid, int right,
                      const std::string& stat) {
    std::vector<PlayerPerformance> merged;
    merged.reserve(right - left + 1);

    int leftIndex = left;
    int rightIndex = mid + 1;

    while (leftIndex <= mid && rightIndex <= right) {
        // Take the higher stat first. On a tie, take the left record first.
        if (getStatVal(players[leftIndex], stat) >=
            getStatVal(players[rightIndex], stat)) {
            merged.push_back(players[leftIndex]);
            ++leftIndex;
        } else {
            merged.push_back(players[rightIndex]);
            ++rightIndex;
        }
    }
    while (leftIndex <= mid) {
        merged.push_back(players[leftIndex]);
        ++leftIndex;
    }
    while (rightIndex <= right) {
        merged.push_back(players[rightIndex]);
        ++rightIndex;
    }
    for (int i = left; i <= right; ++i) {
        players[i] = merged[i - left];
    }
}

// Returns an int so the points will go from a decimal to a straight integer
int MergeSort::getStatVal(const PlayerPerformance& player,
                         const std::string& stat) {
    if (stat == "PTS") {
        return static_cast<int>(player.points);
    }
    if (stat == "REB") {
        return static_cast<int>(player.rebounds);
    }
    if (stat == "AST") {
        return static_cast<int>(player.assists);
    }
    return 0;
}