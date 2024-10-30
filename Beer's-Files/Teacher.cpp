#include"Project.cpp"

main(){
    teacher t1;
    string emp_id, password;
    cout<<"Login \n";
    cout<<"Enter your Employee Id: ";
    cin>>emp_id;
    cout<<"Enter your password: ";
    cin>>password;
    if(/*t1.login(emp_id, password)*/true){
        cout<<"Login successful!\n";
    }
    else{
        cout<<"Incorrect Employee Id or Password!\n";
        cout<<"Press any key to continue... ";
        getchar();
        main();
    }
    while(true){
        t1.show_actions();
        int ch;
        cout<<"Make your choice: ";
        cin>>ch;
        switch(ch){
            case 1:
                // Check attendence
                break;
            case 2:
                // Update attendence
                break;
            case 3:
                // Update marks
                break;
            case 4:
                // Change password
                break;
            case 5:
                // Logout
                return 0;
                break;
            default:
                cout<<"Invalid choice!\n";
                break;
        }
    }
    return 0;
}