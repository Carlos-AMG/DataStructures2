#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cstring>
// #include <vector>
#include "HashTable.h"

//Si nos pasa tamano, borramos todo lo de file y alocamos nuevos recursos
//Si no pasa nada, simplemente leemos nuestro archivo de table

HashTable::HashTable(): vect {std::vector <int> (size, 0)}{
    if (!std::filesystem::exists("./files/file.dat")){
        Student st1;
        std::fstream output ("./files/file.dat", std::ios::binary | std::ios::out);
        if (output.is_open()){
            for (int i = 0; i < 10; i++){
                output.seekp(i * sizeof(Student), std::ios::beg);
                output.write(reinterpret_cast<char *> (&st1), sizeof(Student));
                output.flush();
            }
        }
        output.close();
    }
    std::ifstream input ("./files/table.txt");
    std::string tempSize;
    std::string line;
    std::string index;
    std::string status;
    
    if (input.is_open()){
        getline(input, tempSize, '\n');
        this->size = stoi(tempSize);
        this->vect = std::vector <int> (this->size, 0);
        while (getline(input, line, '\n')){
            // std::stringstream sline(line);
            index = line.substr(0, line.find('-'));
            status = line.substr(line.find('-') + 1, line.length());
            vect[stoi(index)] = stoi(status);
        }
        input.close();
    }
    // calcPercentage();
    // if (percentage >= 70){
    //     doubleTable();
    //     calcPercentage();
    // }
}

int HashTable::__hash(std::string key){
    int myHash = 0;
    for (int i = 0; i < key.length(); i++){
        myHash = (myHash + int(key[i]) * 23) % this->size;
    }
    return myHash;
}

void HashTable::printTable(){
    for (int i = 0; i < vect.size(); i++)
        std::cout << vect[i] << std::endl;
}

void HashTable::setItem(std::string key, std::string className, std::string name){
    // std::fstream output ("./files/file.dat", std::ios::binary | std::ios::out | std::ios::in);    
    int index = __hash(key);

    if (!vect[index]){
        vect[index]++;
        writeItem(index, className, name, key);
    }else{
        vect[index]++;
        int emptyIndex = 0;
        for (int i = index; i < vect.size(); i++){
            if (!vect[i]){
                vect[i]++;
                writeItem(i, className, name, key);
                return;
            }
        }
    }
}

Student HashTable::getItem(std::string key){
    std::ifstream input ("./files/file.dat", std::ios::binary);
    // std::ifstream inputTxt ("./files/table.txt");
    Student temp;
    std::string tempStr;
    int index = __hash(key);
    if (input.is_open()){
        if (vect[index]){
            for (int i = index; i < vect.size(); i++){
                input.seekg(i * sizeof(Student), std::ios::beg);
                input.read((char *) &temp, sizeof(temp));
                tempStr = temp.passwd;
                if (tempStr == key){
                    return temp; 
                }
            }
        }
        return temp;
    }
    input.close();
}

void HashTable::removeItem(std::string key){
    int index = getIndex(key);
    Student temp;
    std::string tempStr;
    int indext;
    std::ifstream input ("./files/file.dat", std::ios::binary);
    // std::fstream output ("./files/file.dat", std::ios::binary | std::ios::out | std::ios::in);    
    for (int i = index; i < vect.size(); i++){
        input.seekg(i * sizeof(Student), std::ios::beg);
        input.read((char *) & temp, sizeof(temp));
        tempStr = temp.passwd;
        if (tempStr == key){
            writeItem(i);
            indext = i;
            vect[i]--;
            break;
        }
    }
    input.close();
    // vect[indext]--;
    // writeItem(index);
    vect[index]--;
}


void HashTable::modifyItem(int index, std::string passwd, std::string className, std::string name){
    // std::fstream output ("./files/file.dat", std::ios::binary | std::ios::out | std::ios::in);    
    writeItem(index, className, name, passwd);
}

int HashTable::getIndex(std::string key){
    std::ifstream input ("./files/file.dat", std::ios::binary);
    Student temp;
    std::string tempStr;
    int index = __hash(key);
    if (input.is_open()){
        if (vect[index]){
            for (int i = index; i < vect.size(); i++){
                input.seekg(i * sizeof(Student), std::ios::beg);
                input.read((char *) & temp, sizeof(temp));
                tempStr = temp.passwd;
                if (tempStr == key){
                    return i;
                }
            }
        }
        return -1;//When there's no data found
    }
    return -2;//When file couldn't open
    input.close();
}


void HashTable::writeItem(int index, std::string className, std::string name, std::string passwd){
    std::fstream output ("./files/file.dat", std::ios::binary | std::ios::out | std::ios::in);    
    Student temp (className, name, passwd);
    if (output.is_open()){
            output.seekp(index * sizeof(Student), std::ios::beg);
            output.write(reinterpret_cast<char *> (&temp), sizeof(Student));
            output.flush();
    }
    output.close();
}

void HashTable::writeItem(int index){
    std::fstream output ("./files/file.dat", std::ios::binary | std::ios::out | std::ios::in);    
    Student temp;
    if (output.is_open()){
            output.seekp(index * sizeof(Student), std::ios::beg);
            output.write(reinterpret_cast<char *> (&temp), sizeof(Student));
            output.flush();
    }
    output.close();
}


void HashTable::calcPercentage(){
    // We count how many elements have been inserted and if it overpasses our treshold, then we duplicate it
    int counter = 0;
    for (int i = 0; i < vect.size(); i++)
        vect[i] ? counter++ : counter;
    this->percentage = (double) counter / size * 100;
    // possible solution, find me another one that makes the function do only one thing
}

void HashTable::doubleTable(){
    for (int i = 0; i < size; i++)
        vect.push_back(false);    
    size = size * 2; //Debemos duplicar el hash.size
    Student st1;
    std::fstream output ("./files/file.dat", std::ios::binary | std::ios::out | std::ios::in);
        if (output.is_open()){
            output.seekp(0, std::ios::end);
            for (int i = size/2; i < size; i++){
                output.seekp(i * sizeof(Student), std::ios::beg);
                output.write(reinterpret_cast<char *> (&st1), sizeof(Student));
            }
            output.close();
        }
}

void HashTable::storeTable(){
    std::ofstream output ("./files/table.txt");
    if (output.is_open()){
        output << this->size << std::endl;
        for (int i = 0; i < this->size; i++){
            output << i << "-" << vect[i] << std::endl;
        }
        output.close();
    }
}

HashTable::~HashTable(){
    storeTable();
}