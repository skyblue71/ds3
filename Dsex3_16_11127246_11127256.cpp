
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
using namespace std;







struct student{
    char sid[10];
    char sname[10];
    int  score0;
    int  score1;
    int  score2;
    int  score3;
    int  score4;
    int  score5;
    float average;


};



class HashTable{
    private:
        string fileID;
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
    bool readFile( string id );
    static string removepunctuation( string& input);
    void OutputBin( );
    void reset();
    void HasTable();






};

int main(){
    string id ;
    cin >> id;
    HashTable *hashTable = new HashTable();
    hashTable->readFile( id );
    hashTable->OutputBin();
    hashTable-> reset();
    return 0;
}

















bool HashTable::readFile(string id){						// declaration: read all from a file
    fstream	inFile;								// file handle
    string 	fileName;							// file name
    reset();
    fileID = id;
    fileName = "input"+id+".txt";
    inFile.open(fileName.c_str(), fstream::in );	// open file to read
    if (!inFile.is_open())						// unable to open file
    { 	cout<<endl<< "### " << fileName << " does not exist!###" << endl;
        return false;
    } //end if
    else
    { 	char	cstr[255];							// input buffer of one line as c-string
        int		fNo, pre, pos;
        while (inFile.getline(cstr, 255, '\n'))		// get all records line by line
        {	student oneR ;						// one data record
            string buf, cut;						// transform c-string into C++ string
            fNo=0; 									// number of fields read so far
            pre=0;									// locate one field of input record
            buf.assign(cstr);						// copy c-string into C++ string
            do										// scan the buffer from left to right
            { 	pos = buf.find_first_of('\t', pre);	// locate the next field by '\t' (tab)
                cut=buf.substr(pre, pos- pre);		// retrieve a field

                switch (++fNo)
                {
                    case 1: {

                        strcpy(oneR.sid, cut.c_str() + '\0' );
                        break;
                    }
                    case 2:    strcpy(oneR.sname, cut.c_str())  ;	// get the school name
                        break;
                    case 3:    oneR.score0 = atoi( cut.c_str() );		// get the department name
                        break;
                    case 4:    oneR.score1 = atoi( cut.c_str() );		// get the department name
                        break;
                    case 5:     oneR.score2 = atoi( cut.c_str() );				// get either day or night
                        break;
                    case 6:     oneR.score3 = atoi( cut.c_str() );				// get graduate or undergraduate
                        break;
                    case 7:     oneR.score4 = atoi( cut.c_str() );	// get the number of students
                        break;
                    case 8:     oneR.score5 = atoi( cut.c_str() );	// get the number of professors
                        break;
                    case 9:     oneR.average = atoi( cut.c_str() );	// get the number of graduates
                        break;

                    default: break;
                } //end switch
                pre = ++pos;								// move to the next field
            } while ((pos > 0) && (fNo <10));				// continue if there are still fields to be read
            this ->students.push_back( oneR );			// save one record into the school list
        } //end outer-while

        inFile.close();							// close file
    } // end else
    //if (!this->allR.size())
    //{ 	cout <<endl<< "### Get nothing from the file "<< fileName << "!###"<< endl;
    //	return false;
    //} //end if
    return true;
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
    this ->fileID.clear();
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
       out << transINTtoBinary( s.score0 );
       out << transINTtoBinary( s.score2 );
       out << transINTtoBinary( s.score3 );
       out << transINTtoBinary( s.score4 );
       out << transINTtoBinary( s.score5 );
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

void HashTable::HasTable() {

    bool binCreate = false;


}




