//
//  main.cpp
//  Sparse Matrices
//
//  Created by Dominik Veselý on 9/29/11.
//  Copyright (c) 2011 CTU. All rights reserved.
//

#include <iostream>
#include <vector>
#include "SparseMatrix.h"

using namespace std;

#ifdef DEBUG
int f1 = 1,f2 =2,ac=2;
#else
int f1 = 0,f2 =1,ac=1;
#endif

// Read sparse Matrix from file and create SparseMatrixObject from it
SparseMatrix* readSparseMatrix(const char* file) ;
// Allocates memory for matrix of size rows x cols
int** createMatrix(int rows, int cols) ;
// Allocates memory for vector of size rows
int* createVector(int rows)  ;
// Allocates memory for vector of size rows and fills it with random numbers
int* generateVector(int rows) ;
// Performs multiplication on csrMatrix with csrMatrix
// Creates SparseMatrix objects and prints the result matrix
void MatrixMatrix(const char* file1, const char* file2) ;
// Performs vector x csrMatrix multiplication
// and prints out the result vector 
void VectorMatrix(const char* file1) ;

SparseMatrix* readSparseMatrix(const char* file) {
    FILE* fp;
    if((fp = fopen(file, "r"))== NULL) {
        cout << "Soubor nenalezen" << endl;
        exit(1);
    }
    
    SparseMatrix* matrix = new SparseMatrix();
    
    int decimal = 0;
    //Add values
    fscanf(fp,"V:");
    while(fscanf(fp,"%d",&decimal) == 1) {
        matrix->val.push_back(decimal);
    };
    //Add cols
    fscanf(fp,"C:");
    while(fscanf(fp,"%d",&decimal) == 1) {
        matrix->col_ind.push_back(decimal);
    };
    
    //Rows
    fscanf(fp,"R:");
    while(fscanf(fp,"%d",&decimal) == 1) {
        matrix->row_ptr.push_back(decimal);
    };
    
    fclose(fp);
    
    return matrix;    
}

int** createMatrix(int rows, int cols) {
    int ** matrix;
	matrix = (int **) calloc(rows, sizeof(int *));
	for(unsigned int i = 0; i < rows; i++)
		matrix[i] = (int *) calloc(cols, sizeof(int));
	return matrix;
}

int* createVector(int rows) {
    int* vector ;
    vector = (int*) calloc(rows, sizeof(int));
    return vector;
}

int* generateVector(int rows) {
    int* vector = createVector(rows);
    for (int i =0; i < rows; i++) {
        srand((unsigned)time(0)); 
        vector[i] = abs(rand());
    }
    return vector;
}

void MatrixMatrix(const char* file1, const char* file2) {
    SparseMatrix *A = readSparseMatrix(file1);
    SparseMatrix *B = readSparseMatrix(file2);
    int rows = (A->getRowSize());
    int columns = B->getColumnSize();
    int **C = createMatrix(rows,columns);
    int y,i,j,x,x2;
    for (y=0; y < 6 ; y++) {
        for(i = A->row_ptr[y]; i < A->row_ptr[y+1]; i++) {
            x = A->col_ind[i];
            for (j = B->row_ptr[x]; j < B->row_ptr[x+1]; j++) {
                x2 = B->col_ind[j];
                C[y][x2] += A->val[i]*B->val[j];
            }
        }
    }
    
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    
    delete A;
    delete B;
    for (i = 0; i < rows; i++) {
        free(C[i]);
    }
    free(C);
}

void VectorMatrix(const char* file1) {
    SparseMatrix *A = readSparseMatrix(file1);
    int *y = createVector(A->getRowSize());
    int *x = generateVector(A->getRowSize());
    
    int i,k,j;
    for (i = 0; i < A->getRowSize(); i++) {
        y[i] = 0;
        for (k = A->row_ptr[i]; k < A->row_ptr[i+1]; k++) {
            j = A->col_ind[k];
            y[i] += A->val[k]*x[j];
        }
    }
    
    for (i = 0; i < A->getRowSize(); i++) {
        cout << y[i] << endl;
    }
    
    delete A;
    free(x);
    free(y);
}

int main (int argc, const char * argv[]) {   
    if(argc > ac) {
        MatrixMatrix(argv[f1],argv[f2]);
    } else {
        VectorMatrix(argv[f1]);
    }   
    return 0;
}

