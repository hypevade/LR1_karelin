#pragma once

#include <vector>
#include <string>
#include "lr1.cpp"
using namespace std;

tuple<vector<float>, float, vector<error>> getProductOfMultiples(const vector<float>& arr, int multiple);
class error;