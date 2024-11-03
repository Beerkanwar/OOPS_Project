#include"Project.cpp"

int main(){
    while(true){
        string emp_id, password;
        cout<<"Enter the Employee Id: ";
        cin>>emp_id;
        cout<<"Enter password: ";
        cin>>password;
        authority a1 /*= authority::search(emp_id)*/;
        // if(!a1.check_password(password)){
        //     cout<<"Incorrect Id or Password!"<<endl;
        //     continue;
        // }
        cout<<"Login successful!"<<endl;
        int ch;
        cout<<"Enter your choice: ";
        cin>>ch;
        // person* p = nullptr;
        if(ch == 1){
            // Attendence system.
            // Get the current time
            // time_t t = time(nullptr);
            // tm* now = localtime(&t);
            // Create a string stream to format the date
            // ostringstream oss;
            // oss<<(now->tm_year + 1900)<<'-'<<setw(2)<<setfill('0')<<(now->tm_mon + 1)<<'-'<<setw(2)<<setfill('0')<<now->tm_mday;
            // string fileName = oss.str() + ".txt";
            // Open the file in write mode
            // ofstream file(fileName);
            // FILE* f = fopen(fileName.c_str(), "w");
            // if (!f.is_open()) {
            //     cerr<<"Failed to create or open the file: "<<fileName<<endl;
            //     return 1;
            // }
            ////////////////////////////////////
            // Attendance system.
            // Get the current date for the filename
            time_t t = time(nullptr);
            tm* now = localtime(&t);
            ostringstream oss;
            oss << (now->tm_year + 1900) << '-' 
                << setw(2) << setfill('0') << (now->tm_mon + 1) << '-' 
                << setw(2) << setfill('0') << now->tm_mday;
            string fileName = oss.str() + ".txt";

            // Open the file in append mode
            ofstream file(fileName, ios::app);
            if (!file.is_open()) {
                cerr << "Failed to create or open the file: " << fileName << endl;
                return 1;
            }

            while (true) {
                string roll_no;
                cout << "Enter Roll No (or -1 to exit): ";
                cin >> roll_no;
                if (roll_no == "-1") {
                    break; // Special code to break the loop
                } else if (true /* student::search(roll_no) */) { // Replace with actual search condition
                    // Get current time for attendance
                    time_t now = time(0);
                    tm* ltm = localtime(&now);
                    // Format time as HH:MM:SS
                    ostringstream timeStream;
                    timeStream << setw(2) << setfill('0') << ltm->tm_hour << ":"
                                << setw(2) << setfill('0') << ltm->tm_min << ":"
                                << setw(2) << setfill('0') << ltm->tm_sec;

                    // Write roll number and time to the file
                    file << "Roll No: " << roll_no << ", Time: " << timeStream.str() << endl;
                    cout << "Attendance recorded for Roll No: " << roll_no << " at " << timeStream.str() << endl;
                } else {
                    cout << "Invalid Roll No!" << endl;
                }
            }
            file.close(); // Close the file after recording
            //////////////////////////////
            // while(true){
            //     string roll_no;
            //     cout<<"Enter Roll No: ";
            //     cin>>roll_no;
            //     if(roll_no == "-1"/*Special code to break the loop*/){
            //         break;
            //     }else if(/*= student::search(roll_no)*/true){
            //         //Insert roll number and time in the file.
            //     }else{
            //         cout<<"Ivalid Roll No!"<<endl;
            //     }
            // }
        }else if(ch == 2){
            // p = new authority();
        }else{
            cout<<"Invalid choice!"<<endl;
            cout<<"Press any key to continue..."<<endl;
            getchar();
            continue;
        }
    }
    return 0;
}
