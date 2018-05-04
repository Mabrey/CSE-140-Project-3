
void loopUnroll(int m, int n, float *A, float *C)
{
    int multOps = m * n * m;        
    int addOps = m * n;
    for( int i = 0; i < m; i++ )
        for( int k = 0; k < n; k++ ) 
            for( int j = 0; j < m; j+= 5 ) {
                //to start untolling the loop, we need to know how far we can unroll it. 
                //since we are in the j loop, we should unroll the j loop by 5 or less? 
                //m is our row/column length so distToColumnEnd will be our boundry for unrolling to prevent reading the next row.
                int distToStripEnd = m - j;

                if (distToStripEnd > 4)    //unroll 5 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[i+(j + 1)*m] += A[i+k*m] * A[(j + 1)+k*m];
                    C[i+(j + 2)*m] += A[i+k*m] * A[(j + 2)+k*m];
                    C[i+(j + 3)*m] += A[i+k*m] * A[(j + 3)+k*m];
                    C[i+(j + 4)*m] += A[i+k*m] * A[(j + 4)+k*m];
                }

                else if (distToStripEnd == 4)   //unroll 4 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[i+(j + 1)*m] += A[i+k*m] * A[(j + 1)+k*m];
                    C[i+(j + 2)*m] += A[i+k*m] * A[(j + 2)+k*m];
                    C[i+(j + 3)*m] += A[i+k*m] * A[(j + 3)+k*m];
                }
                
                else if (distToStripEnd == 3) //unroll 3 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[i+(j + 1)*m] += A[i+k*m] * A[(j + 1)+k*m];
                    C[i+(j + 2)*m] += A[i+k*m] * A[(j + 2)+k*m];
                } 

                else if (distToStripEnd == 2)   //unroll 2 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[i+(j + 1)*m] += A[i+k*m] * A[(j + 1)+k*m];
                }  

                else C[i+j*m] += A[i+k*m] * A[j+k*m];   //normal operation
   
            }
           
}

void loopUnrollWithSwitch(int m, int n, float *A, float *C)
{
    int multOps = m * n * m;        
    int addOps = m * n;
    for( int i = 0; i < m; i++ )
        for( int k = 0; k < n; k++ ) 
            for( int j = 0; j < m; j+= 5) {
                //to start untolling the loop, we need to know how far we can unroll it. 
                //since we are in the j loop, we should unroll the j loop by 5 or less? 
                //m is our row/column length so distToColumnEnd will be our boundry for unrolling to prevent reading the next row.
                int distToStripEnd = m - j;
                if (distToStripEnd > 4) distToStripEnd = 5;
                    
                switch (distToStripEnd){
                    case 5:
                        C[i+(j + 4)*m] += A[i+k*m] * A[(j + 4)+k*m];

                    case 4:
                        C[i+(j + 3)*m] += A[i+k*m] * A[(j + 3)+k*m];
                    
                    case 3:
                        C[i+(j + 2)*m] += A[i+k*m] * A[(j + 2)+k*m];

                    case 2:
                        C[i+(j + 1)*m] += A[i+k*m] * A[(j + 1)+k*m];

                    default:
                        C[i+j*m] += A[i+k*m] * A[j+k*m];

                }
            }         
}



void dgemm( int m, int n, float *A, float *C )
{
    //loop unrolling 
    loopUnroll(m, n, A, C);
    //loopUnrollWithSwitch(m, n, A, C);

}
