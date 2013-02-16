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

int main(int argc, char** argv){
    vector<MatrixXd> omega(3);
    vector<MatrixXd> average(3);
    MatrixXd tmpMatrix;
    /*Get data*/
    for(int i = 0; i < 3; i++){
	omega[i].resize(10,3);
	average[i].resize(1,3);
    }
    
    GetData("data/omega1.txt", 10, 3, tmpMatrix);
    omega[0] = tmpMatrix;
    GetData("data/omega2.txt", 10, 3, tmpMatrix);
    omega[1] = tmpMatrix;
    GetData("data/omega3.txt", 10, 3, tmpMatrix);
    omega[2] = tmpMatrix;

    /*Calculate average*/
    for(int i = 0; i < 3; i++){
	for(int j = 0; j < 10; j++){
	    average[i]+=omega[i].row(j);
	}
	average[i] /= 10.0;
    }

}
