// SID: 1903490
// Date: 14/04/2020

#pragma once

class Node;

#include <vector>
#include <string>

using namespace std;

class Tree
{
private:
	Node* root;

	Node* Balance(Node* target);
	Node* RotateLeft(Node* target);
	Node* RotateRight(Node* target);
	Node* FindNext(Node* target);
	Node* FindPrevious(Node* target);

	string ToString(Node* target);
	Node* Find(Node* target, string value);
	Node* Insert(Node* target, string value);
	Node* Remove(Node* target, string value, int amount);
	vector<Node*> SearchAll(Node* target, string value);

public:
	Tree();

	int Height();
	string ToString();
	Node* Find(string value);
	void Insert(string value);
	void Remove(string value, int amount);
	vector<Node*> SearchAll(string value);
};