/**
*   @file database.h
*   @author Jakari Robinson 
*   This file contains common functions and variables for database.c and files whom depend on it
*/ 

#include <stdio.h>
#include <stdbool.h>

/**Maximum length of an employee ID */ 
#define ID_LENGTH 5

/**Maximum length of all other employee fields (first name, lastname etc) */ 
#define EMPLOYEE_ATTRIBUTE_MAX_LENGTH 16

/**
 * Defines a employee struct to be used in the database
 * 
 */
typedef struct {
    char id[ID_LENGTH]; 
    char firstName[EMPLOYEE_ATTRIBUTE_MAX_LENGTH];
    char lastName[EMPLOYEE_ATTRIBUTE_MAX_LENGTH];
    char skill[EMPLOYEE_ATTRIBUTE_MAX_LENGTH];
    char assignment[EMPLOYEE_ATTRIBUTE_MAX_LENGTH];

} Employee;

/**
 * Defines an database struct that holds a list of employees and other information
 * 
 */
typedef struct {
    Employee **list;
    int count; 
    int capacity; 

} Database;



/**
 * Function dynamically allocates storage for the database 
 * initializes it's fields (to store a resizeable array) and and returns a pointer to the new map
 * @return Database that's emtpy but malloced
 */
Database *makeDatabase();

/**
 * Function free's a database and all it's employees 
 * from memory
 * 
 * @param database you want to destroy 
 */
void freeDatabase( Database *database );

/**
 * Function reads all employees from an employee list file and makes an instance of employee struct 
 * For each employee it finds in the file, then stores a pointer to that struct in an resizeable array
 * of pointers to employee structs. 
 * @param filename of the file you want to read employees from
 * @param database whose list field you want to to be updated with new employees from the file
 */
void readEmployees( char const *filename, Database *database );

/**
 * Function sorts employees in a given databse then prints them. The first function is the comparator function, 
 * The second function paramter decides which employees to print. 
 * function is used for list commands in the program
 * 
 * @param database where the employees are coming from
 * @param compare comparator function for ordering purposes
 * @param test pointer to function used to determine to print an employee will return true if it should be printed
 * @param str string used to determine whether to print an employee
 */
void listEmployees( Database *database, int (*compare)( void const *va, void const *vb ), bool (*test)( Employee const *emp, char const *str ), char const *str );

