/**
*   @file input.h
*   @author Jakari Robinson 
*   
*   Starting point of the program reads commands from the user and manipulates/displays the underlying database contents. 
*/ 

#include "database.h"
#include "input.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/**
 * Function for comparing employees by there skill then ID number
 * 
 * @param va first employee you wan't to compare
 * @param vb second employee you want to compare the first employee too
 * @return int -1 if employee 1 is less than employee 2 0 1 vice versa 
 */
static int compareBySkillThenID( void const *va, void const *vb ) {
    //convert the two pointers to employees
    Employee *employee = *((Employee**) va);

    Employee *comparedEmployee = *((Employee**) vb);

    //if the skill of employee 1 is greater than employee 2 return 1
    if(strcmp(employee->skill, comparedEmployee->skill) > 0) {
        return 1; 
    } 
    //else if the skill of employee 1 is less than employee 2 return -1 
    else if(strcmp(employee->skill, comparedEmployee->skill) < 0) {
        return -1; 
    }
    //else (the skills are the same)
     else {
        //if the ID of employee 1 is greater than employee 2 return 1
        if(strcmp(employee->id, comparedEmployee->id) > 0) {
            return 1; 
        }
        //else if the id of employee 1 is less than employee 2 return -1
        else if(strcmp(employee->id, comparedEmployee->id) < 0) {
            return -1; 
        }
        //else (the id and skill are the same ) return 0; 
        else {
            return 0; 
        }
    }

    //return so the compiler shut's up ( WE SHOULD NEVER GET HERE)
    return 0; 
}

/**
 * Function for comparing employees by there ID number
 * 
 * @param va first employee you want to compare
 * @param vb second employee you want to compare the first employee too 
 * @return int -1 if employee 1 is less than employee 2 0 1 vice versa 
 */
static int compareByID( void const *va, void const *vb ) {
    //converer the two pointers to employees
    Employee *employee = *((Employee**) va);

    Employee *comparedEmployee = *((Employee**) vb);
    
    //if the ID of employee 1 is greater than employee 2 return 1
    if(strcmp(employee->id, comparedEmployee->id) > 0) {
        return 1;
    } else if (strcmp(employee->id, comparedEmployee->id) < 0) {
        return -1; 
    } else {
        return 0; 
    }

    //should never get here 
    return 0; 

}

/**
 * Test function that prints all employees (returns true to do so in listEmployee)
 * 
 * @param emp employee to compare
 * @param str used for comparison
 * @return true if employee should be printed to stout
 * @return false if employee shouldn't be printed to stout
 */
 bool printAllEmployeesFunction( Employee const *emp, char const *str) {
     return true;
 }


/**
 * Test function that compares employees based on skill
 * 
 * @param emp employee to print
 * @param str used for comparison
 * @return true if employee has the same skill as the string arg
 * @return false if the employee has different skill from the string arg
 */
 bool compareEmployeesOnSkill( Employee const *emp, char const *str) {
     if(strcmp(emp->skill, str) == 0) {
         return true;
     } 

     return false;
 }

/**
 * Test function that compares  employees based on assignment
 * 
 * @param emp employee to print
 * @param str used for comparison
 * @return true if employee has the same assignment as the string arg
 * @return false if employee has the different assignment as the string arg
 */
 bool compareEmployeesOnAssignment( Employee const *emp, char const *str) {
     if(strcmp(emp->assignment, str) == 0) {
         return true; 
    }
    return false; 

 }

 /**
 * Test function that compares  employees based on assignment
 * 
 * @param emp employee to print
 * @param str used for comparison
 * @return true if employee has the same assignment as the string arg
 * @return false if employee has the different assignment as the string arg
 */
 bool compareEmployeesOnID( Employee const *emp, char const *str) {
     if(strcmp(emp->id, str) == 0) {
         return true; 
    }
    return false; 

 }

/**
 * Helper function for executing invalid command behavior
 * 
 */
 static void invalidCommand( void ) {
     printf("Invalid command\n\n");
 }



/**
 * Main method of the program
 * @param numberOfCommandLineArgs number of command line arguements
 * @param commandLineArgs array of pointers to each of the command line argument strings
 * @return EXIT_STATUS 0 for success
 */
int main(int numberOfCommandLineArgs, char *commandLineArguements[]) {
    
    //Check if we have the right amount of file names arguements (2 args or more) 
    if(numberOfCommandLineArgs < 2) {
        //If not print usage: agency <employee-file>* to stderr and exit with status of 1
        fprintf(stderr, "usage: agency <employee-file>*\n");
        exit(EXIT_FAILURE);
    }
        
    //Create a pointer to a database struct and create a new empty database
    Database *database = makeDatabase();

    //read employees from both files and store them in the database
    for(int i = 1; i < numberOfCommandLineArgs; i++) {
        readEmployees(commandLineArguements[i], database); 
    }

    //start a while true loop
    while(true) {
        
        //Create a char array  to store possible  first command read
        char firstCommand[10] = {}; 

        //Create char array to store possible second command read
        char secondCommand[10] = {};

        //Create char pointer to store possible third command read
        char thirdCommand[10] = {};

        //create an array to store a possible fourth  command (which is invalid) if there is one after the third command 
        char invalidFourthCommand[10] = {};

        //print cmd>' ' to stdout
        printf("cmd> ");

        //Create an char pointer to point to the command read in from stdin, Readline the next line of user input
        char *lineRead = readLine(stdin);

        

        //Check if readline returned null meaning we reached EOF
        if(lineRead == NULL) {
            //If so exit the program successfully
            free(lineRead);
            freeDatabase(database);
            exit(EXIT_SUCCESS);
        }  

        //scanf all possible commands
        sscanf(lineRead, "%s %s %s %s", firstCommand, secondCommand, thirdCommand, invalidFourthCommand);
        
        //If quit was typed
        if(strcmp(firstCommand, "quit") == 0) {
            //If so print quit to stdin and exit successfully
            printf("quit\n");
            freeDatabase(database);
            free(lineRead);
            exit(EXIT_SUCCESS);
            
        }  

        //echo the commands to stdout
        if(strcmp(secondCommand, "") != 0 && strcmp(thirdCommand, "") != 0 && strcmp(invalidFourthCommand, "") != 0) {
            printf("%s %s %s %s\n", firstCommand, secondCommand, thirdCommand, invalidFourthCommand);
            free(lineRead);
            invalidCommand();
            continue;
        }
        
        if(strcmp(invalidFourthCommand, "") != 0) {
            free(lineRead);
            invalidCommand();
            continue;
        }

        if(strcmp(secondCommand, "") != 0 && strcmp(thirdCommand, "") != 0) {
            printf("%s %s %s\n", firstCommand, secondCommand, thirdCommand);
        } 
        
        else if(strcmp(secondCommand, "") != 0 && strcmp(thirdCommand, "") == 0) { 
            printf("%s %s\n", firstCommand, secondCommand);
        } 
         else {
            printf("%s\n", firstCommand);
        }

        //If its a list command
        if(strcmp("list", firstCommand) == 0) {

                //If there are no employees in the database print the header line and go to the next iteration 
                if(database->count == 0) {
                    listEmployees(database, compareByID, printAllEmployeesFunction, NULL);
                    //print a new line char
                    putchar('\n');
                    free(lineRead);
                    continue;
                } 
                //if there wasn't an additional parameter
                else if(strcmp(secondCommand, "") == 0) {
                     //print out all agency employees sorted by ID (descending) if the there are no employees just print the 
                    //header line for the employee list output
                    listEmployees(database, compareByID, printAllEmployeesFunction, NULL);
                    free(lineRead);
                    //put a new line and continue
                    putchar('\n');
                    continue;
                }
                 //If there was an additional paramater check if it says skill
                else if(strcmp(secondCommand, "skill") == 0) { 

                        //If the next scan says returns nothing or if the next scan is greater than 15 chars do the behavior
                        //for invalid commands and go to the next iteration
                        if(strcmp(thirdCommand, "") == 0 || strlen(thirdCommand) > 15) {
                            free(lineRead);
                            invalidCommand();
                            continue;
                        } 
                        
                        //If the next sccanf was valid (not empty  or greater than 15 chars) call sccanf again to see if there was anything after the last valid command
                        else {
                            if(strcmp(invalidFourthCommand, "") != 0) {
                                //If there was something after the last valid command do the behvaiour for invalidCommands and go to the next iteration
                                free(lineRead);
                                invalidCommand();
                                continue;
                            }

                            //If the second sccanf was valid call listEmployees with the corrrect params (sorted by id descending)
                            listEmployees(database, compareBySkillThenID, compareEmployeesOnSkill, thirdCommand);
                            free(lineRead);
                            //print a new line and continue
                            putchar('\n');
                            continue;

                }
            }
            //If the additional parameter says assignment
            else if(strcmp(secondCommand, "assignment") == 0) {                   
                     
                        //if the next word is more than 20 characters or is nothing do invalid command behavior
                        if(strcmp(thirdCommand, "") == 0 || strlen(thirdCommand) > 20) {
                            free(lineRead);
                            invalidCommand();
                            continue;
                        }

                        //Else the next word was valid 
                        //call list employees sorting by there skill (strcmp descending), then ID number (descending)
                        listEmployees(database, compareBySkillThenID, compareEmployeesOnAssignment, thirdCommand);
                        //print a new line and continue
                        free(lineRead);
                        putchar('\n');
                        continue;
                    }

            //if the additional paramter wasn't valid do invalid command behavior
            else {
                free(lineRead);
                invalidCommand();
                continue;
            }

        } 
                  
        //If it's an assign command
        else if(strcmp(firstCommand, "assign") == 0) {

                //boolean for keeping track if an employee with an id was found
                bool employeeFound = false;

                //index to keep track where the employee with the id we're looking for is in the list
                int targetEmployeeIndex = 0; 

                //If there was no ID (meaning we couldn't find any digits) do invalid command behaviour
                if(secondCommand == NULL) {
                    free(lineRead);
                    invalidCommand();
                    continue;
                }
                //Else if there was some digits 
                //find the employee with that ID
                for(int i = 0; i < database->count; i++) {
                   employeeFound =  compareEmployeesOnID(database->list[i], secondCommand);

                   if(employeeFound) {
                       targetEmployeeIndex = i; 
                       break;
                   }
                }

                //If there was no employee with that ID do invalid command behavior
                if(!employeeFound) {
                    free(lineRead);
                    invalidCommand();
                    continue;
                }
                
                //If the employee with that ID was not available do invalid command behavior
                if(strcmp(database->list[targetEmployeeIndex]->assignment, "Available") != 0) {
                    free(lineRead);
                    invalidCommand();
                    continue;
                }

                //If the employee was availble check If the assignment string is more than 20 characters or empty do invalid command behvaior
                if(strcmp(thirdCommand, "") == 0 || strlen(thirdCommand) > 20) {
                    free(lineRead);
                    invalidCommand();
                    continue;
                }

                //When all checks pass, change the employee with that ID's assignment to the command assignment
                strcpy(database->list[targetEmployeeIndex]->assignment, thirdCommand); 
                free(lineRead);
                putchar('\n');
        }

        //If it's an unassign command
        else if(strcmp(firstCommand, "unassign") == 0) { 
                //boolean to keep track if an employee is found when searching 
                bool employeeFound = false;

                //index to keep track where the employee with the id we're looking for is in the list
                int targetEmployeeIndex = 0; 


                //If there was no ID in the next command (meaning we couldn't find any digits) do invalid command behaviour
                if(strcmp(secondCommand, "") == 0) {
                    free(lineRead);
                    invalidCommand();
                    continue;
                }

                //Else if there was some digits  
                //find the employee with that ID
                for(int i = 0; i < database->count; i++) {
                   employeeFound =  compareEmployeesOnID(database->list[i], secondCommand);

                   if(employeeFound) {
                       targetEmployeeIndex = i; 
                       break;
                   }
                }

                //If there was no employee with that ID do invalid command behavior
                if(!employeeFound) {
                    free(lineRead);
                    invalidCommand();
                    continue;
                }

                //If the employee with that ID was available do invalid command behavior
                if(strcmp(database->list[targetEmployeeIndex]->assignment, "Available") == 0) {
                    free(lineRead);
                    invalidCommand();
                    continue;
                }
            
            //When all checks pass, remove the employee with that ID from the database
            strcpy(database->list[targetEmployeeIndex]->assignment, "Available"); 
            free(lineRead);
            putchar('\n');
        } 
        //Else   command isn't list, assign, unassign, then do invalid command behavior and restart the loop
        else {
            free(lineRead);
            invalidCommand();
            continue;
        }
    }

    freeDatabase(database);
}

