
#include <iostream>
#include "Matrix.h"
#include <tuple>
#include "MatrixOperations.h"
#include <cstring>
#include <iomanip>
using namespace std;



int main()
{
    //int array[9] = { 2, -1, -2, -4, 6, 3, -4, -2, 8 };
    //int k = 0;

    //Matrix sampleMatrix(3, 3);
    //for (int i = 0; i < 3; i++)
    //{
    //    for (int j = 0; j < 3; j++)
    //    {
    //        sampleMatrix[j][i] = array[k];
    //        k++;
    //    }
    //}



    //Matrix lower(3, 3);
    //Matrix upper(3, 3);

    //for (int i = 0; i < 3; i++)
    //{
    //    for (int k = i; k < 3; k++)
    //    {
    //        int sum = 0;
    //        for (int j = 0; j < i; j++)
    //        {
    //            sum += lower[j][i] * upper[k][j];
    //        }
    //        upper[k][i] = sampleMatrix[k][i] - sum;
    //    }

    //    for (int k = i; k < 3; k++)
    //    {
    //        if (i == k) lower[i][i] = 1;
    //        else
    //        {
    //            int sum = 0;
    //            for (int j = 0; j < i; j++)
    //            {
    //                sum += lower[j][k] * upper[i][j];
    //            }
    //            lower[i][k] = (sampleMatrix[i][k] - sum)/upper[i][i];
    //        }

    //    }
    //}

    //int o = 0;
    Matrix sampleMatrix(2, 3);



    sampleMatrix[0][0] = 1;
    sampleMatrix[1][0] = 2;
    sampleMatrix[0][1] = 3;
    sampleMatrix[1][1] = 4;
    sampleMatrix[0][2] = 5;
    sampleMatrix[1][2] = 6;

    Matrix sampleMatrix2 = sampleMatrix;
    Matrix sampleMatrix3(2,3);
    //sampleMatrix.Transpose();


    //tuple<int, int> size = sampleMatrix.Size();
    //
    //int cols = get<0>(size);
    //int rows = get<1>(size);

    //sampleMatrix3 = sampleMatrix2 + sampleMatrix;
    

}


