//Cameron Cassells
//13/11/2024


#include <iostream>
#include <iomanip>
#include "CustomFunctions.hh"

using namespace std;


int main()
{
    // Specifys the files to be read
    string filepath = "/workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2/input2D_float.txt";
    string errorsFile = "/workspaces/SUPA_CPP_Labs/Exercises2024/Ex1_2/error2D_float.txt";

    // Calls the reading function
    vector<pair<float, float>> coords = readCoords(filepath);
    vector<float> errors = readErrors(errorsFile);

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
                print(coords, n);

                break;
            }

            // 2. Calculate magnitudes
		    case 2:
		    {
			    vector<float> magnitudes;
			    for (const auto& coord : coords)
				    magnitudes.push_back(Magnitude(coord));

			        print(magnitudes);
			        break;
            }

            //3. Least squares method
            case 3:
            {
                float m, c;
                LinearRegression(coords, errors, m, c);
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
