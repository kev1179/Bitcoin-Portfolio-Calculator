#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

//TODO: Implement Heap
template <typename T>
class Heap {
private:
	vector<T> heap;

public:
	Heap() {
		heap = {};
	}
};

//TODO: Implement HashMap
template <typename T1, typename T2>
class HashMap {
private:
	vector<double> hashTable;

public:
	HashMap() {
		hashTable = {};
	}
};

//Generates a timestamp. Works properly, has been tested using an online converter!
long generateTimeStamp(string month, string day, string year, string hour, string minute) {
	
	unordered_map<string, int> months;
	months["January"] = 0;
	months["February"] = 1;
	months["March"] = 2;
	months["April"] = 3;
	months["May"] = 4;
	months["June"] = 5;
	months["July"] = 6;
	months["August"] = 7;
	months["September"] = 8;
	months["October"] = 9;
	months["November"] = 10;
	months["December"] = 11;

	struct tm t;
	time_t t_of_day;
	

	t.tm_year = stoi(year) - 1900;  
	t.tm_mon = months[month];           
	t.tm_mday = stoi(day);          
	t.tm_hour = stoi(hour);
	t.tm_min = stoi(minute);
	t.tm_sec = 0;
	t.tm_isdst = -1;        
	t_of_day = mktime(&t);

	return (long)t_of_day;

	//SOURCE: https://www.epochconverter.com/programming/c

}

int main()
{
	ifstream data("data.csv");

	cout << "Welcome to the bitcoin portfolio calculator!" << endl;
	cout << "Enter input in the following format: Month day, year time(military) [Amount of USD spent on bitcoin on that day]" << endl;
	cout << "Example: November 10, 2021 15:14 500.00" << endl;
	cout << "Enter -1 followed by a space when you are finished and the calculator will tell you what your bitcoin is worth today." << endl;

	double btcPrice = 22453.30; //(7/21/2022)

	string month;
	string day;
	string year;
	string hour;
	string minute;
	string USD;

	//Takes in the user input, generates a time stamp based off the time inputted.
	//TODO: Fix ending the loop, doesn't work properly right now. If anyone knows how to fix it by all means go ahead

	while (true) {
		getline(cin, month, ' ');

		if (month.compare("-1") == 0) {
			break;
		}

		getline(cin, day, ',');
		getline(cin, year, ' ');
		getline(cin, year, ' ');
		getline(cin, hour, ':');
		getline(cin, minute, ' ');
		getline(cin, USD, '\n');

		cout << "Month: " << month << endl;
		cout << "Day: " << day << endl;
		cout << "Year: " << year << endl;
		cout << "Hour: " << hour << endl;
		cout << "Minute: " << minute << endl;
		cout << "USD: " << USD << endl;

		cout << generateTimeStamp(month, day, year, hour, minute);
	}


	return 0;
}

