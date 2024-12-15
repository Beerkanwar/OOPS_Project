#include"Classes.cpp"
// Write a program that allows an authority figure to access student attendence data for any date.

main() {
    string emp_id, password;
    cout << "Enter the Employee Id: ";
    cin >> emp_id;
    cout << "Enter password: ";
    cin >> password;
    if (!Authority::checkAuthorityCredentials(emp_id, password))
    {
        cout << "Incorrect Id or Password!\n";
        main();
    }
    cout << "Login successful!\n";
    string date;
    cout<<"Enter the date(in YYYY-MM-DD format) for which you wish to check the data: ";
    cin>>date;
    Authority::calculateTotalHoursInClass(date);
    return 0;
}