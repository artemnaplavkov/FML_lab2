#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <fstream>

using namespace std;

string gram1;
string gram2;
int counter;
int file_or_yourself;
int answer;

string line;
int meter = 0;

vector <char> gramG;
vector <char> gramP;

pair <char, char> GS;
pair <pair<char, char>, char> P;
vector <pair<pair<char, char>, char>> GPS;
string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int small_check(string gram1) {
	if (gram1[1] != '-' || gram1[2] != '>')
	{
		cout << "incorrect insert \n ";
		return 0;
	}
	else {
		return 1;
	}
}

int grammatic(string gram1) {
	GS = make_pair(gram1[0], gram1[4]);
	P = make_pair(GS, gram1[3]);
	GPS.push_back(P);


	if (gram1.size() == 7) {
		if (gram1[5] == '|' && (!(!gram1[6])) && (!gram1[7])) {
			gramG.push_back('@');
			GS = make_pair(gram1[0], '@');
			P = make_pair(GS, gram1[6]);
			GPS.push_back(P);
		}
	}
	else if (gram1.size() == 8) {
		if (gram1[5] == '|' && (!(!gram1[6])) && (!(!gram1[7]))) {
			GS = make_pair(gram1[0], gram1[7]);
			P = make_pair(GS, gram1[6]);
			GPS.push_back(P);
		}
	}
	if (gram1.size() == 10) {
		if (gram1[8] == '|' && (!(!gram1[9])) && (!gram1[10])) {
			gramG.push_back('@');
			GS = make_pair(gram1[0], '@');
			P = make_pair(GS, gram1[9]);
			GPS.push_back(P);
		}
	}
	else if (gram1.size() == 11) {
		if (gram1[8] == '|' && (!(!gram1[9])) && (!(!gram1[10]))) {
			GS = make_pair(gram1[0], gram1[10]);
			P = make_pair(GS, gram1[9]);
			GPS.push_back(P);

		}
	}
	return 0;
}


int insert_by_file(ifstream& in) {
	ifstream in("lab.txt"); 
	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			//std::cout << line << std::endl;
			if (meter == 0) {
				gram1 = line;
				meter++;
				for (int i = 0; i <= gram1.size(); i++) {
					if (gram1[i] != '{' and gram1[i] != '}' and gram1[i] != ',')
						gramG.push_back(gram1[i]);
				}
			}
			else if (meter == 1) {
				gram2 = line;
				meter++;
				for (int i = 0; i <= gram2.size(); i++) {
					if (gram2[i] != '{' and gram2[i] != '}' and gram2[i] != ',')
						gramP.push_back(gram2[i]);
				}
			}
			else if (meter==2) {
				counter = stoi(line);
				meter++;
			}
			else {
				meter++;
				int attempt = small_check(line);
				if (attempt == 0){
					cout << "Error in " << meter << " line\n";
					continue;
				}
				else {
					grammatic(line);
				}
			}
		}
	}
	in.close();
	return 0;
}


int insert_by_yourself() {
	cout << "Insert grammatic G like this: {K,L,M,N} \n";
	cin >> gram1;
	for (int i = 0; i <= gram1.size(); i++) {
		if (gram1[i] != '{' and gram1[i] != '}' and gram1[i] != ',')
			gramG.push_back(gram1[i]);
	}

	cout << "Insert grammatic P like this: {a,b,+,-} \n";
	cin >> gram2;
	for (int i = 0; i <= gram2.size(); i++) {
		if (gram2[i] != '{' and gram2[i] != '}' and gram2[i] != ',')
			gramP.push_back(gram2[i]);
	}
	cout << "Enter the number of clicks \n";
	cin >> counter;
	/*use all new func*/
	return 0;
}




int main() {
	cout << "Print 1 if you would like to open data from file\n  Print 2 to insert by yourself: \n";
	cin >> file_or_yourself;
	if (file_or_yourself == 1) {
		ifstream in("lab.txt");
		if (in.is_open() == false) {
			cout << "File not found. Print 1 - to create it\n";
			cin >> answer;
			if (answer == 1) {
				ofstream MyFile("lab.txt");
				// func insert_by_yourself 
			}
			else {
				cout << "File error. What'a hell are you want from me?" << endl;
				return 0;
			}
		}
		else {
			//func insert_by_file
		}

	}

	return 0;
}