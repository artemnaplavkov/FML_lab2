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
int file_or_yourself=1;
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


static int small_check(string gram1) {
	if (gram1[1] != '-' || gram1[2] != '>')
	{
		cout << "incorrect insert \n ";
		return 0;
	}
	return 1;
}

static void grammatic(string gram1) {
	GS = make_pair(gram1[0], gram1[4]);
	P = make_pair(GS, gram1[3]);
	GPS.push_back(P);


	if (gram1.size() == 8) {
		if (gram1[5] == '|' && (!(!gram1[6])) && (!(!gram1[7]))) {
			GS = make_pair(gram1[0], gram1[7]);
			P = make_pair(GS, gram1[6]);
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
}


static void insert_by_file() {
	ifstream in("lab.txt");
	if (in.is_open()){
		while (std::getline(in, line))
		{
			if (meter == 0) {
				gram1 = line;
				int count_len = gram1.length();
				meter++;
				for (int i = 0; i <= count_len-1; i++) {
					if (gram1[i] != '{' and gram1[i] != '}' and gram1[i] != ',') {
						gramG.push_back(gram1[i]);
					}
				}
			}
			else if (meter == 1) {
				gram2 = line;
				int count_len = gram2.length();
				meter++;
				for (int i = 0; i <= count_len-1; i++) {
					if (gram2[i] != '{' and gram2[i] != '}' and gram2[i] != ','){
						gramP.push_back(gram2[i]);
						}
				}
			}
			else {
				meter++;
				if (line[1] != '-' || line[2] != '>')
				{
					cout << "incorrect insert in" << meter+1<< "line \n ";
					
				}
				else {
					grammatic(line);
				}
				
			}
		}
	}
	in.close();
}


static void insert_by_yourself() {
	cout << "Insert grammatic G like this: {K,L,M,N} \n";
	cin >> gram1;
	int gram1_size = gram1.size();
	for (int i = 0; i <= gram1_size; i++) {
		if (gram1[i] != '{' and gram1[i] != '}' and gram1[i] != ',')
			gramG.push_back(gram1[i]);
	}

	cout << "Insert grammatic P like this: {a,b,+,-} \n";
	cin >> gram2;
	int gram2_size = gram2.size();
	for (int i = 0; i <= gram2_size; i++) {
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
}



int main() {
	//cout << "Print 1 if you would like to open data from file\nPrint 2 to insert by yourself: \n";
	//cin >> file_or_yourself;
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
			insert_by_file();
		}
	}

	start_pos = GPS[0].first.first;
	int GPS_size = GPS.size() - 1;
	
	for (int i = 0; i <= GPS_size; i++) { //deleting invalid ones
		flag = 0;
		first_letter = GPS[i].first.first;
		for (int j = 0; j <= GPS_size; j++) {
				if (GPS[j].first.second == first_letter or GPS[i].first.first == start_pos) {
					flag = 1;
				}
		
		}
		if (flag == 0) {
			for_deleting.push_back(first_letter);
		}
	}

	sort(for_deleting.begin(), for_deleting.end());
	auto it = unique(for_deleting.begin(), for_deleting.end());
	for_deleting.erase(it, for_deleting.end());

	for (int i = 0; i <= GPS.size()-1; i++) {
		flag = 1;
		for (int j = 0; j <= for_deleting.size() - 1; j++) {
			if (GPS[i].first.first == for_deleting[j]) {
				flag = 0;
			}
		}
		if (flag == 1) {
			GPS1.push_back(GPS[i]);
		}
	}
	for (int i = 0; i <= gramG.size() - 1; i++) {
		for (int j = 0; j <= (alphabet.size() - gramG.size() + 1); j++) {
			if (gramG[i] == alphabet[j]) {
				alphabet.erase(j, 1);
			}
		}
	}

	for (int i = 0; i <= GPS1.size()-1; i++) {
		char letter_first_i = GPS1[i].first.first;
		char transfer = GPS1[i].second;
		char letter_second = GPS1[i].first.second;

		for (int j = i + 1; j <= GPS1.size()-1; j++) {
			char letter_first_j = GPS1[j].first.first;
			char alph = alphabet[0];

			if (GPS1[j].second== transfer and  GPS1[j].first.second== letter_second and letter_first_i!= letter_first_j) {
				GPS1[i].first.first = alph;
				GPS1[j].first.first = alph;
				alphabet.erase(0, 1);
				GPS1.erase(GPS1.begin() + j);

				for (int l = 0; l <= GPS1.size()-1; l++) {
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

	for (int i = 0; i<=GPS1.size() - 1; i++) { //deleting the same
		for (int j = i+1; j<=GPS1.size() - 1; j++) {
			if (GPS1[i].first.first == GPS1[j].first.first and GPS1[i].second == GPS1[j].second and GPS1[i].first.second == GPS1[j].first.second) {
				numb_for_del.push_back(i);
			}
		}
	}

	sort(numb_for_del.begin(), numb_for_del.end());
	auto it_1	= unique(numb_for_del.begin(), numb_for_del.end());
	numb_for_del.erase(it_1, numb_for_del.end());

	for (int i = 0;i<= numb_for_del.size() - 1; i++) {
		GPS1.erase(GPS1.begin() + numb_for_del[i]);
	}
	
	for (int i = 0; i <= GPS1.size() - 1; i++) { //deleting the same
		for (int j = i + 1; j <= GPS1.size() - 1; j++) {
			if (GPS1[i].first.first == GPS1[j].first.first and GPS1[i].second == GPS1[j].second and GPS1[i].first.second == GPS1[j].first.second) {
				numb_for_del.push_back(i);
			}
		}
	}

	sort(numb_for_del.begin(), numb_for_del.end());
	auto it_2 = unique(numb_for_del.begin(), numb_for_del.end());
	numb_for_del.erase(it_2, numb_for_del.end());

	for (int i = 0; i <= numb_for_del.size() - 1; i++) {
		GPS1.erase(GPS1.begin() + numb_for_del[i]);
	}

	cout << "\n";
	int GPS1_size = GPS1.size() - 1;
	for (int i = 0; i <= GPS1_size; i++) {
		cout << GPS1[i].first.first << " -> " << GPS1[i].second << " -> " << GPS1[i].first.second << " \n";
	}
	return 0;
}
