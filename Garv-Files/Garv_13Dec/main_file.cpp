#include "Student.h"
#include "Teacher.h"
#include "Authority.h"
#include <iostream>
using namespace std;

void studentMenu() {
    string rollNo;
    cout << "Enter your Roll No: ";
    cin >> rollNo;
    Student::markAttendance(rollNo);
}

// void teacherMenu() {
    // string empId;
    // cout << "Enter your Employee ID: ";
    // cin >> empId;
    // cout << "Fetching attendance records...\n";
    // Teacher::viewAttendance();
    void teacherMenu() {
    string empId, password;
    cout << "Enter your Employee ID: ";
    cin >> empId;
    cout << "Enter your Password: ";
    cin >> password;
    if (Teacher::login(empId, password)) {
        cout << "Login successful. Fetching attendance records...\n";
        Teacher::viewAttendance();
    } else {
        cout << "Invalid credentials.\n";
    }
}
// }

void authorityMenu() {
    string id, password;
    cout << "Enter your ID: ";
    cin >> id;
    cout << "Enter your Password: ";
    cin >> password;
    if (Authority::login(id, password)) {
        cout << "Login successful. You can now edit the database.\n";
        Authority::editDatabase();
    } else {
        cout << "Invalid credentials.\n";
    }
}

int main() {
    char choice;

    while (true) {
        cout << "\nMenu:\n1. Student\n2. Teacher\n3. Authority\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                studentMenu();
                break;
            case '2':
                teacherMenu();
                break;
            case '3':
                authorityMenu();
                break;
            case '4':
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}