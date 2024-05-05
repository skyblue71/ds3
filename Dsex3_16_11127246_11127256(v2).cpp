//11127246 ≥Ø¨f o 11127256 øΩ§—ªy
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>
#include <iostream>
#include <cmath>

#define  COLUMNS 6
#define  MAX_LEN 10
#define  BIG_INT 255


using namespace std;






struct student{
    char sid[MAX_LEN];
    char sname[MAX_LEN];
    unsigned char score[COLUMNS];                       // there are total six scores
    float average;                                      // average score




};

int compareStudent(const student& p1, const student& p2) {
    if ( p1.sid == p2.sid && p1.sname == p2.sname && p1.average == p2.average )
        return 1;
    return 0;
}




class HashTable{
    private:
        string fileName;
        vector<student> students;
        bool binCreate;
        // two methods for trans to binary

public:
    static string floatToBinary( float f );
    static string charToBinary(char c) ;
    static string transCAtoBinary( char cA[] );
    static string transINTtoBinary(int num);
    static string transDectoBinary( float f );
    static string transStrtoBinary( string str );
    bool readBinary() ;
    int readFile( );                                // output a bin and return a num of st
    static string removepunctuation( string& input);
    void OutputBin( );
    void reset();
    void HasTable();


    void QuadraticProbing();

    bool isPrime(int num);

    bool hash_ascii(pair<int, student> *pPair, int it, student student1, int size);


    void outputFile( string str, pair<int, student> *pPair, int size);

    float unsuccessAvl( pair<int, student>  *pPair, int size);


    float successAVL( pair<int, student> *pPair, int size );

    void doubleHash();

    template<typename T>
    int getHigherPrime(T d );

    void genDoubleHash(pair<int, student> *pPair, int index, int size, int mostHigh);

    float successAVLHash(pair<int, student> *pPair, int size );

    bool isEmpty();
};



int main(){
    string fileName;
    int command = -1;
    HashTable *hashTable = new HashTable() ;

    do {
        cout << "\n******* Hash Table *****" << endl;
        cout << "* 0. QUIT              *" << endl;
        cout << "* 1. Quadratic probing *" << endl;
        cout << "* 2. Double hashing    *" << endl;
        cout << "************************" << endl;
        cout << "Input a choice(0, 1, 2): ";
        cin >> command;
        switch ( command ) {
            case 0:
                return 0;


            case 1:{
               hashTable -> reset();                // reset all in hashtable
                if (hashTable -> readBinary())           // readBinary if there's no bin it find .txt
                    hashTable -> QuadraticProbing();
                break;

            }
            case 2:{
                if ( hashTable -> isEmpty() ) {
                    cout << "### Command 1 first. ###" << endl;
                    break;
                }
                hashTable -> doubleHash();
                break;
            }

            default:{

                cout << "Command does not exist!" << endl;
                break;
            }
        }

    } while ( command != 0);



}

















int HashTable::readFile(){						// declaration: read all from a file
    fstream inFile, outFile;                                // declare input and output file
    int stNo = 0;
    do {

        if ( !fileName.compare("0") )               // input 0 then stop this program
            return false;
        inFile.open( ("input" + fileName + ".txt").c_str(), fstream::in );   // trans inputXXX.txt to c char arr
        if ( inFile.is_open())                   // success find a file so no need to loop
            break;
        else{
            cout  << " ### "<< "input" + fileName + ".txt does not exist! ###" << endl;
            return 0;
        }
    } while (true);                             // end  while
    string fileNameBin = "input" + fileName + ".bin";
    outFile.open( fileNameBin.c_str(), fstream::out | fstream::binary );   // open a file and out binary use enum and or
    if ( outFile.is_open()){
        char rBuf[ BIG_INT ];
        while ( inFile.getline( rBuf, BIG_INT, '\n')){
            string temp ;
            student oneSt;
            int      cNO = 0;
            int      pre = 0;
            int      pos = 0;// cNO is use for input case, pre and pos is for substring
            stNo++;                             // num of students
            temp.assign( rBuf );                // assign char[] rBuf to string temp
            pos = temp.find_first_of( '\t', pre ) ;  // return '\t' position in string temp
            while ( pos != string::npos ){

                switch (++cNO) {
                    case 1: {
                        strcpy(oneSt.sid, temp.substr(pre, pos - pre).c_str());
                        break;
                    }
                    case 2: {
                        strcpy(oneSt.sname, temp.substr(pre, pos - pre).c_str());
                        break;
                    }
                    default:{
                        oneSt.score[cNO - 3 ] = atoi( temp.substr( pre, pos - pre ).c_str() );
                        break;
                    }


                }      // end switch
                pre = ++ pos;                           // move pre to a new begin
                pos = temp.find_first_of('\t', pre );   // move pos to a new '\t'
            }   // inner while

            pos = temp.find_last_of('\t');
            oneSt.average = atof( temp.substr( pos + 1 ).c_str() );
            outFile.write( (char*)& oneSt, sizeof(oneSt) ); // write this stu to binary file
        }
        outFile.close();                                // end of write
    }
    inFile.close();                                     // end of read
    return stNo;

} //end readFile







 string HashTable:: removepunctuation( string& input) {						// remove punctuation in data
string output;
for ( char i : input ) {
    if (i != ',' && i != '"' && i != ' ' ) {
        output += i;
    }
}
return output;
}

void HashTable::reset() {
    this ->fileName.clear();
    this ->binCreate = false;
    this ->students.clear();
}

void HashTable::OutputBin()  {
    if (  binCreate  ){
        return;
    }
    ofstream out( "input301.bin");
    /// if not create a bin

    for ( student s : students ) {
       out << transCAtoBinary( s.sid );
       out << transCAtoBinary( s.sname );

       out << floatToBinary( s.average );

    }

    binCreate = true;
}




string HashTable::transCAtoBinary( char  cA[] ) {
    string  binaryString;
    for ( int i = 0; i < 10; i++  ) {
        if ( cA[i] == '\0' ) {
            break;
        }
        binaryString = binaryString + charToBinary( cA[i] ) + " ";
    }
    return  binaryString  ;
}

string HashTable::transINTtoBinary(  int num  ) {
    string num_binary;
    while ( num > 0 ){
        num_binary = to_string( num % 2 ) + num_binary;
        num = num / 2 ;
    }
    string binary;
    for ( char c : num_binary ) {
        binary = binary + charToBinary( c ) + " " ;
    }
   // binary.replace( binary.size() - 1, binary.size() - 1, "" );

    return binary;
}



string HashTable::charToBinary(char c) {
    std::string result;
    for (int i = 7; i >= 0; --i) {
        // triple operate if with right shift operation
        result += ((c >> i) & 1) ? '1' : '0';
    }

    return result;
}

string HashTable::floatToBinary(float f) {
    /// process > 1 part
    string integerPart = transINTtoBinary((int )f);

    /// decimal part is all part - integer part
    string decimalPart = transDectoBinary( f - (int )f  );
    /// if no decimal part
    if ( (int) f == f  ){
        return integerPart;
    }

    return integerPart + decimalPart;
}

string HashTable::transDectoBinary(float f) {
    string  binary = "";
    // if f == 0 then break this loop
    if ( f == 0 ){

        return binary;
    }
    while ( f != 0 ){
        f *= 2;
        if ( f >= 1 ){
            binary += "1";
            f--;
        }
        else{
            binary += "0";
        }

    }



    /// return . and binary
    return "00101110" + transStrtoBinary(binary );
}

string HashTable::transStrtoBinary(string str ) {
    string  binary = "";
    for ( char  c: str ) {
        binary = binary + charToBinary( c ) + " ";
    }


    return binary;
}



bool HashTable::readBinary( ) {
    fstream  binFile;                   // input bin
    student oneSt;
    int     stNo;
    cout << "Input a file number: ";
    cin >> fileName;
    if ( fileName == "0" )
        return false;

    string binFileName =   "input" + fileName + ".bin";

    binFile.open( binFileName.c_str(), fstream::in | fstream::binary) ; // similar output but this time is in
    if ( binFile.is_open() ){
        binFile.seekg(0, binFile.end);              // get the size of this file
        stNo = binFile.tellg() / sizeof( oneSt );   // get nums of this students
        binFile.seekg(0, binFile.beg );             // back to the begining of this file
        for (int i = 0; i < stNo ; i++ ) {          // loop nums of students
            binFile.read( (char *)&oneSt, sizeof( oneSt ) );    // read t
            students.push_back( oneSt );
        }   // end of

    }       // end if
    else{
        cout << "### input" + fileName + ".bin does not exist! ###" << endl << endl;

        if (!readFile()){
            binFile.close();
            return false;
        }
    }
    binFile.close();
    return true;

}

void HashTable::QuadraticProbing() {
    int hashTableSize = students.size() * 1.3;
    while (true ) {
        hashTableSize++;
        if ( isPrime( hashTableSize ) ){
            break;
        }
    }
    pair<int,student> myPair[ hashTableSize ];// array for store hash table
    for ( int i = 0 ; i < students.size(); i++ ) {
        hash_ascii(myPair, i+1, students[i], hashTableSize );
    }

    cout << "Hash table has been successfully created by Quadratic probing" << endl;
    cout << " unsuccessful search: " << unsuccessAvl( myPair, hashTableSize ) << " comparisons on average" << endl;
    cout << " successful search: " << successAVL(  myPair, hashTableSize )  <<  " comparisons on average" << endl;
    outputFile(  "quadratic", myPair, hashTableSize );


}

bool HashTable::isPrime(int num ) {
    int numOfFactors = 0;            /// numOfFactors

    for (int i = 1; i <= num / 2; i++) {
        if (num % i == 0) {
            numOfFactors++;
        }
    }

    return numOfFactors == 1;
}

bool HashTable::hash_ascii(pair<int, student> *pPair, int itOfData, student student1, int size ) {
    double ascii_muti = 1;
    for (int i : student1.sid ) {
        if ( i < 48 || i > 57 )
            break;
    ascii_muti = ascii_muti * i;
    }
    int t = 0;              // seearch times
    do {
        double prob = ascii_muti + t*t ;
        if ( pPair[ (int)fmod(prob, size) ].first == 0 ){

            pPair[(int)fmod(prob, size) ].first = (int)fmod(ascii_muti, size);
            pPair[(int)fmod(prob, size)  ].second = student1;
            return true ;
        }
        t++;
    } while (true );
    return false;

}

void HashTable::outputFile( string str , pair<int, student> *pPair, int size ) {
    ofstream outFile(  str + fileName +".txt" );
    if (!outFile.is_open()) {
        cout << "Failed to open the file." << endl;
        return;
    }
    if ( str == "quadratic" )
        outFile <<"--- Hash table has been successfully created by Quadratic probing ---" << endl;
    else if ( str == "double" )
        outFile <<"--- Hash table has been successfully created by Double hashing ---" << endl;


    for (int i = 0; i < size ; i++ ) {
        outFile << "[ " << i << "] ";
        if (  pPair[i].first != 0 )         // check if there is nothing
            outFile << pPair[i].first << ",\t" << pPair[i].second.sid << ",\t" << pPair[i].second.sname << ",\t" << pPair[i].second.average << endl;
        else
            outFile << endl;
    }
      outFile <<"------------------------------------------------------------------" << endl;
}

float HashTable::unsuccessAvl( pair<int, student> *pPair, int size ) {
    int times[ size ] ;
    // fill times with 0
    fill( times, times+ size, 0);
    for( int i = 0 ; i < size ; i++ ){
        if ( pPair[ i ].first == 0 )
            continue;
        int t = 0;              // seearch times
        do {
            double prob = i +  t*t ;
            if (pPair[ (int)fmod( prob, (double )size )  ].first ==  0  ){
                times[i] = t;
                break;
            }
            t++;
        } while ( true );


    }




    float sum = 0;
    int value_num = 0;
    for (int i = 0; i < size ; i++ ) {
        sum = sum + (float )times[i];
        value_num++;
    }


    // get int previous . so multiply 10000 round it and divide back
     return   round(( sum / (float ) value_num ) * 10000) / 10000;
}







float HashTable::successAVL( pair<int, student> *pPair, int size ) {
    int times[ size ] ;
    fill( times, times+ size, 0);
    for( int i = 0 ; i < size ; i++ ){
        double ascii_muti = 1;
        if ( pPair[i].first != 0 ){
            for (int j : pPair[i].second.sid ) {
                if ( j < 48 || j > 57 )
                    continue;
                ascii_muti = ascii_muti * j;
            }
            int t = 0;              // seearch times
            do {
                double prob = ascii_muti + t*t ;
                if (compareStudent(pPair[ (int)fmod(prob, size) ].second , pPair[i].second ) ){
                    t++;
                    times[i] = t;
                    break;
                }
                t++;
            } while ( true );


        }

    }

    float avg = 0;
    int value_num = 0;
    for (int i = 0; i < size ; i++ ) {
        if ( times[i] == 0 )
            continue;
        avg = avg + (float )times[i];
        value_num++;
    }


            // get int previous . so multiply 10000 round it and divide back
    return   round(( avg / (float )value_num ) * 10000) / 10000;
}

void HashTable::doubleHash() {
    int mostHigh =getHigherPrime( students.size() / 2 ) ;
    int hashTableSize = getHigherPrime(students.size() * 1.3 );
    pair<int,student> myPair[ hashTableSize ];// array for store hash table

    for ( int i = 0 ; i < students.size(); i++ ) {
        genDoubleHash( myPair,  i ,hashTableSize, mostHigh );
    }

    cout << "Hash table has been successfully created by Double hashing" << endl;
    cout << " successful search: " << successAVLHash(  myPair, hashTableSize )  <<  " comparisons on average" << endl;
    outputFile( "double", myPair, hashTableSize );


}

void HashTable::genDoubleHash(pair<int, student> *pPair, int index, int size, int mosthigh ) {
    bool isFull = true;
    for (int i = 0; i < size ; i++) {
        if ( pPair[i].first == 0 )
            isFull = false;
    }
    if ( isFull ){
        cout << "hashTable is full " << endl;
        return;
    }
    // full check

    double hash_ascii = 1;
    for (int c : students[index].sid ) {
        if ( c >= 48 && c <= 57 )
         hash_ascii = hash_ascii * c;
    }


    int init = int(fmod( hash_ascii, size));
    int step = 0;
    int step_num = 1;
    int prob = init;
    do{
        if ( pPair[prob].first == 0 ){
            pPair[prob].first = init;
            pPair[prob].second = students[index];
            return;
        }
        step = mosthigh - int(fmod( hash_ascii, mosthigh ));
        prob = ( init + step * step_num ) % size;
        step_num++;

    }    while ( pPair[init].first != 0 );




}

float HashTable::successAVLHash(pair<int, student> *pPair, int size) {
    int times[ size ] ;
    int mostHigh =getHigherPrime( students.size() / 2 ) ;
    fill( times, times+ size, 0);
    for( int i = 0 ; i < size ; i++ ){
        double ascii_muti = 1;
        if ( pPair[i].first != 0 ){
            for (int j : pPair[i].second.sid ) {
                if ( j < 48 || j > 57 )
                    continue;
                ascii_muti = ascii_muti * j;
            }
            int t = 0;              // seearch times
            do {
                double prob = fmod(ascii_muti, size ) + t*( mostHigh - fmod( ascii_muti, mostHigh) ) ;
                if (compareStudent(pPair[ (int)fmod(prob, size) ].second , pPair[i].second ) ){
                    t++;
                    times[i] = t;
                    break;
                }
                t++;
            } while ( true );


        }

    }

    float avg = 0;
    float value_num = 0;
    for (int i = 0; i < size ; i++ ) {
        if ( times[i] == 0 )
            continue;
        avg = avg + (float )times[i];
        value_num++;
    }

    // get int previous . so multiply 10000 round it and divide back
    return   round(( avg / (float )value_num ) * 10000) / 10000;

}

bool HashTable::isEmpty() {
    if ( students.empty() )
        return true;

    return false;
}

template<typename T>
int HashTable::getHigherPrime( T d ) {
    while (true ) {
        d++;
        if ( isPrime( d ) ){
            return  d;
        }
    }
    return 0;
}
// end readBinary




