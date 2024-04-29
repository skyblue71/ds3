#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct StudentData {
    char sid[10];  // 學號
    char sname[10]; // 姓名
    unsigned char scores[6]; // 分數
    float averagescores; // 平均分數
};

int main() {
    string inputFile = "input302.txt";
    string outputFile = "input302.bin";

    ifstream textFile(inputFile.c_str());
    if (!textFile) {
        cout << "Failed to open input file!" << endl;
        return 1;
    }

    ofstream binFile(outputFile.c_str(), ios::binary);
    if (!binFile) {
        cout << "Failed to open output file!" << endl;
        return 1;
    }

    StudentData sd;
    int score;

    while (textFile >> setw(10) >> sd.sid >> setw(10) >> sd.sname >> score) {
        
        sd.sid[9] = '\0';
        sd.sname[9] = '\0';
        sd.scores[0] = static_cast<unsigned char>(score);
        for (int i = 1; i < 6; i++) {
            textFile >> score;
            sd.scores[i] = static_cast<unsigned char>(score);
        }
        textFile >> sd.averagescores;

        binFile.write(reinterpret_cast<char*>(&sd), sizeof(sd));
    }

    textFile.close();
    binFile.close();

    return 0;
}


