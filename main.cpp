//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Main driver to run our graduate student admission system, controls all subordinate functions
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>      //cin and cout
#include <vector>        //vectors of students
#include "templates.cpp" //templates have to be in cpp files for proper portability, etc
                         //templates.cpp also #includes all the definitions for student classes, helper functions, etc
#include "list.hpp"

//declare vectors to store students in
SortedList<DomesticStudent> domStudents;
SortedList<InternationalStudent> intStudents;
SortedList<Student> mergedStudents;

//global variable to ensure unique appId for each student
int latestAppId = 20200000;

int main()
{
    using std::cout;
    using std::endl;

    //flag to track whether user is dealing with domestic international, or a merged student database
    //0 = domestic, 1 = international, 2 = merged
    int database = 0;
    bool merged = false;

    //read from files and construct all objects
    try
    {
        getDomestics(latestAppId, domStudents);
        getInternationals(latestAppId, intStudents);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    cout << "\nWelcome to Graduate Student Admissions! Please press enter to begin.\n";
    getchar();

    //menus should be continuously printed to the user until they quit
    while (true)
    {
        //offer a choice between international or domestic students
        //based on user input, choose which path
        switch (getDatabaseSelection())
        {
        case 1: //domestic
        {
            cout << "\nYou have selected the Domestic student database\n";
            database = 0;
            if (merged)
            {
                unmerge(domStudents, intStudents, mergedStudents);
                merged = false;
            }
            break;
        }
        case 2: //international
        {
            cout << "\nYou have selected the International student database\n";
            database = 1;
            if (merged)
            {
                unmerge(domStudents, intStudents, mergedStudents);
                merged = false;
            }
            break;
        }
        case 3: //both
        {
            cout << "\nYou have selected to merge the two databases together.\n";
            database = 2;
            if (!merged)
            {
                merge(domStudents, intStudents, mergedStudents);
                merged = true;
            }
            break;
        }
        case 4: //exit
        {
            cout << "Exiting...\n";
            exit(0);
        }
        default: //any other integer
        {
            std::cerr << "Error, please only enter integers from 1 to 4.\n";
            continue;
            break; //just in case
        }
        }

        if (database == 0)
        {
            choosePath(domStudents, latestAppId);
        }
        else if (database == 1)
        {
            choosePath(intStudents, latestAppId);
        }
        else
        {
            choosePath(mergedStudents, latestAppId);
        }

    } //end while
    return 0;
}
