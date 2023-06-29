// Algorithm for SOR method to solve a system of linear equations

#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>

using namespace std;

float sum_func(vector<vector<float>> matrix, vector<float> &vect, int start, int end, int row);
float max_norm_diff(vector<vector<float>> matrix, int stop, int current);
void x_values(vector<vector<float>> matrix, int stop, int current);

int main(){
    const vector<vector<float>> A = {{3,-1,1},{3,6,2},{3,3,7}};
    const vector<float> b = {1,0,4};
    vector<float> x_0 = {0,0,0};
    vector<vector<float>> x;

    x.push_back(x_0);

    int n = b.size();
    int k = 0;
    int N = 100;
    float omega = 1.1;
    float tol = pow(10, -3);

    while (k < N+1){

        vector<float> xnew;

        for (int i = 0; i < n; i++){

            float sum1 = sum_func(A, xnew, 0, i, i);
            float sum2 = sum_func(A, x_0, i+1, n, i);

            float xval = (1-omega)*x_0[i] + (omega/A[i][i])*(b[i] - sum1 - sum2);
            xnew.push_back(xval);
        }
        x.push_back(xnew);
        x_0 = xnew;

        float max = max_norm_diff(x, n, k);
        
        if (max < tol){
            break;
        }

        k = k + 1;
    }
    if (k >= N){
        cout << "Maximum number of iterations reached.";
    }

    x_values(x, n, k);
    cout << k;
}


//Functions

float sum_func(vector<vector<float>> matrix, vector<float> &vect, int start, int end, int row){
    float sum = 0;
    for (int j = start; j < end; j++){
        sum += matrix[row][j]*vect[j];
    }
    return sum;
}

float max_norm_diff(vector<vector<float>> matrix, int stop, int current){
    vector<float> diff;
    for (int i = 0; i < stop; i++){
        diff.push_back(matrix[current+1][i] - matrix[current][i]);
    }

    float max = *max_element(diff.begin(), diff.end());
    return max;
}

void x_values(vector<vector<float>> matrix, int stop, int current){
    for (int i = 0; i < stop; i++){
        int j = i+1;
        cout << "X" << j << ": " << matrix[current-1][i] << endl;
    }
    cout << "Number of iterations: " << current;
}
