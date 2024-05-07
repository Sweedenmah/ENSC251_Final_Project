//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Implementations of a variety of helper functions, such as file i/o, user input and menu printing
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define CURSES_ENABLE true

#include <string>   //strings!
#include <iostream> //input and output
#include <fstream>  //file io
#include <sstream>  //string streams
#include <limits>   //std::streamsize::max

#include "helpers.hpp"
#include "list.hpp"
#include "exceptions.hpp"
#include "ncmenu.hpp"

//can throw MissingField or InvalidProvince
void getDomestics(int &latestAppId, SortedList<DomesticStudent> &inputVec)
{
    //Read the domestic-stu.txt file and exit if failed
    std::string line;
    std::ifstream domesticFile("data/domestic-stu.txt");
    if (!domesticFile.is_open())
    {
        std::cerr << "Unable to open file domestic-stu.txt" << std::endl;
        exit(-1);
    }

    //Read the first line of domestic-stu.txt, which specifies
    //the file format
    getline(domesticFile, line);

    //Keep reading the rest of the lines in domestic-stu.txt.
    while (getline(domesticFile, line))
    {
        /*process each line, get each field separated by a comma.
         *We use istringstream to handle it.
         *Note in this example code here, we assume the file format
         *is perfect and do NOT handle error cases. We will leave the
         *error and exception handling of file format to Lab Assignment 4
         */
        std::istringstream ss(line);

        //declare temp variables to store data members
        std::string firstName, lastName, province, s_cgpa, s_researchScore;
        float cgpa;
        int researchScore;

        //get firstName separated by comma
        getline(ss, firstName, ',');
        if (firstName.empty())
        {
            throw MissingField();
        }

        //get lastName separated by comma
        getline(ss, lastName, ',');
        if (lastName.empty())
        {
            throw MissingField();
        }

        //get province separated by comma
        getline(ss, province, ',');
        if (province.empty())
        {
            throw MissingField();
        }

        //get cpga separated by comma, and convert string to float
        getline(ss, s_cgpa, ',');
        if (s_cgpa.empty())
        {
            throw MissingField();
        }
        cgpa = std::stof(s_cgpa.c_str());

        //get researchScore separated by comma, and convert it to int
        getline(ss, s_researchScore, ',');
        if (s_researchScore.empty())
        {
            throw MissingField();
        }
        researchScore = atoi(s_researchScore.c_str());

        DomesticStudent *inputStu;

        try
        {
            inputStu = new DomesticStudent(firstName, lastName, cgpa, researchScore, latestAppId++, province);
        }
        catch (const std::exception &e) //catches bad_alloc as well as errors with construction
        {
            std::cerr << e.what() << '\n';
            exit(-1);
        }

        inputVec.insert(inputStu);
    }

    //close your file
    domesticFile.close();
}
//can throw MissingField or InvalidCountry
void getInternationals(int &latestAppId, SortedList<InternationalStudent> &inputVec)
{
    //Read the international-stu.txt file and exit if failed
    std::string line;
    std::ifstream internationalFile("data/international-stu.txt");
    if (!internationalFile.is_open())
    {
        std::cerr << "Unable to open file international-stu.txt" << std::endl;
        exit(-1);
    }

    //Read the first line of international-stu.txt, which specifies
    //the file format.
    getline(internationalFile, line);

    //Keep reading the rest of the lines in international-stu.txt
    while (getline(internationalFile, line))
    {
        /*process each line, get each field separated by a comma.
         *We use istringstream to handle it.
         *Note in this example code here, we assume the file format
         *is perfect and do NOT handle error cases. We will leave the
         *error and exception handling of file format to Lab Assignment 4
         */
        std::istringstream ss(line);

        std::string firstName, lastName, country, s_cgpa, s_researchScore, s_readingScore, s_listeningScore, s_speakingScore, s_writingScore;
        float cgpa;
        int researchScore, readingScore, listeningScore, speakingScore, writingScore;

        //get firstName separated by comma
        getline(ss, firstName, ',');
        if (firstName.empty())
        {
            throw MissingField();
        }

        //get lastName separated by comma
        getline(ss, lastName, ',');
        if (lastName.empty())
        {
            throw MissingField();
        }

        //get country separated by comma
        getline(ss, country, ',');
        if (country.empty())
        {
            throw MissingField();
        }

        //get cpga separated by comma, and convert string to float
        getline(ss, s_cgpa, ',');
        if (s_cgpa.empty())
        {
            throw MissingField();
        }
        cgpa = std::stof(s_cgpa.c_str());

        //get researchScore separated by comma, and convert it to int
        getline(ss, s_researchScore, ',');
        if (s_researchScore.empty())
        {
            throw MissingField();
        }
        researchScore = atoi(s_researchScore.c_str());

        //get readingScore separated by comma, and convert it to int
        getline(ss, s_readingScore, ',');
        if (s_readingScore.empty())
        {
            throw MissingField();
        }
        readingScore = atoi(s_readingScore.c_str());

        //get listeningScore separated by comma, and convert it to int
        getline(ss, s_listeningScore, ',');
        if (s_listeningScore.empty())
        {
            throw MissingField();
        }
        listeningScore = atoi(s_listeningScore.c_str());

        //get speakingScore separated by comma, and convert it to int
        getline(ss, s_speakingScore, ',');
        if (s_speakingScore.empty())
        {
            throw MissingField();
        }
        speakingScore = atoi(s_speakingScore.c_str());

        //get writingScore separated by comma, and convert it to int
        getline(ss, s_writingScore, ',');
        if (s_writingScore.empty())
        {
            throw MissingField();
        }
        writingScore = atoi(s_writingScore.c_str());

        InternationalStudent *inputStu;

        try
        {
            inputStu = new InternationalStudent(firstName, lastName, cgpa, researchScore, latestAppId++, country,
                                                ToeflScore(readingScore, listeningScore, speakingScore, writingScore));
        }
        catch (const std::exception &e) //catches bad_alloc as well as construction exceptions
        {
            std::cerr << e.what() << '\n';
            exit(-1);
        }

        inputVec.insert(inputStu);
    }

    //close your file
    internationalFile.close();
}

//returns an integer corresponding to the user's choice from the curses or integer-based menus
int getDatabaseSelection()
{
    std::string choices[5] = {
        "Please select which student database you would like to access:",
        "Domestic Student Database",
        "International Student Database",
        "Merged Databases",
        "Exit program"};

    if (CURSES_ENABLE)
    {
        return getUserInt(choices, 4);
    }

    //fallback, if the curses menu is disabled
    //prints all the options in a normal integer-selection menu
    std::cout << choices[0] << std::endl;
    for (int i = 1; i < 5; i++)
    {
        std::cout << i << ": " << choices[i] << std::endl;
    }
    return getUserInt();
}
int getPathSelection()
{
    std::string choices[11] =
        {
            "Please choose what you would like to do",
            "Search student database by attribute",
            "Search student database by name",
            "Create a new student and add them to the system",
            "Delete students by name",
            "Delete the first and last students of the list",
            "Delete all the students who are not proficient in English",
            "Print all students in the list",
            "Set thresholds for CGPA and research score, then display all qualifying students",
            "Choose a different database",
            "Exit"};

    if (CURSES_ENABLE)
    {
        return getUserInt(choices, 10);
    }

    //fallback, if the curses menu is disabled
    //prints all the options in a normal integer-selection menu
    std::cout << choices[0] << std::endl;
    for (int i = 1; i < 11; i++)
    {
        std::cout << i << ": " << choices[i] << std::endl;
    }
    return getUserInt();
}
int getAttributeSelection()
{
    std::string choices[4] = {
        "Please choose what attribute you would like to search by:",
        "Application ID",
        "CGPA",
        "Research Score"};

    if (CURSES_ENABLE)
    {
        return getUserInt(choices, 3);
    }

    //fallback, if the curses menu is disabled
    //prints all the options in a normal integer-selection menu
    std::cout << choices[0] << std::endl;
    for (int i = 1; i < 4; i++)
    {
        std::cout << i << ": " << choices[i] << std::endl;
    }
    return getUserInt();
}
int getTypeSelection()
{
    std::string choices[3] = {
        "Will this be a domestic or international student?",
        "Domestic",
        "International"};

    if (CURSES_ENABLE)
    {
        return getUserInt(choices, 2);
    }

    //fallback, if the curses menu is disabled
    //prints all the options in a normal integer-selection menu
    std::cout << choices[0] << std::endl;
    for (int i = 1; i < 3; i++)
    {
        std::cout << i << ": " << choices[i] << std::endl;
    }
    return getUserInt();
}

//encapsulate because robust input is too complex
//asks for user to provide an integer, which it promptly returns.
//should handle any malformed inputs gracefully
int getUserInt()
{
    while (true)
    {
        int selection = 0;
        //this code is templated from the ISO's C++ FAQ
        while ((std::cout << "Please enter an integer: ") && !(std::cin >> selection))
        {
            std::cout << "That's not a number. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return selection;
    }
}
float getUserFloat()
{
    while (true)
    {
        float selection = 0;
        //this code is templated from the ISO's C++ FAQ
        while ((std::cout << "Please enter a float: ") && !(std::cin >> selection))
        {
            std::cout << "That's not a number. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return selection;
    }
}
std::string getUserString()
{
    while (true)
    {
        std::string selection = "";
        //this code is templated from the ISO's C++ FAQ
        while ((std::cout << "Please enter a string: ") && !(std::cin >> selection))
        {
            std::cout << "That's not valid. Please try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return selection;
    }
}

//adds a new item to the supplied list of students, with user input, given all necessary information for a generic student.
//This function is overloaded depending on the type of input list, and acts accordingly to determine the
//other necessary information to create the desired type of student.
void insertNew(SortedList<DomesticStudent> &inputList, string first, string last, float cgpa, int rs, int &globalAppId, bool &failure)
{
    using std::cout;
    cout << "Please enter the student's province of origin:\n";
    string province = getUserString();

    try
    {
        auto inputStu = new DomesticStudent(first, last, cgpa, rs, globalAppId, province);
        inputList.insert(inputStu);
        failure = false;
    }
    catch (const std::exception &e) //catches bad_alloc, as well as any exceptions thrown by the constructor in response to bad input
    {
        std::cerr << e.what() << '\n';
        failure = true;
    }
}
void insertNew(SortedList<InternationalStudent> &inputList, string first, string last, float cgpa, int rs, int &globalAppId, bool &failure)
{
    using std::cout;
    cout << "Please enter the student's country of origin:\n";
    string country = getUserString();
    cout << "Please enter the student's TOEFL scores:\n";
    cout << "Reading:\n";
    int reading = getUserInt();
    cout << "Listening:\n";
    int listening = getUserInt();
    cout << "Speaking:\n";
    int speaking = getUserInt();
    cout << "Writing:\n";
    int writing = getUserInt();

    try
    {
        auto inputStu = new InternationalStudent(first, last, cgpa, rs, globalAppId, country, ToeflScore(reading, listening, speaking, writing));
        inputList.insert(inputStu);
        failure = false;
    }
    catch (const std::exception &e) //catches bad_alloc, as well as any exceptions thrown by the constructor in response to bad input
    {
        std::cerr << e.what() << '\n';
        failure = true;
    }
}
void insertNew(SortedList<Student> &inputList, string first, string last, float cgpa, int rs, int &globalAppId, bool &failure)
{
    using std::cout;

    switch (getTypeSelection())
    {
    case 1: //domestic
    {
        cout << "Please enter the student's province of origin:\n";
        string province = getUserString();

        try
        {
            auto inputStu = new DomesticStudent(first, last, cgpa, rs, globalAppId, province);
            inputList.insert(inputStu);
            failure = false;
        }
        catch (const std::exception &e) //catches bad_alloc, as well as any exceptions thrown by the constructor in response to bad input
        {
            std::cerr << e.what() << '\n';
            failure = true;
        }
        break;
    }
    case 2: //international
    {

        cout << "Please enter the student's country of origin:\n";
        string country = getUserString();
        cout << "Please enter the student's TOEFL scores:\n";
        cout << "Reading:\n";
        int reading = getUserInt();
        cout << "Listening:\n";
        int listening = getUserInt();
        cout << "Speaking:\n";
        int speaking = getUserInt();
        cout << "Writing:\n";
        int writing = getUserInt();

        try
        {
            auto inputStu = new InternationalStudent(first, last, cgpa, rs, globalAppId, country, ToeflScore(reading, listening, speaking, writing));
            inputList.insert(inputStu);
            failure = false;
        }
        catch (const std::exception &e) //catches bad_alloc, as well as any exceptions thrown by the constructor in response to bad input
        {
            std::cerr << e.what() << '\n';
            failure = true;
        }
    }
    }
}

void merge(SortedList<DomesticStudent> &list1, SortedList<InternationalStudent> &list2, SortedList<Student> &list3)
{
    //extracts all students from each list and inserts them into the merged list
    auto currentDom = list1.pop();
    while (currentDom != nullptr)
    {
        list3.insert(currentDom);
        currentDom = list1.pop(); //next student
    }
    auto currentInt = list2.pop();
    while (currentInt != nullptr)
    {
        list3.insert(currentInt);
        currentInt = list2.pop(); //next student
    }
}
void unmerge(SortedList<DomesticStudent> &list1, SortedList<InternationalStudent> &list2, SortedList<Student> &list3)
{
    //extracts all students from the merged list, determines their type, and places them in the appropriate list
    auto currentStu = list3.pop();
    while (currentStu != nullptr)
    {
        if (currentStu->isDomestic) //domestic
        {
            list1.insert(dynamic_cast<DomesticStudent *>(currentStu));
        }
        else //international
        {
            list2.insert(dynamic_cast<InternationalStudent *>(currentStu));
        }
        currentStu = list3.pop(); //next student
    }
}
