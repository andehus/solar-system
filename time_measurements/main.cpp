#include <iostream>
#include <stdlib.h>
#include "time.h"
#include "test.h"
using namespace std;
int calc()
{
  return 1;
}
int main(int argc, char **argv)
{
  test *t = new test();
  double average = 0.0;
  clock_t start, stop;
  for(int j = 0; j<10; j++){
    start = clock();
    int d = t->b;
    for(long i = 0; i<1000000000; i++){
      int a = d;
    }
    stop = clock();
    average += ((float)(stop-start)/CLOCKS_PER_SEC);
    cout<<"Total Time: "<<((float)(stop-start)/CLOCKS_PER_SEC)<<" seconds"<<endl;
  }
  cout<<"Average time: "<<average/10<<endl;
}
