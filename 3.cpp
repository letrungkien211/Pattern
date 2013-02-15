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

#include "common.hpp"

using namespace std;
using namespace Eigen;

void kNN(MatrixXd &trainmat, MatrixXd &trainidxmat, 
	 MatrixXd &testmat, MatrixXd &residxmat, int nk){
    MatrixXd distance;
    distance.resize(trainmat.rows(),2);

    for(int i = 0; i < testmat.rows(); i++){
	for(int j = 0; j< trainmat.rows(); j++){
	    MatrixXd tmp = trainmat.row(j)-testmat.row(i);
	    distance(j,0) = tmp.squaredNorm();
	    distance(j,1) = j;
	}
	for(int j = 0; j < trainmat.rows()-1; j++){
	    for(int k = j+1; k < trainmat.rows(); k++){
		if(distance(k,0) < distance(j,0)){
		    swap(distance(j,0), distance(k,0));
		    swap(distance(j,1), distance(k,1));
		}
	    }
	}
	int counter = 0;
	for(int k = 0; k < nk; k++){
	    counter += trainidxmat(distance(k,1));
	}
	residxmat(i,0) = counter>nk/2 ? 1 : 0;
    }
}


int main(int argc, char *argv[]){
    MatrixXd trainData, trainLabel, testData, testLabel, testOutput, weight, tmpMatrix;
    srand(time(NULL));
    /*Initialize matrix*/
    trainData.resize(100,2);
    trainLabel.resize(100,1);
    weight.resize(3,1);
    testData.resize(40,2);
    testLabel.resize(40,1);
    testOutput.resize(40,1);
    weight.resize(3,1);

    /*Get training data*/
    GetData("data/Train1.txt", 50, 2, tmpMatrix);
    trainData.block(0,0,50,2) = tmpMatrix;
    GetData("data/Train2.txt", 50, 2, tmpMatrix);
    trainData.block(50,0,50,2) = tmpMatrix;
    trainLabel.block(0,0,50,1).fill(0);
    trainLabel.block(50,0,50,1).fill(1);
    
    /*Get test data*/
    GetData("data/Test1.txt", 20, 2, tmpMatrix);
    testData.block(0,0,20,2) = tmpMatrix;
    GetData("data/Test2.txt", 20, 2, tmpMatrix);
    testData.block(20,0,20,2) = tmpMatrix;
    testLabel.block(0,0,20,1).fill(0);
    testLabel.block(20,0,20,1).fill(1);

    /*Cross validation- Leave-one-out method*/
    for(int nk = 1; nk <=10; nk++){
	MatrixXd trainDataLeave, trainLabelLeave;
	trainDataLeave.resize(trainData.rows()-1,2);
	trainLabelLeave.resize(trainData.rows()-1,1);

	int sumRate = 0;
	for(int l = 0; l < trainData.rows(); l++){
	    int cnt = 0;
	    for(int i = 0; i < trainData.rows(); i++){
		if(i!=l){
		    trainDataLeave.row(cnt) = trainData.row(i);
		    trainLabelLeave(cnt) = trainLabel(cnt);
		    cnt++;
		}
	    }
	    kNN(trainDataLeave, trainLabelLeave, testData, testOutput, nk);
	    for(int i = 0; i<40; i++){
		if(testOutput(i) == testLabel(i))
		    sumRate++;
	    }
	}
	cout << "KNN: "<< nk <<endl;
	cout << "Precision's rate: " << (double)sumRate/(40.0*trainData.rows()) <<endl;
    }
    return 0;
}
