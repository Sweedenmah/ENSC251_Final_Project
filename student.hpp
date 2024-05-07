//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Declaring all functions and members of Student objects
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <string>
#include <iostream>
#include "exceptions.hpp"

using std::string;

class Student
{
public:
    //constructors
    //default constructor
    Student();
    Student(string firstNameInput, string lastNameInput, float cgpaInput,
            unsigned int researchScoreInput, unsigned int appIdInput, bool isDomesticInput);

    virtual ~Student() = default;

    //getters and setters
    string getFirstName() const;
    string getLastName() const;
    float getCgpa() const;
    unsigned int getResearchScore() const;
    unsigned int getAppId() const;

    void setFirstName(string firstNameInput);
    void setLastName(string lastNameInput);
    void setCgpa(float cgpaInput);
    void setResearchScore(unsigned int researchScoreInput);
    void setAppId(unsigned int appIdInput);

    //comparators
    //return status: -1=left is less than right, 0=equal to, 1=greater than
    friend int compareCGPA(Student *student1, Student *student2);
    friend int compareResearchScore(Student *student1, Student *student2);
    friend int compareFirstName(Student *student1, Student *student2);
    friend int compareLastName(Student *student1, Student *student2);
    friend int multiCompare(Student *student1, Student *student2);

    //must be overriden by child classes
    virtual void printInfo(std::ostream &outs) const = 0;

protected: //protected means that derived classes can inherit these member variables
           //note: protected is generally bad form, the variables here should probably be hidden behind accessor and mutator functions
           //in this case it's probably ok to leave it as is.
    string firstName;
    string lastName;
    float cgpa;
    unsigned int researchScore;
    unsigned int appId;

    //check member variables
    bool areMembersValid() const;

public: //extra public: section at the end here to silence compiler warnings

    //since pure students can never exist, this stores if they are domestic or not so they can be compared against each other.
    bool isDomestic;
    //must be overriden by child classes
    virtual bool speaksEnglish() = 0;
};

#endif //STUDENT_HPP
