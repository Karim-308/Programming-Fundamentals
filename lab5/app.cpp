#include "app.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "../lab1/terminal.h"
#include "employee.h"
#include "swap.h"

using namespace std;

static Employee* employees = NULL;
static int employeeCount = 0;

#ifdef __linux__
#include <termios.h>
#include <unistd.h>

struct RawState {
    termios original;
    bool ready;
    bool active;
};

static RawState rawState = {};
#endif

static void prepareRawMode() {
#ifdef __linux__
    if (!rawState.ready) {
        tcgetattr(STDIN_FILENO, &rawState.original);
        rawState.ready = true;
        rawState.active = false;
    }
#endif
}

static void enableRawInput() {
#ifdef __linux__
    prepareRawMode();
    if (!rawState.active) {
        termios raw = rawState.original;
        raw.c_lflag &= ~(ICANON | ECHO);
        raw.c_cc[VMIN] = 0;
        raw.c_cc[VTIME] = 1;
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
        rawState.active = true;
    }
#endif
}

static void disableRawInput() {
#ifdef __linux__
    if (rawState.ready && rawState.active) {
        tcsetattr(STDIN_FILENO, TCSANOW, &rawState.original);
        rawState.active = false;
    }
#endif
}

static bool addEmployee(Employee* emp) {
    Employee* grown = (Employee*)realloc(employees, (employeeCount + 1) * sizeof(Employee));
    if (grown == NULL)
        return false;
    employees = grown;
    employees[employeeCount] = *emp;
    employeeCount++;
    return true;
}

static void clearEmployees() {
    if (employees != NULL) {
        for (int i = 0; i < employeeCount; ++i) {
            free(employees[i].name);
        }
        free(employees);
    }
    employees = NULL;
    employeeCount = 0;
}

#ifdef __linux__
static Key readLinuxKey() {
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) != 1)
        return KEY_NONE;
    if (c == 27) {
        unsigned char seq[2];
        if (read(STDIN_FILENO, &seq[0], 1) != 1)
            return KEY_ESC;
        if (read(STDIN_FILENO, &seq[1], 1) != 1)
            return KEY_ESC;
        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': return KEY_UP;
                case 'B': return KEY_DOWN;
                case 'C': return KEY_RIGHT;
                case 'D': return KEY_LEFT;
                case 'H': return KEY_HOME;
                case 'F': return KEY_END;
                default: return KEY_OTHER;
            }
        }
        return KEY_OTHER;
    }
    return KEY_OTHER;
}
#endif

Key getKey() {
#ifdef __linux__
    enableRawInput();
    return readLinuxKey();
#else
    return KEY_NONE;
#endif
}

static void drawButton(int y, const char* label, bool selected) {
    goToXY(20, y);
    if (selected) {
        setColor(COLOR_YELLOW);
        cout << "->" << "{ " << label << " }";
        resetColor();
    } else {
        cout << "{ " << label << " }";
    }
}

void drawMenu(MenuItem current) {
    clearScreen();
    goToXY(20, 5);
    cout << "Main Menu";
    drawButton(7, "New", current == MENU_NEW);
    drawButton(9, "Display", current == MENU_DISPLAY);
    drawButton(11, "Swap", current == MENU_SWAP);
    drawButton(13, "2D Arrays", current == MENU_2D);
    drawButton(15, "Exit", current == MENU_EXIT);
    goToXY(0, 20);
}

void exitScreen() {
    clearScreen();
    goToXY(20, 5);
    cout << "Bye Bye!";
    goToXY(28, 5);
    delay(1500);
    clearEmployees();
    disableRawInput();
    clearScreen();
    exit(0);
}

static void waitForReturn() {
    while (true) {
        Key k = getKey();
        if (k == KEY_HOME || k == KEY_LEFT)
            return;
        if (k == KEY_ESC)
            exitScreen();
    }
}

static void screenPlaceholder(const char* title) {
    clearScreen();
    goToXY(20, 5);
    cout << title;
    goToXY(20, 7);
    cout << "Feature coming soon.";
    goToXY(20, 9);
    cout << "Press <- or Home to return...";
    waitForReturn();
}

void screenDisplay() {
    clearScreen();
    goToXY(20, 5);
    cout << "Employees";
    int y = 7;
    if (employeeCount == 0) {
        goToXY(20, y);
        cout << "No employees yet.";
        y += 2;
    } else {
        for (int i = 0; i < employeeCount; ++i) {
            goToXY(20, y);
            cout << i + 1 << ". " << (employees[i].name ? employees[i].name : "Unknown");
            goToXY(20, y + 1);
            cout << "Salary: " << employees[i].salary << " Age: " << employees[i].age << " Gender: " << employees[i].gender;
            y += 3;
        }
    }
    goToXY(20, y);
    cout << "Press <- or Home to return...";
    waitForReturn();
}

void screenSwap() {
    disableRawInput();
    clearScreen();
    goToXY(20, 5);
    cout << "Swap Screen";

    int a;
    while (true) {
        goToXY(20, 7);
        cout << "Enter value for A: ";
        if (cin >> a)
            break;
        cin.clear();
        cin.ignore(1000, '\n');
        goToXY(20, 8);
        cout << "Invalid integer, please try again.      ";
    }
    cin.ignore(1000, '\n');
    goToXY(20, 8);
    cout << "                                           ";

    int b;
    while (true) {
        goToXY(20, 9);
        cout << "Enter value for B: ";
        if (cin >> b)
            break;
        cin.clear();
        cin.ignore(1000, '\n');
        goToXY(20, 10);
        cout << "Invalid integer, please try again.      ";
    }
    cin.ignore(1000, '\n');
    goToXY(20, 10);
    cout << "                                           ";

    int y = 12;

    int tempA = a;
    int tempB = b;
    swapByAdress(&tempA, &tempB);
    goToXY(20, y);
    cout << "swapByAdress: A=" << tempA << " B=" << tempB;
    y += 2;

    tempA = a;
    tempB = b;
    swapXOR(&tempA, &tempB);
    goToXY(20, y);
    cout << "swapXOR: A=" << tempA << " B=" << tempB;
    y += 2;

    tempA = a;
    tempB = b;
    swapByAddSub(&tempA, &tempB);
    goToXY(20, y);
    cout << "swapByAddSub: A=" << tempA << " B=" << tempB;
    y += 2;

    tempA = a;
    tempB = b;
    swapByMultiplyDivide(&tempA, &tempB);
    goToXY(20, y);
    cout << "swapByMultiplyDivide: A=" << tempA << " B=" << tempB;
    y += 2;

    goToXY(20, y + 1);
    cout << "Press Enter to return to the menu...";
    cin.get();
    enableRawInput();
}

void screen2D() {
    screenPlaceholder("2D ARRAYS");
}

void screenNew() {
    disableRawInput();
    while (true) {
        clearScreen();
        goToXY(20, 5);
        cout << "New Employee";
        Employee emp;
        emp.name = NULL;
        char tempName[64];
        goToXY(20, 7);
        cout << "Name: ";
        cin.getline(tempName, sizeof(tempName));
        while (tempName[0] == '\0') {
            goToXY(20, 7);
            cout << "Name: ";
            cin.getline(tempName, sizeof(tempName));
        }
        size_t len = strlen(tempName);
        emp.name = (char*)malloc(len + 1);
        if (emp.name == NULL)
            break;
        strcpy(emp.name, tempName);

        goToXY(20, 9);
        cout << "Salary: ";
        while (!(cin >> emp.salary) || emp.salary < 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            goToXY(20, 9);
            cout << "Salary: ";
        }
        cin.ignore(1000, '\n');

        goToXY(20, 11);
        cout << "Age: ";
        while (!(cin >> emp.age) || emp.age <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            goToXY(20, 11);
            cout << "Age: ";
        }
        cin.ignore(1000, '\n');

        goToXY(20, 13);
        cout << "Gender (M/F): ";
        while (!(cin >> emp.gender) || (emp.gender != 'm' && emp.gender != 'M' && emp.gender != 'f' && emp.gender != 'F')) {
            cin.clear();
            cin.ignore(1000, '\n');
            goToXY(20, 13);
            cout << "Gender (M/F): ";
        }
        cin.ignore(1000, '\n');

        if (!addEmployee(&emp)) {
            free(emp.name);
            break;
        }
        goToXY(20, 15);
        cout << "Employees: " << employeeCount;
        goToXY(20, 17);
        cout << "Add another? (y/n): ";
        char choice;
        while (!(cin >> choice) || (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')) {
            cin.clear();
            cin.ignore(1000, '\n');
            goToXY(20, 17);
            cout << "Add another? (y/n): ";
        }
        cin.ignore(1000, '\n');
        if (choice == 'n' || choice == 'N')
            break;
    }
    enableRawInput();
}
