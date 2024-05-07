//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Implementations for international student-specific members
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <string>
#include <iomanip>
#include "international.hpp"

using std::string;

InternationalStudent::InternationalStudent() {}
InternationalStudent::InternationalStudent(string firstNameInput, string lastNameInput, float cgpaInput, unsigned int researchScoreInput,
                                           unsigned int appIdInput, string countryInput, ToeflScore toeflScoreInput)
    : Student(firstNameInput, lastNameInput, cgpaInput, researchScoreInput, appIdInput, false), country(countryInput), toeflScore(toeflScoreInput)

{
    const std::string countries[5] = {"CANADA", "CHINA", "INDIA", "IRAN", "KOREA"};

    bool valid = false;

    auto countryCheck = country;

    for (auto &c : countryCheck)
    {
        c = static_cast<char>(toupper(c));
    }

    for (auto count : countries)
    {
        if (countryCheck == count)
        {
            valid = true;
            break;
        }
        else if (countryCheck == "IDIAN")
        {
            std::cerr << "Warning: typo automatically corrected: from Idian to India.\n";
            country = "India";
            valid = true;
            break;
        }
    }
    if (!valid)
    {
        throw InvalidCountry();
    }

    //initialization complete
}

//getters and setters
string InternationalStudent::getCountry() const
{
    return country;
}
ToeflScore InternationalStudent::getToeflScore() const
{
    return toeflScore;
}

void InternationalStudent::setCountry(string countryInput)
{
    country = countryInput;
}
void InternationalStudent::setToeflScore(ToeflScore toeflScoreInput)
{
    toeflScore = toeflScoreInput;
}

bool InternationalStudent::speaksEnglish()
{
    return isToeflValid();
}

//other member functions
bool InternationalStudent::isToeflValid() const
{
    if (!toeflScore.isValid())
    {
        return false;
    }
    if (toeflScore.getTotal() < 93)
        return false;
    if (toeflScore.getReading() < 20)
        return false;
    if (toeflScore.getListening() < 20)
        return false;
    if (toeflScore.getSpeaking() < 20)
        return false;
    if (toeflScore.getWriting() < 20)
        return false;
    return true;
}
bool InternationalStudent::speaksEnglish() const
{
    return isToeflValid();
}

void InternationalStudent::printInfo(std::ostream &outs) const
{
    outs << "Student Information: \n";
    outs << "First Name: " << firstName;
    outs << ", Last Name: " << lastName << std::endl;
    outs << "CGPA: " << std::fixed << std::setprecision(1) << cgpa;
    outs << ", Research Score: " << researchScore;
    outs << ", Application ID: " << appId << std::endl;

    outs << "Country = " << country << std::endl;
    outs << toeflScore << std::endl;
}

//friend insertion operator
std::ostream &operator<<(std::ostream &outs, const InternationalStudent &stu)
{
    stu.printInfo(outs);
    return outs;
}
