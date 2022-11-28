#include "Header.h"

int module::CreateBinFile(string nametf, string namebf)
{
	ifstream itf(nametf);
	if (!itf) return 1;
	fstream obf(namebf, ios::binary | ios::out);
	bank b;
	while (!itf.eof()) {
		itf >> b.kodBank;
		itf.get();
		itf.getline(b.bankName, 15, '\n');
		itf.getline(b.address, 15, '\n');
		itf >> b.formSobstv;
		obf.write((char*)&b, sizeof(bank));
	}
	itf.close();
	obf.close();
	return 0;
}

int module::outBinFile(string namebf)
{
	fstream ibf(namebf, ios::binary | ios::in);
	if (!ibf) return 1;
	bank b;
	int len = sizeof(bank);
	ibf.read((char*)&b, len);
	while (!ibf.eof()) {
		cout << b.kodBank << ' ' << b.bankName << ' ' << b.address << ' ' <<
			b.formSobstv << endl;
		ibf.read((char*)&b, len);
	}
	ibf.close();
	return 0;
}

int module::CreateFile(string fname)
{
	int n;
	unsigned int k;
	char nb[15];
	char ad[15];
	char fs[15];
	ifstream f(fname);
	if (f.good()) {
		if (f.fail()) {
			cerr << "Error: Input terminated by data mismatch.\n";
			return 0;
		}
		f.close();
		cerr << "Error: File with that name already exists.\n";
		return 0;
	}
	f.close();
	ofstream file(fname);
	cout << "Input number of banks: \n";
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Input bank code: \n";
		cin >> k;
		file << k << endl;
		cout << "Input bank name: \n";
		cin >> nb;
		file << nb << endl;
		cout << "Input bank address: \n";
		cin >> ad;
		file << ad << endl;
		cout << "Input bank formSobstv: \n";
		cin >> fs;
		file << fs << endl;
	}
	file.close();
	return 1;
}