//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
// All necessary declarations and definitions for a sorted singly-linked list of node templates.
//------------------------------------------------------------------------------------------------------------------------------------------------------------------


#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <limits>
#include <cmath>
#include <fstream>
#include "node.hpp"

template <class T>
class SortedList
{
public:
    //to enable range-based for loops and other more natural interaction with c++11 concepts, for anyone that uses this class
    class iterator
    {
    public:
        //constructor
        iterator(Node<T> *inputPtr) : ptr(inputPtr)
        {
        }
        //increment operator
        iterator operator++()
        {
            ptr = ptr->getLink();
            return *this;
        }
        //inequality operator
        bool operator!=(const iterator &other) const
        {
            return (ptr != other.ptr);
        }
        //dereferencing operator
        const Node<T> &operator*() const
        {
            return *ptr;
        }

    private:
        Node<T> *ptr;
    };

    //just for clarity; this is already in the public category
public:
    //default constructor
    SortedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    //destructor
    ~SortedList()
    {
        //iterates through all the nodes that are stored in this list, deleting each node and the data stored within
        auto current = head;
        while (current != nullptr)
        {
            auto temp = current;
            current = current->getLink();
            delete temp->getDataPtr();
            delete temp;
        }
    }

    //returns a pointer to the data stored in the head of the list
    //and removes it from the list.
    T *pop()
    {
        if (head == nullptr) //avoid dereferencing nullptr
        {
            return nullptr;
        }

        //we have to copy some pointers ahead of time so that we don't
        //lose track of their memory before we can operate on them
        auto temp = head;
        head = head->getLink();
        auto returnValue = temp->getDataPtr();

        //free memory
        delete temp;
        return returnValue;
    }

    //returns true if the list has no elements
    bool isEmpty() const
    {
        return (head == nullptr);
    }

    //puts this new value at the top of the sorted list
    void insert(T *t)
    {
        try //encapsulates problematic behaviour in try...catch statements
        {
            if (head == nullptr) //empty list
            {                    //head and tail both need to point to the same new node
                head = new Node<T>(t);
                tail = head;
                head->setLink(nullptr);
            }
            else if (head == tail)                           //one element in the list
            {                                                // head or tail need to be modified depending on whether the new node is larger or smaller than it
                if (multiCompare(head->getDataPtr(), t) < 1) //if head is smaller than the new node, it must be replaced
                {
                    head = new Node<T>(t);
                    head->setLink(tail);
                }
                else //otherwise, tail must be replaced
                {
                    tail = new Node<T>(t);
                    head->setLink(tail);
                }
            }
            //multiple elements in the list from here on
            else if (multiCompare(head->getDataPtr(), t) < 1) //head is less than t, so t should be at the head
            {
                auto temp = head;
                head = new Node<T>(t);
                head->setLink(temp);
            }
            else // t should be inserted somewhere below head
            {
                Node<T> *current = head;
                while (current != nullptr)
                {
                    if (current->getLink() == nullptr) //current is the last item in the list, so tail must be updated
                    {
                        current->setLink(new Node<T>(t));
                        tail = current->getLink();
                        break;
                    }
                    else if (multiCompare(current->getLink()->getDataPtr(), t) < 1) //the new node goes here
                    {
                        auto temp = current->getLink();
                        current->setLink(new Node<T>(t));
                        current->getLink()->setLink(temp);
                        break;
                    }
                    else
                    { //go to the next item in the list
                        current = current->getLink();
                    }
                }
            }
        }
        catch (const std::exception &e) //this catches bad_alloc (or any other exceptions that may be thrown) and informs the user thereof.
        {
            std::cerr << e.what() << '\n';
        }
    }

    //searches for the supplied name in the list, deletes it if found
    bool searchAndDestroy(std::string first, std::string last)
    {

        //capitalize the given strings in-place to ensure case-insensitivity
        for (auto &c : first)
        {
            c = static_cast<char>(toupper(c));
        }
        for (auto &c : last)
        {
            c = static_cast<char>(toupper(c));
        }

        //set up variables
        Node<T> *node = head;
        Node<T> *parent = nullptr;
        bool success = false;

        //iterates through all the items in the list, deleting matching items as it goes
        while (node != nullptr)
        {
            //store the current variables in case of deletion
            auto nextParent = node;
            auto nextNode = node->getLink();

            //copy the first and last names of the current student, for capitalization and comparison
            auto rightFirst = node->getDataPtr()->getFirstName();
            auto rightLast = node->getDataPtr()->getLastName();

            //capitalization for case-insensitivity
            for (auto &c : rightFirst)
            {
                c = static_cast<char>(toupper(c));
            }
            for (auto &c : rightLast)
            {
                c = static_cast<char>(toupper(c));
            }

            if (first.compare(rightFirst) == 0)
            {
                if (last.compare(rightLast) == 0)
                {
                    //set our next variables to ones that aren't about to get deleted
                    nextParent = parent;
                    nextNode = node->getLink();
                    //delete the node
                    remove(node, parent);
                    success = true;
                }
            }
            parent = nextParent;
            node = nextNode;
        }
        return success; //true or false depending on whether anything was deleted or not
    }

    //deletes the head and tail nodes in a single function
    //this is made complex because this isn't a doubly linked list, so to reassign the tail node
    //we must traverse the entirety of the list in order to find the second-last node
    void aLittleOffTheTopAndBottom()
    {
        remove(head, nullptr);

        if (head == tail) //the list had two or less components before deletion
        {
            remove(tail, nullptr);
            return;
        }
        else if (head->getLink() == tail) //the head had exactly three components before deletion, so it currently has two elements: tail and head.
        {                                 //we only want to remove the tail, since we already removed the head earlier. The second argument is the parent.
            remove(tail, head);
        }
        else //the list had >3 elements before deletion, so we have to traverse it to find the second-last element to reassign to the tail.
        {
            auto current = head;
            while (current->getLink() != tail)
            {
                current = current->getLink();
            } //breaks from the loop when current is tail's parent node
            remove(tail, current);
        }
    }

    //deletes all elements that cannot speak english
    void filterEnglish()
    {
        Node<T>* current = head;
        Node<T>* parent = nullptr;

        //iterates through all the items in the list, deleting failing items as it goes
        while (current != nullptr)
        {
            //store the current variables in case of deletion
            auto nextParent = current;
            auto nextCurrent = current->getLink();

           
                if (!(current->getDataPtr()->speaksEnglish()))
                {
                    //set our next variables to ones that aren't about to get deleted
                    nextParent = parent;
                    nextCurrent = current->getLink();
                    //delete the node
                    remove(current, parent);
                }
            
            parent = nextParent;
            current = nextCurrent;
        }
    }

    //Prints all elements of the list above a supplied research score and cgpa
    void showAllOverThreshold(unsigned int rs, float cgpa, std::ostream &outs)
    {
        auto current = head;

        //iterates through the whole list
        while (current != tail)
        {
            if (current->getDataPtr()->getResearchScore() >= rs)
            {
                if (current->getDataPtr()->getCgpa() > cgpa || fabs(current->getDataPtr()->getCgpa() - cgpa) < std::numeric_limits<float>::epsilon())
                //greater than or equal to, but floats are complicated
                //if these were integers, it could be rewritten as (current->getDataPtr->getCgpa() >= cgpa)
                {
                    current->getDataPtr()->printInfo(outs); //uses polymorphism and virtual method printInfo()
                }
            }
            current = current->getLink(); //move to the next item
        }
    }

    //Calls the above function with a set output file, for later perusal
    void saveAllOverThreshold(unsigned int rs, float cgpa)
    {
        std::ofstream outputFile;
        outputFile.open("admitted.txt", std::ios::trunc); //if a previous output file exists, this will overwrite it
        showAllOverThreshold(rs, cgpa, outputFile);
        outputFile.close();
    }

    //iterators, for the same reason as stated above: more intuitive interaction with c++11 concepts
    //we only allow const iterators here to avoid messy memory issues
    iterator begin() const
    {
        return iterator(head);
    }
    iterator end() const
    {
        return iterator(tail);
    }

private:
    //deletes the node by pointer
    //precondition: begone points to an element that actually exists in the list
    //this is a strict condition, but this is acceptable for a private method.
    void remove(Node<T> *begone, Node<T> *parent)
    {
        if (begone == nullptr)
        {
            return; //nothing to do
        }

        if (parent == nullptr) //avoid dereferencing nullptr
        {
            head = head->getLink();
        }
        else
        {
            parent->setLink(begone->getLink());
        }

        if (begone == tail)
        {
            tail = parent;
        }

        //the above section removed references to begone from the list
        //now we free the memory stored in begone.

        delete begone->getDataPtr();
        delete begone;
    }

    //stores the top and bottom of the list, respectively
    Node<T> *head;
    Node<T> *tail;
};

#endif //LIST_HPP
