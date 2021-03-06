#include <Eigen/Dense>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cassert>
#include <vector>

#include "common.hpp"

using namespace std;
using namespace Eigen;

#define N 10

int main(int argc, char** argv){
    vector<MatrixXd> omega(3);
    vector<MatrixXd> average(3);
    vector<MatrixXd> variance(3);
    MatrixXd distance;
    MatrixXd tmpMatrix;
    MatrixXd testData;


    distance.resize(4,3);
    testData.resize(4,3);
    /*Set size*/
    for(int i = 0; i < 3; i++){
	omega[i].resize(N,3);
	average[i].resize(1,3);
	variance[i].resize(3,3);
    }

    /*Initialize test data*/
    testData(0,0) = 1;    testData(0,1) = 2;     testData(0,2) = 1;
    testData(1,0) = 5;    testData(1,1) = 3;     testData(1,2) = 2;
    testData(2,0) = 0;    testData(2,1) = 0;     testData(2,2) = 0;
    testData(3,0) = 1;    testData(3,1) = 0;     testData(3,2) = 0;


/*Get data*/
    GetData("data/omega1.txt", N, 3, tmpMatrix);
    omega[0] = tmpMatrix;
    GetData("data/omega2.txt", N, 3, tmpMatrix);
    omega[1] = tmpMatrix;
    GetData("data/omega3.txt", N, 3, tmpMatrix);
    omega[2] = tmpMatrix;

    /*Calculate averages*/
    for(int i = 0; i < 3; i++){
	for(int j = 0; j < N; j++){
	    average[i]+=omega[i].row(j);
	}
	average[i] /= N;
    }

    /*Calculate variances*/
    for(int i = 0; i <3; i++){
	for(int j = 0; j < N; j++){
	    MatrixXd tmp = omega[i].row(j)-average[i];
	    variance[i]+= tmp.transpose()*tmp;
	}
	variance[i]/=(N-1);
    }
    /*Calculate mahalanobis distance*/
    for(int i = 0; i <4; i++){
	for(int j = 0; j < 3; j++){
	    MatrixXd d = testData.row(i) - average[j];
	    MatrixXd tmp = d*variance[j].inverse()*d.transpose();
	    distance(i,j) = sqrt(tmp(0));
	}
    }
    cout << distance <<endl <<endl;

    for(int i = 0; i < 12; i++){
	distance(i) = 1/distance(i);
    }

    for(int i = 0; i < 4; i++){
	distance.row(i)/=distance.row(i).sum();
    }

    cout << distance <<endl << endl;
    double prob[] = {0.8,0.1,0.1};
    for(int j = 0; j <3; j++){
	distance.col(j)*=prob[j];
    }
    cout << distance <<endl;
}
