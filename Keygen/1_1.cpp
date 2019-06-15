#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <random>
#include <time.h>

using namespace std;

void add2Sum(int &sum, int value){
	sum = sum << 1;
	sum = sum + value;
}

string keyGen(string name){
	
	srand(time(NULL));

	unsigned int r = 268435456 + rand() % 4026531838;
	stringstream s;
	s << hex << r;
	string random = s.str();

//	cout << random << endl;

	int sum = 0;
	int size = 17 + name.length();

	string serial = random + random +"0" + name;
//	cout << serial<<endl;
	for (int i = 17; i < 17 + name.length(); i++){
		if (serial[i] >= 'a' && serial[i] <= 'z'){
			serial[i] -= 'a';
			serial[i] >>= 1;
		}
		else if (serial[i] >= 'A' && serial[i] <= 'Z'){
			serial[i] -= 'A';
			serial[i] >>= 1;
		}
		else if (serial[i] >= '0' && serial[i] <= '9'){
			serial[i] -= '0';
		}
		else{
			serial[i] = 8;
		}

		//
		if (serial[i] >= size)
			add2Sum(sum, 0);
		else
			add2Sum(sum, serial[serial[i]]);
	}

	sum = sum & 4095;
	int eax, al, bl, ah;
	eax = sum;

	al = eax & 255;
	bl = al;

	ah = (eax & 65280) >> 8;
	al = ah;
	ah = bl;

	bl = bl & 240;
	al = al | bl;

	eax = (ah << 8) + al;
	eax = eax & 4095;


	// Chuyen eax sang temp o he co so 16.
	stringstream s2;
	s2 << hex << eax;
	string temp = s2.str();
	
//	cout << temp << endl;

	
	string password = random + random;
//	cout << password << endl;
	// Thay doi 3 ky tu cuoi cua password.
	int len = temp.length();
	if (len < 3){
		for (int i = 0; i < 3 - len;i++)
			password[13 + i] = '0';
	}
	for (int i = 0; i < len; i++){
		password[15 - i] = temp[len - 1 - i];
	}

	return password;
}

int main(){
	string name;
	string password;

	// Get name.
	cout << "Name:";
	cin >> name;

	// Check name
	if (name.length() <6 || name.length()> 16)
	{
		cout << "Name should be more than 6 chars, and less than 17 chars." << endl;
		system("pause");
		return 0;
	}

	// Return password.
	password = keyGen(name);
	cout << "Password: " << password << endl;

	system("pause");
	return 0;
}