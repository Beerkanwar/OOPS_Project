// // #include <bits/stdc++.h>
// // #include <ctime>
// // #include <fstream>
// // #include <sstream>
// // #include <string>
// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <ctime>
// using namespace std;

// // Base Class: Person
// class person {
// protected:
//     string name;
//     string email;
//     char Gender;

// public:
//     person() : Gender('M') {}  // Default constructor
//     person(string name, string email, char gender)
//         : name(name), email(email), Gender(gender) {}
// };

// // Derived Class: Student
// class student : public person {
// protected:
//     string roll_no;
//     int sem;
//     string branch;
//     string password;

// public:
//     // Student Login Function
//     bool login(const string& rollNumber, const string& password) {
//         ifstream file("students.txt");
//         if (!file.is_open()) {
//             cerr << "Could not open the students file!" << endl;
//             return false;
//         }
//         string line;
//         while (getline(file, line)) {
//             stringstream ss(line);
//             string storedName, storedEmail, storedGender, storedRollNo, storedPassword, storedBranch, storedSem;
//             getline(ss, storedName, ',');
//             getline(ss, storedEmail, ',');
//             getline(ss, storedGender, ',');
//             getline(ss, storedRollNo, ',');
//             getline(ss, storedPassword, ',');
//             getline(ss, storedBranch, ',');
//             getline(ss, storedSem);
            
//             if (storedRollNo == rollNumber && storedPassword == password) {
//                 name = storedName;
//                 email = storedEmail;
//                 Gender = storedGender[0];
//                 roll_no = storedRollNo;
//                 this->password = storedPassword;
//                 branch = storedBranch;
//                 sem = stoi(storedSem);
//                 file.close();
//                 return true;
//             }
//         }
//         file.close();
//         return false;
//     }

//     void show_actions() {
//         cout << "Student Actions: 1. View Attendance, 2. View Grades" << endl;
//     }
// };

// // Derived Class: Teacher
// class teacher : public person {
// protected:
//     string emp_id;
//     string password;
//     string dept;

// public:
//     // Teacher Login Function
//     bool login(const string& empID, const string& password) {
//         ifstream file("teachers.txt");
//         if (!file.is_open()) {
//             cerr << "Could not open the teachers file!" << endl;
//             return false;
//         }
//         string line;
//         while (getline(file, line)) {
//             stringstream ss(line);
//             string storedName, storedEmail, storedGender, storedEmpID, storedPassword, storedDept;
//             getline(ss, storedName, ',');
//             getline(ss, storedEmail, ',');
//             getline(ss, storedGender, ',');
//             getline(ss, storedEmpID, ',');
//             getline(ss, storedPassword, ',');
//             getline(ss, storedDept);
            
//             if (storedEmpID == empID && storedPassword == password) {
//                 name = storedName;
//                 email = storedEmail;
//                 Gender = storedGender[0];
//                 emp_id = storedEmpID;
//                 this->password = storedPassword;
//                 dept = storedDept;
//                 file.close();
//                 return true;
//             }
//         }
//         file.close();
//         return false;
//     }

//     void show_actions() {
//         cout << "Teacher Actions: 1. Mark Attendance, 2. View Class List" << endl;
//     }
// };

// // Derived Class: Authority
// class authority : public person {
// protected:
//     string emp_id;
//     string password;
//     string post;

// public:
//     static authority search(const string& employeeID) {
//         ifstream file("authority.txt");
//         authority a;
//         if (!file.is_open()) {
//             cerr << "Could not open the authority file!" << endl;
//             return a;
//         }
//         string line;
//         while (getline(file, line)) {
//             stringstream ss(line);
//             string storedName, storedEmail, storedGender, storedEmpID, storedPassword, storedPost;
//             getline(ss, storedName, ',');
//             getline(ss, storedEmail, ',');
//             getline(ss, storedGender, ',');
//             getline(ss, storedEmpID, ',');
//             getline(ss, storedPassword, ',');
//             getline(ss, storedPost);
            
//             if (storedEmpID == employeeID) {
//                 a.name = storedName;
//                 a.email = storedEmail;
//                 a.Gender = storedGender[0];
//                 a.emp_id = storedEmpID;
//                 a.password = storedPassword;
//                 a.post = storedPost;
//                 file.close();
//                 return a;
//             }
//         }
//         file.close();
//         return a;
//     }

//     bool check_password(const string& password) const {
//         if (this->password.empty()) {
//             cerr << "Error: No password stored." << endl;
//             return false;
//         }
//         return this->password == password;
//     }

//     void show_actions() {
//         cout << "Authority Actions: 1. View Reports, 2. Modify Data" << endl;
//     }
// };

// int main() {
//     // Example Login Test for Student
//     student s1;
//     if (s1.login("rollNumber123", "password123")) {
//         cout << "Student login successful!" << endl;
//         s1.show_actions();
//     } else {
//         cout << "Invalid student credentials." << endl;
//     }

//     // Example Login Test for Teacher
//     teacher t1;
//     if (t1.login("empID456", "password456")) {
//         cout << "Teacher login successful!" << endl;
//         t1.show_actions();
//     } else {
//         cout << "Invalid teacher credentials." << endl;
//     }

//     // Example Search and Password Check for Authority
//     authority a1 = authority::search("empID789");
//     if (a1.check_password("password789")) {
//         cout << "Authority login successful!" << endl;
//         a1.show_actions();
//     } else {
//         cout << "Invalid authority credentials." << endl;
//     }

//     return 0;
// }




// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <ctime>
// using namespace std;

// // Base Class: Person
// class person {
// protected:
//     string name;
//     string email;
//     char Gender;

// public:
//     person() : Gender('M') {}  // Default constructor
//     person(string name, string email, char gender)
//         : name(name), email(email), Gender(gender) {}
// };

// // Derived Class: Student
// class student : public person {
// protected:
//     string roll_no;
//     int sem;
//     string branch;
//     string password;

// public:
//     bool login(const string& rollNumber, const string& password) {
//         // ifstream file("students.txt");
//         ifstream file("/Users/garvdeepsingh/Documents/C++/oopsProject/students.txt");
//         if (!file.is_open()) {
//             cerr << "Could not open the students file!" << endl;
//             return false;
//         }
//         string line;
//         while (getline(file, line)) {
//             stringstream ss(line);
//             string storedName, storedEmail, storedGender, storedRollNo, storedPassword, storedBranch, storedSem;
//             getline(ss, storedName, ',');
//             getline(ss, storedEmail, ',');
//             getline(ss, storedGender, ',');
//             getline(ss, storedRollNo, ',');
//             getline(ss, storedPassword, ',');
//             getline(ss, storedBranch, ',');
//             getline(ss, storedSem);

//             if (storedRollNo == rollNumber && storedPassword == password) {
//                 name = storedName;
//                 email = storedEmail;
//                 Gender = storedGender[0];
//                 roll_no = storedRollNo;
//                 this->password = storedPassword;
//                 branch = storedBranch;
//                 sem = stoi(storedSem);
//                 file.close();
//                 return true;
//             }
//         }
//         file.close();
//         return false;
//     }

//     void show_actions() {
//         cout << "Student Actions: 1. View Attendance, 2. View Grades" << endl;
//     }
// };

// // Derived Class: Teacher
// class teacher : public person {
// protected:
//     string emp_id;
//     string password;
//     string dept;

// public:
//     bool login(const string& empID, const string& password) {
//         // ifstream file("teachers.txt");
//         ifstream file("/Users/garvdeepsingh/Documents/C++/oopsProject/teachers.txt");
//         if (!file.is_open()) {
//             cerr << "Could not open the teachers file!" << endl;
//             return false;
//         }
//         string line;
//         while (getline(file, line)) {
//             stringstream ss(line);
//             string storedName, storedEmail, storedGender, storedEmpID, storedPassword, storedDept;
//             getline(ss, storedName, ',');
//             getline(ss, storedEmail, ',');
//             getline(ss, storedGender, ',');
//             getline(ss, storedEmpID, ',');
//             getline(ss, storedPassword, ',');
//             getline(ss, storedDept);

//             if (storedEmpID == empID && storedPassword == password) {
//                 name = storedName;
//                 email = storedEmail;
//                 Gender = storedGender[0];
//                 emp_id = storedEmpID;
//                 this->password = storedPassword;
//                 dept = storedDept;
//                 file.close();
//                 return true;
//             }
//         }
//         file.close();
//         return false;
//     }

//     void show_actions() {
//         cout << "Teacher Actions: 1. Mark Attendance, 2. View Class List" << endl;
//     }
// };

// // Derived Class: Authority
// class authority : public person {
// protected:
//     string emp_id;
//     string password;
//     string post;

// public:
//     static authority search(const string& employeeID) {
//         // ifstream file("authority.txt");
//         ifstream file("/Users/garvdeepsingh/Documents/C++/oopsProject/authority.txt");
//         authority a;
//         if (!file.is_open()) {
//             cerr << "Could not open the authority file!" << endl;
//             return a;
//         }
//         string line;
//         while (getline(file, line)) {
//             stringstream ss(line);
//             string storedName, storedEmail, storedGender, storedEmpID, storedPassword, storedPost;
//             getline(ss, storedName, ',');
//             getline(ss, storedEmail, ',');
//             getline(ss, storedGender, ',');
//             getline(ss, storedEmpID, ',');
//             getline(ss, storedPassword, ',');
//             getline(ss, storedPost);

//             if (storedEmpID == employeeID) {
//                 a.name = storedName;
//                 a.email = storedEmail;
//                 a.Gender = storedGender[0];
//                 a.emp_id = storedEmpID;
//                 a.password = storedPassword;
//                 a.post = storedPost;
//                 file.close();
//                 return a;
//             }
//         }
//         file.close();
//         return a;
//     }

//     bool check_password(const string& password) const {
//         if (this->password.empty()) {
//             cerr << "Error: No password stored." << endl;
//             return false;
//         }
//         return this->password == password;
//     }

//     void show_actions() {
//         cout << "Authority Actions: 1. View Reports, 2. Modify Data" << endl;
//     }
// };

// int main() {
//     // Example Login Test for Student
//     student s1;
//     if (s1.login("rollNumber123", "password123")) {
//         cout << "Student login successful!" << endl;
//         s1.show_actions();
//     } else {
//         cout << "Invalid student credentials." << endl;
//     }

//     // Example Login Test for Teacher
//     teacher t1;
//     if (t1.login("empID456", "password456")) {
//         cout << "Teacher login successful!" << endl;
//         t1.show_actions();
//     } else {
//         cout << "Invalid teacher credentials." << endl;
//     }

//     // Example Search and Password Check for Authority
//     authority a1 = authority::search("empID001");
//     if (a1.check_password("password001")) {
//         cout << "Authority login successful!" << endl;
//         a1.show_actions();
//     } else {
//         cout << "Invalid authority credentials." << endl;
//     }

//     return 0;
// }


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
using namespace std;

// Utility function for encrypting a password (basic example)
string encrypt_password(const string& password) {
    string encrypted;
    for (char ch : password) {
        encrypted += ch + 3;  // Simple Caesar cipher
    }
    return encrypted;
}

// Base Class: Person
class person {
protected:
    string name;
    string email;
    char Gender;

public:
    person() : Gender('M') {}  // Default constructor
    person(string name, string email, char gender)
        : name(name), email(email), Gender(gender) {}
    virtual void show_actions() = 0; // Pure virtual function
};

// Derived Class: Student
class student : public person {
protected:
    string roll_no;
    int sem;
    string branch;
    string password;

public:
    bool login(const string& rollNumber, const string& password) {
        ifstream file("students.txt");
        if (!file.is_open()) {
            cerr << "Could not open the students file!" << endl;
            return false;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string storedName, storedEmail, storedGender, storedRollNo, storedPassword, storedBranch, storedSem;
            getline(ss, storedName, ',');
            getline(ss, storedEmail, ',');
            getline(ss, storedGender, ',');
            getline(ss, storedRollNo, ',');
            getline(ss, storedPassword, ',');
            getline(ss, storedBranch, ',');
            getline(ss, storedSem);

            if (storedRollNo == rollNumber && storedPassword == encrypt_password(password)) {
                name = storedName;
                email = storedEmail;
                Gender = storedGender[0];
                roll_no = storedRollNo;
                this->password = storedPassword;
                branch = storedBranch;
                sem = stoi(storedSem);
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    void mark_attendance() {
        ofstream file("attendance.txt", ios::app);
        if (!file.is_open()) {
            cerr << "Could not open the attendance file!" << endl;
            return;
        }
        time_t now = time(0);
        char* dt = ctime(&now);
        file << roll_no << "," << dt;
        file.close();
        cout << "Attendance marked for " << roll_no << endl;
    }

    void view_grades() {
        ifstream file("grades.txt");
        if (!file.is_open()) {
            cerr << "Could not open the grades file!" << endl;
            return;
        }
        string line;
        cout << "Grades for " << roll_no << ":\n";
        while (getline(file, line)) {
            stringstream ss(line);
            string storedRollNo, subject, grade;
            getline(ss, storedRollNo, ',');
            getline(ss, subject, ',');
            getline(ss, grade);
            if (storedRollNo == roll_no) {
                cout << "Subject: " << subject << " | Grade: " << grade << endl;
            }
        }
        file.close();
    }

    void show_actions() override {
        int choice;
        do {
            cout << "\nStudent Actions:\n1. Mark Attendance\n2. View Grades\n3. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    mark_attendance();
                    break;
                case 2:
                    view_grades();
                    break;
                case 3:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 3);
    }
};

// Derived Class: Teacher
class teacher : public person {
protected:
    string emp_id;
    string password;
    string dept;

public:
    bool login(const string& empID, const string& password) {
        ifstream file("teachers.txt");
        if (!file.is_open()) {
            cerr << "Could not open the teachers file!" << endl;
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

            if (storedEmpID == empID && storedPassword == encrypt_password(password)) {
                name = storedName;
                email = storedEmail;
                Gender = storedGender[0];
                emp_id = storedEmpID;
                this->password = storedPassword;
                dept = storedDept;
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    void mark_attendance(const string& studentRollNo) {
        ofstream file("attendance.txt", ios::app);
        if (!file.is_open()) {
            cerr << "Could not open the attendance file!" << endl;
            return;
        }
        time_t now = time(0);
        char* dt = ctime(&now);
        file << studentRollNo << "," << dt;
        file.close();
        cout << "Attendance marked for student " << studentRollNo << endl;
    }

    void view_class_list() {
        ifstream file("students.txt");
        if (!file.is_open()) {
            cerr << "Could not open the students file!" << endl;
            return;
        }
        string line;
        cout << "Class List:\n";
        while (getline(file, line)) {
            stringstream ss(line);
            string storedName, storedRollNo, branch;
            getline(ss, storedName, ','); 
            ss.ignore(numeric_limits<streamsize>::max(), ','); 
            getline(ss, storedRollNo, ',');
            ss.ignore(numeric_limits<streamsize>::max(), ','); 
            getline(ss, branch, ',');
            cout << "Name: " << storedName << " | Roll No: " << storedRollNo << " | Branch: " << branch << endl;
        }
        file.close();
    }

    void show_actions() override {
        int choice;
        do {
            cout << "\nTeacher Actions:\n1. Mark Attendance\n2. View Class List\n3. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
                case 1: {
                    string rollNo;
                    cout << "Enter student roll number to mark attendance: ";
                    cin >> rollNo;
                    mark_attendance(rollNo);
                    break;
                }
                case 2:
                    view_class_list();
                    break;
                case 3:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 3);
    }
};

// Derived Class: Authority
class authority : public person {
protected:
    string emp_id;
    string password;
    string post;

public:
    static authority search(const string& employeeID) {
        ifstream file("authority.txt");
        authority a;
        if (!file.is_open()) {
            cerr << "Could not open the authority file!" << endl;
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
        return !this->password.empty() && this->password == encrypt_password(password);
    }

    void modify_data() {
        // Data modification functionality here
        cout << "Modify Data feature to be implemented\n";
    }

    void show_reports() {
        // Show reports functionality here
        cout << "Reports feature to be implemented\n";
    }

    void show_actions() override {
        int choice;
        do {
            cout << "\nAuthority Actions:\n1. View Reports\n2. Modify Data\n3. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;
            switch (choice) {
                case 1:
                    show_reports();
                    break;
                                case 2:
                    modify_data();
                    break;
                case 3:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 3);
    }
};

// Main Function for Authentication and Menu Navigation
int main() {
    int userType;
    cout << "Welcome to the College Attendance Management System\n";
    cout << "Select User Type:\n1. Student\n2. Teacher\n3. Authority\n4. Exit\n";
    cout << "Enter choice: ";
    cin >> userType;

    switch (userType) {
        case 1: {
            // Student Login and Menu
            student s;
            string rollNo, password;
            cout << "Enter Roll Number: ";
            cin >> rollNo;
            cout << "Enter Password: ";
            cin >> password;
            if (s.login(rollNo, password)) {
                cout << "Student login successful!\n";
                s.show_actions();
            } else {
                cout << "Invalid student credentials.\n";
            }
            break;
        }
        case 2: {
            // Teacher Login and Menu
            teacher t;
            string empID, password;
            cout << "Enter Employee ID: ";
            cin >> empID;
            cout << "Enter Password: ";
            cin >> password;
            if (t.login(empID, password)) {
                cout << "Teacher login successful!\n";
                t.show_actions();
            } else {
                cout << "Invalid teacher credentials.\n";
            }
            break;
        }
        case 3: {
            // Authority Login and Menu
            string empID, password;
            cout << "Enter Employee ID: ";
            cin >> empID;
            authority a = authority::search(empID);
            cout << "Enter Password: ";
            cin >> password;
            if (a.check_password(password)) {
                cout << "Authority login successful!\n";
                a.show_actions();
            } else {
                cout << "Invalid authority credentials.\n";
            }
            break;
        }
        case 4:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Exiting...\n";
    }

    return 0;
}