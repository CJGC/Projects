#include <iostream>
#include <string>
#include <cmath>

using namespace std;

unsigned int binToDec(string bin,int low,int up){
	if(up < low) return 0;
	uint middle = (up+low)/2;
	int bit = 0;
	if(bin[middle] == '1') bit = 1;
	return binToDec(bin,low,middle-1) + bit*pow(2,bin.size()-middle-1) + binToDec(bin,middle+1,up);
}

int main(int argc, char ** argv){
	if(argc != 2){
		cerr << "usage <" << argv[0] << "> <binary num>" << endl;
		return -1;
	}
	string bin = argv[1];
	cout << bin << " in to decimal form = "<< binToDec(bin,0,bin.size()-1) << endl;
	return 0;
}
