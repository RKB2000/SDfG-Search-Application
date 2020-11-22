// SID: 1903490
// Date: 18/05/2020

#include "Node.h"

#pragma region constructors

// Default constructor to create an empty node
Node::Node() 
{
	left = this;
	right = this;
}

// Constructor to create a node with a given value
Node::Node(string newValue)
{
	value = newValue;
	height = 1;
}

#pragma endregion

#pragma region variables

Node* const Node::Empty = new Node();

#pragma endregion

#pragma region public methods

// Gets the node's height
int Node::Height()
{
	return height;
}

// Gets the node's count
int Node::Count()
{
	return count;
}

// Gets the node's value
string Node::Value()
{
	return value;
}

// Changes the node count by a given amount
// Returns false if count reaches 0
bool Node::ChangeCount(int amount)
{
	if (count + amount <= 0)
	{
		// count reaches 0
		return false;
	}

	// Change amount
	count += amount;

	return true;
}

// Updates the node's height value
void Node::UpdateHeight()
{
	// Retrieve the heights of the child nodes
	int lHeight = left->Height();
	int rHeight = right->Height();

	// Set height to the greater height + 1
	height = (rHeight - lHeight >= 0 ? rHeight : lHeight) + 1;
}

// Gets the node's balance factor
// Positive numbers mean the tree is right leaning
// Negative numbers mean the tree is left leaning
int Node::GetBalance()
{
	// Retrieve the heights of the child nodes
	int lHeight = left->Height();
	int rHeight = right->Height();

	// Return the right height - left height
	return rHeight - lHeight;
}

string Node::ToString()
{
	return value + " : " + to_string(count);
}

int Node::Compare(string value)
{
	if (value.find_first_of("*") == string::npos)
	{
		// Does not contain a wildcard
		// Perform default string comparison
		return value.compare(Value());
	}

	// Contains a wildcard

	// Get the length of the words
	__int64 size_x = value.length() + 1;
	__int64 size_y = Value().length() + 1;

	// Create array with two values as true
	bool* comparisons = new bool[size_x * size_y]{ true, true };

	for (unsigned int y = 1; y < size_y; y++)
	{
		for (unsigned int x = 1; x < size_x; x++)
		{
			if (value[x - 1] == Value()[y - 1])
				// If match
				// Look for the element up and left
				comparisons[y * size_x + x] = comparisons[(y - 1) * size_x + (x - 1)];
			else if (value[x - 1] == '*')
				// If wildcard match
				// Look for the element directly up or directly left
				comparisons[y * size_x + x] = comparisons[(y - 1) * size_x + x] || comparisons[y * size_x + (x - 1)];
		}
	}

	// Retrieve if the last character matched
	bool result = !comparisons[size_x * size_y - 1];

	// Delete memory and return
	delete[] comparisons;
	return result;
}

#pragma endregion