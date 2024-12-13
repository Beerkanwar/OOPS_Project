#ifndef AUTHORITY_H
#define AUTHORITY_H

#include "Teacher.h"
#include <fstream>

class Authority : public Teacher {
private:
    string password;

public:
    Authority(string name, string dob, string email, string gender, string empId, string password)
        : Teacher(name, dob, email, gender, empId), password(password) {}

    static bool login(const string& id, const string& password) {
        ifstream database("authority.txt");
        string storedId, storedPassword;
        while (database >> storedId >> storedPassword) {
            if (id == storedId && password == storedPassword) return true;
        }
        return false;
    }

    static void editDatabase() {
        ofstream studentDB("students.txt", ios::app);
        string rollNo;
        cout << "Enter Roll No to add to the database: ";
        cin >> rollNo;
        studentDB << rollNo << endl;
        studentDB.close();
        cout << "Roll No added successfully.\n";
    }
};

#endif // AUTHORITY_H