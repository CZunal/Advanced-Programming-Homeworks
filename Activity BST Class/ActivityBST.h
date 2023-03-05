#include <iostream>
#include <string>
#include <sstream>

using namespace std;
#ifndef ACTIVITY_BST_H
#define ACTIVITY_BST_H

struct tree_node {
	int time;
	string activity;
	tree_node* right;
	tree_node* left;
	tree_node* parent;
	tree_node(int t, const string& a) : time(t), activity(a),
			right(nullptr), left(nullptr),
		parent(nullptr) {}
};

class ActivityBST
{
public:
	ActivityBST(); //Default constructor
	~ActivityBST(); //Destructor
	ActivityBST (const ActivityBST& toCopy); //Copy constructor
	void add(int time, const string& activity); //Adds single tree node object representing an activity to the ActivityBST
	ActivityBST& operator = (const ActivityBST& rhs);
	
	void destructHelper(tree_node* root); //Extra function to recursively delete a node
	tree_node* copyHelper(tree_node* root); //Helper to copy constructor that returns root pointer of a copy of BST  
	void addHelper(ActivityBST &tree, tree_node* root); //Helper that adds a binary trees info to another binary tree
	ostream& inOrder(ostream& out, tree_node* root); //Helper to friend function << operator 
	bool timeValueValid(int time); //Extra function to check if given time value is valid

	//Friend functions:
	friend ostream& operator << (ostream& os, const ActivityBST& activityBST); 
	friend ActivityBST& operator + (ActivityBST& lhs, ActivityBST& rhs);
	friend ActivityBST& operator + (ActivityBST& lhs, const ActivityBST& rhs);
	friend ActivityBST& operator + (const ActivityBST& lhs,  ActivityBST& rhs);
	friend ActivityBST& operator += (ActivityBST& lhs, const ActivityBST& rhs);
private:
	tree_node* root;
};

//free functions
ostream& operator << (ostream& os, const ActivityBST& ct); // to output the value in a BST
ActivityBST& operator + (ActivityBST& lhs, ActivityBST& rhs); //for the regular-const case
ActivityBST& operator + (ActivityBST& lhs, const ActivityBST& rhs); //for the const-regular case
ActivityBST& operator + (const ActivityBST& lhs, ActivityBST& rhs); //for the const-const case
ActivityBST& operator += (ActivityBST& lhs, const ActivityBST& rhs);

string fill_with_zeros(int num_zeros, const string& input);
string number_to_time(int number);

#endif //ACTIVITY_BST_H