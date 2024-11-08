#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// Function to generate sample unique ID list in "unique_ids.txt"
void generateUniqueIDList() {
    ofstream idFile("unique_ids.txt");

    // Adding example unique IDs for students and teachers
    idFile << "11A_001" << endl;
    idFile << "11A_002" << endl;
    idFile << "11B_001" << endl;
    idFile << "11B_002" << endl;
    idFile << "12A_001" << endl;
    idFile << "12A_002" << endl;
    idFile << "12B_001" << endl;
    idFile << "12B_002" << endl;
    
    idFile << "TCH_101" << endl;
    idFile << "TCH_102" << endl;
    idFile << "TCH_103" << endl;
    idFile << "TCH_104" << endl;

    idFile.close();
    cout << "Unique ID list generated in 'unique_ids.txt'." << endl;
}

// Function to log attendance if the unique ID is found in "unique_ids.txt"
void logAttendance(const string &uniqueId) {
    ifstream idFile("unique_ids.txt");
    string id;
    bool found = false;

    // Check if uniqueId exists in the file
    while (getline(idFile, id)) {
        if (id == uniqueId) {
            found = true;
            break;
        }
    }
    idFile.close();

    // If found, log attendance with current time
    if (found) {
        ofstream attendanceFile("attendance_entries.txt", ios::app);
        time_t now = time(0);
        attendanceFile << uniqueId << " " << ctime(&now);
        attendanceFile.close();
        cout << "Attendance logged for ID: " << uniqueId << endl;
    } else {
        cout << "Error: Unique ID not found." << endl;
    }
}

// Main function
int main() {
    int choice;
    string uniqueId;

    while (true) {
        cout << "\nAttendance System Menu:\n";
        cout << "1. Generate Unique ID List\n";
        cout << "2. Log Attendance\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                generateUniqueIDList();
                break;
            case 2:
                cout << "Enter your unique ID (e.g., 11A_001 or TCH_101): ";
                cin >> uniqueId;
                logAttendance(uniqueId);
                break;
            case 3:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
