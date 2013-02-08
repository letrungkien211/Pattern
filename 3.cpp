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

void kNN(MatrixXd &trainmat, MatrixXd &trainidmat, 
	 MatrixXd &testmat, MatrixXd &residxmat, int nk){

}


int main(int argc, char *argv[]){
    MatrixXd trainData, trainLabel, testData, testLabel, weight, tmpMatrix;
    srand(time(NULL));
    /*Initialize matrix*/
    trainData.resize(100,2);
    trainLabel.resize(100,1);
    weight.resize(3,1);
    testData.resize(40,2);
    testLabel.resize(40,1);
    weight.resize(3,1);

    /*Get training data*/
    GetData("data/Train1.txt", 50, 2, tmpMatrix);
    trainData.block(0,0,50,2) = tmpMatrix;
    GetData("data/Train2.txt", 50, 2, tmpMatrix);
    trainData.block(50,0,50,2) = tmpMatrix;
    trainLabel.block(0,0,50,1).fill(-1);
    trainLabel.block(50,0,50,1).fill(1);
    
    /*Get test data*/
    GetData("data/Test1.txt", 20, 2, tmpMatrix);
    testData.block(0,0,20,2) = tmpMatrix;
    GetData("data/Test2.txt", 20, 2, tmpMatrix);
    testData.block(20,0,20,2) = tmpMatrix;
    testLabel.block(0,0,20,1).fill(-1);
    testLabel.block(20,0,20,1).fill(1);

    return 0;
}
