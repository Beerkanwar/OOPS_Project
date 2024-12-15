#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to create the data file
void createDataFile()
{
    ofstream dataFile("data.txt");
    if (!dataFile.is_open())
    {
        cerr << "Error: Unable to create file 'data.txt'.\n";
        return;
    }

    // Add authority's details
    cout << "Enter Authority ID: ";
    string authorityId;
    cin >> authorityId;

    cout << "Enter Authority Name: ";
    string authorityName;
    cin.ignore(); // Ignore any leftover newline character
    getline(cin, authorityName);

    cout << "Enter Authority Password: ";
    string authorityPassword;
    cin >> authorityPassword;

    dataFile << "# Authority\n";
    dataFile << authorityId << "|" << authorityName << "|" << authorityPassword << "\n";

    // Add placeholder data for students
    dataFile << "\n# Students\n";
    dataFile << "11A_001|Alice|studentPass1|0\n";
    dataFile << "11A_002|Bob|studentPass2|0\n";

    // Add placeholder data for teachers

    dataFile.close();
    cout << "File 'data.txt' created successfully.\n";
}

int main()
{
    createDataFile();
    return 0;
}
