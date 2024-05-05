//11127246 陳柏劭 11127256 蕭天語
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


class Hash{

public :	
	string fileName;
	int tableSize;
	int stepSize;
	
	int Text2Binary(  ) // get records from a text file & save as a binary file 
	{ 	
		fstream inFile, outFile; // file handles 
		int stNo = 0;  
		cout << "\nInput a file number ([0] Quit): "; 
		cin>> fileName; 
		string namecopy = fileName;
		if (!fileName.compare("0")){ // No file to open, so quit
			fileName = "0";		 
			return 0; 		 
		}
		
		int txtexist = 0;										// determine txt exist or not
		int binexist = 0;										// determine bin exist or not
		fileName = "input" + fileName + ".bin";
		if( binExist( fileName )) 								
			binexist = 1;
			
		fileName = namecopy;
		
		inFile.open(("input" + fileName + ".txt").c_str(), fstream::in); // open a file 
		if (inFile.is_open()) 
			txtexist = 1;		 
			
		if (txtexist == 0 && binexist == 0){				// if both not exist
			cout << "\n### input" + fileName + ".bin" << " does not exist! ###" << endl;
			cout << "\n### input" + fileName + ".txt" << " does not exist! ###" << endl << endl;
			fileName = "0";	
			inFile.close();	 
			return 0; 	
		}
		else if ( txtexist == 1 && binexist == 0 ){			// if only txt exist
			cout << "\n### input" + fileName + ".bin" << " does not exist! ###" << endl;
			fileName = "input" + fileName + ".bin";
		}
		else if ( txtexist == 0 && binexist == 1 ){			// if only bin exist
			cout << "\n### input" + fileName + ".txt" << " does not exist! ###" << endl;
			inFile.close();
			return 0;
		}
		else if ( txtexist == 1 && binexist == 1 ){			// if both exist
			fileName = "input" + fileName + ".bin";
		}
		outFile.open(fileName.c_str(), fstream:: out | fstream::binary); // create a binary file			
		if (outFile.is_open()) 
		{   
			char rBuf[BIG_INT]; // buffer to keep one whole record		
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
	 	fileName = namecopy;
	 	
		return stNo; // it succeeds if there is at least one records
	} 	// end Text2Binary
	 
	
	
	bool isPrime(int n) {										//determine is prime or not
	    
	    int count = 0;											//計算因數有幾個
	        
	    for( int i = 1; i <= n; i++){							//除到自己為止
	        if(n % i == 0){										//若被整除
	            count++;										//count加一
	        }
	    }    
	        
	    if (count == 2) 										//若只有兩個因數
	        return true;										//是質數
	    else 
	        return false;										//不是質數
	}
	
	int nextprime(int prime) {									// found the next prime that bigger than self
	    
	    bool found = false;
	    while (!found) {
	        prime++;
	        if (isPrime(prime))
	            found = true;
	    }
	    return prime;
	}
	
	long long hash(string key) {								//hash(key) function to find the hvalue
	    long long index = 1;
	    for (int i = 0; key[i] != '\0'; i++) {
	        index *= (int)key[i];
	    }
	    return index % tableSize;
	}
	
	long long step(string key) {								//step(key) function to get the step
	    long long index = 1;
	    for (int i = 0; key[i] != '\0'; i++) {
	        index *= (int)key[i];
	    }
	    return stepSize - (index % stepSize);
	}
	
	int quadraticProbing(int h, int i, int tableSize) {			// return quadratic probing index
	    return (h + i * i) % tableSize;
	}
	
	bool binExist( string fileName ){							// determine bin exist or not
		fstream binFile;
		binFile.open(fileName.c_str(), fstream::in | fstream::binary); // open a binary file
		if (binFile.is_open()){
			binFile.close();
			return true;
		}
		return false;
	}
		
	bool readBinary() // get records from a file and doing quadratic probing
	{ 	string namecopy = "quadratic"+ fileName +".txt";
		string copy = fileName;										//copy filename
		fileName = "input" + fileName + ".bin";
		double success = 0;							//success searching times
		double unsuccess = 0;						//unsuccess searching times
		long long hvalue;							//hash hvalue
		fstream binFile; // input file handle
		studentType oneSt; // keep one record with the required fields 
		int stNo = 0; // total number of students
		 
		binFile.open(fileName.c_str(), fstream::in | fstream::binary); // open a binary file 
		if (binFile.is_open()) 
		{ 	
			binFile.seekg (0, binFile.end); 
			stNo = binFile.tellg() / sizeof(oneSt); 
			binFile.seekg (0, binFile.beg); 
			tableSize = nextprime(int(1.3 * stNo));			//get the tablesize
		    vector<studentType> hashTable(tableSize);		//hash table
		    vector<bool> occupied(tableSize, false);		//hash occupied or not
		    vector<int>  hashvalue(tableSize);				//hash value
		    
			for (int j = 0; j < stNo; j++) 					// first data to the last data
			{ 
				binFile.read((char *)&oneSt, sizeof(oneSt)); // read the entire record from a binary file 
				
				hvalue = hash(oneSt.sid);					// get the hash value
		        int i = 0;									//prevent from getting into infinity loop
		        int index = quadraticProbing(hvalue, i, tableSize);		// equal hvalue
		        success++;												//success seaching++;
		        
		        while (occupied[index] && i < tableSize) {				// keep doing quadratic probing until finding space
		            i++;
		            index = quadraticProbing(hvalue, i, tableSize);
		            success++;
		            
		        }
		        if (i < tableSize) {						//put data into hash
		            hashTable[index] = oneSt;
		            hashvalue[index] = hvalue;
		            occupied[index] = true;
		        }
		        
	
			} //end for 
			binFile.close(); // close input file
			ofstream outFile(namecopy);
			outFile << "--- Hash table created by Quadratic probing ---" << endl;			//writing outfile that in hash table
		    for (int i = 0; i < tableSize; i++) {
		    	
		    	if (i < 100) {
		            outFile << "[ " << i << "]";   
		        }      
		        else {
		            outFile << "[" << i << "]";   
		        }
		        if (occupied[i]) {
		            outFile <<  " " << hashvalue[i] << "," << " " << hashTable[i].sid << "," << " " << hashTable[i].sname << "," <<  " " <<hashTable[i].mean << endl;
		        }
				else 
					outFile << endl;
		    }
		    outFile << "-----------------------------------------------" << endl;
		    outFile.close();
		    
			for (int j = 0; j < tableSize; j++) {									//counting unsuccessful searching times from 0 to tablesize-1
			    if (!occupied[j]) {  												// not occupied then no need to plus
			        unsuccess += 0;
			    } 
				else {
			        int i = j;  	
					int k = 0;	        
			        while(occupied[i]) { 		        							//quadraticProbing until not occcupied
			         	i = quadraticProbing(j, k, tableSize);      
						unsuccess += 1;  											//unsuccessful searching times++;
						k++;      
					}         
					unsuccess -= 1;                             					//unsuccessful searching times-1 because it added one more time
			 	}	    		
			}         
		
			unsuccess = unsuccess/tableSize;										//count unsucessful searching time
			 
		} // end if 
		else{																		//cant open bin
			fileName = copy;
			return false;
		}
			             
		fileName = copy;
		cout << "\nHash table has been successfully created by Quadratic probing" << endl;
		cout << "unsuccessful search: " << fixed << setprecision(4) << unsuccess  << " comparisons on average" << endl;
		cout << "successful search: "<< fixed << setprecision(4) << success / stNo <<" comparisons on average" << endl;
		return true;
	} 	// end readBinary
	
	    
	void doubleHashing() {													//double hashing function
	    string namecopy = "double"+ fileName +".txt";
	    string copy = fileName;												//copy filename
		fileName = "input" + fileName + ".bin";
		double success = 0;													//success searching times
		double unsuccess = 0;												//unsuccess searching times
		long long hvalue;													//hash value
		fstream binFile; // input file handle
		studentType oneSt; // keep one record with the required fields 
		
		int stNo = 0; // total number of students
		binFile.open(fileName.c_str(), fstream::in | fstream::binary); // open a binary file 
		if (binFile.is_open()) 
		{ 
			binFile.seekg (0, binFile.end); 
			stNo = binFile.tellg() / sizeof(oneSt);  
			binFile.seekg (0, binFile.beg); 
			tableSize = nextprime(int(1.3 * stNo));						//count tablesize
		    vector<studentType> hashTable(tableSize);					//hash table
		    vector<bool> occupied(tableSize, false);					//hash occupied or not
		    vector<int>  hashvalue(tableSize);							//hash value
		     
	    	stepSize = nextprime(stNo / 2);								//highest step 最高步階
			
			for (int j = 0; j < stNo; j++) 								// first data to the last data
			{ 
				binFile.read((char *)&oneSt, sizeof(oneSt)); // read the entire record from a binary file 
				
				hvalue = hash(oneSt.sid);								//get hash value
				success++;												//success++
				int Step = step(oneSt.sid);								//count the step
				int i = Step;											//i equals step
		        int index = hvalue;
		        while (occupied[index] && index < tableSize ) {			//keep double hashing
		            index = (hvalue + i) % tableSize;      
		            i+= Step;  											// i = step + step
		            success++;
		        }
		        // put data into hash
		        hashTable[index] = oneSt;
		        hashvalue[index] = hvalue;
		        occupied[index] = true;
	
			} //end for 
		
		    binFile.close();
		    
		    ofstream outFile(namecopy);									//writing outfile that in hash table
		    outFile << "--- Hash table created by Double hashing ---" << endl;
		    for (int i = 0; i < tableSize; i++) {
		        
		        if (i < 100) {
		            outFile << "[ " << i << "]";   
		        }      
		        else {
		            outFile << "[" << i << "]";   
		        }
		        if (occupied[i]) {
		            outFile <<  " " << hashvalue[i] << "," << " " << hashTable[i].sid << "," << " " << hashTable[i].sname << "," <<  " " <<hashTable[i].mean << endl;
		        }
				else 
					outFile << endl;
		    }
		    outFile << "-----------------------------------------------" << endl;
		    outFile.close();
		    fileName = copy;
		    cout << "\nHash table has been successfully created by Double hashing" << endl;
		    cout << "successful search: "<< fixed << setprecision(4) << success / stNo <<" comparisons on average" << endl;
		}
	}
};

int main() {
	string fileName; 	
    int command ;
    double command1done = 0;
    bool success = false;
    Hash h ;
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
        else if( command == 1 ){					//Quadratic probing
            h.Text2Binary();
            if (h.fileName.compare("0")) 	{		//if filename not 0 then readbin
            	if (h.readBinary()){			
            		command1done++;
				}           	
            }
            else{
            	command1done = 0; 
            }
        }
        else if( command == 2 ){					//Double hashing
        	if ( command1done == 0 )
        		cout<< "### Command 1 first. ###" <<endl << endl;
        	else if (h.fileName.compare("0")) 			//if filename not 0 then double hashing
            	h.doubleHashing( );
        }
		else
            cout << endl << "Command does not exist!" << endl << endl;
        
    }
    while ( command  != 0 );
    system("pause");
    return 0;
}
