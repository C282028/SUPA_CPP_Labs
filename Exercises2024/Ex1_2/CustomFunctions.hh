//Cameron Cassells
//20/11/2024


#pragma once 
#include <fstream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

// Function for reading coordinates from a .txt file
vector <pair<float,float>> readCoords(string& filename);

// Function to evaluate the magnitude of each vector
float Magnitude(const pair<float, float>& coord);

// Function for printing coordinates read from the .txt file
void printCoords(vector<pair<float, float>>& coords, int n);

// Function to perform linear regression 
void LinearRegression(const vector<pair<float, float>>& coords, float& m, float& c);