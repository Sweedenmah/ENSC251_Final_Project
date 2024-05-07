//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Implementations for functions shared in all Students or derivatives
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream> //input and output
#include <iomanip>
#include <cmath>
#include <limits>

#include "student.hpp"

Student::Student() {}
Student::Student(string firstNameInput, string lastNameInput, float cgpaInput,
                 unsigned int researchScoreInput, unsigned int appIdInput, bool isDomesticInput) : firstName(firstNameInput), lastName(lastNameInput), cgpa(cgpaInput), researchScore(researchScoreInput),
                                                                                                   appId(appIdInput), isDomestic(isDomesticInput)
{
    if (!areMembersValid())
    {
        throw InvalidMember();
    }
    //initialization complete
}

//getters and setters
string Student::getFirstName() const
{
    return firstName;
}
string Student::getLastName() const
{
    return lastName;
}
float Student::getCgpa() const
{
    return cgpa;
}
unsigned int Student::getResearchScore() const
{
    return researchScore;
}
unsigned int Student::getAppId() const
{
    return appId;
}

void Student::setFirstName(string firstNameInput)
{
    firstName = firstNameInput;
}
void Student::setLastName(string lastNameInput)
{
    lastName = lastNameInput;
}
void Student::setCgpa(float cgpaInput)
{
    cgpa = cgpaInput;
}
void Student::setResearchScore(unsigned int researchScoreInput)
{
    researchScore = researchScoreInput;
}
void Student::setAppId(unsigned int appIdInput)
{
    appId = appIdInput;
}

//print information about member variables
//if this specific function is ever called, it means inheritance broke
void Student::printInfo(std::ostream &outs) const
{
    outs << "ERROR: VIRTUAL FUNCTION CALLED\n";
    exit(-1);
    //outs << "Student Information: \n";
    //outs << "First Name: " << firstName;
    //outs << ", Last Name: " << lastName << std::endl;
    //outs << "CGPA: " << std::fixed << std::setprecision(1) << cgpa;
    //outs << ", Research Score: " << researchScore;
    //outs << ", Application ID: " << appId << std::endl;
}

//check validity
bool Student::areMembersValid() const
{
    if (researchScore > 100 || appId < 20200000 || cgpa < 0 || cgpa > 4.34) //limits
    {
        return false;
    }
    else
    {
        return true;
    }
}

//comparators
int compareCGPA(Student *student1, Student *student2)
{
    //float comparison is weird, we have to take the absolute value of their difference and compare it to a constant
    if (fabs(student1->getCgpa() - student2->getCgpa()) < std::numeric_limits<float>::epsilon())
        return 0; //equal
    else if (student1->getCgpa() > student2->getCgpa())
        return 1;
    else if (student1->getCgpa() < student2->getCgpa())
        return -1;
    else
    {
        std::cerr << ("Unreachable condition reached in compareCGPA\n");
        exit(-1);
    }
}
int compareResearchScore(Student *student1, Student *student2)
{
    if (student1->getResearchScore() > student2->getResearchScore())
        return 1;
    else if (student1->getResearchScore() == student2->getResearchScore())
        return 0;
    else if (student1->getResearchScore() < student2->getResearchScore())
        return -1;
    else
    {
        std::cerr << ("Unreachable condition reached in compareResearchScore\n");
        exit(-1);
    }
}
int compareFirstName(Student *student1, Student *student2)
{
    //string comparisons are also weird
    //string1.compare(string2) returns a positive value if string 2 is greater.

    auto left = student1->getFirstName();
    auto right = student2->getFirstName();
    for (auto &c : left)
    {
        c = static_cast<char>(toupper(c));
    }
    for (auto &c : right)
    {
        c = static_cast<char>(toupper(c));
    }

    if (left.compare(right) < 0)
    {
        return 1;
    }
    else if (left.compare(right) == 0)
    {
        return 0;
    }
    else if (left.compare(right) > 0)
    {
        return -1;
    }
    else
    {
        std::cerr << ("Unreachable condition reached in compareFirstName\n");
        exit(-1);
    }
}
int compareLastName(Student *student1, Student *student2)
{

    auto left = student1->getLastName();
    auto right = student2->getLastName();

    for (auto &c : left)
    {
        c = static_cast<char>(toupper(c));
    }
    for (auto &c : right)
    {
        c = static_cast<char>(toupper(c));
    }

    if (left.compare(right) < 0)
    {
        return 1;
    }
    else if (left.compare(right) == 0)
    {
        return 0;
    }
    else if (left.compare(right) > 0)
    {
        return -1;
    }
    else
    {
        std::cerr << ("Unreachable condition reached in compareLastName\n");
        exit(-1);
    }
}
int multiCompare(Student *student1, Student *student2)
{
    if (compareResearchScore(student1, student2) == 1)
    {
        return 1;
    }
    else if (compareResearchScore(student1, student2) == -1)
    {
        return -1;
    }
    else if (compareCGPA(student1, student2) == 1)
    {
        return 1;
    }
    else if (compareCGPA(student1, student2) == -1)
    {
        return -1;
    }
    else if (student1->isDomestic && !student2->isDomestic)
    {
        return 1;
    }
    else if (!student1->isDomestic && student2->isDomestic)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
