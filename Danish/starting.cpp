#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string>
#include <map>
#include <vector>
#include "Project.cpp"

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

    static Student* search(const string& rollNo) {
        // Placeholder for actual search logic.
        return nullptr; // Replace with actual implementation
    }

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

protected:
    string empId, password;
    vector<string> classes;
};

// Derived class Authority
class Authority : public Teacher {
public:
    Authority(string name, string dob, string email, string gender, string empId, string password, vector<string> classes, string post)
        : Teacher(name, dob, email, gender, empId, password, classes), post(post) {}

    static Authority* search(const string& empId) {
        // Placeholder for actual search logic.
        return nullptr; // Replace with actual implementation
    }

    bool check_password(const string& inputPassword) const {
        return password == inputPassword; // Replace with hashed password check
    }

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
    while (true) {
        string emp_id, password;

        // Login prompt
        cout << "Enter the Employee Id: ";
        cin >> emp_id;
        cout << "Enter password: ";
        cin >> password;

        // Search and validate authority user
        Authority* a1 = Authority::search(emp_id); // Assume Authority::search fetches Authority object
        if (!a1 || !a1->check_password(password)) {
            cout << "Incorrect Id or Password!" << endl;
            continue;
        }

        cout << "Login successful!" << endl;

        while (true) {
            int choice;
            cout << "\nMenu:\n1. Log Attendance\n2. Calculate Total Hours\n3. Logout\nEnter your choice: ";
            cin >> choice;

            if (choice == 1) {
                // Attendance system
                time_t t = time(nullptr);
                tm* now = localtime(&t);
                ostringstream oss;
                oss << (now->tm_year + 1900) << '-' 
                    << setw(2) << setfill('0') << (now->tm_mon + 1) << '-' 
                    << setw(2) << setfill('0') << now->tm_mday;
                string fileName = oss.str() + ".txt";

                ofstream file(fileName, ios::app);
                if (!file.is_open()) {
                    cerr << "Failed to create or open the file: " << fileName << endl;
                    break;
                }

                while (true) {
                    string roll_no;
                    cout << "Enter Roll No (or -1 to exit): ";
                    cin >> roll_no;

                    if (roll_no == "-1") {
                        break;
                    }

                    // Validate roll number
                    Student* student = Student::search(roll_no); // Assume Student::search fetches Student object
                    if (student) {
                        time_t now = time(0);
                        tm* ltm = localtime(&now);

                        ostringstream timeStream;
                        timeStream << setw(2) << setfill('0') << ltm->tm_hour << ":"
                                   << setw(2) << setfill('0') << ltm->tm_min << ":"
                                   << setw(2) << setfill('0') << ltm->tm_sec;

                        file << "Roll No: " << roll_no << ", Time: " << timeStream.str() << endl;
                        cout << "Attendance recorded for Roll No: " << roll_no << " at " << timeStream.str() << endl;
                    } else {
                        cout << "Invalid Roll No!" << endl;
                    }
                }

                file.close();
            } else if (choice == 2) {
                // Calculate total hours
                Person::calculateTotalHoursInClass();
            } else if (choice == 3) {
                // Logout
                cout << "Logging out...\n";
                break;
            } else {
                cout << "Invalid choice!" << endl;
            }
        }
    }

    return 0;
}
