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

// Base class Person
class Person
{
public:
    Person(string name, string dob, string email, string gender, string password)
        : name(name), dob(dob), email(email), gender(gender), password(password) {}

    virtual ~Person() = default;
    virtual string getUniqueID() const = 0;

    // Static method to log attendance using unique ID
    static void logAttendance(const string &uniqueId)
    {
        if (!isValidID(uniqueId))
        {
            cout << "Error: Unique ID not found.\n";
            return;
        }
        // Save attendence entries in a new file everyday (file made day by day)
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

    // Static method to calculate total hours in class
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

    // Function to calculate total hours spent in class
    static void calculateTotalHoursInClass()
    {
        string fileName = "attendance_entries_" + getCurrentDate() + ".txt";
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
                continue;          // Extract unique ID
            getline(iss, dateStr); // Extract timestamp
            time_t currentTime = convertToTimeT(dateStr);

            if (currentTime == 0)
                continue; // Skip invalid timestamps

            if (lastInTime.count(uniqueId) == 0)
            {
                // First entry for this ID
                lastInTime[uniqueId] = currentTime;
            }
            else
            {
                // Calculate time spent and accumulate hours
                double timeSpent = difftime(currentTime, lastInTime[uniqueId]) / 3600.0;
                totalHours[uniqueId] += timeSpent;
                lastInTime.erase(uniqueId); // Remove entry after calculating
            }
        }
        attendanceFile.close();

        // Display total hours
        cout << "Total hours spent in class:\n";
        for (const auto &entry : totalHours)
        {
            cout << "ID: " << entry.first << ", Hours: " << entry.second << " hours\n";
        }
    }

protected:
    string name, dob, email, gender, password;

private:
    // Static helper function to check if unique ID is valid
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

    // Static helper function to convert string date to time_t
};

// Derived class Student
class Student : public Person
{
public:
    Student(string name, string dob, string email, string gender, string rollNo, string classSection, string password)
        : Person(name, dob, email, gender, password), rollNo(rollNo), classSection(classSection) {}

    string getUniqueID() const override { return rollNo; }

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

private:
    string rollNo, classSection;
};

// Derived class Authority
class Authority : public Person
{
public:
    Authority(string name, string dob, string email, string gender, string empId, string password)
        : Person(name, dob, email, gender, password), empId(empId) {}

    string getUniqueID() const override { return empId; }

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
            // Check if we've reached the "# Authority" section
            if (line.find("# Authority") != string::npos)
            {
                isAuthoritySection = true;
                continue;
            }

            // Process only lines in the Authority section
            if (isAuthoritySection && !line.empty())
            {
                stringstream ss(line);
                string file_emp_id, file_name, file_password;

                // Parse the line using '|' as a delimiter
                if (!getline(ss, file_emp_id, '|') || !getline(ss, file_name, '|') || !getline(ss, file_password, '|'))
                {
                    cerr << "Error: Malformed line in 'data.txt': " << line << "\n";
                    continue;
                }

                // Trim whitespace from parsed values
                file_emp_id.erase(file_emp_id.find_last_not_of(" \t") + 1);
                file_password.erase(file_password.find_last_not_of(" \t") + 1);

                // Debugging logs (can be commented out in production)
                cout << "Checking credentials: " << file_emp_id << " " << file_password << "\n";

                // Validate the credentials
                if (file_emp_id == emp_id && file_password == password)
                {
                    return true;
                }
            }
        }

        return false;
    }

private:
    string empId;
};

int main()
{
    while (true)
    {
        string emp_id, password;

        cout << "Enter the Employee Id: ";
        cin >> emp_id;
        if (emp_id == "exit")
            break;
        cout << "Enter password: ";
        cin >> password;

        if (!Authority::checkAuthorityCredentials(emp_id, password))
        {
            cout << "Incorrect Id or Password!\n";
            continue;
        }

        cout << "Login successful!\n";

        while (true)
        {
            int choice;
            cout << "\nMenu:\n1. Log Attendance\n2. Calculate Total Hours\n3. Logout\nEnter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                while (true)
                {
                    string roll_no;
                    cout << "Enter Roll No: ";
                    cin >> roll_no;
                    if (roll_no == "exit")
                        break;
                    bool valid = Student::search(roll_no);
                    if (!valid)
                        cout << "Invalid ID\n";
                    else
                        Person::logAttendance(roll_no);
                }
            }
            else if (choice == 2)
            {
                Person::calculateTotalHoursInClass();
            }
            else if (choice == 3)
            {
                cout << "Logging out...\n";
                break;
            }
            else
            {
                cout << "Invalid choice!\n";
            }
        }
    }

    return 0;
}
