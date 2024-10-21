#include <iostream>

using namespace std;

class Employee {
public:
    string employeeId;
    string employeeName;
    int age;
    int mobileNumber;
    string department;
    double salary;

    Employee() {}

    Employee(const string& id, const string& name, int age, int mobile, const string& dept, double sal)
        : employeeId(id), employeeName(name), age(age), mobileNumber(mobile), department(dept), salary(sal) {}

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
int main(){
    int choice;
    while (true) {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. Update Employee\n";
        cout << "3. Delete Employee\n";
        cout << "4. Display All Employees\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, department;
            int age;
            double salary;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter department: ";
            cin >> department;
            cout << "Enter salary: ";
            cin >> salary;
            emp(0, name, age, department, salary);
        } else if (choice == 2) {
            int id;
            string name, department;
            int age;
            double salary;
            cout << "Enter employee ID to update: ";
            cin >> id;
            cout << "Enter new name: ";
            cin >> name;
            cout << "Enter new age: ";
            cin >> age;
            cout << "Enter new department: ";
            cin >> department;
            cout << "Enter new salary: ";
            cin >> salary;
            emp(id, name, age, department, salary);
        } else if (choice == 3) {
            int id;
            cout << "Enter employee ID to delete: ";
            cin >> id;
        } else if (choice == 4) {
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}