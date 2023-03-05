#include <iostream>
#include <string>
#include<fstream>
#include <vector>
#include <cctype>  //for isdigit
#include <cstdlib> //for atoi

using namespace std;

//A program that finds missing numbers to complete a matrix-vector multiplication operation

//Can Zunal 29453


void printVector(const vector<vector<int>>& vec)
{
	for (int j = 0; j < vec.size(); j++)
	{
		for (int k = 0; k < vec[0].size(); k++)
		{
			cout << vec[j][k] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

//Creates a vector with given data from a text file
void fillVector(ifstream &input, vector<vector<int>> & matrix)
{
	int value;
	int rowCount, columnCount;
	input >> rowCount >> columnCount;

	int totalExpInput = rowCount * columnCount;
	int totalInput;
	for (int i = 0; i < rowCount; i++)
	{
		vector<int> tempVec;
		for (int j = 0; j < columnCount; j++)
		{
			input >> value;
			tempVec.push_back(value);
			value = -2; // to find the mising pieces
		}
		matrix.push_back(tempVec);
	}
	input.close();
	
}

//Checks if there are any empty values by considering -2 as empty
bool isMatrixValid(const vector<vector<int>>& vec)
{
	for (int j = 0; j < vec.size(); j++)
	{
		for (int k = 0; k < vec[0].size(); k++)
		{
			if (vec[j][k] == -2)
			{
				return false;
			}
			
		}
	}
	return true;
}

//Checks if there is exactly one number in each row line 
bool oneInRow(const vector<vector<int>> vec)
{
	for (int j = 0; j < vec.size(); j++)
	{
		if (vec[j].size() != 1)
		{
			return false;
		}
	}
	return true;
}

//checks if values are in given range
bool valuesInRange(const vector<vector<int>> vec, const vector<int> range)
{
	bool includesDiff = false;
	for (int j = 0; j < vec.size(); j++)
	{
		for (int k = 0; k < vec[0].size(); k++)
		{
			bool includes = false;
			for (int x = 0; x < range.size(); x++)
			{
				if (vec[j][k] == range[x]) 
				{
					includes = true;
				}
			}
			if (includes == false)
			{
				return false;
			}
		}
	}
	return true;
}

//Checks whether every values is an positive ingeter
bool isPositiveInt(vector<vector<int>> vec)
{
	for (int j = 0; j < vec.size(); j++)
	{
		for (int k = 0; k < vec[0].size(); k++)
		{
			if (vec[j][k] < 1)
			{
				return false;
			}
		}
	}
	return true;
}

//A function that finds every possible outcome to a linear equation with an expected value
void recFindValues(vector<int> coeff, int expectedValue, int n, vector <int>& vec, vector<vector<int>> &allPosibilities)
{
	if (n == 1 and (expectedValue % coeff[n - 1] != 0))
	{
		return;
	}
	else if (n == 1 and (expectedValue % coeff[n - 1] == 0))
	{
		vector<int> temp;
		int firstVar = expectedValue / coeff[n - 1];
		
		temp.push_back(firstVar);

		
		for (int i = 0; i < vec.size(); i++)
		{
			temp.push_back(vec[i]);
		
		}
		allPosibilities.push_back(temp);
		
		return;
	}
	for (int i = 0; expectedValue - i * coeff[n - 1] >= 0; i++)
	{
		vec.push_back(i);
		recFindValues(coeff, expectedValue - i * coeff[n - 1], n - 1, vec, allPosibilities);
		vec.pop_back();
	}
}


//Compares every vector and selects the lowest one in concenated form
vector<int> vectorComparision(vector<int> variablePos, vector<vector<int>> allPosibilities, vector<int> varValues, int expectedValue)
{ 
	
	vector<vector<int>> vectorInRange;
	for (int i = 0; i < allPosibilities.size(); i++)
	{
		bool allInRange = true;
		int tempValue = expectedValue;
		for (int x = 0; x < allPosibilities[i].size(); x++)
		{
			if (allPosibilities[i][x] < 1 || allPosibilities[i][x] > 9)
			{
				allInRange = false;
			}

			tempValue -= allPosibilities[i][x] * varValues[x];
		}
		if (allInRange && tempValue == 0)
		{
			vectorInRange.push_back(allPosibilities[i]);
		}
	}

	string lowest = "1000000000"; 	//initiliaze to a sufficiently big value
	int lowestIndex = 0;
	for (int i = 0; i < vectorInRange.size(); i++)
	{
		string tempStr = "";
		for (int x = 0; x < vectorInRange[i].size(); x++)
		{
			tempStr += to_string(vectorInRange[i][x]);
		}
		if (atoi(lowest.c_str()) > atoi(tempStr.c_str()))
		{
			lowestIndex = i;
			lowest = tempStr;
		}
	}

	vector<int> lowestVector = vectorInRange[lowestIndex];
	

	return lowestVector;
}


//A function that figures out given variables
void tryVariables(vector<vector<int>> allVariables, vector<vector<int>> vectorRHS, ofstream &outfile)
{
	for (int i = 0; i < allVariables.size(); i++)
	{
		//As we put expected value for the linear equation in the last index
		int expectedValue = allVariables[i][allVariables[i].size() - 1] ;
		if(expectedValue == 0)
		{

		}
		else if (allVariables[i].size() - 1 == 1)
		{
			int columnMiss = allVariables[i][0];
			int missingVal = expectedValue / vectorRHS[columnMiss][0];
			outfile << i << " " << columnMiss << " " << missingVal << endl;
		}
		else
		{
			vector<int> varValues;
			for (int x = 0; x < allVariables[i].size() - 1; x++)
			{
				
				int value = vectorRHS[allVariables[i][x]][0];
				varValues.push_back(value);
			}

			int rowSize = varValues.size();
			vector<int> v;
			vector<vector<int>> allPosibilities;
			//cout << recursiveVariable(allVariables[i], varValues, 0, rowSize - 1, expectedValue) << endl;
			recFindValues(varValues, expectedValue, rowSize, v, allPosibilities);

			vector<int> finalValues = vectorComparision(allVariables[i], allPosibilities, varValues, expectedValue);
			
			for (int j = 0; j < finalValues.size(); j++)
			{
				int columnMiss = allVariables[i][j];
				outfile << i << " " << columnMiss << " " << finalValues[j] << endl;
			}
				
		}
	}
}


//Find variable equations in a matrix multiplication
void findVarMatrix(vector<vector<int>> matrixLHS, vector<vector<int>> vectorRHS, vector<vector<int>> vectorRES, ofstream &outfile)
{
	int firstRow = matrixLHS.size(); 
	int firstColumn = matrixLHS[0].size(); 

	int secondRow = vectorRHS.size(); 
	int secondColumn = vectorRHS[0].size();


	vector<vector<int>> productMatrix;

	//creates the product matrix
	for (int i = 0; i < firstRow; i++)
	{
		vector<int> tempVec;
		for (int j = 0; j < secondColumn; j++)
		{
			tempVec.push_back(0);
		}
		productMatrix.push_back(tempVec);
	}

	vector<vector<int>> allVariables;

	//Iterates over the 3 matrices
	for (int i = 0; i < firstRow; i++)
	{
		for (int j = 0; j < secondColumn; j++)
		{
			vector<int> tempVariables;
			for (int k = 0; k < firstColumn; k++)
			{
				if (matrixLHS[i][k] == -1)
				{
					//To add the variables
					tempVariables.push_back(k);
				}
				else
				{
					productMatrix[i][j] += matrixLHS[i][k] * vectorRHS[k][j];
				}
				// So that in last iteration we will know the needed value
				if (k == firstColumn - 1)
				{
					int neededValue = vectorRES[i][j] - productMatrix[i][j];
					tempVariables.push_back(neededValue);
				}
				
			}
			allVariables.push_back(tempVariables);
		}
	}

	tryVariables(allVariables, vectorRHS, outfile);
	
}


int main()
{
	string fileLHS, fileRHS, fileRES, outfileName;

	//Defining the matrices and vectors
	vector<vector<int>> matrixLHS, vectorRHS, vectorRES;

	bool errorExists = false;

	cout << "Enter LHS matrix filename:";
	cin >> fileLHS;
	ifstream inputLHS(fileLHS); 
	//Opens, checks and transforms RHS file to RHS vector
	if (inputLHS.fail())
	{
		errorExists = true;
	}
	else
	{
		fillVector(inputLHS, matrixLHS);
		if (isMatrixValid(matrixLHS) == false)
		{
			errorExists = true;
		}

		vector<int> rangeLHS{-1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		if (valuesInRange(matrixLHS, rangeLHS))
		{

		}
		else
		{
			errorExists = true;
		}
		inputLHS.close();
	}

	//Opens, checks and transforms RHS file to RHS vector
	cout << "Enter RHS matrix filename:";
	cin >> fileRHS;
	ifstream inputRHS(fileRHS);
	if (inputRHS.fail())
	{
		errorExists = true;
	}
	else
	{

		fillVector(inputRHS, vectorRHS);
		if (isMatrixValid(vectorRHS) == false)
		{
			errorExists = true;
		}

		
		if (oneInRow(vectorRHS))
		{

		}
		else
		{
			errorExists = true;
		}

		vector<int> rangeRHS{1, 2, 3, 4, 5, 6, 7, 8, 9};
		if (valuesInRange(vectorRHS, rangeRHS))
		{

		}
		else
		{
			errorExists = true;
		}


		inputRHS.close();
	}
	
	//Opens, checks and transforms RES file to RES vector
	cout << "Enter RES filename:";
	cin >> fileRES;
	ifstream inputRES(fileRES);
	if (inputRES.fail())
	{
		errorExists = true;
	}
	else
	{
		fillVector(inputRES, vectorRES);
		if (isMatrixValid(vectorRES) == false)
		{
			errorExists = true;
		}
		else
		{
			
		}

		if (oneInRow(vectorRES))
		{

		}
		else
		{
			errorExists = true;
		}

		if (isPositiveInt(vectorRES))
		{

		}
		else
		{
			errorExists = true;
			
		}
		inputRHS.close();
	}

	//Opens the output file
	cout << "Enter output filename:";
	cin >> outfileName;
	ofstream outfile;
	outfile.open(outfileName);
	bool outOpen = false;
	if (outfile.fail())
	{
		errorExists = true;
		outOpen = false;
		
	}
	else
	{
		outOpen = true;
	}

	if (outOpen == true)
	{

		if (errorExists == true)
		{
			outfile << "Error" << endl;
			return 0;
		}
		else
		{
			findVarMatrix(matrixLHS, vectorRHS, vectorRES, outfile);

		}
	}
	else
	{
		cout << "Error" << endl;
	}

	
	outfile.close();

}