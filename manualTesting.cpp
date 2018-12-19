#include "intent.h"
#include <string>

using namespace std;

int main()
{
  intent::utility::multidimensional_vector<5,int>::type v;
  intent::utility::defInit<5,int, decltype(v)>(10,2,v);

  cout << v[0][1][2][3][4] << endl;}

