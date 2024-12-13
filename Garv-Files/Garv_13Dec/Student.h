#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <fstream>

class Student : public Person {
private:
    string rollNo;

public:
    Student(string name, string dob, string email, string gender, string rollNo)
        : Person(name, dob, email, gender), rollNo(rollNo) {}

    string getUniqueID() const override { return rollNo; }

    static void markAttendance(const string& rollNo) {
        if (!isValidRollNo(rollNo)) {
            cout << "Invalid Roll Number.\n";
            return;
        }
        ofstream attendanceFile("attendance.txt", ios::app);
        attendanceFile << rollNo << " " << time(0) << endl;
        attendanceFile.close();
        cout << "Attendance marked for Roll No: " << rollNo << endl;
    }

    static bool isValidRollNo(const string& rollNo) {
        ifstream database("students.txt");
        string id;
        while (database >> id) {
            if (id == rollNo) return true;
        }
        return false;
    }
};

#endif // STUDENT_H