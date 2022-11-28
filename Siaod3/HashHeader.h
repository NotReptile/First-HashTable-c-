#include "Header.h"
#include "HashTable.h";
#include <vector>

bool FileInHash(HashTable* table, string namebf) {
	fstream ibf(namebf, ios::binary | ios::in);
	if (!ibf) return false;
	bank b;
	int len = sizeof(bank);
	ibf.read((char*)&b, len);
	while (!ibf.eof()) {
		//string num = to_string(b.kodBank);
		stringstream str;
		str << b.kodBank;
		string temp_str = str.str();
		char* bankNum = (char*)temp_str.c_str();
		hash_insert(table,bankNum, b.bankName);
		print_table(table);
		ibf.read((char*)&b, len);
	}
	ibf.close();
	return true;
}
int DeletingByHash(HashTable* table,string namebf) {
	char otvet = 'y';
	FILE* db = fopen("Banks.bin", "r+b");
	if (!db){return -1;}
	fseek(db, 0, SEEK_END);
	size_t size = ftell(db);
	size_t count = size / sizeof(bank);
	fseek(db, 0, SEEK_SET);
	std::vector<bank> banks(count);
	fread(banks.data(), sizeof(bank), banks.size(), db);
	fclose(db);
	char ask = 'y';
	do {
		int bankToErase;
		cin >> bankToErase;
		bool found = false;
		stringstream str;
		str << bankToErase;
		string temp_str = str.str();
		char* keyReady = (char*)temp_str.c_str();
		hash_delete(table, keyReady);
		for (size_t i = 0; i < count; ++i)
		{
			if (bankToErase == banks[i].kodBank)
			{
				banks[i] = banks[count - 1];
				count--;
				found = true;
				break;
			}
		}

		if (found)
			cout << "Bank found\n";
		else
			cout << "Bank not found";

		cout << "Wanna delete another bank?[y/n]";
		cin >> ask;
	} while (ask == 'y' || ask == 'Y');

	if (count != banks.size())
	{
		db = fopen("Banks.bin", "wb");
		if (!db){return -1;}
		fwrite(banks.data(), sizeof(bank), count, db);
		fclose(db);

		cout << "\nselected bank deleted successfully!\n";
	}
	return 0;
}
//bool FindByHash(HashTable* table, int key) {
//	stringstream str;
//	str << key;
//	string temp_str = str.str();
//	char* keyReady = (char*)temp_str.c_str();
//	print_search(table, keyReady);
//	return true;
//}
int FindByHash(HashTable* table, int key) {
	FILE* db = fopen("Banks.bin", "r+b");
	if (!db) { return -1; }
	fseek(db, 0, SEEK_END);
	size_t size = ftell(db);
	size_t count = size / sizeof(bank);
	fseek(db, 0, SEEK_SET);
	std::vector<bank> banks(count);
	fread(banks.data(), sizeof(bank), banks.size(), db);
	fclose(db);
	int bankToFind;
	bankToFind = key;
	bool found = false;
	stringstream str;
	str << bankToFind;
	string temp_str = str.str();
	char* keyReady = (char*)temp_str.c_str();
	for (size_t i = 0; i < count; ++i)
	{
		if (bankToFind == banks[i].kodBank)
		{
			print_search(table, keyReady);
			cout << "\nBank kod : " << banks[i].kodBank << "\nBank Name : " << banks[i].bankName
				<< "\nBank address : " << banks[i].address << "\nBank type of ownership : "
				<< banks[i].formSobstv << endl << endl;
			found = true;
			break;
		}
	}

	if (!found)
		cout << "Bank not found\n";

	return 0;
}
void printFileHashTable(HashTable* table) {
	print_table(table);
}