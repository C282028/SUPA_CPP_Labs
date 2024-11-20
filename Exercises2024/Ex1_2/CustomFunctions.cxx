//Cameron Cassells
//20/11/2024


#include <iostream>
#include <sstream>
#include "CustomFunctions.hh"

using namespace std;

vector <pair<float,float>> readCoords(string& filename)
{
    // creates a vecotr from a pair of floats
    vector <pair<float,float>> coords;

    // read variables 
    string line1, line2;
    float x, y;
    int lines = 0;
    ifstream myInput(filename);

    // Finds and opens txt file, checks if successful, then proceeds.
    if (myInput.fail())
    {
        cout << "Unable to open file" << endl;
        return coords;
    }
else
    {
        // Skips the header line (non float values)
        string header;
        getline(myInput, header);

        // Gets the objects from stream and assigns it a string
        while (getline(myInput, line1, ',') && getline(myInput, line2))
        {   
            // Iterates through each line, converts the string to a float, stores them in the vector then prints the most recent 1st & 2nd elements.
            lines++;
            x = stof(line1);
            y = stof(line2);
            coords.emplace_back(x,y);
        }
    }
    myInput.close();
    return coords;
} //readCoords

// Function to evaluate the magnitude of each vector
float Magnitude(const pair<float, float>& coord)
{
	return sqrt(coord.first * coord.first + coord.second * coord.second);
} //Magnitude

// Function for printing coordinates read from the .txt file
void printCoords(vector<pair<float, float>>& coords, int n)
{
    // Print variables
    int lines = 0;
    int lines_to_print = n;

    if (n > coords.size())
    {
        cout << "***Warning*** " << n << " larger than total number of vectors " << "***Warning***" << endl;
        cout << "Printing first 5 coordinates instead" << endl;
        lines_to_print = min(5, static_cast<int>(coords.size()));
    }

    // Print up to the specified number of lines
	for (int i = 0; i < lines_to_print; ++i) 
    {
		float magnitude = Magnitude(coords[i]); 
        cout << "(" << coords[i].first << ", " << coords[i].second << "), Magnitude: " << magnitude << endl;
	}

	cout << lines_to_print << " lines printed from file" << endl;
    cout << coords.size() << " lines read from file" << endl;
} //printCoords

// Function to perform linear regression
void LinearRegression(const vector<pair<float, float>>& coords, float& m, float& c)
{
    // Linear reggression variables 
    size_t n = coords.size();
    float sum_x = 0;
    float sum_y = 0;
    float sum_xy = 0;
    float sum_x2 = 0;

    // iterates through each vector pair 
    for (const auto& coord : coords)
    {
        float x = coord.first;
        float y = coord.second;
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2 += x * x;
    }

    float denominator = n * sum_x2 - sum_x * sum_x;
    
    m = (n * sum_xy - sum_x * sum_y) / denominator;
    c = (sum_y - m * sum_x) / n;

    ostringstream equationStream;
    equationStream << "y = " << m << "x + " << c;
    string equation = equationStream.str();
    cout << "Linear Regression Equation: " << equation << endl;


    string filename = "Outputs/Linear_Regreasion_ Equations.txt";
    ofstream outStream;
    outStream.open(filename);

    if (!outStream.is_open())
    {
        cout << "Error opeining file: " << filename << endl;
    }
    else
    {
        outStream << equation << endl;
        cout << "Output file: " << filename << " opened successfully!" << endl;
    }
    outStream.close();

}