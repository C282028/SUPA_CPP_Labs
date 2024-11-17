//Cameron Cassells
//13/11/2024

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;


// Function for reading coordinates from a .txt file
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


int main()
{
    // Specifys the file to be read
    string filepath = "/workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2/input2D_float.txt";
    // Calls the reading function
    vector<pair<float, float>> coords = readCoords(filepath);
    
	// User input for number of coordinates to print
	int n;
	cout << "Please enter the number of coordinates you would like to print: ";
	cin >> n;

    // Calls the printing function
    printCoords(coords, n);

    return 0;
} // main
