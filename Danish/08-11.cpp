#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

// Function to generate sample unique ID list in "unique_ids.txt"
void generateUniqueIDList() {
    std::ofstream idFile("unique_ids.txt");

    // Adding example unique IDs for students and teachers
    idFile << "11A_001" << std::endl;
    idFile << "11A_002" << std::endl;
    idFile << "11B_001" << std::endl;
    idFile << "11B_002" << std::endl;
    idFile << "12A_001" << std::endl;
    idFile << "12A_002" << std::endl;
    idFile << "12B_001" << std::endl;
    idFile << "12B_002" << std::endl;
    
    idFile << "TCH_101" << std::endl;
    idFile << "TCH_102" << std::endl;
    idFile << "TCH_103" << std::endl;
    idFile << "TCH_104" << std::endl;

    idFile.close();
    std::cout << "Unique ID list generated in 'unique_ids.txt'." << std::endl;
}

// Function to log attendance if the unique ID is found in "unique_ids.txt"
void logAttendance(const std::string &uniqueId) {
    std::ifstream idFile("unique_ids.txt");
    std::string id;
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
        std::ofstream attendanceFile("attendance_entries.txt", std::ios::app);
        time_t now = time(0);
        attendanceFile << uniqueId << " " << ctime(&now);
        attendanceFile.close();
        std::cout << "Attendance logged for ID: " << uniqueId << std::endl;
    } else {
        std::cout << "Error: Unique ID not found." << std::endl;
    }
}

// Main function
int main() {
    int choice;
    std::string uniqueId;

    while (true) {
        std::cout << "\nAttendance System Menu:\n";
        std::cout << "1. Generate Unique ID List\n";
        std::cout << "2. Log Attendance\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                generateUniqueIDList();
                break;
            case 2:
                std::cout << "Enter your unique ID (e.g., 11A_001 or TCH_101): ";
                std::cin >> uniqueId;
                logAttendance(uniqueId);
                break;
            case 3:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}
