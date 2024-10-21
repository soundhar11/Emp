#include <iostream>
#include <sqlite3.h> 
using namespace std;

// Employee class
class Employee {
public:
    string employeeId;
    string employeeName;
    int age;
    int mobileNumber;
    string department;
    double salary;

    // Constructor
    Employee() {}

    Employee(const string& id, const string& name, int age, int mobile, const string& dept, double sal)
        : employeeId(id), employeeName(name), age(age), mobileNumber(mobile), department(dept), salary(sal) {}

    // Method to display employee details
    void displayDetails() const {
        cout << "Employee ID: " << employeeId << endl;
        cout << "Employee Name: " << employeeName << endl;
        cout << "Age: " << age << endl;
        cout << "Mobile Number: " << mobileNumber << endl;
        cout << "Department: " << department << endl;
        cout << "Salary: " << salary << endl;
        cout << "-----------------------------" << endl;
    }
};

// DatabaseManager class to manage SQLite operations
class DatabaseManager {
private:
    sqlite3* db;

public:
    DatabaseManager(const string& dbName) {
        if (sqlite3_open(dbName.c_str(), &db) != SQLITE_OK) {
            cout << "Error opening database: " << sqlite3_errmsg(db) << endl;
            db = nullptr;
        }
        else {
            cout << "Database opened successfully." << endl;
        }
    }

    ~DatabaseManager() {
        if (db) {
            sqlite3_close(db);
            cout << "Database closed." << endl;
        }
    }

    bool executeQuery(const string& query) {
        char* errMsg = nullptr;
        if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
            cout << "SQL error: " << errMsg << endl;
            sqlite3_free(errMsg);
            return false;
        }
        return true;
    }

    sqlite3* getDatabase() const {
        return db;
    }
};

// EmployeeManager class to manage employee operations
class EmployeeManager {
private:
    DatabaseManager& dbManager;

public:
    EmployeeManager(DatabaseManager& db) : dbManager(db) {
        // Create the employee table if it does not exist
        string createTableQuery = "CREATE TABLE IF NOT EXISTS Employee ("
            "EmployeeID TEXT PRIMARY KEY, "
            "Name TEXT NOT NULL, "
            "Age INTEGER, "
            "MobileNumber INTEGER, "
            "Department TEXT, "
            "Salary REAL);";
        dbManager.executeQuery(createTableQuery);
    }

    // Method to add an employee to the database
    void addEmployee(const Employee& employee) {
        string query = "INSERT INTO Employee (EmployeeID, Name, Age, MobileNumber, Department, Salary) VALUES ('" +
            employee.employeeId + "', '" + employee.employeeName + "', " + to_string(employee.age) + ", " +
            to_string(employee.mobileNumber) + ", '" + employee.department + "', " +
            to_string(employee.salary) + ");";
        if (dbManager.executeQuery(query)) {
            cout << "Employee added successfully." << endl;
        }
    }

    // Method to display all employees
    static int displayCallback(void* NotUsed, int argc, char** argv, char** azColName) {
        for (int i = 0; i < argc; i++) {
            cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
        }
        cout << "-----------------------------" << endl;
        return 0;
    }

    void displayAllEmployees() {
        string query = "SELECT * FROM Employee;";
        if (sqlite3_exec(dbManager.getDatabase(), query.c_str(), displayCallback, nullptr, nullptr) != SQLITE_OK) {
            cout << "Failed to retrieve employee records." << endl;
        }
    }
};

// Main function
int main() {
    DatabaseManager dbManager("employee.db");
    EmployeeManager empManager(dbManager);

    int choice;
    while (true) {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string id, name, department;
            int age, mobile;
            double salary;
            cout << "Enter Employee ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Mobile Number: ";
            cin >> mobile;
            cout << "Enter Department: ";
            cin >> department;
            cout << "Enter Salary: ";
            cin >> salary;
            empManager.addEmployee(Employee(id, name, age, mobile, department, salary));
        }
        else if (choice == 2) {
            empManager.displayAllEmployees();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
