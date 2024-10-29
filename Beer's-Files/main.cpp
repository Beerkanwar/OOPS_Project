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
        switch(ch){
            case 1:
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
                while(true){
                    string roll_no;
                    cout<<"Enter Roll No: ";
                    cin>>roll_no;
                    if(roll_no == "-1"/*Special code to break the loop*/){
                        break;
                    }else if(/*= student::search(roll_no)*/true){
                        //Insert roll number and time in the file.
                    }else{
                        cout<<"Ivalid Roll No!"<<endl;
                    }
                }
                break;
            case 2:
                // p = new authority();
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
    }
    return 0;
}
