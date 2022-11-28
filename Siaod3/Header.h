#ifndef MAIN_CPP_HEADER_H
#define MAIN_CPP_HEADER_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include "string.h"
using namespace std;

class module {
public:
	int CreateBinFile(string nametf, string namebf);
	int outBinFile(string namebf);
	int CreateFile(string fname);
};
struct bank {
	unsigned int kodBank;
	char bankName[15];
	char address[15];
	char formSobstv[15];
};
#endif
