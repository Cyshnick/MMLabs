#include <iostream>
#include "cubicsplaincalculator.h"
using namespace std;

int main()
{
    CubicSplainCalculator interpolator;

    interpolator.setInput(
                {
                    {0.0, 1.000},
                    {0.5, 0.938},
                    {1.0, 0.765},
                    {1.5, 0.512},
                    {2.0, 0.224},
                    {2.5,-0.048},
                    {3.0,-0.260},
                    {3.5,-0.380},
                    {4.0,-0.402}
                });

    interpolator.calc();

    for(Real x = 0; x < 4; x += 0.05)
        cout << "(" << x << ";" << interpolator.getInterpolated()(x) << ")\n";

    return 0;
}



//int k=0;
//  cls();
//  do{
//      printf("\nInput filename: ");
//      scanf("%s", filename);
//      InFile = fopen(filename, "rt");
//  }while(InFile==NULL);
//  count_num_lines();
//  rewind(InFile);
//  allocmatrix();
//  readmatrix();
//  for(k=1; k<=N; k++){
//      h[k] = x[k] - x[k-1];
//      if(h[k]==0){
//      printf("\nError, x[%d]=x[%d]\n", k, k-1);
//      return;
//      }
//      l[k] = (y[k] - y[k-1])/h[k];
//  }
//  delta[1] = - h[2]/(2*(h[1]+h[2]));
//  lambda[1] = 1.5*(l[2] - l[1])/(h[1]+h[2]);
//  for(k=3; k<=N; k++){
//     delta[k-1] = - h[k]/(2*h[k-1] + 2*h[k] + h[k-1]*delta[k-2]);
//     lambda[k-1] = (3*l[k] - 3*l[k-1] - h[k-1]*lambda[k-2]) /
//           (2*h[k-1] + 2*h[k] + h[k-1]*delta[k-2]);
//  }
//  c[0] = 0;
//  c[N] = 0;
//  for(k=N; k>=2; k--){
//     c[k-1] = delta[k-1]*c[k] + lambda[k-1];
//  }
//  for(k=1; k<=N; k++){
//     d[k] = (c[k] - c[k-1])/(3*h[k]);
//     b[k] = l[k] + (2*c[k]*h[k] + h[k]*c[k-1])/3;
//  }
//  printresult();
//  testresult();
//  freematrix();
