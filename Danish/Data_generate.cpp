#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void createDataFile()
{
    ofstream dataFile("data.txt");
    if (!dataFile.is_open())
    {
        cerr << "Error: Unable to create file 'data.txt'.\n";
        return;
    }
    cout << "Enter Authority ID: ";
    string authorityId;
    cin >> authorityId;
    cout << "Enter Authority Name: ";
    string authorityName;
    cin.ignore();
    getline(cin, authorityName);
    cout << "Enter Authority Password: ";
    string authorityPassword;
    cin >> authorityPassword;
    dataFile << "# Authority\n";
    dataFile << authorityId << "|" << authorityName << "|" << authorityPassword << "\n";
    dataFile << "\n# Students\n";
    cout << "Enter number of students: ";
    int numStudents;
    cin >> numStudents;
    for (int i = 0; i < numStudents; ++i)
    {
        string rollNo, studentName, studentPassword;
        cout << "Enter Roll No for Student " << (i + 1) << ": ";
        cin >> rollNo;
        cout << "Enter Name for Student " << (i + 1) << ": ";
        cin.ignore();
        getline(cin, studentName);
        cout << "Enter Password for Student " << (i + 1) << ": ";
        cin >> studentPassword;
        dataFile << rollNo << "|" << studentName << "|" << studentPassword << "|0\n";
    }
    dataFile.close();
    cout << "File 'data.txt' created successfully.\n";
}

int main()
{
    createDataFile();
    return 0;
}