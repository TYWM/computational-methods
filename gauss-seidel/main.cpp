#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "matrix.h"

using namespace std;

vector<double> gaussSeidel(matrix a, vector<double> b, int n, int maxIterations, int& iterations){
    vector<double> x(n);
    vector<double> oldx(n);
    int i,j;
    double accuracy = 1e-15;
    bool notAccurate = true;
    double sum = 0;

    while(notAccurate && iterations < maxIterations){
        for(i=0; i<n; i++){
            sum = b[i];
            for(j=0; j<n; j++){
                if(j!=i)
                    sum -= a.getValue(i,j) * x[j];
            }
            x[i] = sum/a.getValue(i,i);
        }

        notAccurate = false;
        for(i=0; i<n; i++)
            if(fabs(x[i]-oldx[i]) > accuracy)
                notAccurate = true;
        oldx = x;
        ++iterations;
    }
    return x;
}

int main()
{
    ifstream inFile;
    int n;
    inFile.open("data.txt");
    inFile >> n;
    vector<double> b(n);
    matrix a(n,n);
    double inputValue = 0;
    int iterations = 0;

    // Read in a
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

    int maxIterations = 800;
    vector<double> x(n);
    x = gaussSeidel(a,b,n,maxIterations, iterations);

    // Print result
    ofstream outFile;
    outFile.open("output.txt");
    cout << "The values in x:  ";
    for (int i=0; i<n; i++) {
        cout << x[i] << " ";
        outFile << x[i] << " ";
    }
    cout << endl << endl;
    outFile << endl <<endl;
    outFile << "There were a total of " << iterations << " iterations.";
    cout << "There were a total of " << iterations << " iterations.";
    outFile.close();

    return 0;
}
