#include "Header.h"
#include "HashHeader.h";
int main() {
    HashTable* ht = create_table(SIZE);
	string fname;
	int flag = 0;
	while (!flag) {
        module object;
        cout << "Choose what to do:\n";
        cout << "1: Create a file" << endl;
        cout << "2: Transfer EXISTED file to bin" << endl;
        cout << "3: Transfer CREATED file to bin" << endl;
        cout << "4: Output bin file" << endl;
        cout << "5: Connect file and hashtable" << endl;
        cout << "6: Delete element by hash" << endl;
        cout << "7: Find element by hash" << endl;
        cout << "8: Test HashTable" << endl;
        cout << "9: Print File HashTable" << endl;
        cout << "0: Stop the program\n" << endl;
        int x;
        int key = 0;

        cin >> x;
        switch (x) {
        case 1:
            cout << "Enter file name" << endl;
            cin >> fname;
            object.CreateFile(fname);
            break;
        case 2: 
            object.CreateBinFile("TestFile.txt", "Banks.bin");
            break;
        case 3:
            object.CreateBinFile(fname, "Banks.bin");
            break;
        case 4:
            cout << "Bin File : " << endl;
            object.outBinFile("Banks.bin");
            break;
        case 5:
            FileInHash(ht, "Banks.bin");
            break;
        case 6:
            cout << "input key to delete" << endl;
            DeletingByHash(ht,"Banks.bin");
            break;
        case 7:
            cout << "input key to find" << endl;
            cin >> key;
            FindByHash(ht, key);
            break;
        case 8:
            testHeshT();
            break;
        case 9:
            printFileHashTable(ht);
            break;
        case 0: 
            flag = 1;
            break;
        default:
            cerr << "Invalid input. An integer between 0 and 9 was expected.\n";
            break;
        }
	}
}