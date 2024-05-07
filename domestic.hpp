//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Declarations and function prototypes for Domestic Student objects
//------------------------------------------------------------------------------------------------------------------------------------------------------------------


#ifndef DOMESTIC_HPP
#define DOMESTIC_HPP
//inclusion guards

#include <string>
#include "student.hpp"
 
using std::string;

class DomesticStudent : public Student
{
public:
    //constructors
    DomesticStudent();
    DomesticStudent(string firstNameInput, string lastNameInput, float cgpaInput,
                    unsigned int researchScoreInput, unsigned int appIdInput, string provinceInput);

    //getter and setter
    string getProvince() const;
    void setProvince(string provinceInput);

    bool speaksEnglish(); //domestics are assumed to be able to speak english

    void printInfo(std::ostream& outs) const;

    //friend
    friend std::ostream& operator<<(std::ostream& outs, const DomesticStudent& stu);

private:
    string province;
};

#endif //DOMESTIC_HPP
