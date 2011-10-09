//
//  SparseMatrix.cpp
//  Sparse Matrices
//
//  Created by Dominik Veselý on 9/29/11.
//  Copyright (c) 2011 CTU. All rights reserved.
//

#include "SparseMatrix.h"


SparseMatrix::SparseMatrix() {
    this->row_ptr = vector<int>();
    this->val = vector<int>();
    this->col_ind = vector<int>();    
}

SparseMatrix::~SparseMatrix() {
    
}

int SparseMatrix::getRowSize() {
   return (int) (row_ptr.size()-1);
}

int SparseMatrix::getColumnSize() {
    int max = 0;
    for (int i = 0; i < col_ind.size(); i++) {
        max = (col_ind[i] > max ? col_ind[i]  : max);
    }  
    return max;
}

// i = row , j = column


SparseMatrix* multiplicate(const SparseMatrix &matrix);   