#include<iostream>
#include<vector>
using namespace std;
// return type vector
vector<int> fun(vector<int> v)
{
  vector<int>s;
  for(int i=0;i<v.size();i++)
    s.push_back(v[i]*2);
  return s; // return vector
}
int main()
{
  vector<int> inV,kV;
  //inV[0] = 1;
  inV.push_back(1);
  inV.push_back(2);
  inV.push_back(3);
  kV=fun(inV); // function call
  for(int i=0;i<kV.size();i++)
  cout<<kV[i]<<" ";
  cout<<endl;
  return 0;
}