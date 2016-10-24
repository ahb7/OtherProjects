//Hackerrank Challenge - Towers
//Matrix Multiplication using Strassen's Algorithm
#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>

using namespace std;

const int MOD = 1.0e9 + 7;

void usage(void){
    cout << "Usage:" << endl;
    cout << "Enter height of the towers in integer, (1<=N<10^18)" << endl;
    cout << "Enter how many types of heights available (Min=1, Max=15)" << endl;
    cout << "Enter each height (should be < 15) separated by space" << endl;
    cout << endl << "Example:" << endl;
    cout << "9" << endl;
    cout << "2" << endl;
    cout << "4 5" << endl;
}

// This is Matrix addition function
vector<vector<long long> > mSum(vector<vector<long long> > X, vector<vector<long long> > Y, int dim)
{
    vector<vector<long long> > sumMatrix;
    sumMatrix.resize(dim);
    for(int i=0; i<dim; i++){
        sumMatrix[i].resize(dim);
    }

    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            sumMatrix[i][j] = (X[i][j] + Y[i][j]) % MOD;
        }
    }

    return sumMatrix;
}


// This is Matrix subtraction function
vector<vector<long long> > mMinus(vector<vector<long long> > X, vector<vector<long long> > Y, int dim)
{
    vector<vector<long long> > minusMatrix;
    minusMatrix.resize(dim);
    for(int i=0; i<dim; i++){
        minusMatrix[i].resize(dim);
    }
    long long int temp;
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            temp = (X[i][j] - Y[i][j]);
            if (temp < 0) {
                temp = temp * (-1);
                temp = temp % MOD;
                temp = (MOD - temp);
            }
            minusMatrix[i][j] = temp % MOD;
        }
    }

    return minusMatrix;
}


// This is Matrix multiplication function using Strassen's Algorithm
vector<vector<long long> > matrixMult(vector<vector<long long> > X, vector<vector<long long> > Y, int dim)
{
    int halfDim;
    int newDim;

    // I am hard coding dim to nearest 2**n; as maximum matrix dimension is 15*15
    if (dim == 3) {
        newDim = 4;
    } else if ((dim > 4 ) && (dim < 8)) {
        newDim = 8;
    } else if (dim > 8){
        newDim = 16;
    } else {
        newDim = dim;
    }

    // Create dotMatrix which will be returned as result
    vector<vector<long long> > dotMatrix;
    dotMatrix.resize(dim);
    for(int i=0; i<dim; i++){
        dotMatrix[i].resize(dim);
    }
    // Termination condition of the recursion
    if (dim == 1) {
        dotMatrix[0][0] = (X[0][0] * Y[0][0]) % MOD;
        return dotMatrix;
    }

    // Create newX and newY matching size 2**n with extra rows as zeros
    vector<vector<long long> > newX;
    newX.resize(newDim);
    for(int i=0; i<newDim; i++){
        newX[i].resize(newDim);
    }
    vector<vector<long long> > newY;
    newY.resize(newDim);
    for(int i=0; i<newDim; i++){
        newY[i].resize(newDim);
    }

    for(int i=0; i<newDim; i++){
        for(int j=0; j<newDim; j++) {
            if ((i < dim) && ( j < dim)){
                newX[i][j] = X[i][j];
                newY[i][j] = Y[i][j];
            } else {
                newX[i][j] = 0;
                newY[i][j] = 0;
            }
        }
    }

    halfDim = (newDim/2);

    // Create 19 Matrices of size half of original dimension - halfDim
    vector<vector<long long> > A11;
    A11.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        A11[i].resize(halfDim);
    }
    vector<vector<long long> > A12;
    A12.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        A12[i].resize(halfDim);
    }
    vector<vector<long long> > A21;
    A21.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        A21[i].resize(halfDim);
    }
    vector<vector<long long> > A22;
    A22.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        A22[i].resize(halfDim);
    }

    vector<vector<long long> > B11;
    B11.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        B11[i].resize(halfDim);
    }
    vector<vector<long long> > B12;
    B12.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        B12[i].resize(halfDim);
    }
    vector<vector<long long> > B21;
    B21.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        B21[i].resize(halfDim);
    }
    vector<vector<long long> > B22;
    B22.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        B22[i].resize(halfDim);
    }

    vector<vector<long long> > C11;
    C11.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        C11[i].resize(halfDim);
    }
    vector<vector<long long> > C12;
    C12.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        C12[i].resize(halfDim);
    }
    vector<vector<long long> > C21;
    C21.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        C21[i].resize(halfDim);
    }
    vector<vector<long long> > C22;
    C22.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        C22[i].resize(halfDim);
    }

    vector<vector<long long> > M1;
    M1.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        M1[i].resize(halfDim);
    }
    vector<vector<long long> > M2;
    M2.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        M2[i].resize(halfDim);
    }
    vector<vector<long long> > M3;
    M3.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        M3[i].resize(halfDim);
    }
    vector<vector<long long> > M4;
    M4.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        M4[i].resize(halfDim);
    }
    vector<vector<long long> > M5;
    M5.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        M5[i].resize(halfDim);
    }
    vector<vector<long long> > M6;
    M6.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        M6[i].resize(halfDim);
    }
    vector<vector<long long> > M7;
    M7.resize(halfDim);
    for(int i=0; i<halfDim; i++){
        M7[i].resize(halfDim);
    }

    // Now divide main matrices newX and newY into four As and four Bs
    for(int i=0; i<halfDim; i++) {
        for(int j=0; j<halfDim; j++){
            A11[i][j] = newX[i][j];
            B11[i][j] = newY[i][j];
        }
    }
    for(int i=0; i<halfDim; i++) {
        for(int j=halfDim; j<newDim; j++){
            A12[i][j-halfDim] = newX[i][j];
            B12[i][j-halfDim] = newY[i][j];
        }
    }
    for(int i=halfDim; i<newDim; i++) {
        for(int j=0; j<halfDim; j++){
                A21[i-halfDim][j] = newX[i][j];
                B21[i-halfDim][j] = newY[i][j];
        }
    }
    for(int i=halfDim; i<newDim; i++) {
        for(int j=halfDim; j<newDim; j++){
            A22[i-halfDim][j-halfDim] = newX[i][j];
            B22[i-halfDim][j-halfDim] = newY[i][j];
        }
    }

    //Now calculate seven M matrices
    M1 = matrixMult(mSum(A11, A22, halfDim), mSum(B11, B22, halfDim), halfDim);
    M2 = matrixMult(mSum(A21, A22, halfDim), B11, halfDim);
    M3 = matrixMult(A11, mMinus(B12, B22, halfDim), halfDim);
    M4 = matrixMult(A22, mMinus(B21, B11, halfDim), halfDim);
    M5 = matrixMult(mSum(A11, A12, halfDim), B22, halfDim);
    M6 = matrixMult(mMinus(A21, A11, halfDim), mSum(B11, B12, halfDim), halfDim);
    M7 = matrixMult(mMinus(A12, A22, halfDim), mSum(B21, B22, halfDim), halfDim);

    // Now calculate the four C matrices
    C11 = mSum(mMinus(mSum(M1, M4, halfDim), M5, halfDim), M7, halfDim);
    C12 = mSum(M3, M5, halfDim);
    C21 = mSum(M2, M4, halfDim);
    C22 = mSum(mMinus(M1, M2, halfDim), mSum(M3, M6, halfDim), halfDim);

    //Now we have to merge the four Cs into final result matrix
    //Remove the extra row and column of 0s from final matrix, if they were added
    for(int i=0; i<halfDim; i++) {
        for(int j=0; j<halfDim; j++){
            // All of C11 should go to final matrix
            dotMatrix[i][j] = C11[i][j];
        }
    }
    for(int i=0; i<halfDim; i++) {
        for(int j=0; j<halfDim; j++){
            // Few columns of C12 needs to be removed if they are zeros
            if ((j + halfDim) < dim){
                dotMatrix[i][j+halfDim] = C12[i][j];
            }
        }
    }
    for(int i=0; i<halfDim; i++) {
        for(int j=0; j<halfDim; j++){
            // Few rows of C21 needs to be removed if they are zeros
            if ((i + halfDim) < dim){
                dotMatrix[i+halfDim][j] = C21[i][j];
            }
        }
    }
    for(int i=0; i<halfDim; i++) {
        for(int j=0; j<halfDim; j++){
            // Few rows and columns of C12 needs to be removed if they are zeros
            if (((i + halfDim) < dim) && ((j + halfDim) < dim)){
                dotMatrix[i+halfDim][j+halfDim] = C22[i][j];
            }
        }
    }

    return dotMatrix;
}


// This is Matrix Exponentiation function using iterative squaring
vector<vector<long long> > matrixExp(vector<vector<long long> > M, long long n, int dim)
{
    vector<vector<long long> > resultMatrix;
    resultMatrix.resize(dim);
    for(int i=0; i<dim; i++){
        resultMatrix[i].resize(dim);
    }

    // This matrix saves an instance of the computed matrix when n becomes odd
    // And does one final multiplication before returning results
    vector<vector<long long> > oddOffsetMatrix;
    oddOffsetMatrix.resize(dim);
    for(int i=0; i<dim; i++){
        oddOffsetMatrix[i].resize(dim);
    }

    // Set oddOffsetMatrix to Identity Matrix
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            if (i == j) {
                oddOffsetMatrix[i][j] = 1;
            } else {
                oddOffsetMatrix[i][j] = 0;
            }
        }
    }

    if (n == 0) {
        return oddOffsetMatrix;
    }

    while (n > 1) {
        // When n is even
        if ((n % 2) == 0) {
            M = matrixMult(M, M, dim);
            n = n/2;
        } else {
            // When n is odd
            oddOffsetMatrix = matrixMult(M, oddOffsetMatrix, dim);
            M = matrixMult(M, M, dim);
            n = (n-1)/2;
        }

    }

    resultMatrix = matrixMult(M, oddOffsetMatrix, dim);

    return resultMatrix;
}

int main()
{
    long long n;
    int noOfHeights;
    // Get n height of the desired towers
    long long maxNo = 1.0e18;
    cin >> n;
    if ((n <= 0) || (n > maxNo)) {
        cout << "Error: entered number out of range" << endl;
        usage();
        return -1;
    }

    // Get how many types of bricks available
    cin >> noOfHeights;
    if ((noOfHeights <= 0) || (noOfHeights > 15)) {
        cout << "Error: Number of Heights is between 1 to 15" << endl;
        usage();
        return -1;
    }

    // Create and Initialize Height Vector H
    // h1 <=> H[1]; left H[0] = 0 unused; for convenience
    int *H = new int[15+1];
    for (int i=0; i <=15; i++){
        H[i]=0;
    }

    // Get the brick heights and mark the H vector '1' for those
    // HeightList is not needed, only maxHeight sufficient
    // I optimized by not hard coding to 15; instead max height entered
    int maxHeight = 0;
    int *heightList = new int[noOfHeights+1];
    for (int i=1; i<=noOfHeights; i++){
        cin >> heightList[i];
        if ((heightList[i] > 15) || (heightList[i] <= 0)){
            cout << "Error: Brick height can not be " << heightList[i] <<endl;
            usage();
            return -1;
        }
        for (int j=1; j<i; j++){
            if(heightList[j] == heightList[i]) {
                cout << "Error: Brick height should be unique " << heightList[i] <<endl;
                usage();
                return -1;
            }
        }
        if (heightList[i] > maxHeight){
            maxHeight = heightList[i];
        }
        H[heightList[i]]=1;
    }

    // We got maximum Height of brick (which should be <=15)
    // Now let us create F(Memoization) vectors
    // We will create F vector only up to maxHeight (up to 15)

    // Dynamic Programming: Store Computed function values in array Memo[]
    long long *Memo = new long long[maxHeight+1];
    long long totalTowers = 0;
    int totalMinutes = 0;
    // Memo[0] is just for mathematical convenience
    Memo[0] = 1;
    // f(n) = h1*f(n-1) + h2*f(n-2) + h3*f(n-3)+... n<=maxHeight
    for (int i=1; i<=maxHeight; i++){
        totalTowers=0;
        for (int j=1; j<=i; j++){
            totalTowers = (totalTowers + (H[j]*Memo[i-j]) %MOD)  % MOD;
        }
        Memo[i] = totalTowers % MOD;
    }

    // Create Matrix M of size maxHeight X maxHeight using Vector H
    // Matrix M is 0,0 indexed, when maxHeight 15, M = 0..14 X 0..14
    vector<vector<long long> > M;
    M.resize(maxHeight);
    for (int i=0; i<maxHeight; i++) {
        M[i].resize(maxHeight);
    }
    for (int i=0; i<maxHeight; i++) {
        for (int j=0; j<maxHeight; j++) {
            if (i == (maxHeight-1)) {
                // Last row is copy of reverse of H
                M[i][j] = H[maxHeight-j];
            } else if (j == i+1) {
                // For diagonal '1'
                M[i][j] = 1;
            } else {
                M[i][j] = 0;
            }
        }
    }

    //Main Matrix Exponentiation Calculation
    totalTowers = 0;
    if (n > maxHeight) {
        long long power = n - maxHeight;
        M = matrixExp(M, power, maxHeight);

        // Once I get the final Matrix, I multiply highest row with the Memo[] vector
        // Rather than adding another function for (m,m)and (m,1) vector multiplication
        // I do not need to compute other element of the Memo in this case
        // as only the highest element of Memo[] is our answer
        // cout << Memo[maxHeight] << endl;
        for(int i=0; i<maxHeight; i++){
            // Memo[] has index (0..maxHeight), we need (1..maxHeight)
            totalTowers = ((totalTowers + ((M[maxHeight-1][i] * Memo[i+1]) % MOD)) %  MOD);
            //cout <<"M: " <<M[maxHeight-1][i] <<" Memo: "<<Memo[i+1] <<endl;
        }
    } else {
        totalTowers = Memo[n];
    }

    // Multiply noOfTowers by cost 2 and return results in modulo
    totalMinutes = (totalTowers * 2) % MOD;
    cout << totalMinutes <<endl;

    delete[] H;
    delete[] Memo;
    delete[] heightList;

    return 0;
}
