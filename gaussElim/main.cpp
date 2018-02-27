#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "matrix.h"

using namespace std;

vector<double> gauss(matrix mat) {
    int n = mat.getrow();

    double newValue = 0;
    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = abs(mat.getValue(i,i));
        double checkValue = 0;
        int maxRow = i;
        for (int k=i+1; k<n; k++) {
            checkValue = abs(mat.getValue(k,i));
            if (checkValue > maxEl) {
                maxEl = checkValue;
                maxRow = k;
            }
        }

        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1;k++) {
            double tmp = mat.getValue(maxRow,k);
            mat.setValue(maxRow,k,mat.getValue(i,k));
            mat.setValue(i,k,tmp);
        }

        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -(mat.getValue(k,i)/mat.getValue(i,i));
            for (int j=i; j<n+1; j++) {
                if (i==j) {
                    mat.setValue(k,j,0);
                } else {
                    newValue = mat.getValue(k,j)+(c*mat.getValue(i,j));
                    mat.setValue(k,j,newValue);
                }
            }
        }
    }

    // Solve
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        x[i] = mat.getValue(i,n)/mat.getValue(i,i);
        for (int k=i-1;k>=0; k--) {
            newValue = mat.getValue(k,n)-(mat.getValue(k,i)*x[i]);
            mat.setValue(k,n,newValue);
        }
    }
    return x;
}


int main() {
    ifstream inFile;
    int n;
    inFile.open("data.txt");
    inFile >> n;
    vector<double> b(n);

    matrix mat(n,n+1);
    double inputValue = 0;
    // Read input data
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            inFile >> inputValue;
            mat.setValue(i,j,inputValue);
        }
    }

    //Read in b
    for (int i=0;i<n;i++){
        inFile >> inputValue;
        b[i] = inputValue;
    }

    //put b into A as an augmented matrix
    for (int i=0; i<n; i++) {
        mat.setValue(i,n,b[i]);
    }

    inFile.close();
    cout << "Here is what you entered:" << endl;
    mat.displayAugmented();

     //Calculate solution
    vector<double> x(n);
    x = gauss(mat);

    // Print result
    ofstream outFile;
    outFile.open("output.txt");
    cout << "The values in x:  ";
    for (int i=0; i<n; i++) {
        cout << x[i] << " ";
        outFile << x[i] << " ";
    }
}
