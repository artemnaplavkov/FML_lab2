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
char start_pos;
int flag = 0;
vector <char> for_deleting;
char first_letter;
int count_for_delet = 0;
vector <pair<pair<char, char>, char>> GPS1;
vector <int> numb_for_del;

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
	return 1;
}

int grammatic(string gram1) {
	GS = make_pair(gram1[0], gram1[4]);
	P = make_pair(GS, gram1[3]);
	GPS.push_back(P);

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
					if (meter == 3) {
						start_pos = line[0];
					}
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
	for (int i = 0; i <= counter - 1; i++) {
		cout << "Insert " << i + 1 << " letter of grammar, by using ->  \n";
		cin >> gram1;
		int attempt = small_check(gram1);
		if (attempt == 0) {
			cout << "Error in line\n";
			i--;
			continue;
		}
		else {
			grammatic(gram1);
		}
	}
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
				cout << "File successfully created \n";
				insert_by_yourself();
			}
			else {
				cout << "File error. What'a hell are you want from me?\n";
				return 0;
			}
		}
		else {
			insert_by_file(in);
		}
	}

	for (i = 1;GPS.size()-1;i++) { //deleting invalid ones
		flag = 0;
		first_letter = GPS[i].first.first;
		for (j = 1; GPS.size(); j++) {
			if (GPS[j].first.second == first_letter) {
				flag = 1;
			}
		}
		if (flag == 0) {
			for_deleting.push_back(first_letter)
		}
	}

	for (i = 1; for_deleting.size(); i++) { //deleting invalid ones
		first_letter = for_deleting[i];
		for (j = 1; GPS.size()-1; j++) {
			if (GPS[j].first.second != first_letter and GPS[j].first.first != first_letter) {
				GPS1.push_back(GPS[j]);
			}
		}
	}

	for (int i = 0; i <= gramG.size() - 1; i++) {
		for (int j = 0; j <= (alphabet.size() - gramG.size() + 1); j++) {
			if (gramG[i] == alphabet[j]) {
				alphabet.erase(j, 1);
			}
		}
	}

	for (int i = 0; i <= GPS.size() - 1; i++) {

		char letter_first_i = GPS1[i].first.first;
		char transfer = GPS1[i].second;
		char letter_second = GPS1[i].first.second;

		for (int j = i + 1; j <= GPS.size() - 1; j++) {
			char letter_first_j = GPS1[i].first.first;
			char alph = alphabet[0];

			if (transfer ==GPS1[j].second and letter_second== GPS1[j].first.second) {
				GPS1[i].first.first = alphabet[0];
				GPS1[j].first.first = alphabet[0];
				alphabet.erase(0, 1);
				GPS1.erase(GPS.begin() + j);

				for (int l = 0; l <= GPS1.size() - 1; l++) {
					if (GPS1[l].first.second == letter_first_i || GPS1[l].first.second == letter_first_j) {
						GPS1[l].first.second = alph;
					}
					if (GPS1[l].first.first == letter_first_i || GPS1[l].first.first == letter_first_j) {
						GPS1[l].first.first = alph;
					}
				}
			}
		}
	}

	for (int i = 0; GPS1.size() - 1;i++) { //deleting the same
		for (int j = 0; GPS1.size() - 1;j++) {
			if (GPS1[i].first.first == GPS1[j].first.first and GPS1[i].second == GPS1[j].second and GPS1[i].first.second == GPS1[j].first.second) {
				numb_for_del.push_back(j)
			}
		}
	}
	for (int i = 0; numb_for_del.size() - 1; i++) {
		GPS1.erase(GPS1.begin() + i);
	}


	cout << "\n";
	for (int i = 0; i <= GPS1.size() - 1; i++) {
			cout << GPS1[i].first.first << " -> " << GPS1[i].second << " -> " << GPS1[i].first.second << " \n";
		}
	return 0;
}
