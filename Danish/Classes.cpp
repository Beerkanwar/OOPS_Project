#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <chrono>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <algorithm>
using namespace std;

string getCurrentDate() {
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm* now_tm = localtime(&now_c);
    ostringstream oss;
    oss << put_time(now_tm, "%Y-%m-%d");
    return oss.str();
}

class Person
{
public:
    Person() = default;
    Person(string name, string dob, string email, string gender, string password)
        : name(name), dob(dob), email(email), gender(gender), password(password) {}

    virtual ~Person() = default;
    virtual string getUniqueID() const = 0;
    static void logAttendance(const string &uniqueId)
    {
        if (!isValidID(uniqueId))
        {
            cout << "Error: Unique ID not found.\n";
            return;
        }
        string fileName = "attendance_entries_" + getCurrentDate() + ".txt";
        ofstream attendanceFile(fileName, ios::app);
        if (!attendanceFile.is_open())
        {
            cerr << "Error: Could not open 'attendance_entries.txt' for writing.\n";
            return;
        }
        time_t now = time(0);
        attendanceFile << uniqueId << " " << ctime(&now);
        attendanceFile.close();
        cout << "Attendance logged for ID: " << uniqueId << endl;
    }
    static time_t convertToTimeT(const string &dateStr)
    {
        struct tm timeStruct = {};
        istringstream ss(dateStr);
        ss >> get_time(&timeStruct, "%a %b %d %H:%M:%S %Y");
        if (ss.fail())
        {
            cerr << "Error: Failed to parse date string: " << dateStr << endl;
            return 0;
        }
        return mktime(&timeStruct);
    }
    static void calculateTotalHoursInClass(string date = getCurrentDate())
    {
        string fileName = "attendance_entries_" + date + ".txt";
        ifstream attendanceFile(fileName);
        if (!attendanceFile.is_open())
        {
            cerr << "Error: Could not open 'attendance_entries.txt'.\n";
            return;
        }
        string line, uniqueId, dateStr;
        map<string, double> totalHours;
        map<string, time_t> lastInTime;
        while (getline(attendanceFile, line))
        {
            istringstream iss(line);
            if (!(iss >> uniqueId))
                continue;
            getline(iss, dateStr);
            time_t currentTime = convertToTimeT(dateStr);
            if (currentTime == 0)
                continue;
            if (lastInTime.count(uniqueId) == 0)
            {
                lastInTime[uniqueId] = currentTime;
            }
            else
            {
                double timeSpent = difftime(currentTime, lastInTime[uniqueId]) / 3600.0;
                if(timeSpent < 0.5) timeSpent = 0;
                totalHours[uniqueId] += timeSpent;
                lastInTime.erase(uniqueId);
            }
        }
        attendanceFile.close();
        cout << "Total hours spent in class:\n";
        for (const auto &entry : totalHours)
        {
            cout << "ID: " << entry.first << ", Hours: " << round(entry.second) << " hours\n";
        }
    }
    friend ostream& operator<<(ostream& os, const Person& p);
    friend istream& operator>>(istream& is, Person& p);
protected:
    string name, dob, email, gender, password;
private:
    static bool isValidID(const string &uniqueId)
    {
        ifstream idFile("unique_ids.txt");
        if (!idFile.is_open())
        {
            cerr << "Error: Could not open 'unique_ids.txt'.\n";
            return false;
        }
        string id;
        while (getline(idFile, id))
        {
            if (id == uniqueId)
                return true;
        }
        return false;
    }
};

ostream& operator<<(ostream& os, const Person& p) {
    os << p.name << " " << p.dob << " " << p.email << " " << p.gender;
    return os;
}

istream& operator>>(istream& is, Person& p) {
    is >> p.name >> p.dob >> p.email >> p.gender;
    return is;
}

class Student : public Person
{
public:
    Student() = default;
    Student(string name, string dob, string email, string gender, string rollNo, string classSection, string password)
        : Person(name, dob, email, gender, password), rollNo(rollNo), classSection(classSection) {}

    string getUniqueID() const override { return rollNo;}
    static bool search(const string &rollNo)
    {
        ifstream file("data.txt");
        if (!file.is_open())
        {
            cerr << "Error: Could not open 'student_data.txt'.\n";
            return false;
        }
        string line;
        while (getline(file, line))
        {
            int res = line.find(rollNo);
            if (res != string::npos)
                return true;
        }
        return false;
    }
    friend ostream& operator<<(ostream& os, const Student& s);
    friend istream& operator>>(istream& is, Student& s);
private:
    string rollNo, classSection;
};

ostream& operator<<(ostream& os, const Student& s) {
    os << static_cast<const Person&>(s) << " " << s.rollNo << " " << s.classSection;
    return os;
}

istream& operator>>(istream& is, Student& s) {
    is >> static_cast<Person&>(s) >> s.rollNo >> s.classSection;
    return is;
}

class Authority : public Person
{
public:
    Authority() = default;
    Authority(string name, string dob, string email, string gender, string empId, string password)
        : Person(name, dob, email, gender, password), empId(empId) {}

    string getUniqueID() const override { return empId;}
    static bool checkAuthorityCredentials(const string &emp_id, const string &password)
    {
        ifstream file("data.txt");
        if (!file.is_open())
        {
            cerr << "Error: Could not open 'data.txt'. Make sure the file exists.\n";
            return false;
        }
        string line;
        bool isAuthoritySection = false;
        while (getline(file, line))
        {
            if (line.find("# Authority") != string::npos)
            {
                isAuthoritySection = true;
                continue;
            }
            if (isAuthoritySection && !line.empty())
            {
                stringstream ss(line);
                string file_emp_id, file_name, file_password;
                if (!getline(ss, file_emp_id, '|') || !getline(ss, file_name, '|') || !getline(ss, file_password, '|'))
                {
                    cerr << "Error: Malformed line in 'data.txt'\n";
                    continue;
                }
                file_emp_id.erase(file_emp_id.find_last_not_of(" \t") + 1);
                file_password.erase(file_password.find_last_not_of(" \t") + 1);
                if (file_emp_id == emp_id && file_password == password)
                {
                    return true;
                }
            }
        }
        return false;
    }
    friend ostream& operator<<(ostream& os, const Authority& a);
    friend istream& operator>>(istream& is, Authority& a);
private:
    string empId;
};

ostream& operator<<(ostream& os, const Authority& a) {
    os << static_cast<const Person&>(a) << " " << a.empId;
    return os;
}

istream& operator>>(istream& is, Authority& a) {
    is >> static_cast<Person&>(a) >> a.empId;
    return is;
}