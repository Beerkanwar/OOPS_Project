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
    void show_actions(){}
};