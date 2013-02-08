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
