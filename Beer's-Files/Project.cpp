#include <bits/stdc++.h>
#include<ctime>
#include<fstream>
#include<ctime>
#include<iomanip>
#include<sstream>
using namespace std;

class person
{
protected:
    string name;
    string email;
    char Gender;
};

class student : public person
{
protected:
    string roll_no;
    string std;
    string password;
public:
    bool login(const string& rollNumber, const string& password) {
        ifstream file("students.txt");
        if (!file.is_open()) {
            cerr << "Could not open the file!" << endl;
            return false;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string storedName, storedEmail, storedGender, storedStudentID, storedPassword, storedstd;
            getline(ss, storedName, ',');
            getline(ss, storedEmail, ',');
            getline(ss, storedGender, ',');
            getline(ss, storedStudentID, ',');
            getline(ss, storedPassword);
            if (storedStudentID == roll_no && storedPassword == password) {
                this->name = storedName;
                this->email = storedEmail;
                this->Gender = storedGender[0];
                this->roll_no = storedStudentID;
                this->password = storedPassword;
                this->std = storedstd;
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    void show_actions(){}
    friend class authority;
};


class teacher : public person
{
protected: 
    string emp_id;
    string password;
    string dept;

public:
    bool login(const string& empID, const string& password) {
        ifstream file("teachers.txt");
        if (!file.is_open()) {
            cerr << "Could not open the file!" << endl;
            return false;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string storedName, storedEmail, storedGender, storedEmpID, storedPassword, storedDept;
            getline(ss, storedName, ',');
            getline(ss, storedEmail, ',');
            getline(ss, storedGender, ',');
            getline(ss, storedEmpID, ',');
            getline(ss, storedPassword, ',');
            getline(ss, storedDept);
            if (storedEmpID == empID && storedPassword == password) {
                this->name = storedName;
                this->email = storedEmail;
                this->Gender = storedGender[0];
                this->emp_id = storedEmpID;
                this->password = storedPassword;
                this->dept = storedDept;
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    void show_actions(){}
};


class authority : public teacher
{
protected:
    string post;
public:
    static authority search(const string& employeeID) {
        ifstream file("authority.txt");
        authority a;
        if (!file.is_open()) {
            cerr << "Could not open the file!" << endl;
            return a;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string storedName, storedEmail, storedGender, storedEmpID, storedPassword, storedPost;
            getline(ss, storedName, ',');
            getline(ss, storedEmail, ',');
            getline(ss, storedGender, ',');
            getline(ss, storedEmpID, ',');
            getline(ss, storedPassword, ',');
            getline(ss, storedPost);
            if (storedEmpID == employeeID) {
                a.name = storedName;
                a.email = storedEmail;
                a.Gender = storedGender[0];
                a.emp_id = storedEmpID;
                a.password = storedPassword;
                a.post = storedPost;
                file.close();
                return a;
            }
        }
        file.close();
        return a;
    }
    bool check_password(const string& password) const {
        if(this->password.empty()) {
            cerr << "Error: No password stored." << endl;
            return false;
        }
        return this->password == password;
    }
    void show_actions(){}
};