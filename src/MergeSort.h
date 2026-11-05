#pragma once
#include <vector>
#include <string>
#include "PlayerPerformance.h"
using namespace std;

class MergeSort {
public:
    static void mergeSort(vector<PlayerPerformance>& players, const string& stat);
private:
    static void mergeHelp(vector<PlayerPerformance>& players, int left, int right, const string& stat);
    static void merge(vector<PlayerPerformance>& players, int left, int mid, int right, const string& stat);
    static int getStatVal(const PlayerPerformance& player, const string& stat);
};