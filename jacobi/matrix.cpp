#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
#include <ctime>

using namespace std;

matrix::matrix(int r, int c){
        row=r; col=c;
        A=new double *[row];
        for(int i=0; i<row; i++) {
                A[i]=new double[col];
        }
        for(int i=0; i<row; i++) {
                for(int j=0; j<col; j++) {
                        A[i][j]=0.0;
                }
        }
}

void matrix::display(){
        for(int i=0; i<row; i++) {
                for(int j=0; j<col; j++) {
                        cout<<setw(8)<<A[i][j];
                }
                cout<<endl;
        }
        cout<<endl;
}

void matrix::displayAugmented(){
        for(int i=0; i<row; i++) {
                for(int j=0; j<col; j++) {
                        if(j!=col-1)
                                cout<<setw(8)<<A[i][j];
                        if(j==col-2)
                                cout << " | ";
                        if(j==col-1)
                                cout << setw(5) << A[i][j];
                }
                cout<<endl;
        }
        cout<<endl;
}

void matrix::ident(){
        if(col==1) {A[0][0]=1.0; }
        else{
                for(int i=0; i<row; i++)
                        A[i][i]=1.0;
        }
}

void matrix::random_mat(double m){
        double sum=0.0;
        double r;
        default_random_engine gen(time(NULL));
        uniform_real_distribution<double> rdist(-1*m, m);
        for(int i=0; i<row; i++) {
                for(int j=0; j<col; j++) {
                        r=rdist(gen);
                        A[i][j]=r;
                        sum = sum+abs(r);
                }
                A[i][i]=sum;
                sum=0.0;
        }
}
