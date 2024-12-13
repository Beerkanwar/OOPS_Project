#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <stdexcept>
#include <algorithm> // For std::remove_if

class Student {
public:
    std::string uniqueID;
    std::string name;

    Student(const std::string& id, const std::string& name) : uniqueID(id), name(name) {}
};

class AttendanceManager {
private:
    std::vector<Student> students;
    std::string attendanceFile;

public:
    AttendanceManager(const std::string& filename) : attendanceFile(filename) {
        loadStudents();
    }

    void loadStudents() {
        std::ifstream file("students.csv");
        if (!file.is_open()) {
            throw std::runtime_error("Could not open student file.");
        }
        std::string id, name;
        while (file >> id >> name) {
            students.push_back(Student(id, name));
        }
        file.close();
    }

    bool markAttendance(const std::string& studentID) {
        // Check if the student ID exists
        for (std::vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
            if (it->uniqueID == studentID) {
                // Mark attendance with timestamp
                std::ofstream attendance(attendanceFile, std::ios::app);
                if (!attendance.is_open()) {
                    throw std::runtime_error("Could not open attendance file.");
                }
                time_t now = time(0);
                attendance << studentID << "," << it->name << "," << ctime(&now);
                attendance.close();
                return true;
            }
        }
        return false;
    }

    void viewStudentDetails(const std::string& studentID) const {
        for (std::vector<Student>::const_iterator it = students.begin(); it != students.end(); ++it) {
            if (it->uniqueID == studentID) {
                std::cout << "Student ID: " << it->uniqueID << ", Name: " << it->name << std::endl;
                return;
            }
        }
        std::cout << "Student not found." << std::endl;
    }

    void addStudent(const std::string& id, const std::string& name) {
        students.push_back(Student(id, name));
        std::ofstream file("students.csv", std::ios::app);
        if (file.is_open()) {
            file << id << " " << name << std::endl;
            file.close();
        } else {
            throw std::runtime_error("Could not open student file for writing.");
        }
    }

    void deleteStudent(const std::string& studentID) {
        std::vector<Student>::iterator it = std::remove_if(students.begin(), students.end(), [&studentID](const Student& student) {
            return student.uniqueID == studentID;
        });
        
        if (it != students.end()) {
            students.erase(it, students.end());
            // Update the CSV file
            std::ofstream file("students.csv", std::ios::trunc);
            if (file.is_open()) {
                for (std::vector<Student>::const_iterator sit = students.begin(); sit != students.end(); ++sit) {
                    file << sit->uniqueID << " " << sit->name << std::endl;
                }
                file.close();
            } else {
                throw std::runtime_error("Could not open student file for writing.");
            }
        }
    }
};

class Authority {
private:
    std::string uniqueID;

public:
    Authority(const std::string& id) : uniqueID(id) {}

    bool verify(const std::string& inputID) {
        return uniqueID == inputID;  // Simple verification
    }
};

int main() {
    AttendanceManager attendanceManager("attendance.csv");

    // Example user input for demonstration
    std::string studentID;
    std::cout << "Enter Student Unique ID to mark attendance: ";
    std::cin >> studentID;

    try {
        if (attendanceManager.markAttendance(studentID)) {
            std::cout << "Attendance marked successfully!" << std::endl;
        } else {
            std::cout << "Invalid Student ID!" << std::endl;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    // Authority verification and editing student details example
    Authority authority("admin123");
    std::string authID;
    std::cout << "Enter Authority Unique ID for verification: ";
    std::cin >> authID;

    if (authority.verify(authID)) {
        std::cout << "Authority verified. You can proceed with editing." << std::endl;

        // Add a student example
        std::string newID, newName;
        std::cout << "Enter new student ID and name to add: ";
        std::cin >> newID >> newName;
        try {
            attendanceManager.addStudent(newID, newName);
            std::cout << "Student added successfully!" << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
        }

        // Delete a student example
        std::string deleteID;
        std::cout << "Enter Student Unique ID to delete: ";
        std::cin >> deleteID;
        attendanceManager.deleteStudent(deleteID);
        std::cout << "Student deleted successfully!" << std::endl;

    } else {
        std::cout << "Unauthorized access!" << std::endl;
    }

    // View individual details
    std::cout << "Enter Student Unique ID to view details: ";
    std::cin >> studentID;
    attendanceManager.viewStudentDetails(studentID);

    return 0;
}