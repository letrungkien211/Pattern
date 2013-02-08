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

using namespace std;
using namespace Eigen;


/** Get data from files**/
void GetData(string filename, int rows, int cols, MatrixXd &m){
    string line;
    ifstream myfile(filename.c_str());
    m.resize(rows, cols);
    if(myfile.is_open()){
	int i = 0;
	while(myfile.good() && i< rows){
	    for(int j= 0; j<cols; j++){
		myfile >> m(i,j);
	    }
	    i++;
	}
    }
    else{
	cerr << "Error open file!" <<endl;
	exit(1);
    }
}

int main(int argc, char *argv[]){
    MatrixXd trainData, trainLabel, testData, testLabel, tmpMatrix;
    
    MatrixXd weight;

    /*Initialize matrix*/
    trainData.resize(100,3);
    trainLabel.resize(100,1);
    weight.resize(3,1);
    testData.resize(40,3);
    testLabel.resize(40,1);
    weight.resize(3,1);

    /*Get training data*/
    GetData("data/Train1.txt", 50, 2, tmpMatrix);
    trainData.block(0,1,50,2) = tmpMatrix;
    GetData("data/Train2.txt", 50, 2, tmpMatrix);
    trainData.block(50,1,50,2) = tmpMatrix;
    trainData.block(0,0,100,1).fill(1);
    trainLabel.block(0,0,50,1).fill(-1);
    trainLabel.block(50,0,50,1).fill(1);
    
    /*Get test data*/
    GetData("data/Test1.txt", 20, 2, tmpMatrix);
    testData.block(0,1,20,2) = tmpMatrix;
    GetData("data/Test2.txt", 20, 2, tmpMatrix);
    testData.block(20,1,20,2) = tmpMatrix;
    testData.block(0,0,40,1).fill(1);
    testLabel.block(0,0,20,1).fill(-1);
    testLabel.block(20,0,20,1).fill(1);

#if(0)
    /*Calculate the weight by pseudo-inverse matrix*/
    weight = (trainData.transpose()*trainData).inverse()*trainData.transpose()*trainLabel;
    cout <<weight <<endl;
#endif
    
    return 0;
}
