#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

// Base class Person
class Person {
public:
    Person(string name, string dob, string email, string gender, string password)
        : name(name), dob(dob), email(email), gender(gender), password(password) {}

    virtual ~Person() = default;
    virtual string getUniqueID() const = 0;

    // Static method to log attendance using unique ID
    static void logAttendance(const string& uniqueId) {
        if (!isValidID(uniqueId)) {
            cout << "Error: Unique ID not found.\n";
            return;
        }

        ofstream attendanceFile("attendance_entries.txt", ios::app);
        if (!attendanceFile.is_open()) {
            cerr << "Error: Could not open 'attendance_entries.txt' for writing.\n";
            return;
        }

        time_t now = time(0);
        attendanceFile << uniqueId << " " << ctime(&now);
        attendanceFile.close();
        cout << "Attendance logged for ID: " << uniqueId << endl;
    }

    // Static method to calculate total hours in class
    static void calculateTotalHoursInClass() {
        ifstream attendanceFile("attendance_entries.txt");
        if (!attendanceFile.is_open()) {
            cerr << "Error: Could not open 'attendance_entries.txt'.\n";
            return;
        }

        string line, uniqueId, dateStr;
        map<string, double> totalHours;
        map<string, time_t> lastInTime;

        while (getline(attendanceFile, line)) {
            istringstream iss(line);
            if (!(iss >> uniqueId)) continue;
            getline(iss, dateStr);
            time_t currentTime = convertToTimeT(dateStr);

            if (lastInTime.count(uniqueId) == 0) {
                lastInTime[uniqueId] = currentTime;
            } else {
                double timeSpent = difftime(currentTime, lastInTime[uniqueId]) / 3600.0;
                totalHours[uniqueId] += timeSpent;
                lastInTime.erase(uniqueId);
            }
        }
        attendanceFile.close();

        cout << "Total hours spent in class:\n";
        for (const auto& entry : totalHours) {
            cout << "ID: " << entry.first << ", Hours: " << entry.second << " hours\n";
        }
    }

protected:
    string name, dob, email, gender, password;

private:
    // Static helper function to check if unique ID is valid
    static bool isValidID(const string& uniqueId) {
        ifstream idFile("unique_ids.txt");
        if (!idFile.is_open()) {
            cerr << "Error: Could not open 'unique_ids.txt'.\n";
            return false;
        }

        string id;
        while (getline(idFile, id)) {
            if (id == uniqueId) return true;
        }
        return false;
    }

    // Static helper function to convert string date to time_t
    static time_t convertToTimeT(const string& timeStr) {
        struct tm tm{};
        istringstream ss(timeStr);
        ss >> get_time(&tm, "%a %b %d %H:%M:%S %Y");
        return mktime(&tm);
    }
};

// Derived class Student
class Student : public Person {
public:
    Student(string name, string dob, string email, string gender, string rollNo, string classSection, string password)
        : Person(name, dob, email, gender, password), rollNo(rollNo), classSection(classSection) {}

    string getUniqueID() const override { return rollNo; }

    static unique_ptr<Student> search(const string& rollNo) {
        ifstream file("student_data.txt");
        if (!file.is_open()) {
            cerr << "Error: Could not open 'student_data.txt'.\n";
            return nullptr;
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string storedRollNo, name, dob, email, gender, classSection, password;
            iss >> storedRollNo >> name >> dob >> email >> gender >> classSection >> password;
            if (storedRollNo == rollNo) {
                return make_unique<Student>(name, dob, email, gender, storedRollNo, classSection, password);
            }
        }
        return nullptr;
    }

private:
    string rollNo, classSection;
};

// Derived class Authority
class Authority : public Person {
public:
    Authority(string name, string dob, string email, string gender, string empId, string password)
        : Person(name, dob, email, gender, password), empId(empId) {}

    string getUniqueID() const override { return empId; }

   static bool checkAuthorityCredentials(const string& emp_id, const string& password) {
    ifstream file("data.txt");
    if (!file.is_open()) {
        cerr << "Error: Could not open 'data.txt'. Make sure the file exists.\n";
        return false;
    }

    string line;
    bool isAuthoritySection = false;

    while (getline(file, line)) {
        // Check if we've reached the "# Authority" section
        if (line.find("# Authority") != string::npos) {
            isAuthoritySection = true;
            continue;
        }

        // Process only lines in the Authority section
        if (isAuthoritySection && !line.empty()) {
            stringstream ss(line);
            string file_emp_id, file_name, file_password;

            // Parse the line using '|' as a delimiter
            if (!getline(ss, file_emp_id, '|') || !getline(ss, file_name, '|') || !getline(ss, file_password, '|')) {
                cerr << "Error: Malformed line in 'data.txt': " << line << "\n";
                continue;
            }

            // Trim whitespace from parsed values
            file_emp_id.erase(file_emp_id.find_last_not_of(" \t") + 1);
            file_password.erase(file_password.find_last_not_of(" \t") + 1);

            // Debugging logs (can be commented out in production)
            cout << "Checking credentials: " << file_emp_id << " " << file_password << "\n";

            // Validate the credentials
            if (file_emp_id == emp_id && file_password == password) {
                return true;
            }
        }
    }

    return false;
}


private:
    string empId;
};

int main() {
    while (true) {
        string emp_id, password;

        cout << "Enter the Employee Id: ";
        cin >> emp_id;
        cout << "Enter password: ";
        cin >> password;

        if (!Authority::checkAuthorityCredentials(emp_id, password)) {
            cout << "Incorrect Id or Password!\n";
            continue;
        }

        cout << "Login successful!\n";

        while (true) {
            int choice;
            cout << "\nMenu:\n1. Log Attendance\n2. Calculate Total Hours\n3. Logout\nEnter your choice: ";
            cin >> choice;

            if (choice == 1) {
                string roll_no;
                cout << "Enter Roll No: ";
                cin >> roll_no;

                auto student = Student::search(roll_no);
                if (student) {
                    Person::logAttendance(student->getUniqueID());
                } else {
                    cout << "Invalid Roll No!\n";
                }
            } else if (choice == 2) {
                Person::calculateTotalHoursInClass();
            } else if (choice == 3) {
                cout << "Logging out...\n";
                break;
            } else {
                cout << "Invalid choice!\n";
            }
        }
    }

    return 0;
}
