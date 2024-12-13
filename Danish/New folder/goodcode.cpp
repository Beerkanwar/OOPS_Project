#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

// Base class Person
class Person {
public:
    Person(string name, string dob, string email, string gender)
        : name(name), dob(dob), email(email), gender(gender) {}

    virtual ~Person() = default;
    virtual string getUniqueID() const = 0;

    // Static method to log attendance using unique ID
    static void logAttendance(const string& uniqueId) {
        if (!isValidID(uniqueId)) {
            cout << "Error: Unique ID not found.\n";
            return;
        }
        ofstream attendanceFile("attendance_entries.txt", ios::app);
        time_t now = time(0);
        attendanceFile << uniqueId << " " << ctime(&now);
        attendanceFile.close();
        cout << "Attendance logged for ID: " << uniqueId << endl;
    }

    // Static method to calculate total hours in class
    static void calculateTotalHoursInClass() {
        ifstream attendanceFile("attendance_entries.txt");
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
    string name, dob, email, gender;

private:
    // Static helper function to check if unique ID is valid
    static bool isValidID(const string& uniqueId) {
        ifstream idFile("unique_ids.txt");
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
        : Person(name, dob, email, gender), rollNo(rollNo), classSection(classSection), password(password) {}

    string getUniqueID() const override { return rollNo; }

private:
    string rollNo, classSection, password;
    friend class Authority;
};

// Derived class Teacher
class Teacher : public Person {
public:
    Teacher(string name, string dob, string email, string gender, string empId, string password, vector<string> classes)
        : Person(name, dob, email, gender), empId(empId), password(password), classes(classes) {}

    string getUniqueID() const override { return empId; }

private:
    string empId, password;
    vector<string> classes;
};

// Derived class Authority
class Authority : public Teacher {
public:
    Authority(string name, string dob, string email, string gender, string empId, string password, vector<string> classes, string post)
        : Teacher(name, dob, email, gender, empId, password, classes), post(post) {}

private:
    string post;
};

// Function to generate the unique ID list file for testing purposes
void generateUniqueIDList() {
    ofstream idFile("unique_ids.txt");
    idFile << "# Students (Roll Numbers)\n11A_001\n11A_002\n11B_001\n11B_002\n12A_001\n12A_002\n";
    idFile << "# Teachers (Employee IDs)\nTCH_101\nTCH_102\n";
    idFile << "# Authority (Employee IDs)\nAUTH_201\n";
    idFile.close();
    cout << "Unique ID list generated in 'unique_ids.txt'.\n";
}

int main() {
    char choice;
    string uniqueId;

    while (true) {
        cout << "\nMenu:\n1. Generate Unique ID List\n2. Log Attendance\n3. Calculate Total Hours\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                generateUniqueIDList();
                break;
            case '2':
                cout << "Enter your unique ID (e.g., 11A_001 or TCH_101): ";
                cin >> uniqueId;
                Person::logAttendance(uniqueId);
                break;
            case '3':
                Person::calculateTotalHoursInClass();
                break;
            case '4':
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
