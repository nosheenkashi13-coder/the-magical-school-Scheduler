#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

// -----------------------------
// STRUCTURES
// -----------------------------
struct Teacher {
    int id;
    string name;
    string subject;
    string availability;
    Teacher* next;
    Teacher* prev;
};

struct ClassRoom {
    string className;
    string subject;
};

struct Schedule {
    string teacherName;
    string className;
    string subject;
};

// -----------------------------
// GLOBALS
// -----------------------------
Teacher* headTeacher = NULL;
Teacher* tailTeacher = NULL;
queue<ClassRoom> classQueue;
stack<Schedule> scheduleStack;

// -----------------------------
// TEACHER MANAGEMENT (Doubly Linked List)
// -----------------------------
void addTeacher() {
    Teacher* newT = new Teacher;

    cout << "\nEnter Teacher ID: ";
    cin >> newT->id;
    cout << "Enter Name: ";
    cin >> newT->name;
    cout << "Enter Subject: ";
    cin >> newT->subject;
    cout << "Enter Availability: ";
    cin >> newT->availability;

    newT->next = NULL;
    newT->prev = NULL;

    // First teacher
    if (headTeacher == NULL) {
        headTeacher = tailTeacher = newT;
    }
    else {
        tailTeacher->next = newT;
        newT->prev = tailTeacher;
        tailTeacher = newT;
    }

    cout << "? Teacher added successfully.\n";
}

void viewTeachers() {
    if (headTeacher == NULL) {
        cout << "? No teachers found.\n";
        return;
    }

    cout << "\n?? Teacher List (Forward):\n";
    Teacher* temp = headTeacher;
    while (temp != NULL) {
        cout << "ID: " << temp->id
             << " | Name: " << temp->name
             << " | Subject: " << temp->subject
             << " | Availability: " << temp->availability << endl;
        temp = temp->next;
    }
}

void viewTeachersReverse() {
    if (tailTeacher == NULL) {
        cout << "? No teachers found.\n";
        return;
    }

    cout << "\n?? Teacher List (Reverse):\n";
    Teacher* temp = tailTeacher;
    while (temp != NULL) {
        cout << "ID: " << temp->id
             << " | Name: " << temp->name
             << " | Subject: " << temp->subject
             << " | Availability: " << temp->availability << endl;
        temp = temp->prev;
    }
}

void updateTeacher() {
    int id;
    cout << "\nEnter Teacher ID to update: ";
    cin >> id;

    Teacher* temp = headTeacher;

    while (temp != NULL && temp->id != id)
        temp = temp->next;

    if (temp == NULL) {
        cout << "? Teacher not found.\n";
        return;
    }

    cout << "Enter new Name: ";
    cin >> temp->name;
    cout << "Enter new Subject: ";
    cin >> temp->subject;
    cout << "Enter new Availability: ";
    cin >> temp->availability;

    cout << "? Teacher updated successfully.\n";
}

void deleteTeacher() {
    int id;
    cout << "\nEnter Teacher ID to delete: ";
    cin >> id;

    Teacher* temp = headTeacher;

    while (temp != NULL && temp->id != id)
        temp = temp->next;

    if (temp == NULL) {
        cout << "? Teacher not found.\n";
        return;
    }

    // Only node
    if (temp == headTeacher && temp == tailTeacher) {
        headTeacher = tailTeacher = NULL;
    }
    else if (temp == headTeacher) { // Delete at head
        headTeacher = headTeacher->next;
        headTeacher->prev = NULL;
    }
    else if (temp == tailTeacher) { // Delete at tail
        tailTeacher = tailTeacher->prev;
        tailTeacher->next = NULL;
    }
    else { // Middle
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    delete temp;
    cout << "? Teacher deleted successfully.\n";
}

// -----------------------------
// CLASS MANAGEMENT (Queue)
// -----------------------------
void addClass() {
    ClassRoom c;

    cout << "\nEnter Class Name: ";
    cin >> c.className;
    cout << "Enter Subject: ";
    cin >> c.subject;

    classQueue.push(c);

    cout << "? Class added to queue.\n";
}

void viewClasses() {
    if (classQueue.empty()) {
        cout << "? No classes scheduled.\n";
        return;
    }

    cout << "\n?? Classes in Queue:\n";
    queue<ClassRoom> temp = classQueue;

    while (!temp.empty()) {
        cout << "Class: " << temp.front().className
             << " | Subject: " << temp.front().subject << endl;
        temp.pop();
    }
}

// -----------------------------
// CONFLICT CHECKER (Stack search)
// -----------------------------
bool checkConflict(string teacherName, string subject) {
    stack<Schedule> temp = scheduleStack;

    while (!temp.empty()) {
        Schedule s = temp.top();
        temp.pop();

        if (s.teacherName == teacherName && s.subject == subject)
            return true;
    }
    return false;
}

// -----------------------------
// SCHEDULE GENERATOR (Stack)
// -----------------------------
void generateSchedule() {
    if (headTeacher == NULL || classQueue.empty()) {
        cout << "? Need at least one teacher and one class.\n";
        return;
    }

    Teacher* tempTeacher = headTeacher;
    queue<ClassRoom> tempClass = classQueue;

    cout << "\n?? Generating Schedule...\n";

    while (!tempClass.empty()) {
        ClassRoom c = tempClass.front();
        tempClass.pop();

        if (checkConflict(tempTeacher->name, c.subject)) {
            cout << "? Conflict: " << tempTeacher->name
                 << " already assigned for subject " << c.subject << endl;
        } 
        else {
            Schedule s;
            s.teacherName = tempTeacher->name;
            s.className = c.className;
            s.subject = c.subject;

            scheduleStack.push(s);

            cout << "? " << s.teacherName << " assigned to "
                 << s.className << " (" << s.subject << ")\n";
        }

        tempTeacher = tempTeacher->next;
        if (tempTeacher == NULL)
            tempTeacher = headTeacher;
    }

    cout << "?? Schedule generation completed!\n";
}

void viewTimetable() {
    if (scheduleStack.empty()) {
        cout << "? Timetable is empty.\n";
        return;
    }

    cout << "\n?? Timetable (Latest First):\n";
    stack<Schedule> temp = scheduleStack;

    while (!temp.empty()) {
        Schedule s = temp.top();
        temp.pop();

        cout << "Teacher: " << s.teacherName
             << " | Class: " << s.className
             << " | Subject: " << s.subject << endl;
    }
}

// -----------------------------
// MENUS
// -----------------------------
void teacherMenu() {
    int choice;

    do {
        cout << "\n========== ????? TEACHER MANAGEMENT ==========\n";
        cout << "1. Add Teacher\n";
        cout << "2. View Teachers\n";
        cout << "3. View Teachers Reverse\n";
        cout << "4. Update Teacher\n";
        cout << "5. Delete Teacher\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTeacher(); break;
            case 2: viewTeachers(); break;
            case 3: viewTeachersReverse(); break;
            case 4: updateTeacher(); break;
            case 5: deleteTeacher(); break;
        }
    } while (choice != 0);
}

void classMenu() {
    int choice;

    do {
        cout << "\n========== ?? CLASS MANAGEMENT ==========\n";
        cout << "1. Add Class\n";
        cout << "2. View Classes\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addClass(); break;
            case 2: viewClasses(); break;
        }
    } while (choice != 0);
}

void scheduleMenu() {
    int choice;

    do {
        cout << "\n========== ?? SCHEDULE ==========\n";
        cout << "1. Generate Schedule\n";
        cout << "2. View Timetable\n";
        cout << "0. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: generateSchedule(); break;
            case 2: viewTimetable(); break;
        }
    } while (choice != 0);
}

// -----------------------------
// MAIN MENU
// -----------------------------
int main() {
    int choice;

    do {
        cout << "\n============================================";
        cout << "\n       ?? SCHOOL TIMETABLE SCHEDULER";
        cout << "\n============================================";
        cout << "\n1. Teacher Management";
        cout << "\n2. Class Management";
        cout << "\n3. Schedule Generator";
        cout << "\n4. View Timetable";
        cout << "\n0. Exit";
        cout << "\n--------------------------------------------";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: teacherMenu(); break;
            case 2: classMenu(); break;
            case 3: scheduleMenu(); break;
            case 4: viewTimetable(); break;
            case 0: cout << "\n? Exiting System...\n"; break;
            default: cout << "? Invalid Option!\n";
        }
    } while (choice != 0);

    return 0;
}
