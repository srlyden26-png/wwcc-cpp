/*
Name: Your Name
Project: Student Tracker Midterm
Description: Tracks student data including GPA and attendance.
*/

#include <iostream>
#include <string>
using namespace std;

// Struct
struct Student {
    int id;
    string name;
    double gpa;
    int daysPresent;
    int totalDays;
};

// Constants
const int MAX_STUDENTS = 100;

// Function prototypes
void displayMenu();
void addStudent(Student students[], int &count);
void viewStudents(Student students[], int count);
void searchStudent(Student students[], int count);
double calculateAverageGPA(Student students[], int count);
void showTopStudents(Student students[], int count);

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students, count);
                break;
            case 2:
                viewStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                cout << "Average GPA: " << calculateAverageGPA(students, count) << endl;
                break;
            case 5:
                showTopStudents(students, count);
                break;
            case 6:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }

    } while (choice != 6);

    return 0;
}

// Menu
void displayMenu() {
    cout << "\n==== Student Tracker ====\n";
    cout << "1. Add Student\n";
    cout << "2. View Students\n";
    cout << "3. Search Student\n";
    cout << "4. Class GPA Average\n";
    cout << "5. Honor Roll (GPA >= 3.5)\n";
    cout << "6. Exit\n";
    cout << "Enter choice: ";
}

// Add student
void addStudent(Student students[], int &count) {
    if (count >= MAX_STUDENTS) {
        cout << "Student list is full.\n";
        return;
    }

    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, students[count].name);

    cout << "Enter ID: ";
    cin >> students[count].id;

    cout << "Enter GPA: ";
    cin >> students[count].gpa;

    cout << "Days present: ";
    cin >> students[count].daysPresent;

    cout << "Total days: ";
    cin >> students[count].totalDays;

    count++;
    cout << "Student added!\n";
}

// View all students
void viewStudents(Student students[], int count) {
    if (count == 0) {
        cout << "No students available.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        double attendance = 0.0;
        if (students[i].totalDays != 0) {
            attendance = (double)students[i].daysPresent / students[i].totalDays * 100;
        }

        cout << "\nName: " << students[i].name;
        cout << "\nID: " << students[i].id;
        cout << "\nGPA: " << students[i].gpa;
        cout << "\nAttendance: " << attendance << "%\n";
    }
}

// Search student
void searchStudent(Student students[], int count) {
    string search;
    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, search);

    bool found = false;

    for (int i = 0; i < count; i++) {
        // String find requirement
        if (students[i].name.find(search) != string::npos) {
            cout << "\nFound: " << students[i].name;

            // Substring example (first letter)
            string initial = students[i].name.substr(0, 1);
            cout << " (Initial: " << initial << ")";

            cout << "\nGPA: " << students[i].gpa << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }
}

// Average GPA
double calculateAverageGPA(Student students[], int count) {
    if (count == 0) return 0.0;

    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += students[i].gpa;
    }

    return sum / count;
}

// Honor roll
void showTopStudents(Student students[], int count) {
    bool found = false;

    for (int i = 0; i < count; i++) {
        if (students[i].gpa >= 3.5) {
            cout << students[i].name << " - GPA: " << students[i].gpa << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No honor roll students.\n";
    }
}