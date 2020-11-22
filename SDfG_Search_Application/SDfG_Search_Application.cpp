// SID: 1903490
// Date: 18/05/2020

// SDfG_Search_Application.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "HelperFunctions.h"
#include "FileFunctions.h"
#include "InputFunctions.h"
#include "Tree.h"

#include <iostream>
#include <string>

using namespace std;

void Search();
void Insert();
void Remove();
void Display();
int Menu();

const char RES_DIRECTORY[]{ "Resources/" };
enum MenuOptions { SearchOption, InsertOption, RemoveOption, DisplayOption, QuitOption };

Tree* tree;

int main()
{
    // Introduction
    cout << "Welcome to the Binary Search Tree application." << endl;
    cout << "This program will read multiple text documents and organise them into a binary search tree." << endl;
    cout << "You can then search, query, insert, or remove words in the tree." << endl;
    cout << endl;

    // Create a new tree
    tree = new Tree();

    // Open the resource folder
    Open(tree, RES_DIRECTORY);

    cout << endl;

    // Menu option
    int menu = QuitOption;

    while ((menu = Menu()) != QuitOption)
    {
        switch (menu)
        {
        case SearchOption:
            cout << "Searching the Tree." << endl;
            Search();
            break;

        case InsertOption:
            cout << "Insert into the Tree." << endl;
            Insert();
            break;

        case RemoveOption:
            cout << "Remove from the Tree." << endl;
            Remove();
            break;

        case DisplayOption:
            cout << "Display the Tree." << endl;
            Display();
            break;
        }

        cout << endl;
        cout << "Returning to Menu..." << endl;
        cout << endl;
    }

    cout << "Thank you for using this program!" << endl;
    cout << "Press ENTER to quit." << endl;
    cin.ignore();
}

// Displays the menu and returns menu selection
int Menu()
{
    // Defaults
    int menu = QuitOption;

    // Display Menu
    cout << "Main Menu" << endl;
    cout << "Please enter the number corresponding to the option you want:" << endl;
    cout << "1)  Search" << endl;
    cout << "2)  Insert" << endl;
    cout << "3)  Remove" << endl;
    cout << "4)  Display" << endl;
    cout << "5)  Quit" << endl;

    menu = IntInput("What do you want to do?: ", 1, QuitOption + 1);
    menu--;

    switch (menu)
    {
        // Valid    
    case QuitOption:
    case SearchOption:
    case InsertOption:
    case RemoveOption:
    case DisplayOption:
        break;

        // Invalid
    default:
        cout << endl;
        cout << "Menu option unrecognised." << endl;
        cout << "Please enter one of the options listed." << endl;
        break;
    }

    return menu;
}

// Asks for a value and then searches the tree for it
void Search()
{
    // Check if the tree exists
    if (tree->Height() < 1 || tree == NULL)
    {
        cout << "Tree cannot be searched: Tree is empty." << endl;
        return;
    }

    // Ask for search value
    string value = StringInput("Please enter a word to search for: ", "Enter a single word with no punctuation (Accepted punctuation are '*&'').", 1, 100, "*");

    // Check if value contains *
    if (value.find_first_of("*") != string::npos)
    {
        SearchAll(tree, value);
    }
    else
    {
        Search(tree, value);
    }
}

// Asks for a value and removes it from the tree
void Remove()
{
    // Check if the tree exists
    if (tree->Height() < 1 || tree == NULL)
    {
        cout << "Items cannot be removed: Tree is empty." << endl;
        return;
    }

    // Ask for a value to remove
    string value = StringInput("Please enter a word to remove: ", "Enter a single word with no punctuation, wildcards are not permitted (Accepted punctuation are '&'').", 1, 100);  

    // Find that value
    if (!Search(tree, value))
        return;

    // Ask how many to remove
    int amount = IntInput("How many would you like to remove?\n(Enter 0 for all): ", 0);
    
    if (amount > 0)
    {
        cout << "This will permanently remove " << amount << " from '" << value << "'." << endl;
    }
    else
    {
        cout << "This will permanently remove '" << value << "'." << endl;
    }

    // Confirm they want to remove
    if (Confirm())
    {
        // Remove the item
        cout << "Removing item..." << endl;
        tree->Remove(value, amount);
        cout << "Complete." << endl;
    }
    else
    {
        cout << "Canceling deletion..." << endl;
    }
}

// Asks for and inserts a line of text
void Insert()
{
    cout << "Please enter a sentence to be inserted into the tree." << endl;
    cout << "Punctuation is allowed. Make sure each word is separated" << endl;
    cout << "by a space. Press enter to confirm." << endl;

    string input; 
    getline(cin, input);

    if (Insert(tree, input))
    {
        // Insert successful
        cout << "Input inserted." << endl;
    }
    else
    {
        cout << "Empty/Invalid input detected." << endl;
        cout << "Insert cancelled." << endl;
    }
}

// Displays the tree in order
void Display()
{
    // Check if the tree exists
    if (tree->Height() < 1 || tree == NULL)
    {
        cout << "Tree is empty." << endl;
        return;
    }

    cout << tree->ToString() << endl;
}