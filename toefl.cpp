//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Implementations of all required functions for toefl scores
//------------------------------------------------------------------------------------------------------------------------------------------------------------------


#include "toefl.hpp"
#include "exceptions.hpp"
#include <iostream>

//default constructor
ToeflScore::ToeflScore(int readingInput, int listeningInput, int speakingInput, int writingInput) : reading(readingInput), listening(listeningInput), speaking(speakingInput), writing(writingInput)
{
    //initialization already done above
    if (!isValid())
    {
        throw BadToefl();
    }
}
//implicit constructor
ToeflScore::ToeflScore()
{
    //nothing to be done
}

//getters and setters
int ToeflScore::getReading() const
{
    return reading;
}
int ToeflScore::getListening() const
{
    return listening;
}
int ToeflScore::getSpeaking() const
{
    return speaking;
}
int ToeflScore::getWriting() const
{
    return writing;
}
int ToeflScore::getTotal() const
{
    //total is defined as the sum as all the others, so we never actually store it
    return reading + listening + speaking + writing;
}

void ToeflScore::setReading(int readingInput)
{
    reading = readingInput;
}
void ToeflScore::setListening(int listeningInput)
{
    listening = listeningInput;
}
void ToeflScore::setSpeaking(int speakingInput)
{
    speaking = speakingInput;
}
void ToeflScore::setWriting(int writingInput)
{
    writing = writingInput;
}

bool ToeflScore::isValid() const
{
    //upper and lower bounds for toefl score
    if (reading > 30 || listening > 30 || speaking > 30 || writing > 30 ||
        reading < 0 || listening < 0 || speaking < 0 || writing < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

std::ostream &operator<<(std::ostream &outs, const ToeflScore &toefl)
{
    outs << "TOEFL Score: ";
    outs << "Reading: " << toefl.reading;
    outs << ", Listening: " << toefl.listening;
    outs << ", Speaking: " << toefl.speaking;
    outs << ", Writing: " << toefl.writing;
    outs << ", Total: " << toefl.getTotal() << std::endl;
    return outs;
}