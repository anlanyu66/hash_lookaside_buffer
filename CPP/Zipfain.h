//
// Created by Anlan Yu on 12/4/19.
//

#ifndef HLB_ZIPFAIN_H
#define HLB_ZIPFAIN_H

#include <math.h>
#include <stdlib.h>

double HsubV=0;

void InitZipfHsubV(double p,int V=100) {
    // calculate the V-th harmonic number HsubV. WARNING: V>1
    HsubV = 0.0;
    for (int i=1; i<=V; i++)
        HsubV += 1.0/pow( (double)i, p); //Hsub=zipfian 1/c
}

//int ino[105]={0};
float drd;
float zipf(float x1, float x2, double p,int V=100) {
    float x,i;
    double r, sum;

    do {
        // assume InitZipfHsubV called, HsubV known
        // faster, no need to compute HsubV every time !

        drd = drand48();
        r=drd*HsubV;
        sum=1.0;
        drd = drand48();i=drd;
        while (sum<r){
            //i++;  //commented by Yufei Tao

            drd = drand48(); i+=drd+1.0;

            sum += 1.0/pow( (double)i, p);
        }

        /* i follows Zipf distribution and lies between 1 and V */
        /* x lies between 0. and 1. and then between x1 and x2 */
        x = ( (float) i - 1. ) / ( (float) V - 1. );
        x = (x2 - x1) * x + x1;

        //if( x > x1 && x < x2 ) ino[int(ceil(i))]++ ;//printf( "i:%f r:%f x:%f\n",i,r,x );
    } while (x < x1 || x > x2);
    return(x);
}
#endif //HLB_ZIPFAIN_H
