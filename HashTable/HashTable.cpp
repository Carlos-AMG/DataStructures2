#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
// #include <vector>
#include "HashTable.h"

//Si nos pasa tamano, borramos todo lo de file y alocamos nuevos recursos
//Si no pasa nada, simplemente leemos nuestro archivo de table

HashTable::HashTable(): vect {std::vector <bool> (size, false)}{
    if (!std::filesystem::exists("./files/file.dat")){
        Student st1;
        std::fstream output ("./files/file.dat", std::ios_base::binary | std::ios_base::out);
        if (output.is_open()){
            for (int i = 0; i < 10; i++){
                output.seekp(i * sizeof(Student), std::ios_base::beg);
                output.write(reinterpret_cast<char *> (&st1), sizeof(Student));
            }
            output.close();
        }
    }
    std::ifstream input ("./files/table.txt");
    std::string tempSize;
    std::string line;
    std::string index;
    std::string status;
    
    if (input.is_open()){
        getline(input, tempSize, '\n');
        this->size = stoi(tempSize);
        this->vect = std::vector <bool> (this->size, false);
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
    // std::cout << myHash << std::endl;
    return myHash;
}


void HashTable::printTable(){
    for (int i = 0; i < vect.size(); i++)
        std::cout << vect[i] << std::endl;
}

void HashTable::setItem2(std::string key, std::string className, std::string name){
    std::ifstream tableIn ("./files/table1.txt");
    std::fstream output ("./files/file.dat", std::ios_base::binary | std::ios_base::out | std::ios_base::in);    
    int index = __hash(key);

    std::string line;
    std::vector <std::string> lines;
    std::stringstream helperString;
    std::stringstream indexHelper;

    if (tableIn.is_open()){
        getline(tableIn, line);
        while (getline(tableIn, line)){
            lines.push_back(line);
        }
        tableIn.close();
    }

    if (!vect[index]){
        // std::cout << "it runs" << std::endl;
        writeItem(index, className, name, key, output);
        // Student::Student (std::string className, std::string name, std::string passwd){

        vect[index] = true;
        helperString << key << "|" << index << "|";
        indexHelper << index << "-" << 1 << "*";
        lines[index] = indexHelper.str();
        lines[index].append(helperString.str());
        // std::cout << "================> " << lines[index] << std::endl;
    }else{
        int emptyIndex = 0;
        for (int i = 0; i < vect.size(); i++){
            if (!vect[i]){
                emptyIndex = i;
                vect[i] = true;
                std::cout << "found an empty spot in: " << i << std::endl;
                writeItem(emptyIndex, className, name, key, output);
                break;
            }
        }

        helperString.clear();
        indexHelper.clear();
        helperString << key << "|" << emptyIndex << "|";
        // indexHelper << key << "|" << emptyIndex;
        indexHelper << emptyIndex << "-" << 1 << "*";
        lines[emptyIndex] = indexHelper.str();
        lines[emptyIndex].append(helperString.str());
        lines[index].append(helperString.str());
    }

    // std::cout << "lines-----------> " << lines[index] << std::endl;
    std::ofstream outputTxt ("./files/table1.txt", std::ios::trunc);
    if (outputTxt.is_open()){
        outputTxt << this->size << std::endl;
        for (int i = 0; i < lines.size(); i++){
            outputTxt << lines[i] << std::endl;
        }
        outputTxt.close();
    }
}


Student HashTable::getItem(std::string key, bool flag){
    std::fstream input ("./files/file.dat", std::ios_base::binary | std::ios_base::out | std::ios_base::in);
    std::ifstream inputTxt ("./files/table1.txt");
    Student temp;
    std::string line;
    std::string word;
    std::string tempString;
    std::string keys;
    std::string indices;
    std::string indexBool;
    std::vector <std::string> keyArr;
    int index = __hash(key); 
    // std::cout << "index found: " << index << std::endl;
    if (inputTxt.is_open() && input.is_open()){
        for (int i = 0; i <= index; i++){ //Para iterar hasta la linea
            getline(inputTxt, line, '\n');
        }
        while (getline(inputTxt, line, '\n')){
            indices = line.substr(0, line.find('*'));
            keys = line.substr(line.find('*') + 1);
            indexBool = indices.substr(indices.find("-") + 1);
            std::stringstream s_keys(keys);
            // std::cout << "line: " << line << std::endl;
            // std::cout << "indices: " << indices << std::endl;
            // std::cout << "indexBool: " << indexBool << std::endl;
            if (indexBool == "0"){
                if (flag)
                    std::cout << "Exiting due to no student registered" << std::endl;
                return temp;
            }
            int i = 1;
            while (getline(s_keys, word, '|')){
                keyArr.push_back(word);
                if (i % 2 == 0){
                    // cout << keyArr[0] << " - " << keyArr[1] << endl;
                    if (keyArr[0] == key){
                        // std::cout << "Key: " << keyArr[0] << " found, index: "<<  keyArr[1] << std::endl;
                        if (stoi(keyArr[1]) == index){
                            // std::cout << "Retrieve from current index" << std::endl;
                            input.seekg(stoi(keyArr[1]) * sizeof(Student));
                            input.read((char *) & temp, sizeof(temp));
                        }else{
                            // std::cout << "Go-to index: " << keyArr[1] << std::endl;
                            inputTxt.seekg(0, std::ios::beg);
                            for (int i = 0; i <= stoi(keyArr[1]); i++){ //Para iterar hasta la linea
                                getline(inputTxt, line, '\n');
                            }
                            getline(inputTxt, line, '\n');
                            // std::cout << "line ----------> " << line << std::endl;
                            input.seekg(stoi(keyArr[1]) * sizeof(Student));
                            input.read((char *) & temp, sizeof(temp));
                        }
                        return temp;
                    }
                    keyArr.clear();
                    // break;
                }
                i++;
            }
            // std::cout << "Found" << std::endl;
            // return temp;
        }
    }
    return temp;
}

// Student::Student (std::string className, std::string name, std::string passwd)

void HashTable::writeItem(int index, std::string className, std::string name, std::string passwd, std::fstream & output){
    // std::fstream output ("./files/file.dat", std::ios_base::binary | std::ios_base::out | std::ios_base::in);    
    Student temp (className, name, passwd);
    if (output.is_open()){
            output.seekp(index * sizeof(Student), std::ios_base::beg);
            output.write(reinterpret_cast<char *> (&temp), sizeof(Student));
            output.close();
    }
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
    std::fstream output ("./files/file.dat", std::ios_base::binary | std::ios_base::out | std::ios_base::in);
        if (output.is_open()){
            output.seekp(0, std::ios_base::end);
            for (int i = size/2; i < size; i++){
                // std::cout << "-> " <<  i << std::endl;
                output.seekp(i * sizeof(Student), std::ios_base::beg);
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
            output << i << "-" << vect[i] << "*" << std::endl;
        }
        output.close();
    }
}

HashTable::~HashTable(){
    storeTable();
}