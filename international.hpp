//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Declarations for all international student-specific functions and members
//------------------------------------------------------------------------------------------------------------------------------------------------------------------


#ifndef INTERNATIONAL_HPP
#define INTERNATIONAL_HPP

#include <string>
#include <iostream>

#include "student.hpp"
#include "toefl.hpp"

class InternationalStudent : public Student
{
public:
    //constructor
    InternationalStudent();
    InternationalStudent(string firstNameInput, string lastNameInput, float cgpaInput,
                         unsigned int researchScoreInput, unsigned int appIdInput, string countryInput, ToeflScore toeflScoreInput);

    //getters and setters
    string getCountry() const;
    ToeflScore getToeflScore() const;

    void setCountry(string countryInput);
    void setToeflScore(ToeflScore toeflScoreInput);
    
    //other member functions
    bool speaksEnglish() const;
    bool isToeflValid() const;

    //friend
    friend std::ostream& operator<<(std::ostream& outs, const InternationalStudent& stu);

    //overrides parent function
    void printInfo(std::ostream& outs) const;

    //overrides parent function
    bool speaksEnglish();

private:
    string country;
    ToeflScore toeflScore;
};

#endif //INTERNATIONAL_HPP
