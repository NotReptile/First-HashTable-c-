#include <iostream>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

#define SIZE 10000

using namespace std;

unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
        i += str[j];
    return i % SIZE;
}

struct HashItem {
    char* key;
    char* value;
};

struct HashTable {
    HashItem** items;//массив указателей на items
    int size;
    int count;
};

HashItem* create_item(char* key, char* value) {
    HashItem* item = (HashItem*)malloc(sizeof(HashItem));
    item->key = (char*)malloc(strlen(key) + 1);// выделяем память на ключ
    item->value = (char*)malloc(strlen(value) + 1);//выделяем память на значение
    strcpy(item->key, key);
    strcpy(item->value, value);
    return item; //возврат указателя на item
}

HashTable* create_table(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));//выделяем память для структуры HashTable
    table->size = size;
    table->count = 0;
    table->items = (HashItem**)calloc(table->size, sizeof(HashItem*)); 
    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL; // устанавливаем все элементы хэш таблицы в null
    return table;
}

void free_item(HashItem* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        HashItem* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }
    free(table->items);
    free(table);
}

void hash_insert(HashTable* table, char* key, char* value) {

    HashItem* item = create_item(key, value);
    unsigned long index = hash_function(key);
    HashItem* current_item = table->items[index];

    if (current_item == NULL) {
        if (table->count == table->size) {
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }
        table->items[index] = item;
        table->count++;
    }

    else {
        if (strcmp(current_item->key, key) == 0) {
            strcpy(table->items[index]->value, value);
            return;
        }
        else {
            //Collision
            while (current_item != NULL) {
                cout << "COLLISION!" << endl;
                stringstream strs;
                strs << index;
                string temp_str = strs.str();
                char* indexChar = (char*)temp_str.c_str();
                cout << "Index Char :  " << indexChar << endl;
                if (index == hash_function(indexChar)) {
                    printf("Impossible to generate unique hash\n");
                    free_item(item);
                    return;
                }
                index = hash_function(indexChar);
                cout << "Index after hash func:  " << index << endl;
                current_item = table->items[index];

            }
            table->items[index] = item;
            table->count++;
        }
    }
}

void reHash(HashTable* table) {
     int newSize = table -> size * 2;
     free_table(table);
     create_table(newSize);
}

void hash_delete(HashTable* table, char* key) {
    unsigned long index = hash_function(key);
    HashItem* item = table->items[index];
    HashItem* current_item = table->items[index];

    if (item == NULL) {
        cout << "element doesnt exist" << endl;
        return;
    }
    else {
        table->items[index] = NULL;
        table->count--;
    }
}

char* hash_search(HashTable* table, char* key) {
    int index = hash_function(key);
    HashItem* item = table->items[index];

    if (item != NULL) {
        int flag = 0;
        while (!flag) {
            if (strcmp(item->key, key) == 0) {
                return item->value; // Возвращаем значение если элеменет не NULL
            }
            else {
                int fg = 0;
                while (!fg) { // collision
                    stringstream strs;
                    strs << index;
                    string temp_str = strs.str();
                    char* indexChar = (char*)temp_str.c_str();
                    cout << "Index Char :  " << indexChar << endl;
                    if (index == hash_function(indexChar)) {
                        cout << "element doesn't exist\n";
                        return NULL;
                    }
                    index = hash_function(indexChar);
                    cout << "Index after hash func:  " << index << endl;
                    item = table->items[index];
                    if (item != nullptr) {
                        fg = 1;
                    }


                }
            }
        }
    }
    return NULL; // Если не находим - вернуть NULL
}

void print_search(HashTable* table, char* key) {
    char* val;
    if ((val = hash_search(table, key)) == NULL) {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

void print_table(HashTable* table) {
    printf("\nHash Table\n-------------------\n");
    for (int i = 0; i < table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, table->items[i]->value);
        }
    }
    printf("-------------------\n\n");
}
int testHeshT() {
    HashTable* ht = create_table(SIZE);
    cout << "==========================" << endl;
    cout << "===== add first elem =====" << endl;
    char num[15] = "23"; // hash 101
    char adress[20] = "first address";
    hash_insert(ht, num, adress);
    print_table(ht);
    cout << "===== search first elem ==" << endl;
    print_search(ht, num);
    cout << endl;

    cout << "==========================" << endl;
    cout << "===== add second elem ====" << endl;
    char num3[15] = "101"; // hash 146
    char adress3[20] = "test address";
    hash_insert(ht, num3, adress3);
    print_table(ht);
    cout << "===== search second elem =" << endl;
    print_search(ht, num3);
    cout << endl;

    cout << "==========================" << endl;
    cout << "===== add thrid elem =====" << endl;
    char num2[15] = "32"; // hash 101 -> 146 -> 155
    char adress2[20] = "second address";
    hash_insert(ht, num2, adress2);
    print_table(ht);
    cout << "===== search thrid elem ==" << endl;
    print_search(ht, num2);
    cout << endl;

    cout << "==========================" << endl;
    cout << "===== deleting second elem" << endl;
    hash_delete(ht, num3);// удаляем 2 элемент 
    cout << "===== search thrid elem ==" << endl;
    print_search(ht, num2);// выполняем поиск третьего элемента (хэш 1ого 101 | хэш второго(удаленного) 101 -> 146 | хэш третьего 101 -> 146 -> 155) проверяем не найдет ли он пустое место на месте с хэшем 146 
    cout << endl;

    cout << "==========================" << endl;
    cout << "===== add fourth elem ====" << endl;
    char num4[15] = "200";
    char adress4[20] = "newTest address";
    hash_insert(ht, num4, adress4);// добавляем четвертый элемент со значением 200 | хэшем 146
    print_table(ht);
    cout << "===== search fourth elem =" << endl;
    print_search(ht, num4);


    cout << endl << endl;
    cout << "FINAL HASH TABLE";
    print_table(ht);


    free_table(ht);// удаляем таблицу
    return 0;
}