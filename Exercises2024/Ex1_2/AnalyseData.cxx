//Cameron Cassells
//13/11/2024

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{
    // Variables 
    string line1;
    string line2;
    string filename = "input2D_float.txt";
    ifstream myInput;
    float x, y;
    int lines = 0;

    // Finds and opens txt file, checks if successful, then proceeds.
    myInput.open("/workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2/input2D_float.txt");
    if (myInput.fail())
    {
        cout << "Unable to open file" << endl;
        return -1;
    }

    else
    {
        // Skips the header line (non float values)
        string header;
        getline(myInput, header);

        // Gets the objects from stream and assigns it a string
        while (getline(myInput, line1, ',') && getline(myInput, line2))
        {   
            // Iterates through each line, converts the string to a float, then prints to terminal.
            lines++;
            x = stof(line1);
            y = stof(line2);
            cout << x << " " << y << endl;
        }
    }
    // Prints total No. of lines and closes the file.
    cout << lines << " lines read from file" << endl;
    myInput.close();

    return 0;
    
} // main // namespace
