// SID: 1903490
// Date: 16/05/2020

#pragma once

#include <string>

using namespace std;

class Node
{
	friend class Tree;
private:
	Node();

	string value{ "" };
	int height{ 0 };
	int count{ 1 };
	Node* left{ Empty };
	Node* right{ Empty };

	bool ChangeCount(int amount);

public:
	Node(string word);

	static Node* const Empty;

	int Height();
	int Count();
	string Value();
	void UpdateHeight();
	int GetBalance();
	string ToString();
	int Compare(string value);
};

