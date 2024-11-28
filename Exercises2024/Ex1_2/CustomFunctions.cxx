//Cameron Cassells
//20/11/2024


#include <iostream>
#include <sstream>
#include "CustomFunctions.hh"
#include <iomanip>
#include <cmath>

using namespace std;

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

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

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

// Function to evaluate the magnitude of each vector
float Magnitude(const pair<float, float>& coord)
{
	return sqrt(coord.first * coord.first + coord.second * coord.second);
} //Magnitude

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

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

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

// Overloaded print function for magnitudes
void print(const vector<float>& magnitudes)
{
	for (size_t i = 0; i < magnitudes.size(); ++i)
	{
		cout << "Coordinate " << i + 1 << ": " << fixed << setprecision(3) << magnitudes[i] << endl;
	}
	cout << magnitudes.size() << " magnitudes printed." << endl;
}

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

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

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

// Function to perform Least squares method
void LinearRegression(const vector<pair<float, float>>& coords, const vector<float>& errors, float& m, float& c, float& chi2_per_ndf)
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
	chi2_per_ndf = chi2 / ndf;


	// Output results to console
	ostringstream equationStream;
	equationStream << "y = " << m << "x + " << c;
	string equation = equationStream.str();
	cout << "Linear Regression Equation: " << equation << endl;
	cout << "Chi-squared / NDF: " << chi2_per_ndf << endl;
}

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

// Function to calculate x^y for each data point with y rounded to the nearest whole number
float calculateXY(float x, float y)
{
	// Round y to the nearest whole number
	int exponent = static_cast<int>(round(y));

	// Calculate x^y for positive exponents
	float result = 1;
	for (int i = 0; i < exponent; ++i)
		result *= x;

	return result;
}

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

// Overloaded Function to save magnitudes to a file
void saveToFile(const vector<float>& data, const string& filename)
{
    ofstream outFile("Outputs/" + filename);

    if (!outFile.is_open())
    {
        cout << "Error: Unable to create or write to the file '" << filename << "'." << endl;
        return;
    }

    for (const auto& value : data)
        outFile << fixed << setprecision(3) << value << endl;

    outFile.close();
    cout << "Magnitudes successfully saved to 'Outputs/" << filename << "'." << endl;
}

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

// Overloaded Function to save equations and Chi-squared/NDF to a file
void saveToFile(const string& equation, float chi2_per_ndf, const string& filename)
{
    ofstream outFile("Outputs/" + filename);

    if (!outFile.is_open())
    {
        cout << "Error: Unable to create or write to the file '" << filename << "'." << endl;
        return;
    }

    outFile << equation << endl;
    outFile << "Chi-squared / NDF: " << fixed << setprecision(3) << chi2_per_ndf << endl;

    outFile.close();
    cout << "Regression results successfully saved to 'Outputs/" << filename << "'." << endl;
}

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//

// Overloaded Function to save x^y calculations to a file
void saveToFile(const vector<pair<float, float>>& data, const string& filename)
{
    ofstream outFile("Outputs/" + filename);

    if (!outFile.is_open())
    {
        cout << "Error: Unable to create or write to the file '" << filename << "'." << endl;
        return;
    }

    for (const auto& entry : data)
    {
        outFile << "(" << fixed << setprecision(3) << entry.first
                << ", " << fixed << setprecision(3) << entry.second << ")" << endl;
    }

    outFile.close();
    cout << "Coordinates or Results successfully saved to 'Outputs/" << filename << "'." << endl;
}

//000000oooooo............oooooo000000000000oooooo............oooooo000000000000oooooo............oooooo000000//
