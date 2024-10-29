#include"Project.cpp"

int main(){
    student s1;
    string roll, pass;
    cout<<"Welcome to Student portal!\n";
    cout<<"Login \n";
    cout<<"Enter your roll number: ";
    cin>>roll;
    cout<<"Enter your password: ";
    cin>>pass;
    if(/*s1.login(roll, pass)*/true){
        cout<<"Login successful!\n";
    }else{
        cout<<"Incorrect roll number or password!\n";
        cout<<"Press any key to continue...";
        getchar();
        main();
    }
    while(true){
        s1.show_actions();
        int ch;
        cout<<"Make your choice: ";
        cin>>ch;
        switch(ch){
            case 1:
                // Check attendence
                break;
            case 2:
                // Complaint Portal
                break;
            case 3:
                // View profile
                break;
            case 4:
                // Logout
                return 0;
                break;
            default:
                cout<<"Invalid choice!";
                break;
        }
    }
    return 0;
}