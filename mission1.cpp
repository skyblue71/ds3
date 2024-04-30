
#include <iostream> // cout, endl
#include <fstream> // open, is open, close, write, ignore 
#include <string> // string, find_last_of, substr, clear 
#include <cstdlib> // atoi, system 
#include <iomanip> // setw 
#include <cstring> // strcpy 
#include <cmath> 
#include <cstring>
#include <vector>
using namespace std; 
#define COLUMNS 6 // number of scores for each student 

#define MAX_LEN 10 // array size of student id and name 

#define BIG_INT 255 // integer upper bound 


typedef struct ST {// type of a student record 
	char sid[MAX_LEN]; // student id 
	char sname[MAX_LEN]; // student name 
	unsigned char score[COLUMNS]; // a set of scores in [0, 100] 
	float mean; // the average of scores 
} studentType; 


string Text2Binary(  ); 
void readBinary( string fileName ); 
bool binexist( string fileName );

string Text2Binary(  ) // get records from a text file & save as a binary file 
{ 	string fileName;
	fstream inFile, outFile; // file handles 
	int stNo = 0;  
	cout << "\nInput a file number ([0] Quit): "; 
	cin>> fileName; 
	if (!fileName.compare("0")) // No file to open, so quit 
		return "0"; 		 
	inFile.open(("input" + fileName + ".txt").c_str(), fstream::in); // open a file 
	if (!inFile.is_open()) {
		cout << "\n### input" + fileName + ".bin does not exist! ###" << endl;
		cout << "\n### input" + fileName + ".txt does not exist! ###" << endl;
		return "0"; // successfully open a file, so leave the loop
	}
	
	string namecopy = fileName;
	fileName = "input" + fileName + ".bin";
	if( !binexist( fileName )) 
		cout << "\n### " << fileName << " does not exist! ###" << endl; 
	
		
	outFile.open(fileName.c_str(), fstream:: out | fstream::binary); // create a binary file
	if (outFile.is_open()) 
	{   char rBuf[BIG_INT]; // buffer to keep one whole record		
		while (inFile.getline(rBuf, BIG_INT, '\n')) // retrieve one entire record from file 
		{ 	string temp;	// duplicate a string in another format
			studentType oneSt; // keep one record with all the required fields
			int cNo = 0, pre = 0, pos = 0; // indicators to extract each field in a record 
			stNo++;		// number of records	
 			temp.assign(rBuf);		// make a duplicate of the entire record
 			pos = temp.find_first_of("\t", pre); // move to the end of the first field
			
			while (pos != string::npos) 
			{ 	switch (++cNo) 
				{ 	case 1: strcpy(oneSt.sid, temp.substr(pre, pos - pre).c_str()); 
						break; // copy a student id
			 
					case 2: strcpy(oneSt.sname, temp.substr(pre, pos - pre).c_str()); 
						break; // copy a student name 
			
					default: oneSt.score[cNo-3] = atoi(temp.substr(pre, pos - pre).c_str()); 
						break; 	// copy each score
				} //end switch 
				pre = ++pos; 		 
				pos = temp.find_first_of("\t", pre); // move to the end of the next field 
			} //end inner while 
			
			pos = temp.find_last_of("\t"); // position of the rightmost tab
			 
			oneSt.mean = atof(temp.substr(pos+1).c_str()); // copy the average score 

			outFile.write((char *)&oneSt, sizeof(oneSt));// write the entire record into a binary file 
		} //end outer while 
		outFile.close(); // write out the binary file 
	} //end else 
	inFile.close(); // close the text file 
	return namecopy; // it succeeds if there is at least one records
} 	// end Text2Binary
 


bool isPrime(int n) {
    
    int count = 0;											//計算因數有幾個
        
    for( int i = 1; i <= n; i++){							//除到自己為止
        if(n % i == 0){										//若被整除
            count++;										//count加一
        }
    }    
        
    if (count == 2) 										//若只有兩個因數
        return true;				//是質數
    else 
        return false;			//不是質數
}

int nextprime(int prime) {
    
    bool found = false;
    while (!found) {
        prime++;
        if (isPrime(prime))
            found = true;
    }
    return prime;
}

long long hashindex(string sid, int tableSize) {
    long long index = 1;
    for (int i = 0; sid[i] != '\0'; i++) {
        index *= (int)sid[i];
    }
    return index % tableSize;
}

int quadraticProbing(int h, int i, int tableSize) {
    return (h + i * i) % tableSize;
}

bool binexist( string fileName ){
	fstream binFile;
	binFile.open(fileName.c_str(), fstream::in | fstream::binary); // open a binary file
	if (binFile.is_open()){
		binFile.close();
		return true;
	}
	return false;
}
	
void readBinary(string fileName) // get records from a file 
{ 	string namecopy = "quadratic"+ fileName +".txt";
	fileName = "input" + fileName + ".bin";
	int success = 0;
	double unsuccess = 0;
	long long hvalue;
	fstream binFile; // input file handle
	studentType oneSt; // keep one record with the required fields 
	int stNo = 0; // total number of students
	binFile.open(fileName.c_str(), fstream::in | fstream::binary); // open a binary file 
	if (binFile.is_open()) 
	{ 
		binFile.seekg (0, binFile.end); 
		stNo = binFile.tellg() / sizeof(oneSt); 
		binFile.seekg (0, binFile.beg); 
		int tableSize = nextprime(int(1.3 * stNo));
	    vector<studentType> hashTable(tableSize);
	    vector<bool> occupied(tableSize, false);
	    vector<int>  hashvalue(tableSize);
		for (int j = 0; j < stNo; j++) 
		{ 
			binFile.read((char *)&oneSt, sizeof(oneSt)); // read the entire record from a binary file 
			//cout<<oneSt.sid<<endl;
			hvalue = hashindex(oneSt.sid, tableSize);
	        int i = 0;
	        int index = quadraticProbing(hvalue, i, tableSize);
	        success++;
	        while (occupied[index] && i < tableSize) {
	            i++;
	            index = quadraticProbing(hvalue, i, tableSize);
	            success++;
	        }
	        if (i < tableSize) {
	            hashTable[index] = oneSt;
	            hashvalue[index] = hvalue;
	            occupied[index] = true;
	        }
			//cout << "[" << j+1 << "]" << oneSt.sid << "," << oneSt.sname << endl; 

		} //end for 
		binFile.close(); // close input file
		ofstream outFile(namecopy);
	    for (int i = 0; i < tableSize; i++) {
	        if (occupied[i]) {
	            outFile << "[" << i << "]" << hashvalue[i] << "," << hashTable[i].sid << "," << hashTable[i].sname << "," <<  hashTable[i].mean << endl;
	        }
	        else
	        	outFile << "[" << i << "]" << endl; 
	    }
	    outFile.close();
	    int totalComparisons = 0;
		for (int j = 0; j < tableSize; j++) {
		    if (!occupied[j]) {  
		        totalComparisons += 1;
		    } 
			else {
		        int i = j;  		        
		        while(occupied[i]) { 		        
		        	totalComparisons += 1;
		         	i++;                  
		        	if(i>=tableSize)
		        		i=0;   
				}                           
				totalComparisons += 1;	              
		 	}	        		
		}         
		unsuccess = (double) totalComparisons/tableSize;	
	} // end if              
	
	cout << "\nHash table has been successfully created by Quadratic probing" << endl;
	cout << "unsuccessful search: " << setprecision(5) << (double)unsuccess  << " comparisons on average" << endl;
	cout << "successful search: "<< setprecision(5) << (double)success / stNo <<" comparisons on average" << endl;
	
} 	// end readBinary

    
int main() {
	string fileName; 	
    int command ;
    double command2done = 0;
    bool success = false;
    
    do {
        cout << "\n******* Hash Table *****" << endl;
        cout << "* 0. QUIT              *" << endl;
        cout << "* 1. Quadratic probing *" << endl;
        cout << "* 2. Double hashing    *" << endl;
        cout << "************************" << endl;
        cout << "Input a choice(0, 1, 2): ";
        // declare a char to switch execute options

        cin >> command;
        if( command == 0 ){

            break;
        }
        else if( command == 1 ){
            fileName = Text2Binary();
            if (fileName.compare("0")) 			
            	readBinary(fileName );
        }
		else
            cout << endl << "Command does not exist!" << endl;
        
    }
    while ( command  != 0 );
    system("pause");
    return 0;
}

