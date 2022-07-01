
#include <iostream>
#include "Matrix.h"
#include <tuple>
#include "MatrixOperations.h"
#include <cstring>
#include <iomanip>
#include <chrono>
using namespace std;
using namespace std::chrono;

//class MyData
//{
//private:
//    vector<int> private_data_;
//public:
//    MyData() {}
//    MyData(vector<int> data) : private_data_(data) {}
//
//    void setMyData(vector<int>&& sourceData)
//    {
//        private_data_ = std::move(sourceData);
//    }
//
//    void setMyData2(vector<int> sourceData)
//    {
//        private_data_ = sourceData;
//    }
//};


int main()
{
    vector<double> a = { 42, 13, 0, 0, 21, 5, 7, 0, 12 };
    vector<double> b = { 4, 7, 2 };
    Matrix A = Matrix(3, 3, a);
    Matrix B = Matrix(3, 1, b);

    Matrix x = LinsolveLU(A, B);


    //int array[9] = { 2, -1, -2, -4, 6, 3, -4, -2, 8 };
    int array[9] = { 12, -51, 4, 6, 167, -68, -4, 24, -41 };
    int k = 0;
    //Matrix* sampleMatrix3;


    //int* array = new int[100000000]();
    //array[10] = 47;
    //int o = array[10];

    //int array2[100000000]{};
    //array2[10] = 47;

    //sampleMatrix3 = new Matrix(2, 2);


    Matrix sampleMatrix(3, 3);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sampleMatrix[i][j] = array[k];
            k++;
        }
    }
    // 

    //double arr[] = { 1, 2, 3, 4 };
    //double dataset[4] = { 1, 2, 3, 4 };
    //vector<double> dataVector = { 1, 2, 3, 4 };





    //Matrix sampleMatrix(2,2, arr, sizeof(arr)/sizeof(arr[0]));
    //Matrix smpleMatrix2(2, 2, dataVector);
    //sampleMatrix.MakeIdentity();
    //Matrix sampleMatrix2(1000, 1000);
    //sampleMatrix2.Fill(2);


    //std::tuple<Matrix, Matrix> QR = sampleMatrix.QRDecomposition();
    //std::vector<double> eigenvalues = sampleMatrix.Eigenvalues();

    //vector<int> vec;
    //for (int i = 0; i < 100000000; i++)
    //{
    //    vec.push_back(i);
    //}

    //MyData* data1 = new MyData(vec);

    //Matrix sampleMatrix3(1000, 1000);

    //auto start = high_resolution_clock::now();

    //for (int i = 0; i < 1; i++)
    //{
    //    //MyData* data2 = new MyData();
    //    //data2->setMyData(std::move(vec));

    //    //data2->setMyData2(vec);

    //    //sampleMatrix3 = sampleMatrix * sampleMatrix2;


    //    //Matrix* sampleMatrix2 = new Matrix(sampleMatrix);
    //    //Matrix* sampleMatrix2;
    //    //Matrix sampleMatrix2(sampleMatrix);
    //    //auto d = Matrix(std::move(sampleMatrix));
    //    //cout << &sampleMatrix << endl;
    //    //auto d = Matrix(static_cast<Matrix&&>(sampleMatrix));

    //}
    ////sampleMatrix.Transpose();

    //auto stop = high_resolution_clock::now();

    //auto duration = duration_cast<microseconds>(stop - start);




    //sampleMatrix.Size();


    ////Matrix m1 = std::get<0>(LU);
    ////Matrix m2 = get<1>(LU);

    ////double det = sampleMatrix.Determinant();
    //double o = 0;

    


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
    //Matrix sampleMatrix(2, 3);



    //sampleMatrix[0][0] = 1;
    //sampleMatrix[0][1] = 2;
    //sampleMatrix[0][2] = 3;
    //sampleMatrix[1][0] = 4;
    //sampleMatrix[1][1] = 5;
    //sampleMatrix[1][2] = 6;

    //sampleMatrix = sampleMatrix * 2;


    std::vector<double> eigs = sampleMatrix.Eigenvalues();

    double norm = sampleMatrix.FrobeniusNorm();

    sampleMatrix.Size();


    //Matrix sampleMatrix2 = sampleMatrix;
    //Matrix sampleMatrix3(2,3);
    //sampleMatrix.Transpose();

    //Matrix sampleMatrix3 = sampleMatrix * sampleMatrix2;
    //sampleMatrix3.Size();

    //tuple<int, int> size = sampleMatrix.Size();
    //
    //int cols = get<0>(size);
    //int rows = get<1>(size);

    //sampleMatrix3 = sampleMatrix2 + sampleMatrix;
    

}


