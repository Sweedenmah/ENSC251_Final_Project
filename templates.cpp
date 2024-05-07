//----------------------------------------------------------------------------------------------------------------------
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//----------------------------------------------------------------------------------------------------------------------
// All main functions that require templating go here, as they interfere with .hpp inclusion
//----------------------------------------------------------------------------------------------------------------------

#include <limits>
#include <cmath>
#include "helpers.hpp"

//main logic allowing users to choose what function they would like to use
template <class T>
void choosePath(SortedList<T> &inputList, int &globalAppId)
{
    switch (getPathSelection())
    {
    case 1: //attribute-based search
    {
        bool found = false;

        switch (getAttributeSelection())
        {
        case 1: //application id
        {
            std::cout << "\nPlease enter the application ID of the student you are searching for:\n";
            unsigned int appId = getUserInt();

            for (const auto &node : inputList) //iterate through the list of students using the iterators defined in list.hpp
            {
                if (appId == node.getDataPtr()->getAppId()) //values match
                {
                    std::cout << std::endl;                  //newline for padding
                    node.getDataPtr()->printInfo(std::cout); //output information
                    found = true;
                    break; //there can only be one student with each app id
                }
            }
            break;
        }
        case 2: //cgpa
        {
            std::cout << "\nPlease enter the CGPA you are searching for:\n";
            float cgpa = getUserFloat();

            for (const auto &node : inputList)
            {
                if (fabs(cgpa - node.getDataPtr()->getCgpa()) < std::numeric_limits<float>::epsilon()) //float comparison isn't simple
                {
                    std::cout << std::endl; //newline for padding
                    node.getDataPtr()->printInfo(std::cout);
                    found = true;
                }
            }
            break;
        }
        case 3: //Research Score
        {
            std::cout << "\nPlease enter the research score you are searching for:\n";
            unsigned int researchScore = getUserInt();

            for (const auto &node : inputList)
            {
                if (researchScore == node.getDataPtr()->getResearchScore())
                {
                    std::cout << std::endl; //newline for padding
                    node.getDataPtr()->printInfo(std::cout);
                    found = true;
                }
            }
            break;
        }
        }

        if (!found)
        {
            std::cout << "\nNo student with that attribute was found.\n";
        }
        break;
    }
    case 2: //name-based search
    {
        bool found = false;

        std::cout << "\nPlease enter the first name of the student you are looking for\n";
        std::string first = getUserString();
        std::cout << "\nThank you. Next, please enter the last name\n";
        std::string last = getUserString();

        //capitalize
        for (auto &c : first)
        {
            c = static_cast<char>(toupper(c));
        }
        for (auto &c : last)
        {
            c = static_cast<char>(toupper(c));
        }

        //iterate through all the students in the list
        for (const auto &node : inputList)
        {
            //store for capitalization
            auto nodeFirst = node.getDataPtr()->getFirstName();
            auto nodeLast = node.getDataPtr()->getLastName();

            //capitalize
            for (auto &c : nodeFirst)
            {
                c = static_cast<char>(toupper(c));
            }
            for (auto &c : nodeLast)
            {
                c = static_cast<char>(toupper(c));
            }

            if (first.compare(nodeFirst) == 0 && last.compare(nodeLast) == 0) //if first and last names match
            {
                node.getDataPtr()->printInfo(std::cout);
                found = true;
            }
        }

        if (!found)
        {
            std::cout << "\nNo student with that attribute was found.\n";
        }
        break;
    }
    case 3: //Add new student
    {
        using std::cout;
        bool failure = false;

        //remain in the loop until the user enters valid information
        do
        {
            cout << "Please enter all requisite information for a student of this type\n";
            cout << "Please enter the first name:\n";
            string first = getUserString();
            cout << "Please enter the last name:\n";
            string last = getUserString();
            cout << "Please enter the student's CGPA:\n";
            float cgpa = getUserFloat();
            cout << "Please enter the student's research score:\n";
            int rs = getUserInt();

            insertNew(inputList, first, last, cgpa, rs, globalAppId, failure);
            //automatically calls the correct overload of insertNew based on the type of inputList

        } while (failure);

        globalAppId++;
        std::cout << "Student successfully created and added!\n";
        break;
    }
    case 4: //Delete Student
    {
        using std::cout;
        cout << "Please enter the first and last name of the student you wish to delete:\n";
        string first = getUserString();
        string last = getUserString();

        //deletes all students with that name, then informs the user
        if (!inputList.searchAndDestroy(first, last))
        {
            cout << "Student not found; list unaltered\n";
        }
        else
        {
            cout << "Student(s) deleted.\n";
        }
        break;
    }
    case 5: //delete head and tail nodes
    {
        inputList.aLittleOffTheTopAndBottom();
        std::cout << "Deletion Successful. If the target list had less than three elements, it is now empty.\n";
        break;
    }
    case 6: //drop students who aren't proficient in English
    {
        inputList.filterEnglish();
        std::cout << "Success. List now only contains proficient students.\n";
        break;
    }
    case 7: //print all
    {
        for (const auto &node : inputList)
        {
            node.getDataPtr()->printInfo(std::cout);
        }
        break;
    }
    case 8: //print all students that fit certain thresholds
    {
        using std::cout;
        cout << "Please enter the lowest CGPA you will accept: \n";
        float cgpa_thresh = getUserFloat();
        cout << "Please enter the lowest research score you will accept: \n";
        unsigned int rs_thresh = getUserInt(); //unsigned just to silence compiler warnings

        inputList.showAllOverThreshold(rs_thresh, cgpa_thresh, std::cout);
        cout << "Would you like to save the admitted students to disk?\n";
        cout << "Please enter 1 for yes, or any other integer for no.\n";

        switch (getUserInt())
        {
        case 1:
        {
            inputList.saveAllOverThreshold(rs_thresh, cgpa_thresh);
            cout << "Admitted student information saved to admitted.txt\n";
            break;
        }
        default: //anything other than a 1
        {
            break;
        }
        }
        break;
    }
    case 9: //back
    {
        return;
    }
    case 10: //exit
    {
        std::cout << "Exiting...\n";
        exit(0);
        break; //just in case
    }
    }

    std::cout << "Please press enter to continue\n";
    getchar();
}
