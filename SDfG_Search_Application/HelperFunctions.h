// SID: 1903490
// Date: 18/05/2020

#pragma once

#include "Tree.h"
#include "Node.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

string const ALLOWED = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890$&'";

// Binary searches a tree for a value
bool Search(Tree* tree, string value)
{
    // Find value in tree
    cout << "Finding '" << value << "' in tree..." << endl;
    Node* result = tree->Find(value);

    // Display the result
    if (result == Node::Empty)
    {
        cout << "Unable to find '" << value << "'." << endl;
        return false;
    }
    else
    {
        cout << "The following was found on '" << value << "':" << endl;
        cout << result->ToString() << endl;
        return true;
    }
}

// Searches the entire tree for a value
bool SearchAll(Tree* tree, string value)
{
    // Search the tree
    cout << "Searching tree for '" << value << "'..." << endl;
    vector<Node*> result = tree->SearchAll(value);

    // Display the results
    if (result.size() < 1)
    {
        cout << "Unable to find any results." << endl;
        return false;
    }
    else
    {
        cout << "Found " << result.size() << " matching results:" << endl;

        for (Node* node : result)
        {
            cout << node->ToString() << endl;
        }

        return true;
    }
}

// Formats an input into a suitable tree value
bool Format(string& input, string whitelist = "")
{
    whitelist += ALLOWED;

    for (unsigned int i = 0; i < input.size(); i++)
    {
        // Make everything lowercase
        input[i] = tolower(input[i]);
        
        if (whitelist.find(input[i]) == string::npos)
        {
                input.erase(i, 1);
                i--;
        }
    }

    // Return whether word still exists
    return input.size() > 0;
}

// Inserts an input stream into the the given tree
bool Insert(Tree* tree, istream& stream)
{
    string tempString;
    unsigned int words = 0;

    // >> operator retrieves data from the stream ignoring white spaces
    while (stream >> tempString)
    {
        if (Format(tempString))
        {
            // If the format was successful, insert the word
            words++;
            tree->Insert(tempString);
        }
    }

    // Check if any words were actually inserted
    return words > 0;
}

// Inserts a string into the tree
bool Insert(Tree* tree, string input)
{
    // Convert to stream
    stringstream stream(input);

    // Insert stream
    return Insert(tree, stream);
}