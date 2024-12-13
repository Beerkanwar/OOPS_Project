#ifndef TEACHER_H
#define TEACHER_H

#include "Person.h"
#include <map>
#include <fstream>
#include <sstream>

class Teacher : public Person {
private:
    string empId;

public:
    Teacher(string name, string dob, string email, string gender, string empId)
        : Person(name, dob, email, gender), empId(empId) {}

    string getUniqueID() const override { return empId; }

    static void viewAttendance() {
        ifstream attendanceFile("attendance.txt");
        map<string, int> attendanceCount;
        string rollNo;
        time_t timestamp;

        while (attendanceFile >> rollNo >> timestamp) {
            attendanceCount[rollNo]++;
        }

        cout << "Attendance Records:\n";
        for (const auto& record : attendanceCount) {
            cout << "Roll No: " << record.first << ", Attendance: " << record.second << endl;
        }
    }

    static bool login(const string& id, const string& password) {
    ifstream database("teachers.txt");
    string storedId, storedPassword;
    while (database >> storedId >> storedPassword) {
        if (id == storedId && password == storedPassword) return true;
    }
    return false;
}
};

#endif // TEACHER_H