# SDfG-Search-Application
An AVL Tree implementation for reading and searching text files.

This project was for my second trimester module of Software Develop for Games. It is a c++ console application for reading and searching text files.

## Overview
This program is a way of organising a dictionary of words; its dictionary is structured in a tree structure. Upon load, it will read any text files in its ‘Resources’ folder and load them into its tree. You can then search for a word or pattern, insert more words, remove any words, and view the entire contents.

It uses an AVL Tree implementation as a backend datastructure. It will automatically insert and then sort the tree-like structure for optimal searching operations. 

## Compatible Symbols
The program has a set whitelist of compatible letters, numbers, and symbols it will read. These are standard English symbols:

**Letters**:
ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz

**Numbers**:
1234567890

**Symbols**:
&’$

All other characters and symbols will be removed from the word.

## Preparing Files
If you have any text documents or large volumes of text to be inserted. You can place these inside a ‘Resources’ folder to be automatically inserted when the program is loaded.
The ‘Resources’ folder (case sensitive) should be in the same place as the executable file.

Make sure all text to be inserted is in a text document (files end with ‘.txt’) and place all of them inside the ‘Resources’ folder. They will all be read. By default, it is likely that your Operating System creates a text file in the UTF-8 encoding. Any encoding derived from ASCII (e.g. ANSI, UTF-8, UTF-16 etc.) should be read fine.
