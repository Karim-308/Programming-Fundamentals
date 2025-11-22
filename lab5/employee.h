#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stddef.h>
#include <string>

typedef struct {
    std::string name;
    double salary;
    int age;
    char gender;
} Employee;

#endif
