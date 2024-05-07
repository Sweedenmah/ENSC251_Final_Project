//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Part 3 : Unit Test
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define userMode false

#include <iostream>      //cin and cout
#include <vector>        //vectors of students
#include "templates.cpp" //templates have to be in cpp files for proper portability, etc
                         //templates.cpp also #includes all the definitions for student classes, helper functions, etc
#include "list.hpp"

int latestAppId = 20200000;
int latestAppId2 = 20201000;

SortedList<DomesticStudent> U_domStudents;
SortedList<InternationalStudent> U_intStudents;
SortedList<Student> U_mergedStudents;

//-------------------------------------------------------------------------------------------------------------------------------
//                                                  Information for Student Objects
//
//                               Includes faulty test cases as well as the boundary and illegal test cases
//-------------------------------------------------------------------------------------------------------------------------------
string first[] = {"Gaspar", "Devon", "Jake", "Simon", "Sleave"};
string last[] = {"Fung", "Burnham", "Merkl", "Mao", "McDichael"};
// testing if incorrect provice is added
string province[] = {"BC", "NS", "QC", "PE", "DD"};
// testing what happens with different additions of cgpa and rs, same for international students
float cgpa[] = {0.0, static_cast<float> (4.3), static_cast<float> (2.4), static_cast<float> (4.0), static_cast<float> (999)};
int rs[] = {0, 100, 50, 80, 999};

//list of 5 example inputs for international

//Alex,Zhang,China,3.7,95,24,25,29,26
// Peter,Choi,Korea,4,85,23,19,22,28
// Chaewon,Kim,Korea,3.10,82,22,22,23,27
// Daeun,Gim,Korea,3.00,83,21,21,24,26
// Eungyung,Ghim,Korea,2.90,84,20,20,25,25

string first_int[] = {"Alex", "Peter", "Daeun", "Chaewon", "Eungyung"};
string last_int[] = {"Zhang", "Choi", "Gim", "Kim", "Ghim"};
string country[] = {"China", "Korea", "Korea", "Korea", "America"};
//Toefl Scores
int reading [] = {28, 26, 30, 28, 999};
int listening [] = {28, 10, 30, 30, 1};
int speaking [] = {28, 17, 25, 25, 0};
int writing [] = {28, 18, 16, 15, 0};

float cgpa_int[] = {0.0, static_cast<float> (4.3), static_cast<float> (2.4), static_cast<float> (4.0), static_cast<float> (999)};
int rs_int[] = {0, 100, 50, 80999};

unsigned int app_id[] = {20200001, 20200002, 2020003, 20200004, 20200005, 20201111, 20201001, 20201002, 20201003, 20201004, 20201005, 20211111};
float cgpa_search[] = {0.0, static_cast<float> (4.3), static_cast<float> (4.0), static_cast<float> (999), static_cast<float>(1.4)};
unsigned int researchScore[] = {90, 0, 50, 999, 10};

float cgpa_thresh[] = {0.0, static_cast<float> (4.3), static_cast<float> (4.0), static_cast<float> (999), static_cast<float>(1.4)};
unsigned int researchScore_thresh[] = {90, 0, 50, 999, 10};

//------------------------------------------------------------------------------------------------------------------------

// 1. Insert DomesticStudent (& InternationalStudent) object into the DomesticStudent (and InternationalStudent) singly linked list in order.
void test1()
{

    bool repeat = false;
    do
    {

        using namespace std;

        // list of 5 example inputs for domestic so that we have a decent amount of names to work with, same for international

        cout << "Adding domestic students\n";
        for (int i = 0; i < 5; i++)
        {
            try
            {
                auto inputStu = new DomesticStudent(first[i], last[i], cgpa[i], rs[i], latestAppId++, province[i]);
                U_domStudents.insert(inputStu);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        std::cout << "Successfully added objects into the list, will now print out list\n";
        // print out the list to show that the student has been added
        for (const auto &node : U_domStudents)
        {
            cout << std::endl;
            node.getDataPtr()->printInfo(cout);
        }

        cout << "Adding international students\n";
        for (int i = 0; i < 4; i++)
        {
            try
            {
                auto inputStu = new InternationalStudent(first_int[i], last_int[i], cgpa_int[i], rs_int[i], latestAppId2++, country[i], ToeflScore(reading[i], listening[i], speaking[i], writing[i]));
                U_intStudents.insert(inputStu);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        std::cout << "Successfully added object into the list, will now print out both lists\n";
        // print out the list to show that the student has been added
        for (const auto &node : U_domStudents)
        {
            auto stu = node.getDataPtr();
            stu->printInfo(std::cout);
        }

        for (const auto &node : U_intStudents)
        {
            auto stu = node.getDataPtr();
            stu->printInfo(std::cout);
        }

        if (userMode)
        {
            std::cout << "Would you like to repeat this test?\n 0 for yes, 1 for no\n";
            std::cin >> repeat;
        }

    } while (repeat == 0 && userMode);
}

// 2. Search existing DomesticStudent (and InternationalStudent) objects in the  DomesticStudent (and InternationalStudent) linked list based on the user input information “application id”, or “cgpa”, or “researchScore”.
void test2()
{

    bool found = false;
    for (int i = 0; i < 5; i++)
    {
        for (const auto &node : U_domStudents)
        {
            if (app_id[i] == node.getDataPtr()->getAppId())
            {
                auto stu = node.getDataPtr();
                if (node.getDataPtr()->isDomestic)
                {
                    //DomesticStudent domstu = dynamic_cast<DomesticStudent&>(stu);
                    stu->printInfo(std::cout);
                }
                else
                {
                    stu->printInfo(std::cout);
                }

                found = true;
                break; //there can only be one student with each app id
            }
        }
    };

    found = false;
    for (int i = 6; i < 12; i++)
    {
        for (const auto &node : U_intStudents)
        {
            if (app_id[i] == node.getDataPtr()->getAppId())
            {
                auto stu = node.getDataPtr();
                if (node.getDataPtr()->isDomestic)
                {
                    //DomesticStudent domstu = dynamic_cast<DomesticStudent&>(stu);
                    stu->printInfo(std::cout);
                }
                else
                {
                    stu->printInfo(std::cout);
                }

                found = true;
                break; //there can only be one student with each app id
            }
        }
    };

    found = false;
    for (int i = 0; i < 5; i++)
    {
        for (const auto &node : U_domStudents)
        {
            if (fabs(cgpa_search[i] - node.getDataPtr()->getCgpa()) < std::numeric_limits<float>::epsilon()) //float comparison isn't simple
            {
                auto stu = node.getDataPtr();
                stu->printInfo(std::cout);
                found = true;
            }
        }
    }

    found = false;
    for (int i = 6; i < 12; i++)
    {
        for (const auto &node : U_intStudents)
        {
            if (fabs(cgpa_search[i] - node.getDataPtr()->getCgpa()) < std::numeric_limits<float>::epsilon()) //float comparison isn't simple
            {
                auto stu = node.getDataPtr();
                stu->printInfo(std::cout);
                found = true;
            }
        }
    }

    found = false;
    for (int i = 0; i < 5; i++)
    {
        for (const auto &node : U_domStudents)
        {
            if (researchScore[i] == node.getDataPtr()->getResearchScore())
            {
                auto stu = node.getDataPtr();
                stu->printInfo(std::cout);
                found = true;
            }
        };
    };

    found = false;
    for (int i = 6; i < 12; i++)
    {
        for (const auto &node : U_intStudents)
        {
            if (researchScore[i] == node.getDataPtr()->getResearchScore())
            {
                auto stu = node.getDataPtr();
                stu->printInfo(std::cout);
                found = true;
            }
        };
    };

    if (!found)
    {
        std::cout << "No student with that attribute was found.\n";
    }
}

// 3. Search existing DomesticStudent (and InternationalStudent) objects in the DomesticStudent (and InternationalStudent) linked list based on the user input information “firstName and lastName”.
void test3()
{

    bool searching = false;
    do
    {

        bool found = false;
        for (int i = 0; i < 5; i++)
        {
            for (const auto &node : U_domStudents)
            {
                if (first[i].compare(node.getDataPtr()->getFirstName()) == 0)
                {
                    if (last[i].compare(node.getDataPtr()->getLastName()) == 0)
                    {
                        auto stu = node.getDataPtr();
                        stu->printInfo(std::cout);
                        found = true;
                    }
                }
            }
        }

        if (!found)
        {
            std::cout << "No student with that attribute was found.\n";
        }
        break;

        found = false;
        for (int i = 0; i < 5; i++)
        {
            for (const auto &node : U_intStudents)
            {
                if (first_int[i].compare(node.getDataPtr()->getFirstName()) == 0)
                {
                    if (last_int[i].compare(node.getDataPtr()->getLastName()) == 0)
                    {
                        auto stu = node.getDataPtr();
                        stu->printInfo(std::cout);
                        found = true;
                    }
                }
            }
        }

        if (!found)
        {
            std::cout << "No student with that attribute was found.\n";
        }
        break;

        if (userMode)
        {
            std::cout << "Would you like to repeat this test?\n 0 for yes, 1 for no\n";
            std::cin >> searching;
        }

    } while (searching == 0 && userMode);
}
// 4. Delete existing DomesticStudent (and InternationalStudent) objects in the DomesticStudent (and InternationalStudent) linked list based on the user input information “firstName and lastName”.
void test4()
{
    bool removed = false;
    do
    {

        string dom_first[] = {"Sleave", "Gaspar", "DNE"};
        string dom_last[] = {"McDichael", "Fung", "DNE"};
        string int_first[] = {"Peter", "Alex", "DNEint"};
        string int_last[] = {"Choi", "Zhang", "DNEint"};

        for (int i = 0; i < 3; i++)
        {
            if (U_domStudents.searchAndDestroy(dom_first[i], dom_last[i]))
            {
                std::cout << "Printing out the new list\n";
                // printing out the new list such that it can be seen whether delete has truly worked
                for (const auto &node : U_domStudents)
                {
                    auto stu = node.getDataPtr();
                    stu->printInfo(std::cout);
                }
                break;
            }
            else
            {
                std::cout << "Student not found; list unaltered\n";
            }
            break;
        }

        for (int j = 0; j < 3; j++)
        {
            if (U_intStudents.searchAndDestroy(int_first[j], int_last[j]))
            {
                std::cout << "Printing out the new list\n";
                // printing out the new list such that it can be seen whether delete has truly worked
                for (const auto &node : U_intStudents)
                {
                    auto stu = node.getDataPtr();
                    stu->printInfo(std::cout);
                }
                break;
            }
            else
            {
                std::cout << "Student not found; list unaltered\n";
            }
            break;
        }

        if (userMode)
        {
            std::cout << "Would you like to repeat this test?\n 0 for yes, 1 for no\n";
            std::cin >> removed;
        }

    } while (removed == 0 && userMode);
}

// 5. Delete both the head node and tail node from the DomesticStudent (and InternationalStudent) linked list in a single delete function.
void test5()
{

    bool deleted = false;
    do
    {

        U_domStudents.aLittleOffTheTopAndBottom();
        std::cout << "Deletion Successful\n";
        // printing out the list to display that it really has been successfully deleted
        for (const auto &node : U_domStudents)
        {
            auto stu = node.getDataPtr();
            stu->printInfo(std::cout);
        }
        

        if (userMode)
        {
            std::cout << "Would you like to repeat this test?\n 0 for yes, 1 for no\n";
            std::cin >> deleted;
        }

    } while (deleted == 0 && userMode);
}
// 6. Merge the two sorted DomesticStudent and InternationalStudent linked lists into a single Student linked list.
void test6()
{

    bool merged;
    do
    {

        std::cout << "Now merging the sorted U_domStudents and U_intStudents list. \n";

        merge(U_domStudents, U_intStudents, U_mergedStudents);

        // print out the lists

        for (const auto &node : U_mergedStudents)
        {
            auto stu = node.getDataPtr();
            stu->printInfo(std::cout);
        }

        std::cout << "Successfully merged both files \n";
        if (userMode)
        {
            std::cout << "Would you like to repeat this test?\n 0 for yes, 1 for no\n";
            std::cin >> merged;
        }

    } while (merged == 0 && userMode);
}

// 7. Search existing Student objects in the merged linked list based on the user input information “cgpa_threshold and researchScore_threshold”.
void test7()
{

    bool again = 0;

    do
    {
        using std::cin;
        using std::cout;

        float c1 = 4.0;
        int r1 = 80;

        // just displaying info based on input
        cout << "Will now printout those those within threshold\n";
        U_mergedStudents.showAllOverThreshold(r1, c1, std::cout);

        U_mergedStudents.saveAllOverThreshold(r1, c1);

        //testing multiple different values
        for (int i = 0; i < 5; i++)
        {
            U_mergedStudents.showAllOverThreshold(researchScore_thresh[i], cgpa_thresh[i], std::cout);
        }

        if (userMode)
        {
            std::cout << "Would you like to repeat this test?\n 0 for yes, 1 for no\n";
            std::cin >> again;
        }

    } while (again == 0 && userMode);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    return 0;
}