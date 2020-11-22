// SID: 1903490
// Date: 14/04/2020

#include "Tree.h"
#include "Node.h"

Tree::Tree()
{
	root = Node::Empty;
}

#pragma region private methods

// Balances a node if needed
Node* Tree::Balance(Node* target)
{
	// Get the balance factor of all the nodes
	int balance = target->GetBalance();
	int leftBalance = target->left->GetBalance();
	int rightBalance = target->right->GetBalance();

	if (balance < -1)
	{
		if (leftBalance < 0)
		{
			// Left-Left
			// Rotate right to fix
			return RotateRight(target);
		}
		else
		{
			// Left-Right
			// Rotate the left child left, then this node right
			target->left = RotateLeft(target->left);
			return RotateRight(target);
		}		
	}	

	if (balance > 1)
	{
		if (rightBalance > 0)
		{
			// Right-Right
			// Rotate left to fix
			return RotateLeft(target);
		}
		else
		{
			// Right-Left
			// Rotate the right child right, then this node left
			target->right = RotateRight(target->right);
			return RotateLeft(target);
		}
	}	

	// Node is balanced
	return target;
}

// Rotates left around a node
Node* Tree::RotateLeft(Node* target)
{
	// Retrieve the pointers
	Node* oldRoot = target;
	Node* newRoot = target->right;

	// Switch positions
	oldRoot->right = newRoot->left;
	newRoot->left = oldRoot;

	// Update height
	oldRoot->UpdateHeight();
	newRoot->UpdateHeight();

	// Return the new root
	return newRoot;
}

// Rotates right around a node
Node* Tree::RotateRight(Node* target)
{
	// Retrieve the pointers
	Node* oldRoot = target;
	Node* newRoot = target->left;

	// Switch positions
	oldRoot->left = newRoot->right;
	newRoot->right = oldRoot;

	// Update height
	oldRoot->UpdateHeight();
	newRoot->UpdateHeight();

	// Return the new root
	return newRoot;
}

// Finds the closest largest value
Node* Tree::FindNext(Node* target)
{
	// Start at the right node
	Node* focus = target->right;

	while (focus != Node::Empty && focus->left != Node::Empty)
	{
		// Repeat until the next node is empty
		// Search down the far left branch
		focus = focus->left;
	}

	return focus;
}

// Finds the closest smallest value
Node* Tree::FindPrevious(Node* target)
{
	// Start at the left node
	Node* focus = target->left;

	while (focus != Node::Empty && focus->right != Node::Empty)
	{
		// Repeat until the next node is empty
		// Search down the far right branch
		focus = focus->right;
	}

	return focus;
}

// Display the tree in order
string Tree::ToString(Node* target)
{
	string result;

	if (target == Node::Empty)
		// Tree is empty
		return result;

	string left = ToString(target->left);
	string right = ToString(target->right);

	// Display left branch
	if (!left.empty())
		result.append(left + "\n");

	// Display this node
	result.append(target->ToString());

	// Display right branch
	if (!right.empty())
		result.append("\n" + right);

	return result;
}

// Finds a node with a given value
Node* Tree::Find(Node* target, string value)
{
	int compare = target->Compare(value);

	if (target == Node::Empty || compare == 0)
	{
		// We have found the node/end of line
		return target;
	}
	else if (compare < 0)
	{
		// Less/Left
		return Find(target->left, value);
	}
	else
	{
		// More/Right
		return Find(target->right, value);
	}
}

// Inserts a new node with a given value
Node* Tree::Insert(Node* target, string value)
{
	if (target == Node::Empty)
	{
		// Found the node's position
		// Create a new one here
		return new Node(value);
	}

	int compare = target->Compare(value);

	if (compare == 0)
	{
		// We have found the node
		target->ChangeCount(1);
		return target;
	}
	else if (compare < 0)
	{
		// Less/Left
		target->left = Insert(target->left, value);
	}
	else
	{
		// More/Right
		target->right = Insert(target->right, value);
	}

	// Change the height of this node
	target->UpdateHeight();

	// Balance this node if unbalanced
	return Balance(target);
}

// Removes a node from the tree
Node* Tree::Remove(Node* target, string value, int amount)
{
	if (target == Node::Empty)
		return target;

	int compare = target->Compare(value);

	if (compare == 0)
	{
		// We have found the node
		if (amount == 0 || !target->ChangeCount(-amount))
		{
			// Delete whole node

			// Get the closest two nodes
			Node* next = FindNext(target);
			Node* prev = FindPrevious(target);

			if (next != Node::Empty)
			{
				// Next is not empty
				// Change next pointers to target pointers
				target->value = next->value;

				// Remove the old node
				target->right = Remove(target->right, target->value, 0);
			}
			else if (prev != Node::Empty)
			{
				// Previous is not empty
				// Change next pointers to target pointers
				target->value = prev->value;

				// Remove the old node
				target->left = Remove(target->left, target->value, 0);
			}
			else
			{
				// End of a branch
				delete target;
				return Node::Empty;
			}
		}
		else
		{
			return target;
		}
	}
	else if (compare < 0)
	{
		// Less/Left
		target->left = Remove(target->left, value, amount);
	}
	else
	{
		// More/Right
		target->right = Remove(target->right, value, amount);
	}

	target->UpdateHeight();
	
	return Balance(target);
}

std::vector<Node*> Tree::SearchAll(Node* target, string value)
{
	std::vector<Node*> result;

	if (target == Node::Empty)
		// Return empty vector
		return result;

	// Get vectors of left and right subtrees
	std::vector<Node*> left = SearchAll(target->left, value);
	std::vector<Node*> right = SearchAll(target->right, value);

	// Test if this node matches the value
	bool isMatch = target->Compare(value) == 0;

	// Allocate the return vector
	result.reserve(left.size() + right.size() + isMatch);

	// Fill up the return vector
	result.insert(result.end(), left.begin(), left.end());
	if (isMatch) result.insert(result.end(), target);
	result.insert(result.end(), right.begin(), right.end());

	return result;
}

#pragma endregion

#pragma region public methods

// Gets the tree's height from the root node
int Tree::Height()
{
	return root->Height();
}

// Displays the entire tree
string Tree::ToString()
{
	return ToString(root);
}

// Finds a node in the tree
Node* Tree::Find(string value)
{
	return Find(root, value);
}

// Inserts a value into the tree
void Tree::Insert(string value) 
{
	root = Insert(root, value);
}

// Removes an amount from a value
void Tree::Remove(string value, int amount)
{
	root = Remove(root, value, amount);
}

// Searches whole tree for a value
std::vector<Node*> Tree::SearchAll(string value) 
{
	return SearchAll(root, value);
}

#pragma endregion