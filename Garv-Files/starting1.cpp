// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <map>
// #include <ctime>
// #include <iomanip>
// #include <vector>

// using namespace std;

// // Base class Person
// class Person {
// public:
//     Person(string name, string dob, string email, string gender)
//         : name(name), dob(dob), email(email), gender(gender) {}

//     virtual ~Person() = default;
//     virtual string getUniqueID() const = 0;

//     // Static method to log attendance using unique ID
//     static void logAttendance(const string& uniqueId) {
//         if (!isValidID(uniqueId)) {
//             cout << "Error: Unique ID not found.\n";
//             return;
//         }
//         ofstream attendanceFile("attendance_entries.txt", ios::app);
//         time_t now = time(0);
//         attendanceFile << uniqueId << " " << ctime(&now);
//         attendanceFile.close();
//         cout << "Attendance logged for ID: " << uniqueId << endl;
//     }

//     // Static method to calculate total hours in class
//     static void calculateTotalHoursInClass() {
//         ifstream attendanceFile("attendance_entries.txt");
//         string line, uniqueId, dateStr;
//         map<string, double> totalHours;
//         map<string, time_t> lastInTime;

//         while (getline(attendanceFile, line)) {
//             istringstream iss(line);
//             if (!(iss >> uniqueId)) continue;
//             getline(iss, dateStr);
//             time_t currentTime = convertToTimeT(dateStr);

//             if (lastInTime.count(uniqueId) == 0) {
//                 lastInTime[uniqueId] = currentTime;
//             } else {
//                 double timeSpent = difftime(currentTime, lastInTime[uniqueId]) / 3600.0;
//                 totalHours[uniqueId] += timeSpent;
//                 lastInTime.erase(uniqueId);
//             }
//         }
//         attendanceFile.close();

//         cout << "Total hours spent in class:\n";
//         for (const auto& entry : totalHours) {
//             cout << "ID: " << entry.first << ", Hours: " << entry.second << " hours\n";
//         }
//     }

// protected:
//     string name, dob, email, gender;

// private:
//     // Static helper function to check if unique ID is valid
//     static bool isValidID(const string& uniqueId) {
//         ifstream dataFile("data.txt");
//         string line;

//         // Parse the "data.txt" file
//         bool inAuthoritySection = false, inStudentSection = false;

//         while (getline(dataFile, line)) {
//             if (line.find("# Authority") != string::npos) {
//                 inAuthoritySection = true;
//                 inStudentSection = false;
//             } else if (line.find("# Students") != string::npos) {
//                 inAuthoritySection = false;
//                 inStudentSection = true;
//             } else if (!line.empty() && line[0] != '#') {
//                 // Process line based on the section
//                 istringstream iss(line);
//                 string id;
//                 getline(iss, id, '|'); // Extract unique ID

//                 if ((inAuthoritySection || inStudentSection) && id == uniqueId) {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }

//     // Static helper function to convert string date to time_t
//     static time_t convertToTimeT(const string& timeStr) {
//         struct tm tm{};
//         istringstream ss(timeStr);
//         ss >> get_time(&tm, "%a %b %d %H:%M:%S %Y");
//         return mktime(&tm);
//     }
// };

// // Derived class Student
// class Student : public Person {
// public:
//     Student(string name, string dob, string email, string gender, string rollNo, string classSection, string password)
//         : Person(name, dob, email, gender), rollNo(rollNo), classSection(classSection), password(password) {}

//     string getUniqueID() const override { return rollNo; }

// private:
//     string rollNo, classSection, password;
//     friend class Authority;
// };

// // Derived class Teacher
// class Teacher : public Person {
// public:
//     Teacher(string name, string dob, string email, string gender, string empId, string password, vector<string> classes)
//         : Person(name, dob, email, gender), empId(empId), password(password), classes(classes) {}

//     string getUniqueID() const override { return empId; }

// private:
//     string empId, password;
//     vector<string> classes;
// };

// // Derived class Authority
// class Authority : public Teacher {
// public:
//     Authority(string name, string dob, string email, string gender, string empId, string password, vector<string> classes, string post)
//         : Teacher(name, dob, email, gender, empId, password, classes), post(post) {}

// private:
//     string post;
// };

// // Function to generate dummy data.txt file for testing
// void generateDataFile() {
//     ofstream dataFile("data.txt");
//     dataFile << "# Authority\n";
//     dataFile << "auth_101|Gurkaranbir|Karan007\n";
//     dataFile << "# Students\n";
//     dataFile << "11A_001|Alice|studentPass1|0\n";
//     dataFile << "11A_002|Bob|studentPass2|0\n";
//     dataFile.close();
//     cout << "Dummy data file generated as 'data.txt'.\n";
// }

// int main() {
//     while (true) {
//         string emp_id, password;

//         cout << "Enter the Employee Id: ";
//         cin >> emp_id;
//         cout << "Enter password: ";
//         cin >> password;

//         if (!Authority::isValidID(emp_id, password)) {
//             cout << "Incorrect Id or Password!\n";
//             continue;
//         }

//         cout << "Login successful!\n";

//         while (true) {
//             int choice;
//             cout << "\nMenu:\n1. Log Attendance\n2. Calculate Total Hours\n3. Logout\nEnter your choice: ";
//             cin >> choice;

//             if (choice == 1) {
//                 string roll_no;
//                 cout << "Enter Roll No: ";
//                 cin >> roll_no;

//                 auto student = Student::search(roll_no);
//                 if (student) {
//                     Person::logAttendance(student->getUniqueID());
//                 } else {
//                     cout << "Invalid Roll No!\n";
//                 }
//             } else if (choice == 2) {
//                 Person::calculateTotalHoursInClass();
//             } else if (choice == 3) {
//                 cout << "Logging out...\n";
//                 break;
//             } else {
//                 cout << "Invalid choice!\n";
//             }
//         }
//     }

//     return 0;
// }
