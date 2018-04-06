#include <iostream>
	using std::cout;
	using std::cin;
	using std::endl;
#include <fstream>
	using std::ifstream;
#include <string>
	using std::string;
#include <sstream>
#include <bitset>

#define INFO_BITS 4
#define CROSSWORD_LEN 7
#define PARITY_BITS 3

struct Constraints {
	int set_A[4] = {1, 2, 4, 6};
	int set_B[4] = {0, 2, 3, 6};
	int set_C[4] = {0, 4, 5, 6};
};	//end struct.

struct Crossword {
	int c[7] = {};
};

//function prototyping
string convertASCII_to_BITSET(string);
string convertBITSET_to_ASCII(string);
void create_parity_matrix(Constraints, int [][CROSSWORD_LEN], int);
void create_generation_matrix(int[][CROSSWORD_LEN], int, int[][PARITY_BITS], int);
void print_PM_matrix (int [][CROSSWORD_LEN], int);
string make_crossword(int[], int[]);
int modulos2_ADD(int a, int b, int c);
string encoder_algorithm(string);
void decoder_algorithm();
void check_output_function();
void create_noise();

int main() {
	
	//taking input from file.
	ifstream input("Input.txt");
	string data;
	//input >> data;
	if (input.is_open()) {
		string temp;
    	while(!input.eof()) {
    		getline (input, temp);
    		data.append(temp + '\n');  		
		}
		input.close();
	}	else cout << "file not found / can't open the file Input.txt" << endl;
	cout << data << endl;
	
	//converting the text to 8 bit binary string
	string binary = convertASCII_to_BITSET(data);
	cout << "bitcode string : " << binary << endl;
	
	//converting 8 bit binary string to text
	string text = convertBITSET_to_ASCII(binary);
	cout << "converting back :\n" << text << endl;
	
	Constraints default_constraints;
	
	//creating parity matrix
	int parity_matrix [PARITY_BITS][CROSSWORD_LEN];
	//initializing matrix
	for (int i = 0; i < PARITY_BITS; i++)
		for (int j = 0; j < CROSSWORD_LEN; j++)
			parity_matrix[i][j] = 0;
	cout << endl;
	print_PM_matrix(parity_matrix, PARITY_BITS);
	cout << endl;
	create_parity_matrix(default_constraints, parity_matrix, PARITY_BITS);
	print_PM_matrix(parity_matrix, PARITY_BITS);
	
	//encoding the string;
	string encoded = encoder_algorithm (binary);
	
	return 0;
}	//end main function.

//function defination
string convertASCII_to_BITSET(string input) {
	string output;
	for ( int i = 0; i < input.size(); i++) {
		std::bitset<8> bitcode(input[i]);
		output.append( bitcode.to_string() );
	}	//end for
	return output;
}	//end method convertASCII_to_BITSET

string convertBITSET_to_ASCII(string input) {
	std::stringstream sstream(input);
	string output;
    while( sstream.good() ) {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }
	return output;
}	//end method convertBITSET_to_ASCII

void print_PM_matrix (int matrix[][CROSSWORD_LEN], int row) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < CROSSWORD_LEN; j++)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}	//end row traversal			
}	//end print_matrix.

void print_GM_matrix (int matrix[][PARITY_BITS], int row) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < CROSSWORD_LEN; j++)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}	//end row traversal			
}	//end print_matrix.

void create_parity_matrix(Constraints default_constraints, int parity_matrix[][CROSSWORD_LEN], int row) {
	for (int j = 0; j < 4; j++)
		parity_matrix[0][default_constraints.set_A[j]] = 1;
	for (int j = 0; j < 4; j++)
		parity_matrix[1][default_constraints.set_B[j]] = 1;
	for (int j = 0; j < 4; j++)
		parity_matrix[2][default_constraints.set_C[j]] = 1;
	return;
}	//end method create_parity_matrix

string encoder_algorithm (string binary) {
	string encoded;
	int bsize = binary.size();
	int no_of_char = bsize/8;
	int size_encoded = 2 * no_of_char;
	for (int i = 0; i < bsize; i++) {
		int temp[INFO_BITS];
		int cell[CROSSWORD_LEN];
		for (int j = 0; j < 4; j++) {
			temp[j] = binary[i+j];
		}	//end for.
		encoded += make_crossword(cell, temp);
		i += 3;
	}	//end for.
	return encoded;
}	//end method encoder.

string make_crossword(int cell[], int unit[]) {
	string result;
	cell[0] = unit[0];
	cell[2] = unit[1];
	cell[4] = unit[2];
	cell[6] = unit[3];
	cell[1] = modulos2_ADD(cell[2], cell[4], cell[6]);
	cell[3] = modulos2_ADD(cell[0], cell[2], cell[6]);
	cell[5] = modulos2_ADD(cell[0], cell[4], cell[6]);
	for (int i = 0; i < CROSSWORD_LEN; i++)
		result += cell[i];
	cout << result << '\n';
	return result; 	
}	//end make_crossword.

int modulos2_ADD(int a, int b, int c) {
	int result = a + b + c;
	if ( (result) >= 2 )
		result = 0;
	return result;
}	//end method.

/*
void create_noise() {
	
}	//end method create_noise.

bool check_output_function(string encoded, int corrupted) {
	bool flag;
	return flag;
}	//end method check_output_function.

string error_decoder (string encoded) {
	
	return decoded
}	//end method error_decoder.
*/


