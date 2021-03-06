
void loopUnroll(int m, int n, float *A, float *C)
{
 
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

void reordering(int m, int n, float *A, float *C){
   /* 
   //i, k, j    naive 
    for( int i = 0; i < m; i++ )
        for( int k = 0; k < n; k++ )
            for( int j = 0; j < m; j++ ) 
                C[i+j*m] += A[i+k*m] * A[j+k*m];
   
    //i, j, k   pretty bad
    for( int i = 0; i < m; i++ )
        for( int j = 0; j < m; j++ ) 
            for( int k = 0; k < n; k++ )
                C[i+j*m] += A[i+k*m] * A[j+k*m];
    
    //j, i, k   Pretty bad
    for( int j = 0; j < m; j++ )
        for( int i = 0; i < m; i++ ) 
            for( int k = 0; k < n; k++ )
                C[i+j*m] += A[i+k*m] * A[j+k*m];
*/    
    //j, k, i   Best
    for( int j = 0; j < m; j++ ) 
        for( int k = 0; k < n; k++ )
            for( int i = 0; i < m; i++ )
                C[i+j*m] += A[i+k*m] * A[j+k*m];
/*
    //k, i, j   slightly better
    for( int k = 0; k < n; k++ )
        for( int i = 0; i < m; i++ )
            for( int j = 0; j < m; j++ ) 
                C[i+j*m] += A[i+k*m] * A[j+k*m];

    //k, j, i   Pretty good
    for( int k = 0; k < n; k++ )
        for( int j = 0; j < m; j++ ) 
            for( int i = 0; i < m; i++ )
                C[i+j*m] += A[i+k*m] * A[j+k*m];
 */
}

void reorderingWithUnroll(int m, int n, float *A, float *C){
    for( int j = 0; j < m; j++ ) 
        for( int k = 0; k < n; k++ )
            for( int i = 0; i < m; i+=8 ){
                //to start untolling the loop, we need to know how far we can unroll it. 
                //since we are in the j loop, we should unroll the j loop by 5 or less? 
                //m is our row/column length so distToColumnEnd will be our boundry for unrolling to prevent reading the next row.
                int distToStripEnd = m - i;

                if (distToStripEnd > 7)    //unroll 5 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[(i + 1)+j*m] += A[(i + 1)+k*m] * A[j+k*m];
                    C[(i + 2)+j*m] += A[(i + 2)+k*m] * A[j+k*m];
                    C[(i + 3)+j*m] += A[(i + 3)+k*m] * A[j+k*m];
                    C[(i + 4)+j*m] += A[(i + 4)+k*m] * A[j+k*m];
                    C[(i + 5)+j*m] += A[(i + 5)+k*m] * A[j+k*m];
                    C[(i + 6)+j*m] += A[(i + 6)+k*m] * A[j+k*m];
                    C[(i + 7)+j*m] += A[(i + 7)+k*m] * A[j+k*m];
                    
                }

                else if (distToStripEnd == 7)    //unroll 5 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[(i + 1)+j*m] += A[(i + 1)+k*m] * A[j+k*m];
                    C[(i + 2)+j*m] += A[(i + 2)+k*m] * A[j+k*m];
                    C[(i + 3)+j*m] += A[(i + 3)+k*m] * A[j+k*m];
                    C[(i + 4)+j*m] += A[(i + 4)+k*m] * A[j+k*m];
                    C[(i + 5)+j*m] += A[(i + 5)+k*m] * A[j+k*m];
                    C[(i + 6)+j*m] += A[(i + 6)+k*m] * A[j+k*m];
                }

                else if (distToStripEnd == 6)    //unroll 5 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[(i + 1)+j*m] += A[(i + 1)+k*m] * A[j+k*m];
                    C[(i + 2)+j*m] += A[(i + 2)+k*m] * A[j+k*m];
                    C[(i + 3)+j*m] += A[(i + 3)+k*m] * A[j+k*m];
                    C[(i + 4)+j*m] += A[(i + 4)+k*m] * A[j+k*m];
                    C[(i + 5)+j*m] += A[(i + 5)+k*m] * A[j+k*m];
                }

                else if (distToStripEnd == 5)    //unroll 5 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[(i + 1)+j*m] += A[(i + 1)+k*m] * A[j+k*m];
                    C[(i + 2)+j*m] += A[(i + 2)+k*m] * A[j+k*m];
                    C[(i + 3)+j*m] += A[(i + 3)+k*m] * A[j+k*m];
                    C[(i + 4)+j*m] += A[(i + 4)+k*m] * A[j+k*m];
                }

                else if (distToStripEnd == 4)   //unroll 4 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[(i + 1)+j*m] += A[(i + 1)+k*m] * A[j+k*m];
                    C[(i + 2)+j*m] += A[(i + 2)+k*m] * A[j+k*m];
                    C[(i + 3)+j*m] += A[(i + 3)+k*m] * A[j+k*m];
                }
                
                else if (distToStripEnd == 3) //unroll 3 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[(i + 1)+j*m] += A[(i + 1)+k*m] * A[j+k*m];
                    C[(i + 2)+j*m] += A[(i + 2)+k*m] * A[j+k*m];
                } 

                else if (distToStripEnd == 2)   //unroll 2 times
                {
                    C[i+j*m] += A[i+k*m] * A[j+k*m];
                    C[(i + 1)+j*m] += A[(i + 1)+k*m] * A[j+k*m];
                }  

                else C[i+j*m] += A[i+k*m] * A[j+k*m];   //normal operation
   
            }

}

void matrixPad(int m, int n, float *A, float *C) {

	if (n % 2 == 1) {

		//make rows = columns so we operate on square matrix
		int newN = n + 1;
		//allocate new memory for padded matrix
		float *paddedA = (float*)malloc(m * (newN) * sizeof(float));

		//initialize matrix to 0
		for (int i = 0; i < (m * newN); i++) {
				paddedA[i] = 0;		
		}

		//copy original matrix to padded matrix
		for (int i = 0; i < (m * n); i++) {
				paddedA[i] = A[i];
			
		}

		//multiply
		for (int i = 0; i < m; i++)
			for (int k = 0; k < newN; k++)
				for (int j = 0; j < m; j++)
					C[i + j * m] += paddedA[i + k * m] * paddedA[j + k * m];
	}

	else if (m % 2 == 1) {

		//make colomns = rows so we operate on square matrix
		int newM = m + 1;
		int dif = 1;
		
		//allocate new memory for padded matrix
		float *paddedA = (float*)malloc(newM * n * sizeof(float));

		for (int i = 0; i < (newM * n); i++) {
				paddedA[i] = 0;
		}

        int j = 0;
		for (int i = 0; i < m * n; i++) {
			if (i % m == 0 && i !=0)
                j++;
            
            paddedA[j] = A[i];
            j++;
		}

		//multiply
        /*
		for (int i = 0; i < newM; i++)
			for (int k = 0; k < n; k++)
				for (int j = 0; j < newM; j++)
					C[i + j * m] += paddedA[i + k * m] * paddedA[j + k * m];

        */
        for( int i = 0; i < m; i++ )
            for( int k = 0; k < n; k++ ) 
                for( int j = 0; j < m; j++ ) 
	                C[i+j*m] += A[i+k*m] * A[j+k*m];
	}

	else {

		//multiply
		for (int i = 0; i < m; i++)
			for (int k = 0; k < n; k++)
				for (int j = 0; j < m; j++)
					C[i + j * m] += A[i + k * m] * A[j + k * m];
	}

}


void dgemm( int m, int n, float *A, float *C )
{
    
    //loopUnroll(m, n, A, C);
    //loopUnrollWithSwitch(m, n, A, C);
    //reordering(m, n, A, C);
    //reorderingWithUnroll(m, n, A, C);
	matrixPad(m, n, A, C);
   

}
