#include "HeapSort.h"
#include <algorithm>
using namespace std;
int HeapSort::getStatVal(const PlayerPerformance& player, const string& stat) {
    if (stat == "PTS") {
        return player.points;
    }
    if (stat == "REB") {
        return player.rebounds;
    }
    if (stat == "AST") {
        return player.assists;
    }
    return 0;
}
void HeapSort::heapify(vector<PlayerPerformance>& players, int n, int i, const string& stat) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && getStatVal(players[left], stat) < getStatVal(players[smallest], stat)) {
        smallest = left;
    }

    if (right < n && getStatVal(players[right], stat) < getStatVal(players[smallest], stat)) {
        smallest = right;
    }
    if (smallest != i) {
        swap(players[i], players[smallest]);
        heapify(players, n, smallest, stat);
    }
}
void HeapSort::heapSort(vector<PlayerPerformance>& players, const string& stat) {
    int n = players.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(players, n, i, stat);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(players[0], players[i]);
        heapify(players, i, 0, stat);
    }
}

