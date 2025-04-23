// C++ program to create comparator using function pointer 
#include <algorithm> 
#include <iostream> 
#include <vector> 
using namespace std; 

// Custom comparison function 
bool customComparison(int a, int b) 
{
	cout << "a:" << a << ", b:" << b << endl;	
	// Custom comparison logic 
	return a < b; // it sorts in ascending order 
} 

int main() 
{ 
	// Creating a vector of integers 
	vector<int> myVec = { 7, 5, 2, 1, 4, 3 }; 

	cout << "Vector: "; 
	for (int num : myVec) { 
		cout << num << " "; 
	} 
	cout << endl; 
	// Using sort with a function pointer 
	sort(myVec.begin(), myVec.end(), customComparison); 

	// Displaying the sorted vector 
	cout << "Sorted Vector: "; 
	for (int num : myVec) { 
		cout << num << " "; 
	} 
	cout << endl; 

	return 0; 
}

