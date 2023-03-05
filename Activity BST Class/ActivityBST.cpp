#include  "ActivityBST.h"

string fill_with_zeros(int num_zeros, const string& input) 
{
	int zeros_to_add = num_zeros - input.length();
	if (zeros_to_add < 0) zeros_to_add = 0;
	return string(zeros_to_add, '0') + input;
}

//Given function from the take home file
string number_to_time(int number) 
{
	if (number > 2359 || number < 0) return "ERROR";
	return fill_with_zeros(2, to_string(number / 100)) + ":" + fill_with_zeros(2,
		to_string(number % 100));
}

bool ActivityBST::timeValueValid(int time) //Extra function to check if given time value is valid
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

void ActivityBST::destructHelper(tree_node* root) //Recursive funtion to delete every node
{
	if (root != nullptr) {
		destructHelper(root->left);
		destructHelper(root->right);
		delete root;
	}
}

ActivityBST::ActivityBST() //Default constructor
{
	root = nullptr;
}

ActivityBST::~ActivityBST() //Destructor
{
	destructHelper(root);
}

tree_node* ActivityBST::copyHelper(tree_node* root) //Helper to copy constructor that returns root pointer of a copy of BST  
{
	if (root == nullptr)
	{
		return nullptr;
	}
	tree_node* copyNode = new tree_node(root->time, root->activity);
	copyNode->left = copyHelper(root->left);
	copyNode->right = copyHelper(root->right);
	return copyNode;

}

ActivityBST::ActivityBST(const ActivityBST& toCopy) //Copy constructor
{
	root = copyHelper(toCopy.root);
} 

void ActivityBST::add(int time, const string& activity) //Adds single tree node object representing an activity to the ActivityBST
{
	if(timeValueValid(time))
	{
		tree_node* newNode = new tree_node(time, activity);
		if (root == nullptr) //For the first node, root
		{
			root = newNode;
		}
		else //Remaining nodes
		{
			tree_node* rootHolder = root;
			while (rootHolder) //If root not nullptr
			{
				if (time < rootHolder->time)//If value in the node is bigger than time value
				{
					if (rootHolder->left != nullptr)
					{
						rootHolder = rootHolder->left; //Go to left
					}
					else
					{
						newNode->parent = rootHolder; //Linked the new node to its parent
						rootHolder->left = newNode;
						break;
					}
				}
				else if(time > rootHolder->time) //If value in the node is lower than time value
				{
					if (rootHolder->right != nullptr)
					{
						rootHolder = rootHolder->right; //Go to right
					}
					else
					{
						newNode->parent = rootHolder; //Linked the new node to its parent
						rootHolder->right = newNode;
						break;
					}
				}
				else // If time value is already on the list
				{
					break;
				}
			}
		}
	}
}

ActivityBST& ActivityBST::operator = (const ActivityBST& rhs)
{
	root = copyHelper(rhs.root); //Copy the BST in rhs
	return *this; 
}

void addHelper(ActivityBST &tree, tree_node* root)
{
	if (root == nullptr)
	{
		return;
	}
	tree_node* copyNode = new tree_node(root->time, root->activity);
	addHelper(tree, root->left);
	addHelper(tree, root->right);
	tree.add(root->time, root->activity);
}

ActivityBST& operator+ (ActivityBST& lhs, ActivityBST& rhs)
{
	ActivityBST copyLHS(lhs);
	rhs += copyLHS;
	return rhs;
}

ActivityBST& operator+ (const ActivityBST& lhs,  ActivityBST& rhs)
{
	ActivityBST copyLHS(lhs); 
	rhs += copyLHS;
	return rhs;
}

ActivityBST& operator+ (ActivityBST& lhs,  const ActivityBST& rhs)
{
	ActivityBST copyRHS(rhs);
	lhs += copyRHS;

	return lhs;
}

ActivityBST& operator+= (ActivityBST& lhs, const ActivityBST& rhs)
{

	addHelper(lhs, rhs.root); //Add second tree to the first tree
	return lhs;
}

ostream& ActivityBST::inOrder(ostream& out, tree_node* root)  //Helper to friend function << operator 
{
	if (root != nullptr)
	{
		inOrder(out, root->left);
		out << "[" << number_to_time(root->time) << "]" << " - " << root->activity << endl;
		inOrder(out, root->right);
	}
	return out;
}

ostream& operator << (ostream& out, const ActivityBST& rhs) 
{
	ActivityBST temp;
	return temp.inOrder(out, rhs.root);
}