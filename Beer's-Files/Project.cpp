#include <bits/stdc++.h>
#include<ctime>
// #include<stdint.h>
// #include <C:\Program Files\MySQL\MySQL Connector C++ 9.1\include\jdbc\mysql_driver.h>
// #include <C:\Program Files\MySQL\MySQL Connector C++ 9.1\include\jdbc\mysql_connection.h>
// #include <C:\Program Files\MySQL\MySQL Connector C++ 9.1\include\jdbc\cppconn\statement.h>
// #include <C:\Program Files\MySQL\MySQL Connector C++ 9.1\include\jdbc\cppconn\resultset.h>
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
    int sem;
    string branch;
    string password;
public:
    static bool login(const string& rollNumber, const string& password) {
        ifstream file("students.txt");
        if (!file.is_open()) {
            cerr << "Could not open the file!" << endl;
            return false;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string storedRollNo, storedPassword;
            getline(ss, storedRollNo, ',');
            getline(ss, storedPassword);
            if (storedRollNo == rollNumber && storedPassword == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    void show_actions(){}
};


class teacher : public person
{
protected: 
    string emp_id;
    string password;
    string dept;

public:
    void show_actions(){}
};


class authority : public person
{
protected:
    string emp_id;
    string password;
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
    void show_actions(){}
};