//Cameron Cassells
//13/11/2024


#include <iostream>
#include <iomanip>
#include "CustomFunctions.hh"

using namespace std;


int main()
{
    // Specifys the file to be read
    string filepath = "/workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2/input2D_float.txt";

    // Calls the reading function
    vector<pair<float, float>> coords = readCoords(filepath);

    // Variable to control the menu loop
    bool exitProgram = false;

    while (!exitProgram)
    {

        // Display menu to the user
        int choice;
        cout << "\nPlease select an option:" << endl;
        cout << "1. Print coordinates" << endl;
        cout << "2. Calculate magnitudes" << endl;
        cout << "3. Perform linear regression" << endl;
        cout << "4. Exit program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            // 1. Print coordinates 
            case 1: 
            {
                int n;
                cout << "\nPlease enter the number of coordinates you would like to print: ";
                cin >> n;

                // Calls the printing function
                printCoords(coords, n);

                break;
            }

            // 2. Calculate magnitudes
            case 2:
            {
                cout << "\nMagnitude of coordinates:" << endl;
                for (size_t i = 0; i < coords.size(); ++i)
                {
                    float magnitude = Magnitude(coords[i]);
                    cout << "Coordinate " << i + 1 << ": " << fixed << setprecision(2) << magnitude << endl;
                }
                break;
            }

            case 3:
            {
                float m, c;
                LinearRegression(coords, m, c);
                break;
            }

            // 4. Exit program
            case 4:
            {
                cout << "Exiting program." << endl;
                exitProgram = true;
                break;
            }

            default:
            {
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
            }
        }
    }

    return 0;
} // main
