#include <iostream>

using namespace std;

int main()
{
  int szh = 0;
  int bit = 1;

  do
    ++szh;
  while (bit<<=1);

  cout<<"A szohossz :"<< szh <<" bites"<<endl;

  return 0;
}
