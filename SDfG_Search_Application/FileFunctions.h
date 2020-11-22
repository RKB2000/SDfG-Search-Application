// SID: 1903490
// Date: 18/05/2020

#pragma once

class Tree;

#include "HelperFunctions.h"

#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

const char FILE_EXTENSION[]{ ".txt" };

void ReadFile(Tree* tree, fs::path path)
{
    // Open the file path
    // This is closed once it goes out of scope
    ifstream file(path);

    // Checks that the file is a text document and it can be opened
    if (!file || path.extension() != FILE_EXTENSION)
        throw runtime_error(path.string() + " is incompatible. Please use text documents.");

    // Checks that the file has data in
    if (!Insert(tree, file))
        throw runtime_error(path.string() + " is an empty file.");
}

void Open(Tree* tree, fs::path path)
{
    int total = 0;
    int success = 0;

    cout << "Attempting to read resources..." << endl;

    if (!fs::exists(path))
    {
        // Path does not exist
        cout << path << " directory does not exist." << endl;
    }
    else if (!fs::is_directory(path))
    {
        total++;
        cout << "(" << total << ") Found " << path << endl;

        // Not a folder
        // Handles any errors when opening the file
        try
        {
            ReadFile(tree, path);
            success++;
        }
        catch (exception const& e)
        {
            cout << "   A problem occurred reading the file:" << endl;
            cout << "   " << e.what() << endl;
        }
    }
    else
    {
        // Loops through every file in the resources directory
        // Recursive loops through subdirectories as well
        for (auto& p : fs::recursive_directory_iterator(path))
        {
            if (p.is_directory())
                // Ignore folders
                continue;

            total++;
            cout << "(" << total << ") Found " << p.path() << endl;

            // Handles any errors when opening the file
            try
            {
                ReadFile(tree, p.path());
                cout << "   Success" << endl;
                success++;
            }
            catch (exception const& e)
            {
                cout << "   A problem occurred reading the file:" << endl;
                cout << "   " << e.what() << endl;
            }
        }
    }

    cout << endl;
    cout << "Successfully loaded " << success << " / " << total << " files." << endl;

    if (success == 0)
    {
        cout << "Unable to read any files." << endl;
        cout << "Please add documents to the 'Resources' folder and restart," << endl;
        cout << "or add text manually through the 'Insert' option in the menu." << endl;
    }
}