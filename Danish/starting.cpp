#include"Classes.cpp"

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
            cout << "\nSelect an option:\n1. Log Attendance\n2. Calculate Total Hours\n3. Logout\nEnter your choice: ";
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
