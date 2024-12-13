#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>
#include <iostream>

using namespace std;

int main() {
    try {
        // Initialize MySQL Driver and establish connection
        sql::mysql::MySQL_Driver* driver;
        sql::Connection* conn;
        driver = sql::mysql::get_mysql_driver_instance();
        conn = driver->connect("tcp://127.0.0.1:3306", "root", "your_password"); // Change as per your credentials

        // Select the database to use
        conn->setSchema("your_database_name");  // Change to your database

        // Create a statement object
        sql::Statement* stmt = conn->createStatement();

        // SQL command to create the students table
        string createTableQuery = R"(
            CREATE TABLE IF NOT EXISTS students (
                student_id INT PRIMARY KEY AUTO_INCREMENT,
                name VARCHAR(100) NOT NULL,
                email VARCHAR(100) NOT NULL,
                gender CHAR(1) NOT NULL,
                roll_no VARCHAR(20) NOT NULL UNIQUE,
                sem INT NOT NULL,
                branch VARCHAR(50) NOT NULL,
                password VARCHAR(255) NOT NULL,
                registration_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        )";
        stmt->execute(createTableQuery);
        cout << "Table created successfully!" << endl;

        // Inserting some sample data
        sql::PreparedStatement* pstmt;
        pstmt = conn->prepareStatement("INSERT INTO students (name, email, gender, roll_no, sem, branch, password) VALUES (?, ?, ?, ?, ?, ?, ?);");

        pstmt->setString(1, "John Doe");
        pstmt->setString(2, "johndoe@example.com");
        pstmt->setString(3, "M");
        pstmt->setString(4, "CS101");
        pstmt->setInt(5, 3);
        pstmt->setString(6, "Computer Science");
        pstmt->setString(7, "password123");
        pstmt->execute();

        pstmt->setString(1, "Jane Smith");
        pstmt->setString(2, "janesmith@example.com");
        pstmt->setString(3, "F");
        pstmt->setString(4, "ME102");
        pstmt->setInt(5, 4);
        pstmt->setString(6, "Mechanical Engineering");
        pstmt->setString(7, "password456");
        pstmt->execute();

        cout << "Sample data inserted successfully!" << endl;

        // Clean up
        delete pstmt;
        delete stmt;
        delete conn;
    } catch (sql::SQLException& e) {
        cout << "SQLException: " << e.what() << endl;
        cout << "MySQL error code: " << e.getErrorCode() << endl;
    }
    return 0;
}