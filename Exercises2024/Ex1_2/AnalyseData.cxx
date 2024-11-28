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
        cout << "4. Calculate x^y for each data point (y rounded to nearest whole number)" << endl;
        cout << "5. Exit program" << endl;
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
            } //1

            // 2. Calculate magnitudes
            case 2: 
            {
                vector<float> magnitudes;
                for (const auto& coord : coords)
                magnitudes.push_back(Magnitude(coord));

                print(magnitudes);

                // Save magnitudes to a file
                saveToFile(magnitudes, "Magnitudes.txt");

                break;
            }//2

            //3. Least squares method
            case 3:
            {
                float m, c, chi2_per_ndf;
                LinearRegression(coords, errors, m, c, chi2_per_ndf);

                // Generate equation string
                ostringstream equationStream;
                equationStream << "y = " << m << "x + " << c;
                string equation = equationStream.str();

                // Save linear regression results to a file
                saveToFile(equation, chi2_per_ndf, "Linear_Regression.txt");

                break;
            }//3

            // 4. Calculate x^y for each data point
            case 4:
            {
                vector<pair<float, float>> xyResults;
                for (const auto& coord : coords)
                {
                    float x = coord.first;
                    float y = coord.second;
                    float result = calculateXY(x, y);
                    xyResults.emplace_back(x, result);
                }

                // Print and save x^y results
                for (const auto& result : xyResults)
                    cout << "x = " << result.first << ", x^y = " << result.second << endl;

                saveToFile(xyResults, "XY_Calculations.txt");

                break;
            }//4

            // 5. Exit program
            case 5:
            {
                cout << "Exiting program." << endl;
                exitProgram = true;
                break;
            }//5

            default:
            {
                cout << "Invalid choice. Please select a valid option." << endl;
                break;
            }//default
        }
    }

    return 0;
} // main
