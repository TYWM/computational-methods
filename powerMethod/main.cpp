#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "matrix.h"

using namespace std;

int main()
{
    int n;
    int step = 0;
    ifstream inFile;
    inFile.open("data.txt");
    inFile >> n;
    matrix a(n,n);
    vector<double> x(n);
    vector<double> c(n);
    double eigenValue = 0;
    double temp = 0;

    double inputValue = 0;
    //read input data
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            inFile >> inputValue;
            a.setValue(i,j,inputValue);
        }
    }

    //Initialize x
    for(int i=0; i<n; i++)
        x[i] = 1000;

    cout << "Here is the matrix A you entered:" << endl;
    a.display();
    inFile.close();

    ofstream outFile;
    outFile.open("output.txt");

    do{
        for(int i=0;i<n;i++)
        {
            c[i]=0;
            for(int j=0;j<n;j++)
                c[i]+=a.getValue(i,j)*x[j];
        }
        for(int i=0;i<n;i++)
            x[i]=c[i];

        temp=eigenValue;
        eigenValue=0;

        for(int i=0;i<n;i++)
        {
            if(fabs(x[i])>fabs(eigenValue))
                eigenValue=x[i];
        }
        for(int i=0;i<n;i++)
            x[i]/=eigenValue;

    cout << "Current lambda at step " << step << " : " << eigenValue << endl;
    outFile << "Current lambda at step " << step << " : " << eigenValue << endl;
    step++;

    }while(fabs(eigenValue-temp) > 0.00001);

    cout << endl;
    outFile <<endl;
    cout<<"Final Eigenvector: " << endl;
    outFile<<"Final Eigenvector: " << endl;
    for(int i=0;i<n;i++){
        cout<<x[i]<<endl;
        outFile<<x[i]<<endl;
    }


    outFile.close();
    return 0;
}
