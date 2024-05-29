#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int SIZE = 255;
const int SUBSIZE = 3;

class TextFile {
public:
	//Decare the blanck database
	string database[SIZE][SUBSIZE];

	//Reset the database with its main accounts 
	void clear() {

		ofstream f("database.txt");

		string data[SIZE][SUBSIZE];
		for (int i = 0; i < SIZE; i++) {
			data[i][0] = "x"; data[i][1] = "x"; data[i][2] = "0";
		}
		data[0][0] = "admin"; data[0][1] = "password"; data[0][2] = "1";
		data[1][0] = "Josh"; data[1][1] = "Test"; data[1][2] = "2";

		write(data);

		f.close();
	}

	//Writes array database into the .txt file
	void write(string data[SIZE][SUBSIZE]) {
		ofstream f("database.txt");
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SUBSIZE; j++) {
				f << data[i][j] << " ";
			}
			f << "\n";
		}
		f.close();
	}

	//Adds new users to the database
	void writeNew(string username, string password) {
		read();

		for (int i = 0; i < SIZE - 1; i++) {
			if (database[i][0] == "x") {
				database[i][0] = username; database[i][1] = password; database[i][2] = to_string(i + 1);
				break;
			}
		}

		write(database);
	}

	//Reads the database file
	void read() {
		string myText;

		ifstream MyReadFile("database.txt");

		index = 0;

		while (getline(MyReadFile, myText)) {
			convertToArray(myText);
			index++;
		};

		MyReadFile.close();
	}
	

private:
	int index = 0;

	//Converts the databse file line by line into the array
	void convertToArray(string s) {
		int subIndex = 0;
		string newItem;


		for (int i = 0; i < size(s); i++){
			if (s[i] != ' ') {
				newItem.append(s.substr(i, 1));
			}

			else if (s[i] == ' ') {
				database[index][subIndex] = newItem;
				newItem = "";
				subIndex++;
			}
		}
	}
	
};