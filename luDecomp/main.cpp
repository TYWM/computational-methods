#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "matrix.h"

using namespace std;

vector<double> luDecomposition(matrix a, matrix l, matrix u, vector<double> b, int n){

        //Factor A into L and U matrices
        int i = 0, j = 0, k = 0;
        matrix tempA(n,n);
        double multiplier = 0;
        for(i=0; i<n; i++) {
                l.setValue(i,i,1);
        }

        for(i=0; i<n; i++) {
                for(j=0; j<n; j++) {
                        tempA.setValue(i,j,a.getValue(i,j));
                }
        }
        for(k=0; k<n-1; k++) {
                for(i=k+1; i<n; i++) {
                        multiplier = tempA.getValue(i,k)/tempA.getValue(k,k);
                        l.setValue(i,k,multiplier);
                        for(j=k+1; j<n; j++) {
                                double temp = tempA.getValue(i,j) - multiplier*tempA.getValue(k,j);
                                tempA.setValue(i,j,temp);
                        }
                }
        }
        for(i=0; i<n; i++) {
                for(j=i; j<n; j++) {
                        u.setValue(i,j,tempA.getValue(i,j));
                }
        }

        //Now that we have L and U, solve for x with these steps
        vector<double> y(n);
        vector<double> x(n);
        double sum = 0;

        //Solve Ly=b for y with forward substitution (y=b/L)
        y[0] = b[0]/l.getValue(0,0);
        for(i=1; i<n; i++) {
                sum=0;
                for(j=0; j<i; j++) {
                        sum = sum+l.getValue(i,j)*y[j];
                }
                y[i] = (b[i]-sum)/l.getValue(i,i);
        }

        cout << "The values in the y vector: " << endl;
        for (auto const& c : y)
                std::cout << setw(8) << c << ' ';
        cout << endl << endl;

        //Solve Ux=y for x with back substitution (x=y/U)
        x[n-1] = y[n-1]/u.getValue(n-1,n-1);
        for(i=n-2; i>=0; i--) {
                sum = 0;
                for(j=i+1; j<n; j++) {
                        sum = sum+u.getValue(i,j)*x[j];
                }
                x[i] = (y[i]-sum)/u.getValue(i,i);
        }

        return x;
}

int main()
{
        ifstream inFile;
        int n;
        inFile.open("data.txt");
        inFile >> n;

        //Create matrices to work with
        matrix a(n,n);
        matrix l(n,n);
        matrix u(n,n);
        vector<double> b(n);
        double inputValue = 0;
        // Read input data
        for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                        inFile >> inputValue;
                        a.setValue(i,j,inputValue);
                }
        }

        cout << "Here is the matrix a you entered:" << endl;
        a.display();

        //Read in b
        for (int i=0; i<n; i++) {
                inFile >> inputValue;
                b[i] = inputValue;
        }
        inFile.close();

        cout << "Here is the vector b you entered:" << endl;
        for (auto const& c : b)
                std::cout << setw(8) << c << ' ';
        cout << endl << endl;

        //Create the solution vector, and call luDecomposition to solve
        vector<double> x(n);
        x=luDecomposition(a,l,u,b,n);

        cout << "Here is the upper triangular matrix U: " << endl;
        u.display();
        cout << "Here is the lower triangular matrix L: " << endl;
        l.display();

        // Print result
        ofstream outFile;
        outFile.open("output.txt");
        cout << "The values in x:  ";
        for (int i=0; i<n; i++) {
            cout << x[i] << " ";
            outFile << x[i] << " ";
        }

        //Calculate error vector
        vector<double> errorVec(n);
        for(int i = 0; i < n; i++) {
                for(int j = 0; j<n; j++) {
                        errorVec[i]=(a.getValue(i,j)*b[j]);
                }
        }

        cout << "The values in the error vector: " << endl;
        for (auto const& c : errorVec)
                std::cout << setw(8) << c << ' ';
        cout << endl << endl;

        //Calculate magnitude of residual:
        double sumBeforeRoot = 0;
        for(int i=0; i < n; i++) {
                sumBeforeRoot += errorVec[i];
        }
        double magResidual = sqrt(sumBeforeRoot);

        cout<<"The magnitude of the residual:  " << magResidual;


        cout << endl << endl;

        return 0;
}
