//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Implementations of Domestic Student-specific functions
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <string>
#include "domestic.hpp"

//constructor
DomesticStudent::DomesticStudent() {}
DomesticStudent::DomesticStudent(string firstNameInput, string lastNameInput, float cgpaInput,
                                 unsigned int researchScoreInput, unsigned int appIdInput, string provinceInput)
    : Student(firstNameInput, lastNameInput, cgpaInput, researchScoreInput, appIdInput, true), province(provinceInput)
{
    const std::string provinces[13] = {"NL", "PE", "NS", "NB", "QC", "ON", "MB", "SK", "AB", "BC", "YT", "NT", "NU"};

    bool valid = false;

    for (auto &c : province)
    {
        c = static_cast<char>(toupper(c));
    }

    for (const auto& prov : provinces)
    {
        if (province.compare(prov) == 0)
        {
            valid = true;
            break;
        }
    }
    if (!valid)
    {
        throw InvalidProvince();
    }
    //initialization complete
}

//getter and setter
string DomesticStudent::getProvince() const
{
    return province;
}
void DomesticStudent::setProvince(string provinceInput)
{
    province = provinceInput;
}

bool DomesticStudent::speaksEnglish()
{
    return true;
}

//overloaded insertion operator
std::ostream &operator<<(std::ostream &outs, const DomesticStudent &stu)
{
    stu.printInfo(outs);
    return outs;
}

void DomesticStudent::printInfo(std::ostream &outs) const
{
    outs << "Student Information: \n";
    outs << "First Name: " << firstName;
    outs << ", Last Name: " << lastName << std::endl;
    outs << "CGPA: " << std::fixed << std::setprecision(1) << cgpa;
    outs << ", Research Score: " << researchScore;
    outs << ", Application ID: " << appId << std::endl;

    outs << "Province = " << province << std::endl << std::endl;
}
