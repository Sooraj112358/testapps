#include <iostream>
#define n 4

void interchange(int m[][n]) 
{ 
    std::swap(m[0], m[n-1]);
    std::swap(m[1], m[n-2]);
    //for (int i = 0; i < n/2; ++i) 
    //{
        //for(int j = 0; j < n; j++)
        //{
        //    std::swap(m[i][j], m[n-i-1][j]);
        //}
    //}
} 

int main()
{
    int m[n][n] = { { 8, 9, 7, 6 }, 
            { 4, 7, 6, 5 }, 
            { 3, 2, 1, 8 }, 
            { 9, 9, 7, 7 } }; 
    for (int i = 0; i < n; ++i) 
    {
        for(int j = 0; j < n; j++)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Interchange" << std::endl; 
    interchange(m);

    for (int i = 0; i < n; ++i) 
    {
        for(int j = 0; j < n; j++)
        {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}

