//---------------------------------------------------------------------------------------------------------------------------------------------------------------
// Jake Merkl / Devon Burnham / Gaspar Fung / Chenting Mao
// 301398265  / 301394066     / 301386235   / 301399922
//
// Group 8
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
// Definitions of all ncurses-based functions needed
//------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <ncurses.h>
#include <menu.h>
#include <string>
#include "ncmenu.hpp"

//initializes curses and sets various parameters for proper operation
void initCurses()
{
    initscr(); //start curses
    cbreak();  //intercept each character immediately as it is pressed, don't wait for enter
    noecho();  //suppress output
    curs_set(0); //invisible cursor
    keypad(stdscr, TRUE); //allows us to read keys other than standard alphanumeric, such as arrow keys and function keys
                          //useful to capture arrow keys for menu navigation
}

//shows an interactive menu to the user, returns an integer corresponding to the index of their choice
//note: ncurses is written in C, not C++, so the interface with this library is a little outdated,
//and requires specific ways of memory management.
//also, when ncurses is used in a project, valgrind and other such memory leak-detecting tools aren't very accurate
//(as noted by the developers of ncurses), because curses implementations hold on to their memory even after it has been properly
//freed using free_menu() and free_item() as specified. This is intended behaviour, and doesn't correspond to a real memory leak.
int printMenu(std::string *choices, int n_choices)
{
    ITEM **items; //declare array of item pointers
    int c;        //declare a variable to store the input character in
    MENU *menu;   //declare menu pointer

    items = new ITEM *[n_choices + 1]; //allocate memory for all the item pointers, plus a null termination

    for (int i = 0; i < n_choices; i++)
    {
        items[i] = (new_item(choices[i + 1].c_str(), "")); //instantiate new items from the strings in choices
    }
    items[n_choices] = (nullptr); //curses likes null-terminated arrays

    menu = new_menu(items);                                                 //instantiate new menu from item list
    mvprintw(LINES - 3, 0, choices[0].c_str());                             //print instructions (mvprintw allows printing information to any location on screen)
    mvprintw(LINES - 2, 0, "Please choose an option using the arrow keys"); //print header
    post_menu(menu);                                                        //send it to the screen
    refresh();                                                              //actually show it

    while ((c = getch()) != '\n')
    {
        switch (c)
        {
        case KEY_DOWN: //special character corresponding to the down arrow key
        {
            menu_driver(menu, REQ_DOWN_ITEM); //move to upper item
            break;
        }
        case KEY_UP:
        {
            menu_driver(menu, REQ_UP_ITEM); //move to lower item
            break;
        }
        }
    }

    int index = item_index(current_item(menu)); //get the actual index of the chosen item

    unpost_menu(menu); //unpost the menu
    free_menu(menu);   //free the memory associated with the menu
    for (int i = 0; i < n_choices; i++)
    {
        free_item(items[i]); //free the memory associated with each item
    }
    endwin(); //close the ncurses window

    return (index+1);
}

int getUserInt(std::string *choices, int n_choices)
{
    initCurses();
    return printMenu(choices, n_choices);
}
