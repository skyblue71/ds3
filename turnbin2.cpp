#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

struct StudentData {
    char sid[10];   // 學號
    char sname[10]; // 姓名
    unsigned char scores[6]; // 分數
    float averagescores; // 平均分數
};

int main() {
    string inputFile = "input301.txt";
    string outputFile = "input301.bin";

    ifstream textFile(inputFile);
    if (!textFile.is_open()) {
        cout << "Failed to open input file!" << endl;
        return 1;
    }

    ofstream binFile(outputFile, ios::binary);
    if (!binFile.is_open()) {
        cout << "Failed to open output file!" << endl;
        return 1;
    }

    string line;
    int score;
	StudentData sd;
   
    while (textFile >> setw(10) >> sd.sid) {
        getline(textFile, line);  
        stringstream ss(line);
        string name;

        getline(ss, name, '\t');
        strncpy(sd.sname, name.c_str(), sizeof(sd.sname) - 1);
        sd.sname[sizeof(sd.sname) - 1] = '\0'; 

        for (int i = 0; i < 6; i++) {
            ss >> score;
            sd.scores[i] = static_cast<unsigned char>(score);
        }
        ss >> sd.averagescores;

        binFile.write(reinterpret_cast<const char*>(&sd), sizeof(sd));
    }

    textFile.close();
    binFile.close();

    return 0;
}