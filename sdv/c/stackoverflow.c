// C program to demonstrate stack overflow 
// by allocating a large local memory 
#include<stdio.h> 

int main() { 

// Creating a matrix of size 10^5 x 10^5 
// which may result in stack overflow. 
int mat[1024*1024][2]; 
} 
