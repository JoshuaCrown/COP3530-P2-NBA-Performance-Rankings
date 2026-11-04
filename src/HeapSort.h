#pragma once
#include <vector>
#include "PlayerPerformance.h"
using namespace std;

class HeapSort {
public:
    static void heapSort(vector<PlayerPerformance>& players, const string& stat);
public:
    static void heapify(vector<PlayerPerformance>& players, int n, int i, const string& stat);
    static int getStatVal(const PlayerPerformance& player, const string& stat);
};