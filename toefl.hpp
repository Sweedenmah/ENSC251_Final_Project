//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Declarations for toeflScore related functions and members
//------------------------------------------------------------------------------------------------------------------------------------------------------------------


#ifndef TOEFL_HPP
#define TOEFL_HPP
//inclusion guards

#include <iostream>

class ToeflScore
{
public:
    //constructor
    ToeflScore(int readingInput, int listeningInput, int speakingInput, int writingInput);
    //default constructor
    ToeflScore();

    //getters and setters
    int getReading() const;
    int getListening() const;
    int getSpeaking() const;
    int getWriting() const;
    int getTotal() const;

    void setReading(int readingInput);
    void setListening(int listeningInput);
    void setSpeaking(int speakingInput);
    void setWriting(int writingInput);
    //no setTotal(), as total is calculated based on all the rest

    //are the toefl scores actually possible?
    bool isValid() const;

    //overloaded insertion operator
    friend std::ostream &operator<<(std::ostream &outs, const ToeflScore &toefl);

private: //to ensure ADT
    int reading;
    int listening;
    int speaking;
    int writing;
    int total;
};

#endif //TOEFL_HPP
