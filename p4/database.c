/**
*   @file database.c
*   @author Jakari Robinson 
*   
*   File that contains database operations for the agency program
*/ 

#include "database.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/**
 * Helper function to print employees to stdout
 * @param *Employee pointer to employee you want to print
 */
 static void printEmployee(Employee *employee) {
     printf("%-4s %-15s %-15s %-15s %-20s\n", employee->id, employee->firstName, employee->lastName, employee->skill, employee->assignment);
     
}


Database *makeDatabase() {
    
    
    //Create and Mallocing a struct
    Database *database = (Database *) malloc( sizeof(Database) );


    //malloc the list of pointers to employees
    database->list  = (Employee **) malloc(5 * sizeof(Employee *));

    //Set the employee count to 0 
    database->count = 0;

    //Set the  list capacity to 5
    database->capacity = 5;

    //set each pointer to point to an instance of an empty employee
    for(int i = 0; i < 5; i++) {
        database->list[i] = (Employee *) malloc(sizeof(Employee));
    }
    
    //return a pointer to the database
    return database; 

}


void freeDatabase( Database *database ) {
    //loop through all the pointers in the list array of pointers
    for(int i = 0; i < database->capacity; i++) {
        //for each pointer to an employee free the employee that the current pointer is pointing too 
        free(database->list[i]);
    }

    //Free what the list pointer was pointing too (the whole array of pointers that the list was pointing too)
    free(database->list);
    //Free the database struct itself 
    free(database);
}
 

void readEmployees( char const *filename, Database *database ) {
    //attempt to open the file
   FILE *file =  fopen(filename, "r");
    //If the file can't be opened (was null) print: Can't open file: filename to standard error and exit with a status of 1
    if(!file) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        free(database);
        exit(EXIT_FAILURE);
    }

    //boolean to keep track if readline is null
    bool readLineNull = false; 

    //start a while loop while the line isn't null
    while(!readLineNull) {

        int count = database->count;

        //read the first line and store it in a char array
        char *lineRead = readLine(file); 

        //check if the line is null
        if(lineRead == NULL) {
            readLineNull = true;
            continue; 
        } 

        //Create string array of 5 for employee id
        char employeeID[ID_LENGTH] = {};

        //create char arrays for the employee first name last name skill and assignment (one larger than necessary for error checking so 17)
        char firstName[EMPLOYEE_ATTRIBUTE_MAX_LENGTH] = {};
        char lastName[EMPLOYEE_ATTRIBUTE_MAX_LENGTH] = {};
        char skill[EMPLOYEE_ATTRIBUTE_MAX_LENGTH] = {};
        char assignment[EMPLOYEE_ATTRIBUTE_MAX_LENGTH] = "Available";
        
        //read in all the fields
        sscanf(lineRead, "%s %s %s %s", employeeID, firstName, lastName, skill);

        //if the ints found using scannf wasn't exactly 4 print this to standard error: Invalid employee file: filename and exit with a status of one
        if(strlen(employeeID) != 4) {
             fprintf(stderr, "Invalid employee file: %s\n", filename);
             free(lineRead);
             free(database);
             fclose(file);
             exit(EXIT_FAILURE);

        }

        //if the length of the first name was greater than 15  or nothing was read at all print this to standard error: Invalid employee file: filename and exit with a status of one
        if(strlen(firstName) > 15 || strcmp(firstName, "") == 0) {
             fprintf(stderr, "Invalid employee file: %s\n", filename);
             free(lineRead);
             free(database);
             fclose(file);
             exit(EXIT_FAILURE);
        }

        ///if the length of the last  name was greater than 15 or nothing was read at all print this to standard error: Invalid employee file: filename and exit with a status of one
        if(strlen(lastName) > 15 || strcmp(lastName, "") == 0) {
             fprintf(stderr, "Invalid employee file: %s\n", filename);
             free(lineRead);
             free(database);
             fclose(file);
             exit(EXIT_FAILURE);
        }

        ///if the length of the skill was greater than 15 or nothing was read at all print this to standard error: Invalid employee file: filename and exit with a status of one
        if(strlen(skill) > 15 || strcmp(skill, "") == 0) {
             fprintf(stderr, "Invalid employee file: %s\n", filename);
             free(lineRead);
             free(database);
             fclose(file);
             exit(EXIT_FAILURE);
        }

        //check if the count of the list of employees in the database is at capacity
        if(database->count == database->capacity) {
            //double capacity
            database->capacity*=2;

            //resize the database list array
            database->list = (Employee **) realloc(database->list, database->capacity * sizeof(Employee *) ); 

            //Realloc each employee pointer to point to a fresh block of employee
            for(int i = database->count; i < database->capacity ; i++) {
                database->list[i] = (Employee *) malloc(sizeof(Employee));
            }
                
            
        }
            
        //Add the new employee struct pointer to the list of employees 
        strcpy((database->list[count])->firstName, firstName); 
        strcpy((database->list[count])->lastName, lastName); 
        strcpy((database->list[count])->id, employeeID); 
        strcpy((database->list[count])->assignment, assignment); 
        strcpy((database->list[count])->skill, skill); 

        //free memory
        free(lineRead);
        
        //increment database count
        database->count++; 
    
    }
    
    //Check for duplicates ID's in the read in employees if you find one print this to standard error: Invalid employee file: filename and exit with a status of one
    for(int i = 0; i < database->count; i++) {
        for(int j = i + 1; j < database->count; j++) {
            if(strcmp(database->list[i]->id,  database->list[j]->id) == 0) {
                fprintf(stderr, "Invalid employee file: %s\n", filename);
                freeDatabase(database);
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
        
    }

    //free memory
    fclose(file);
    

}


void listEmployees( Database *database, int (*compare)( void const *va, void const *vb ), bool (*test)( Employee const *emp, char const *str ), char const *str ) {

    //boolean to see if an employee was printed
    bool employeePrinted = false; 

    //boolean to see if header was printed
    bool headerPrinted = false; 

    //run Qsort on the list array of employees in the database
    qsort(database->list, database->count, sizeof(Employee **), compare);
    //loop through all the employees in the data base
    for(int i = 0; i < database->count; i++) {
        //if this is the first iteration print the header
        if(i == 0) {
            printf("ID   First Name      Last Name       Skill           Assignment\n");
            headerPrinted = true;
        } 

        //if the test function returns true
        if(test(database->list[i], str)) {
            printEmployee(database->list[i]);
            employeePrinted = true; 
        }

    }

    //if there was no employees printed print the header input to stdin
    if(!employeePrinted && !headerPrinted) {
        printf("ID   First Name      Last Name       Skill           Assignment\n");
    }

}

