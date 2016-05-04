//Author: Brandon Manni
//Program: Takes two numbers, will find a prime sequence between them if one exists. Uses backtracking to terminate early if a solution won't work.
//Date Created: April 9, 2015
//Date Modified: April 15, 2015
#include<iostream>
#include<vector>
using namespace std;

bool vectorContains(vector <int> list, int x);
void printSequence(vector<int> list);
bool isPrime(int x);
bool createSequence(vector <int> staticSequence, vector <int> &sequence, int &position, bool &solutionExists);

bool vectorContains(vector <int> list, int x)
{
//Pre-Conditions: Must take a vector of ints and an int to search for.
//Post-Conditions: Will return true if the vector contains the element, or false if it doesn't contain the element.
	for(unsigned int i=0; i<list.size(); i++)
	{
		if(list[i]==x)
			return true;
	}
	return false;
}
void printSequence(vector<int> list)
{
//Pre-Conditions: Takes a vector of ints.
//Post-Conditions: It prints them all out on one line with spacing between each element.
	for (unsigned int i = 0; i < list.size(); i++)
		cout << list[i] << " ";
	cout << endl;
}
bool isPrime(int n)
{
//Pre-Conditions: Takes any positive integer and tests it for all it's mod values from 2 to integer-1.
//Post-Conditions: If it is a prime, it returns true. If it is not a prime, it breaks early and returns false.
	if (n <= 3)
		return n > 1;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
	for (unsigned int i = 5; i * i <= n; i += 6)
		if (n % i == 0 || n % (i + 2) == 0)
			return false;
	return true;
}
bool createSequence(vector <int> staticSequence, vector <int> &sequence, int position, bool &solutionExists)
{
//Pre-Conditions: Takes a static int vector, a changing prime sequence vector which is the same size as the static, int to store position, and boolean flag for early termination.
//Post-Conditions: Will recursively backtrack until a problem is solved. If no prime sequence is found, the prime sequence vector will end with all 0s. If one is found, the first one will be printed and backtracking will terminate.
	if (position == staticSequence.size()) //Solution has been found.
	{
		printSequence(sequence);
		solutionExists = true;
		return true;
	}
	else
	{
		if (!solutionExists) //Early termination flag. When a solution has been found, the program stops searching for the next solution. The solution is the first in lexicographical order.
		{
			for (unsigned int i = 0; i < staticSequence.size(); i++)
			{
				if (!vectorContains(sequence, staticSequence[i]))
				{
					if (position == 0) //In the first iteration, we have nothing to compare, so insert the value no matter what.
					{
						sequence[position] = staticSequence[i];
						if (!createSequence(staticSequence, sequence, position + 1, solutionExists)) //If no new legal moves exist, remove the last item entered. This is the backtracking.
							sequence[position] = 0;
					}
					else
					{
						if (isPrime(sequence[position - 1] + staticSequence[i])) //Checks if adding the value is legal (adjacent values add up to a prime).
						{
							sequence[position] = staticSequence[i];
							if (!createSequence(staticSequence, sequence, position + 1, solutionExists)) //If no new legal moves exist, backtrack.
								sequence[position] = 0;
						}
					}
				}
			}
			return false;
		}
		else
			return true;
	}
}

int main()
{
//Pre-Conditions: Takes a starting number greater than 0, and a ending number greater than or equal to the starting number.
//Post-Cinditions: If the starting and ending numbers are not both 0, it will give you a prime sequence if one exists or tell you one dosn't exist. If they are 0 0, the program will exit.
	int start, end;
	int numElements;
	bool solutionFound;
	vector <int> staticSequence; //Doesn't change. Stores all values between start and end.
	vector <int> sequence; //Changes as the program goes. Will store the first solution it gets if one exists.
	
	while(true)
	{
		solutionFound = false;
		cin >> start >> end;
		if(start == 0 && end==0)
			break;
		numElements = (end - start) + 1;
		staticSequence.resize(0);
		sequence.resize(0);
		staticSequence.resize(numElements);
		for (int i = 0; i < numElements; i++)
			staticSequence[i]= i+start;
		sequence.resize(numElements, 0); //Creating the changing vector and filling it with all 0s.
		createSequence(staticSequence, sequence, 0, solutionFound);
		if (!solutionFound) //Only prints that no solution was found after the backtracking has ended. If one was found, this is skipped.
			cout << "No prime sequence exists" << endl; 
	}
	return 0;
}