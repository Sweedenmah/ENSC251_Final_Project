//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Declares function prototypes for helper functions
//------------------------------------------------------------------------------------------------------------------------------------------------------------------


#ifndef HELPER_HPP 
#define HELPER_HPP
//guard against double inclusion

#include <string>
#include "domestic.hpp"
#include "international.hpp"
#include "list.hpp"
#include "exceptions.hpp"

//read from file and return all students in a vector
void getDomestics(int &latestAppId, SortedList<DomesticStudent>& inputVec);
void getInternationals(int &latestAppId, SortedList<InternationalStudent>& inputVec);

//various small helper functions
int getPathSelection();
int getDatabaseSelection();
int getAttributeSelection();

int getUserInt();
float getUserFloat();
std::string getUserString();

void insertNew(SortedList<DomesticStudent> &inputList,      string first, string last, float cgpa, int rs, int &globalAppId, bool& failure);
void insertNew(SortedList<InternationalStudent> &inputList, string first, string last, float cgpa, int rs, int &globalAppId, bool& failure);
void insertNew(SortedList<Student> &inputList,              string first, string last, float cgpa, int rs, int &globalAppId, bool& failure);

void merge(SortedList<DomesticStudent> &list1, SortedList<InternationalStudent> &list2, SortedList<Student> &list3);
void unmerge(SortedList<DomesticStudent> &list1, SortedList<InternationalStudent> &list2, SortedList<Student> &list3);

#endif //HELPER_HPP
