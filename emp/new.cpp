#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


struct Employee {
    int id;
    string name;
    string department;
};


void addEmployee();
void viewEmployees();
void deleteEmployee();
void updateEmployee();
void searchEmployee();
void saveToFile();
void loadFromFile();

vector<Employee> employees;


int main() {
    loadFromFile();
    int choice;
    while (true) {
        cout << "\nEmployee Management System" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. View Employees" << endl;
        cout << "3. Update Employee" << endl;
        cout << "4. Delete Employee" << endl;
        cout << "5. Search Employee" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: updateEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: searchEmployee(); break;
            case 6: saveToFile(); exit(0);
            default: cout << "Invalid choice! Try again." << endl;
        }
    }
    return 0;
}

void addEmployee() {
    Employee emp;
    cout << "Enter Employee ID: ";
    cin >> emp.id;


    for (const auto& e : employees) {
        if (e.id == emp.id) {
            cout << "Error: Employee ID already exists!" << endl;
            return;
        }
    }

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, emp.name);
    cout << "Enter Department: ";
    getline(cin, emp.department);
    employees.push_back(emp);
    saveToFile();
    cout << "Employee added successfully!" << endl;
}

void viewEmployees() {
    if (employees.empty()) {
        cout << "No employees found." << endl;
        return;
    }
    for (const auto& emp : employees) {
        cout << "\nID: " << emp.id << "\nName: " << emp.name << "\nDepartment: " << emp.department << endl;
    }
}

void updateEmployee() {
    int id;
    cout << "Enter Employee ID to update: ";
    cin >> id;
    bool found = false;

    for (auto& emp : employees) {
        if (emp.id == id) {
            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, emp.name);
            cout << "Enter New Department: ";
            getline(cin, emp.department);
            saveToFile();
            cout << "Employee updated successfully!" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Employee not found." << endl;
    }
}

void deleteEmployee() {
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if (it->id == id) {
            employees.erase(it);
            saveToFile();
            cout << "Employee deleted successfully!" << endl;
            return;
        }
    }
    cout << "Employee not found." << endl;
}

void searchEmployee() {
    int id;
    cout << "Enter Employee ID to search: ";
    cin >> id;

    for (const auto& emp : employees) {
        if (emp.id == id) {
            cout << "\nID: " << emp.id << "\nName: " << emp.name << "\nDepartment: " << emp.department << endl;
            return;
        }
    }
    cout << "Employee not found." << endl;
}

void saveToFile() {
    ofstream file("employees.data");
    if (!file) {
        cout << "Error saving to file!" << endl;
        return;
    }
    for (const auto& emp : employees) {
        file << emp.id << "\n" << emp.name << "\n" << emp.department << "\n";
    }
    file.close();
}

void loadFromFile() {
    ifstream file("employees.data");
    if (!file) {
        cout << "No existing employee records found." << endl;
        return;
    }
    Employee emp;
    employees.clear();
    while (file >> emp.id) {
        file.ignore();
        getline(file, emp.name);
        getline(file, emp.department);
        employees.push_back(emp);
    }
    file.close();
}

