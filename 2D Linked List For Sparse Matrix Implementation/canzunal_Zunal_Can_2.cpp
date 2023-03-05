#include "sparse_matrix_2d_linked_list.h"
#include <fstream>
#include <sstream>
#include <iostream>


row_node* read_matrix(const string& filename, int& num_rows, int& num_columns)
{

	ifstream myFile(filename);

	if (myFile.fail())
	{
		cout << "Error" << endl;
		return nullptr;
	}
	else
	{
		myFile >> num_rows >> num_columns;

		string line; // to traverse the file line by line

		row_node* rowHead = nullptr; //Create a new pointer for linked list
		row_node* rowTail = nullptr;
		int rowCount = 0;
		while (rowCount < num_rows)
		{
			row_node* rowTemp = new row_node();
			cell_node* tail = nullptr, * head = nullptr; //Create a head and tail node for a doubly linked list
			int columnIdx = 0;
			while (columnIdx < num_columns)
			{
				int value;
				myFile >> value;
				int newValue = value; //Note that it create a ASCII number
				int column = columnIdx;
				//If the new value is not equal to 0 add it to sparse matrix
				if (newValue != 0)
				{
					cell_node* temp = new cell_node(); //Initiliza a new node
					temp->column = column; //Get the values
					temp->value = newValue;
					if (head == nullptr) //For the first element to added
					{
						head = temp;
						rowTemp->cell = temp;
						tail = temp;
					}
					else //For rest of the elements
					{
						temp->left = tail;
						temp->right = nullptr;
						tail->right = temp;
						tail = temp;
					}
				}
				columnIdx++;
			}
			if (rowHead == nullptr)
			{
				rowHead = rowTemp;
				rowTail = rowTemp;
			}
			else
			{
				rowTail->down = rowTemp;
				rowTail = rowTail->down;
			}
			rowCount++;
		}
		myFile.close();
		return rowHead;
	}

}

void print_matrix(row_node* head, int num_rows, int num_columns)
{
	while (head != nullptr)
	{
		cell_node* cell = head->cell;
		int columnCount = 0;
		while (cell != nullptr || columnCount < num_columns)
		{
			if (cell != nullptr)
			{
				int columnSparse = cell->column;
				int columnValue = cell->value;
				if (columnSparse == columnCount)
				{
					cout << columnValue << " ";
					cell = cell->right;
				}
				else
				{
					cout << 0 << " ";
				}
			}
			else
			{
				cout << 0 << " ";
			}
			columnCount++;
		}
		cout << endl;
		head = head->down;
	}
}

void delete_matrix(row_node* head)
{
	row_node* tempRow;
	while (head != nullptr)
	{
		cell_node* cell = head->cell;

		cell_node* temp;
		while (cell != nullptr)
		{
			temp = cell->right;
			delete cell;
			cell = temp;
		}

		tempRow = head->down;
		delete head;
		head = tempRow;
	}
}

row_node* add_matrices(row_node* left, row_node* right, int num_rows, int num_columns)
{
	row_node* resultingMatrix = nullptr;
	row_node* rowTail = nullptr;
	bool nodeExists = false; // In case if all resulsts of the multiplication are 0
	while (left != nullptr && right != nullptr)
	{
		cell_node* leftCell = left->cell;
		int leftValue = 0;

		cell_node* rightCell = right->cell;
		int rightValue = 0;

		int columnCount = 0;
		row_node* rowTemp = new row_node(); //To create more row elements
		cell_node* tail = nullptr, * head = nullptr;
		while (leftCell != nullptr || columnCount < num_columns)
		{
			//For lhs
			if (leftCell != nullptr)
			{
				int columnSparse = leftCell->column;
				int columnValue = leftCell->value;
				if (columnSparse == columnCount) //To check the columns that has a value
				{
					leftValue = columnValue;
					leftCell = leftCell->right;
				}
				else
				{
					leftValue = 0;
				}
			}
			else
			{
				leftValue = 0;
			}

			if (rightCell != nullptr) 
			{
				int columnSparse = rightCell->column;
				int columnValue = rightCell->value;
				if (columnSparse == columnCount) //To check the columns that has a value
				{
					rightValue = columnValue;
					rightCell = rightCell->right;
				}
				else
				{
					rightValue = 0;
				}
			}
			else
			{
				rightValue = 0;
			}
		
			if (rightValue != 0 || leftValue != 0) //To avoid every value being 0
			{
				int currentValue = leftValue + rightValue;
				if (currentValue != 0) // To avoid added values being 0
				{
					nodeExists == 0;
					cell_node* temp = new cell_node(); //Initiliza a new node
					temp->column = columnCount; //Get the values
					temp->value = currentValue;
					if (head == nullptr) //For the first element to added
					{
						head = temp;
						rowTemp->cell = temp;
						tail = temp;
					}
					else //For rest of the elements
					{
						temp->left = tail;
						temp->right = nullptr;
						tail->right = temp;
						tail = temp;
					}
				}
				
			}
			columnCount++;
		}
		
		if (resultingMatrix == nullptr) //For the first row
		{
			resultingMatrix = rowTemp;
			rowTail = rowTemp;
		}
		else
		{
			rowTail->down = rowTemp; // For other rows
			rowTail = rowTail->down;
		}
		
		right = right->down;
		left = left->down;
	}
	
	return resultingMatrix;
	
	
}

bool is_symmetric(row_node* head, int num_rows, int num_columns)
{

	bool symmetry = true;
	//checks if symmetry possible
	if (num_rows == num_columns)
	{
		row_node* transposed = transpose(head, num_rows, num_columns); //matrix[i][j] needs to be equal to transposed[i][j] for symmetry
		while (head != nullptr && transposed != nullptr)
		{
			cell_node* cellHead = head->cell;
			cell_node* transposedHead = transposed->cell;
			while (cellHead != nullptr && transposedHead != nullptr)
			{
				int cellValue = cellHead->value;
				int headValue = transposedHead->value;
				if (cellValue != headValue)
				{
					symmetry = false;
				}

				cellHead = cellHead->right;
				transposedHead = transposedHead->right;
			}

			head = head->down;
			transposed = transposed->down;
		}
		return symmetry;
	}
	else
	{
		return false;
	}

}

row_node* transpose(row_node* head, int num_rows, int num_columns)
{

	row_node* transposedHead = nullptr; //Create a new pointer for transposed linked list
	row_node* rowTail = nullptr;

	row_node* headHolder = head;

	int columnIdx = 0; //To know which column to get


	while (headHolder != nullptr && columnIdx != num_columns) //Until the last row
	{
		cell_node* cells; //To select each cell

		row_node* rowTemp = new row_node(); // Temp node to append transposed linked list
		cell_node* cellTail = nullptr, * cellHead = nullptr; //Create a head and tail node for a doubly linked list

		int rowIdx = 0;
		while (headHolder != nullptr) //Until the last column
		{
			cells = headHolder->cell;
			int value;
			for (int i = 0; i < columnIdx + 1; i++)
			{
				if (cells != nullptr)
				{
					int row = cells->column;
					if (row == i)
					{
						value = cells->value;
						cells = cells->right;
					}
					else
					{
						value = 0;
					}
				}
				else
				{
					value = 0;
				}

			}
			if (value != 0)
			{
				cell_node* tempCell = new cell_node(); //Initiliza a new node
				tempCell->column = rowIdx; //Get the values
				tempCell->value = value;
				if (cellHead == nullptr) //For the first element
				{
					cellHead = tempCell;
					rowTemp->cell = tempCell;
					cellTail = tempCell;
				}
				else //For the rest of the elements
				{
					tempCell->left = cellTail;
					tempCell->right = nullptr;
					cellTail->right = tempCell;
					cellTail = tempCell;
				}
			}
			headHolder = headHolder->down; //To go to lowest row;

			rowIdx++;
		}
		if (transposedHead == nullptr)
		{
			transposedHead = rowTemp;
			rowTail = rowTemp;
		}
		else
		{
			rowTail->down = rowTemp;
			rowTail = rowTail->down;
		}
		columnIdx++;
		headHolder = head;
	}

	return transposedHead;
}
