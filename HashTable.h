#ifndef INC_1_2_HASHTABLE_H
#define INC_1_2_HASHTABLE_H

#include <iostream>
#include <string>
#include <list>
#include <vector>

#include "Clients_comparasion.h"

class HashTable {
private:
    int tableSize;
    struct Entry{
        int key;
        std::string value;
        int status;

        Entry(): status(0){};
    };
    std::list<Entry>* table;  //key,value,status

public:
    HashTable(int size) : tableSize(size) {
        table = new std::list<Entry>[tableSize];
    }
    bool isEmpty() const;
    int hf1(const Person& person);
    int hf2(int hash1,int trial,const int tableSize);
    void add(const Person& person);
    void remove(const Person& person);
    void search(const Person& person);
    void print();
    void helpDel(int hash);
    void solution(int hash, Entry newEntry,const Person& person, int n);
    void replace(int i);
    ~HashTable() {
        delete[] table;
    }
};

bool HashTable::isEmpty() const{
    int sum{};
    for (int i{}; i < tableSize; i++){
        sum += table[i].size();
    }

    if (!sum) {
        return true;
    }
    return false;
}

//int ASCIIWordSum(string str)
//{
//    int l = str.length();
//    int sum = 0;
//    int bigSum = 0;
//    for (int i = 0; i < l; i++) {
//
//        sum +=  str[i];
//    }
//
//    bigSum += sum;
//    return bigSum;
//}

int HashTable::hf1(const Person& person){
//    std::string line = fio.F + fio.I + fio.O;
    int hash = 0;
    int key = person.getNUM().number;
    while (key > 0){
        hash += key % 1000;
        key = (key-key % 1000) / 1000;
    }

    return hash % tableSize;

};
int HashTable::hf2(int hash1,int trial,const int tableSize){
    return ((hash1 + trial * 1) % tableSize);
};

void HashTable::solution(int hash, Entry newEntry,const Person& person, int n){
    int trial = 1;


        if (n == 1){
            while (trial < tableSize) {
                int index = hf2(hash, trial, tableSize);
                if (table[index].empty() || table[index].front().status == 0) {
                    //newEntry.key = index;
                    table[index].clear();
                    table[index].push_front(newEntry);
                    return;
                }
                trial++;
            }
        }
        if (n == 2){
            int trial = 1;
//            std::string line = room.letter + to_string(room.digit) + " " + fio.F + " " + fio.I + " " + fio.O + " " + to_string(time.hour) + " " + to_string(time.minute);
            std::string line = std::to_string(person.getNUM().number) + " " + person.getFIO().surname + " " + person.getFIO().name + " " + person.getFIO().f_name + " "
                    + std::to_string(person.getDB().day) + "." + std::to_string(person.getDB().month)
                    + "." + std::to_string(person.getDB().year) + " " + person.getADRESS().address;
            while (trial < tableSize) {
                int index = hf2(hash, trial, tableSize);
                if (!table[index].empty()) {
                    if (table[index].front().status == 1) {
                        Entry &entry = table[index].front();
                        if (table[index].front().value == line) {
                            // Mark the entry as deleted
                            entry.status = 0;
                            std::cout << "Удалено: " << entry.value << std::endl;
                            helpDel(index);
                            return;
                        }
                    }
                }

                trial++;
            }

        }
        if (n == 3){
            std::string line = std::to_string(person.getNUM().number) + " " + person.getFIO().surname + " " + person.getFIO().name + " " + person.getFIO().f_name + " "
                               + std::to_string(person.getDB().day) + "." + std::to_string(person.getDB().month)
                               + "." + std::to_string(person.getDB().year) + " " + person.getADRESS().address;
            while (trial < tableSize) {
                int index = hf2(hash, trial, tableSize);
                // Check if the entry at the index matches the given FIOs and time
                if (!table[index].empty() && table[index].front().status != 0) {
                    Entry& entry = table[index].front();
                    if (entry.value == line)  {
                        std::cout << "Найдено: " << entry.value << std::endl;
                        return;
                    }
                }
                trial++;
            }
        }


    if (trial >= tableSize) {
        std::cout << "ERROR" << std::endl;
    }
}

void HashTable::add(const Person&person) {
    int hash = hf1(person);
    Entry newEntry;
    std::string line = std::to_string(person.getNUM().number) + " " + person.getFIO().surname + " " + person.getFIO().name + " " + person.getFIO().f_name + " "
                       + std::to_string(person.getDB().day) + "." + std::to_string(person.getDB().month)
                       + "." + std::to_string(person.getDB().year) + " " + person.getADRESS().address;
    newEntry.value = line;
    newEntry.status = 1;
    newEntry.key = hash;
    for (int i = 0; i < tableSize;i++) {
        // Check if an entry with the same key exists
        for (auto &entry: table[i]) {
            if (entry.value == newEntry.value && entry.status == 1) {
                std::cout << "Невозможно добавить! Такая запись уже есть!" << std::endl;
                return;
            }
        }
    }
    //std::cout << hash << std::endl;
    if (table[hash].empty() || table[hash].front().status == 0){
        //newEntry.key = hash;
        table[hash].clear();
        table[hash].push_front(newEntry);
        return;
    }
    else{
        solution(hash, newEntry, person, 1);
    }
}

//
//void HashTable::helpDel(int hash){
//    int last = hash;
//    int k = hash;
//    int i = 0;
//
//
//    for (int i = hash; i < tableSize;i++){
//        k = k + 1;
//        if (table[i].front().key != table[hash].front().key && i < tableSize){
//            table[hash].front() = table[i-1].front();
//            table[i-1].clear();
//            swap(table[i-1],table[i]);
////            while (i < tableSize){
////                table[i-1] = table[i];
////                i = i + 1;
////            }
//            return;
//        }
////        if (i == tableSize && table[i].front().key == table[hash].front().key)
////        {
////            hash = 0;
////
////            goto flag;
////        }
//
//    }
//
//
//
//
//
//
//    if (k >= tableSize) {
//        table[last].clear();
//        //return;
//    }
//}

void HashTable::helpDel(int hash) {
    int counter = 1;
    int tempIndex = 0;
    bool found = false;

    do {
        int index = hf2(hash, counter, tableSize);
        if (!table[index].empty() && table[index].front().status != 0) {
            if (table[index].front().key != table[hash].front().key) {
                tempIndex = index - 1;
                if (tempIndex < 0)
                    tempIndex = tempIndex + tableSize;
                found = true;
            }
        }
        counter++;
    } while (counter <= tableSize && !found && table[hash].front().status != 0);

    table[hash] = table[tempIndex];
    table[tempIndex].clear();

    int trial = 0;
    int i = 0;
    while (i < tableSize) {
        int suphash = hf2(table[i].front().key, trial, tableSize);
        if (table[i].front().key != i && table[suphash].empty()) {
            table[suphash] = table[i];
            table[i].clear();
        }
        i++;
    }
}

void HashTable::remove(const Person&person) {
    int hash = hf1(person);
    Entry& entry = table[hash].front();
    std::string inputline = std::to_string(person.getNUM().number) + " " + person.getFIO().surname + " " + person.getFIO().name + " " + person.getFIO().f_name + " "
                       + std::to_string(person.getDB().day) + "." + std::to_string(person.getDB().month)
                       + "." + std::to_string(person.getDB().year) + " " + person.getADRESS().address;
    if (isEmpty() == false) {
        if (entry.status == 1 && entry.value == inputline) {
            //entry.status = 0;
            std::cout << "Удалено: " << entry.value << std::endl;
            helpDel(hash);
            //return;
        } else if (entry.status == 0 || entry.value != inputline || table[hash].empty()) {
            bool found = false;
            solution(hash, entry, person, 2);
            if (found == false) {
                std::cout << "Запись не найдена" << std::endl;
            }
        }
    }
    if (isEmpty()== true){
        std::cout << "Таблица пустая" << std::endl;
    }
}

void HashTable::search(const Person&person) {
    int hash = hf1(person);
    int trial = 0;
    int rehash = hash;
    std::string line = std::to_string(person.getNUM().number) + " " + person.getFIO().surname + " " + person.getFIO().name + " " + person.getFIO().f_name + " "
                       + std::to_string(person.getDB().day) + "." + std::to_string(person.getDB().month)
                       + "." + std::to_string(person.getDB().year) + " " + person.getADRESS().address;

    while (!table[rehash].empty() && trial < tableSize) {
        Entry& entry = table[hash].front();
//        if (!table[hash].empty() && table[hash].front().status == 1) {
        if (entry.key == hash && entry.value == line && table[rehash].front().status == 1) {
            std::cout << "Найдено: " << entry.value << std::endl;
            return;
        }
        trial++;
        rehash = hf2(hash,trial,tableSize);

        //hash = hf2(hash,trial,tableSize);

        //}
    }
    if (table[rehash].empty() || trial >= tableSize){
        std::cout << "Такого элемента нет" << std::endl;
        return;
    }
}

void HashTable::print() {
    //std::cout << "       Hash1 " << "                Value          " << "      Status " << std::endl;
    for (int i = 0; i < tableSize; i++) {
        std::cout <<"[" <<i << "]" <<" ";
        for (auto& entry : table[i]) {
            std::cout << "     " <<entry.key << "   " << entry.value;
        }
        std::cout << std::endl;
    }
}

#endif //INC_1_2_HASHTABLE_H
