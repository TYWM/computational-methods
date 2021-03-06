#ifndef MATRIX_H
#define MATRIX_H
#include <cstddef>
#include <vector>

class matrix{

public:
    matrix(){A=NULL;};
    ~matrix(){};
    matrix(int r, int c);
    void setValue(int r, int c, double value){A[r][c]=value;};
    double getValue(int r, int c){return A[r][c];};
    int getrow(){return row;};
    int getcol(){return col;};
    void display();
    void displayAugmented();
    void ident();
    void random_mat(double m);
    std::vector<double> gauss(matrix A);


private:
    int row;
    int col;
    double ** A;
};

#endif // MATRIX_H
