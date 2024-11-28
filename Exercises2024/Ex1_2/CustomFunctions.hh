//Cameron Cassells
//20/11/2024


#pragma once 
#include <fstream>
#include <vector>
#include <utility>
#include <string>

using namespace std;

// Function for reading coordinates from a .txt file
vector <pair<float,float>> readCoords(string& filename);

// Function to evaluate the magnitude of each vector
float Magnitude(const pair<float, float>& coord);

// Overloaded printing functions
void print(const vector<pair<float, float>>& coords, int n);
void print(const vector<float> &magnitudes);

// Function to read coordinate errors from a.txt file
vector<float> readErrors(const string& filename);

// Function to perform linear regression with chi-squared fit
void LinearRegression(const vector<pair<float, float>>& coords, const vector<float>& errors, float& m, float& c);