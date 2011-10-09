//
//  SparseMatrix.h
//  Sparse Matrices
//
//  Created by Dominik Veselý on 9/29/11.
//  Copyright (c) 2011 CTU. All rights reserved.
//

#ifndef Sparse_Matrices_SparseMatrix_h
#define Sparse_Matrices_SparseMatrix_h

#include <vector>

using namespace std;

class SparseMatrix {    
    
public:
    
    vector<int> val;
    vector<int> col_ind;
    vector<int> row_ptr;  
    
    SparseMatrix();
    ~SparseMatrix();
    
    int getRowSize();
    int getColumnSize();   
    
    void multiplicate(const SparseMatrix &matrix);   
    
};



#endif
