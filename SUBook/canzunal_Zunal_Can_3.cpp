#include <iostream>
#include <string>
#include <sstream>
#include "activity_bst.h"

using namespace std;
//Can Zunal 29453

//Extra functions: ---------------------------------------------------------------- 

//Given function from the take home file
string fill_with_zeros(int num_zeros, const string& input) {
	int zeros_to_add = num_zeros - input.length();
	if (zeros_to_add < 0) zeros_to_add = 0;
	return string(zeros_to_add, '0') + input;
}

//Given function from the take home file
string number_to_time(int number) {
	if (number > 2359 || number < 0) return "ERROR";
	return fill_with_zeros(2, to_string(number / 100)) + ":" + fill_with_zeros(2,
		to_string(number % 100));
}

//Checks if time value is in given boundaries
bool timeValueValid(int time)
{
	int hour = time / 100; //hour
	int minute = time % 100; //minute
	
	if (hour >= 0 and hour <= 23)
	{
		if (minute >= 0 and minute <= 59)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//Checks if a node is the max node
bool isLastNode(tree_node* root, tree_node* currentNode)
{
	tree_node* rootHolder = root;
	while (rootHolder->parent) //Finds the root
	{
		rootHolder = rootHolder->parent;
	}
	while (rootHolder->right) //Goes to last 
	{
		rootHolder = rootHolder->right;
	}
	if (currentNode == rootHolder)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Finds the min node
int minNode(tree_node* root)
{
	tree_node* rootHolder = root;
	
	
	while (rootHolder->parent) //Finds the root
	{
		rootHolder = rootHolder->parent;
	}
	while (rootHolder->left) //Goes to left most node
	{
		rootHolder = rootHolder->left;
	}
	return rootHolder->time;
	
}

int maxNode(tree_node* root)
{
	tree_node* rootHolder = root;
	while (rootHolder->parent) //Finds the root
	{
		rootHolder = rootHolder->parent;
	}
	while (rootHolder->right) //Goes to right most node
	{
		rootHolder = rootHolder->right;
	}

	return rootHolder->time;
}

//A faction that cout the the value if it is in a given range
bool isInRange(int lowerBound, int upperBound, int time, string activity)
{
	if (lowerBound <= time && upperBound > time)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int rootValue(tree_node* root)
{
	tree_node* rootHolder = root;
	while (rootHolder->parent) //Finds the root
	{
		rootHolder = rootHolder->parent;
	}

	return rootHolder->time;
}

//Right most node of left subtree
bool lastNodeOfLeft(tree_node* root, tree_node* currentNode) //Checks if the value is the biggest number in left subtree
{
	tree_node* rootHolder = root;
	while (rootHolder->parent) //Finds the root
	{
		rootHolder = rootHolder->parent;
	}
	rootHolder = rootHolder->left;
	while (rootHolder->right) //Goes to right most node
	{
		rootHolder = rootHolder->right;
	}

	if (currentNode == rootHolder)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Functions given in the homework and additional recursive function-------------------------------

void add_activity(tree_node*& root, int time, const string& activity)
{
	string clockWise = number_to_time(time); //Clock wise notation
	if (timeValueValid(time))
	{
		tree_node* newNode = new tree_node(time, activity); //New node to be inserted
		if (root == nullptr) //For the first node, root
		{
			root = newNode;
			cout << "Added activity '" << activity << "' at " << clockWise << endl;
		}
		else //Remaining nodes
		{
			tree_node* rootHolder = root;
			while (rootHolder) //If root not nullptr
			{
				if (time < rootHolder->time) //If value in the node is bigger than time value
				{
					if (rootHolder->left != nullptr)
					{
						rootHolder = rootHolder->left; //Go to left
					}
					else
					{
						newNode->parent = rootHolder; //Linked the new node to its parent
						rootHolder->left = newNode;
						cout << "Added activity '" << activity << "' at " << clockWise << endl;
						break;
					}
				}
				else if (time > rootHolder->time) //If value in the node is lower than time value
				{
					if (rootHolder->right != nullptr)
					{
						rootHolder = rootHolder->right; //Go to right
					}
					else
					{
						newNode->parent = rootHolder; //Linked the new node to its parent
						rootHolder->right = newNode;
						cout << "Added activity '" << activity << "' at " << clockWise << endl;
						break;
					}
				}
				else // If time value is already on the list
				{
					cout << "Duplicate value..." << endl;
					break;
				}
			}
		}

	}
	else
	{
		cout << "ERROR!Could not add activity '" << activity << "' due to illegal time value" << endl;
	}

}

void print_activity_recursive(tree_node* root, int time)
{
	tree_node* rootHolder = root;
	if (rootHolder == nullptr) //base case
	{
		return;
	}
	int minTime = minNode(rootHolder); //Minimum time value
	if (time < minTime) //Time value is lower than minimum value in BST
	{
		cout << "Time: " << number_to_time(time) << ", Activity: free" << endl;
		rootHolder = nullptr;
		return;
	}
		
	print_activity_recursive(rootHolder->left, time);
	if (rootHolder->parent) //If the current node have a parent
	{
		if (rootHolder->left) //If the current node have a left child
		{
			if (rootHolder->right) // If the current node have a right child
			{
				if (isInRange(rootHolder->time, rootHolder->right->time, time, rootHolder->activity))
				{
					cout << "Time: " << number_to_time(time) << ", Activity: " << rootHolder->activity << endl;
				}
					
			}
			else
			{
				if (isInRange(rootHolder->time, rootHolder->parent->time, time, rootHolder->activity))
				{
					cout << "Time: " << number_to_time(time) << ", Activity: " << rootHolder->activity << endl;
				}
			}
		}
		else //If no left child
		{
			if (isLastNode(root, rootHolder)) //If the last node of the tree
			{
				if (isInRange(rootHolder->time, 2400, time, rootHolder->activity))
				{
					cout << "Time: " << number_to_time(time) << ", Activity: " << rootHolder->activity << endl;
				}
			}
			else
			{
				if (rootHolder->right) // If the current node have a right child
				{
					if (isInRange(rootHolder->time, rootHolder->right->time, time, rootHolder->activity))
					{
						cout << "Time: " << number_to_time(time) << ", Activity: " << rootHolder->activity << endl;
					}
				}
				else
				{
					if (lastNodeOfLeft(root, rootHolder))
					{
						if (isInRange(rootHolder->time, rootValue(rootHolder), time, rootHolder->activity))
						{
							cout << "Time: " << number_to_time(time) << ", Activity: " << rootHolder->activity << endl;
						}
					}
					else
					{
						if (isInRange(rootHolder->time, rootHolder->parent->time, time, rootHolder->activity))
						{
							cout << "Time: " << number_to_time(time) << ", Activity: " << rootHolder->activity << endl;
						}
					}

				}
			}
		}
	}
	else //If the current node is the root
	{
		if (rootHolder->right) //If root has a right node
		{
			if (isInRange(rootHolder->time, rootHolder->right->time, time, rootHolder->activity))
			{
				cout << "Time: " << number_to_time(time) << ", Activity: " << rootHolder->activity << endl;
			}
				
		}
		else // If root doesn't have a right node
		{
			if (isInRange(rootHolder->time, 2400, time, rootHolder->activity))
			{
				cout << "Time: " << number_to_time(time) << ", Activity: " << rootHolder->activity << endl;
			}
		}

	}
	print_activity_recursive(rootHolder->right, time);
		
}

void print_activity(tree_node* root, int time)
{
	if (timeValueValid(time)) 
	{
		tree_node* rootHolder = root;
		if (rootHolder == nullptr) //If the tree empty
		{
			cout << "Time: " << number_to_time(time) << ", Activity: free" << endl;
			return;
		}
		else
		{
			print_activity_recursive(rootHolder, time);
		}
	}
	else
	{
		cout << "ERROR! Could not print activity at specific time due to illegal time" << endl;
	}
}

void print_activity_and_duration_recursive(tree_node* root, int time)
{
	tree_node* rootHolder = root;
	if (rootHolder == nullptr) //base case
	{
		return;
	}

	int minTime = minNode(rootHolder); //Minimum time value
	if (time < minTime) //Time value is lower than minimum value in BST
	{
		cout << "Time period: [00:00 - " << number_to_time(minTime) << "]: " << "free" << endl;
		rootHolder = nullptr;
		return;
	}

	print_activity_and_duration_recursive(rootHolder->left, time);
	if (rootHolder->parent) //If the current node have a parent
	{
		if (rootHolder->left) //If the current node have a left child
		{
			if (rootHolder->right) // If the current node have a right child
			{
				if (isInRange(rootHolder->time, rootHolder->right->time, time, rootHolder->activity))
				{
					cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->right->time) << "]: " << rootHolder->activity << endl;
				}

			}
			else
			{
				if (isInRange(rootHolder->time, rootHolder->parent->time, time, rootHolder->activity))
				{
					cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->parent->time) << "]: " << rootHolder->activity << endl;
				}
			}
		}
		else //If no left child
		{
			if (isLastNode(root, rootHolder)) //If the last node of the tree
			{
				if (isInRange(rootHolder->time, 2400, time, rootHolder->activity))
				{
					cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(0000) << "]: " << rootHolder->activity << endl;

				}
			}
			else
			{
				if (rootHolder->right) // If the current node have a right child
				{
					if (isInRange(rootHolder->time, rootHolder->right->time, time, rootHolder->activity))
					{
						cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->right->time) << "]: " << rootHolder->activity << endl;

					}
				}
				else
				{
					if (lastNodeOfLeft(root, rootHolder))
					{
						if (isInRange(rootHolder->time, rootValue(rootHolder), time, rootHolder->activity))
						{
							cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootValue(rootHolder)) << "]: " << rootHolder->activity << endl;

						}
					}
					else
					{
						if (isInRange(rootHolder->time, rootHolder->parent->time, time, rootHolder->activity))
						{
							cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->parent->time) << "]: " << rootHolder->activity << endl;
						}
					}

				}
			}
		}
	}
	else //If the current node is the root
	{
		if (rootHolder->right) //If root has a right node
		{
			if (isInRange(rootHolder->time, rootHolder->right->time, time, rootHolder->activity))
			{
				cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->right->time) << "]: " << rootHolder->activity << endl;
			}
		}
		else // If root doesn't have a right node
		{
			if (isInRange(rootHolder->time, 2400, time, rootHolder->activity))
			{
				cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(0000) << "]: " << rootHolder->activity << endl;
			}
		}
	}
	print_activity_and_duration_recursive(rootHolder->right, time);
}

void print_activity_and_duration(tree_node* root, int time)
{
	if (timeValueValid(time))
	{
		tree_node* rootHolder = root;
		if (rootHolder == nullptr) //If the tree is empty
		{
			cout << "Time period: [00:00 - 00:00]: free" << endl;
			return;
		}
		else
		{
			print_activity_and_duration_recursive(rootHolder, time); //Enter recursive function
		}
	}
	else
	{
		cout << "ERROR! Could not print activity at specific time due to illegal time" << endl;
	}
}

void print_single_recursive(tree_node* root, const string& activity)
{

	tree_node* rootHolder = root;

	if (activity == "free") //Improvment so that if activity is free recursion will be ignored
	{
		int firstStarts = minNode(rootHolder); //Starting point of the minimum value in the list
		if (firstStarts == 0) //In case there is no free time
		{
			rootHolder = nullptr;
			return;
		}
		else
		{
			cout << "Time period: [00:00 - " << number_to_time(firstStarts) << "]: free" << endl;
		}
	}

	if (rootHolder == nullptr) //base case
	{
		return;
	}

	print_single_recursive(rootHolder->left, activity);
	if (rootHolder->parent) //If the current node have a parent
	{
		if (rootHolder->left) //If the current node have a left child
		{
			if (rootHolder->right) // If the current node have a right child
			{
				if (activity == rootHolder->activity)
				{
					cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->right->time) << "]: " << rootHolder->activity << endl;
				}
			}
			else
			{
				if (activity == rootHolder->activity)
				{
					cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->parent->time) << "]: " << rootHolder->activity << endl;
				}
			}
		}
		else //If no left child
		{
			if (isLastNode(root, rootHolder)) //If the last node of the tree
			{
				if (activity == rootHolder->activity)
				{
					cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << "00:00" << "]: " << rootHolder->activity << endl;
				}
			}
			else
			{
				if (rootHolder->right) // If the current node have a right child
				{

					if (activity == rootHolder->activity)
					{
						cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->right->time) << "]: " << rootHolder->activity << endl;
					}
				}
				else
				{
					if (lastNodeOfLeft(root, rootHolder))
					{
						if (activity == rootHolder->activity)
						{
							cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootValue(rootHolder)) << "]: " << rootHolder->activity << endl;
						}
					}
					else
					{
						if (activity == rootHolder->activity)
						{
							cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->parent->time) << "]: " << rootHolder->activity << endl;
						}
					}

				}
			}
		}
	}
	else //If the current node is the root
	{
		if (rootHolder->right) //If root has a right node
		{
			if (activity == rootHolder->activity)
			{

				cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << number_to_time(rootHolder->right->time) << "]: " << rootHolder->activity << endl;
			}
		}
		else // If root doesn't have a right node
		{
			if (activity == rootHolder->activity)
			{
				cout << "Time period: [" << number_to_time(rootHolder->time) << " - " << "00:00" << "]: " << rootHolder->activity << endl;
			}
		}
	}
	print_single_recursive(rootHolder->right, activity);
}

void print_single_activity(tree_node* root, const string& activity)
{
	
	tree_node* rootHolder = root;

	if (rootHolder == nullptr) //If the tree is empty
	{
		cout << "Time period: [00:00 - 00:00]: free" << endl;
		return;
	}
	else
	{
		print_single_recursive(rootHolder, activity);
	}
}

void print_all_activities(tree_node* root) //Recursive function to iterate over the list
{
	tree_node* rootHolder = root;
	if (rootHolder != nullptr)
	{
		print_all_activities(rootHolder->left); //Cases go to bottom left
		string clockWise = number_to_time(rootHolder->time); //Clock wise notation
		cout << "[" << clockWise << "]" << " - " << rootHolder->activity << endl;
		print_all_activities(rootHolder->right);
	}
}

void delete_tree(tree_node* root)	
{
	if (root != NULL)
	{
		delete_tree(root->left);
		delete_tree(root->right);
		delete root;
	}
	
	root = NULL;
}