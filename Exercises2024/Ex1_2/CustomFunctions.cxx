//Cameron Cassells
//20/11/2024


#include <iostream>
#include <sstream>
#include "CustomFunctions.hh"
#include <iomanip>
#include <cmath>

using namespace std;

// Function to read coordinates from a file defined in AnalysData.cxx
vector <pair<float,float>> readCoords(string& filename)
{
    // creates a vecotor from a pair of floats
    vector <pair<float,float>> coords;

    // read variables 
    string line1, line2;
    float x, y;
    ifstream myInput(filename);

    // Finds and opens txt file, checks if successful, then proceeds.
	if (myInput.fail())
	{
		cout << "Error: Unable to open the file '" << filename << "'. Ensure the file exists and is readable." << endl;
		return coords;
	}

        // Skips the header line (non float values)
        string header;
        getline(myInput, header);

        // Gets the objects from stream and assigns it a string
        while (getline(myInput, line1, ',') && getline(myInput, line2))
        {   
            // Iterates through each line, converts the string to a float then stores them in the vector.
            x = stof(line1);
            y = stof(line2);
            coords.emplace_back(x,y);
        }
    myInput.close();
    return coords;
} //readCoords


// Function to evaluate the magnitude of each vector
float Magnitude(const pair<float, float>& coord)
{
	return sqrt(coord.first * coord.first + coord.second * coord.second);
} //Magnitude


// Overloaded print function for coordinates
void print(const vector<pair<float, float>>& coords, int n)
{
	if (n > coords.size())
	{
		cout << "***Warning*** Requested " << n << " is larger than total coordinates. Printing the first 5." << endl;
		n = min(5, static_cast<int>(coords.size()));
	}

	for (int i = 0; i < n; ++i)
	{
		cout << fixed << setprecision(3) << "(" << coords[i].first << ", " << coords[i].second << ")" << endl;
	}
	cout << n << " coordinates printed." << endl;
} //printCoords


// Overloaded print function for magnitudes
void print(const vector<float>& magnitudes)
{
	for (size_t i = 0; i < magnitudes.size(); ++i)
	{
		cout << "Coordinate " << i + 1 << ": " << fixed << setprecision(3) << magnitudes[i] << endl;
	}
	cout << magnitudes.size() << " magnitudes printed." << endl;
}


// Function to read error values 
vector<float> readErrors(const string& errorPairs)
{
    // creates a vecotor from a pair of floats
    vector <float> errors;

    // read variables 
    string line1, line2;
	float y;
	ifstream myInput(errorPairs);

    // Finds and opens txt file, checks if successful, then proceeds.
	if (myInput.fail())
	{
		cout << "Error: Unable to open the file '" << errorPairs << "'. Ensure the file exists and is readable." << endl;
		return errors;
	}
	
	// Skip the header line
    string header;
    getline(myInput, header);

	// Gets the objects from stream and assigns it a string
    while (getline(myInput, line1, ',') && getline(myInput, line2))
	{
		// Convert y (second value) to float and store in errors
		y = stof(line2);
		errors.push_back(y);
	}
	return errors;
}



// Function to perform Least squares method
void LinearRegression(const vector<pair<float, float>>& coords, const vector<float>& errors, float& m, float& c)
{
    // Linear reggression variables 
    size_t n = coords.size();
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    // iterates through each vector pair and computes sums
    for (const auto& coord : coords)
    {
        float x = coord.first;
        float y = coord.second;
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2 += x * x;
    }

 	// Calculate slope (m) and intercept (c)
	float denominator = n * sum_x2 - sum_x * sum_x;
	m = (n * sum_xy - sum_x * sum_y) / denominator;
	c = (sum_y - m * sum_x) / n;

	// Compute chi-squared
	float chi2 = 0;
	for (size_t i = 0; i < n; ++i)
	{
		float x = coords[i].first;
		float y = coords[i].second;
		float sigma = errors[i];
		float y_pred = m * x + c;
		chi2 += pow((y - y_pred) / sigma, 2);
	}

	// Degrees of freedom: NDF = n - p (p = 2 for slope and intercept)
	int ndf = n - 2;
	float chi2_per_ndf = chi2 / ndf;


	// Output results to console
	ostringstream equationStream;
	equationStream << "y = " << m << "x + " << c;
	string equation = equationStream.str();
	cout << "Linear Regression Equation: " << equation << endl;
	cout << "Chi-squared / NDF: " << chi2_per_ndf << endl;

	// Write the equation to a file
	string filename = "Outputs/Linear_Regression_Equations.txt";
	ofstream outStream(filename);

	if (!outStream.is_open())
	{
		cout << "Error: Unable to create or write to the file '" << filename << endl;
	}
	else
	{
		outStream << equation << endl;
		outStream << chi2_per_ndf << endl;
		cout << "Output file: " << filename << " opened successfully!" << endl;
	}

	outStream.close();
}