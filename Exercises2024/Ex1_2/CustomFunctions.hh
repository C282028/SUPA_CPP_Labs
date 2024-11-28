//Cameron Cassells
//20/11/2024


#pragma once 
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>

using namespace std;

// Function for reading coordinates from a .txt file
vector <pair<float,float>> readCoords(string& filename);

// Function to read coordinate errors from a.txt file
vector<float> readErrors(const string& filename);


// Overloaded printing functions
void print(const vector<pair<float, float>>& coords, int n);
void print(const vector<float> &magnitudes);


// Function to evaluate the magnitude of each vector
float Magnitude(const pair<float, float>& coord);

// Function to perform linear regression with chi-squared fit
void LinearRegression(const vector<pair<float, float>>& coords, const vector<float>& errors, float& m, float& c, float& chi2_per_ndf);

// Function to calculate x^y for each data point, with y rounded to nearest whole number
float calculateXY(float x, float y);

// Overloaded saving Functions
void saveToFile(const vector<float>& data, const string& filename); //magnitudes
void saveToFile(const string& equation, float chi2_per_ndf, const string& filename); //linear regression and Chi-squared/NDF
void saveToFile(const vector<pair<float, float>>& data, const string& filename); //x^y calculations