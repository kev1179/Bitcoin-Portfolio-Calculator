#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <forward_list>
#include <list>
#include <iomanip>
#include <queue>

using namespace std;

//TODO: Implement Heap
template <typename T>
class Heap {
private:
	vector<T> heap;
	string type; //Would either be "min" or "max"
	bool isMax;
	int size;
public:
	//Constructor for heap, specifies which type of heap it is and sets a boolean variable for you to use later.
	Heap(string type) {
		heap = {};
		this->type = type;
		size = 0;

		if (type.compare("max") == 0)
			isMax = true;
		else
			isMax = false;
	}

	//Returns the element at the top of the heap
    T top()
    {
        return heap[0];
    }
		

	//Takes out the element at the top and returns it. Here you would need to implement heapify down which can be found in the slides.
	T extractTop() {
        T top = heap[0];
        heap[0] = heap[size - 1];
        heap.pop_back();
        size--;
        if (isMax)
            heapifyDown(0);
        else
            minHeapifyDown(0);
        return top;
	}

	//Inserts an element into the heap. Here you would need to write heapify up which can also be found in the slides.
	void insert(T val) {
        heap.push_back(val);
        size++;
        if (isMax)
            heapifyUp(size - 1);
        else
            minHeapifyUp(size - 1);
	}

	void heapifyDown(int index) {
	    int left, right, largest;

	    left = 2 * index + 1;
        right = 2 * index + 2;
        largest = index;

        if (left < size && (heap[left] > heap[index] || (heap[left] == heap[index] && isMax)))
            largest = left;
        if (right < size && (heap[right] > heap[largest] || (heap[right] == heap[largest] && isMax)))
            largest = right;
        if (largest != index) {
            T temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;
            heapifyDown(largest);
        }
    }

    // create heapify up function
    void heapifyUp(int index) {
        if (index == 0)
            return;
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent] || (heap[index] == heap[parent] && isMax)) {
            T temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            heapifyUp(parent);
        }
    }

    // implement min heapify down function
    void minHeapifyDown(int index) {
        int left, right, smallest;

        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;

        if (left < size && heap[left] < heap[index])
            smallest = left;
        if (right < size && heap[right] < heap[smallest])
            smallest = right;
        if (smallest != index) {
            T temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;
            minHeapifyDown(smallest);
        }
    }

    // implement min heapify up function
    void minHeapifyUp(int index) {
        if (index == 0)
            return;
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) {
            T temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;
            minHeapifyUp(parent);
        }
    }

    bool empty()
    {
        if (size == 0)
        {
            return true;
        }
        return false;
    }
};

template <typename T1, typename T2>
class Entry
{
    T1 key;
    T2 value;
public:
    //Constructor for Entry
    Entry(T1 key, T2 value)
    {
        this->key = key;
        this->value = value;
    }

    T1& getKey()
    {
        return key;
    }

    T2& getValue()
    {
        return value;
    }
};

//TODO: Implement HashMap
template <typename T1, typename T2>
class HashMap
{
    vector<list<Entry<T1, T2>>> hashTable;
    int size;
    const double maxLoadFactor = 0.8;
public:
    //Constructor for HashMap
    HashMap()
    {
        list<Entry<T1, T2>> emptyList;
        for (int i = 0; i < 5; i++)
        {
            hashTable.push_back(emptyList);
        }
        size = 0;
    }

    //Hash function
    int hasherFunc(T1 key)
    {
        return key % (hashTable.size() * 60) / 60;
    }

    //Creates an entirely new hashmap if load factor approached maxLoadFactor
    void rehash()
    {
        vector<list<Entry<T1, T2>>> originalTable = hashTable;
        hashTable.clear();

        list<Entry<T1, T2>> emptyList;
        hashTable.resize(originalTable.size() * 2, emptyList);
        size = 0;

        for (int i = 0; i < originalTable.size(); i++)
        {
            if (!originalTable[i].empty())
            {
                for (auto itr = originalTable[i].begin(); itr != originalTable[i].end(); itr++)
                {
                    insert(itr->getKey(), itr->getValue());
                }
            }
        }
    }

	//Inserts entry to hashmap
	void insert(T1 key, T2 val)
	{
        int index = hasherFunc(key);

        Entry<T1, T2> entry(key, val);
        hashTable[index].push_back(entry);
        size++;

        double loadFactor = (double) size / hashTable.size();
        if (loadFactor >= maxLoadFactor)
        {
            rehash();
        }
	}

    //Accesses key and returns value
    T2& access(T1 key)
    {
        int index = hasherFunc(key);

        auto itr = find(key, index);
        T2 value = 0.0;

        if (itr != hashTable[index].end())
        {
            value = itr->getValue();
        }
        return value;
    }

	//Removes an entry from the hashmap based on the key
	void remove(T1 key)
	{
        int index = hasherFunc(key);

        auto itr = find(key, index);
        if (itr != hashTable[index].end())
        {
            hashTable[index].erase(itr);
        }
	}

    //Finds a key from the hashmap
    typename list<Entry<T1, T2>>::iterator find(T1 key, int index)
    {
        if (!hashTable[index].empty())
        {
            for (auto itr = hashTable[index].begin(); itr != hashTable[index].end(); itr++)
            {
                if (key == itr->getKey())
                {
                    return itr;
                }
            }
        }
        return hashTable[index].end();
    }

    //Prints all entries from hashmap
    void print()
    {
        for (int i = 0; i < hashTable.size(); i++)
        {
            cout << i << ":";
            for (auto itr = hashTable[i].begin(); itr != hashTable[i].end(); itr++)
            {
                cout << " <" << itr->getKey() << ", " << itr->getValue() << ">";
            }
            cout << endl;
        }
    }

    //Returns # of entries in table
    int entries()
    {
        return size;
    }

    //Returns bucket size
    int bucket_count()
    {
        return hashTable.size();
    }
};

//Generates a timestamp. Works properly, has been tested using an online converter!
long generateTimeStamp(string month, string day, string year, string hour, string minute) 
{
    if (month[0] == '\n')
    {
        month.erase(month.begin());
    }

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

//Reads the data from the csv file and places it into a hashmap.
//Right now, we are using the STL hashmap but when we're done we will change this to our own.
void populateMap(HashMap<long, double>& priceMap, ifstream& data) 
{
    cout << "LOADING..." << endl;
	string line;
	getline(data, line);
	vector<string> tempVector;
	while (getline(data, line)) {
		tempVector.clear();
		stringstream stream(line);
		string temp;
		while (getline(stream, temp, ',')) {
			tempVector.push_back(temp);
		}
		if (tempVector[1].compare("NaN") != 0) {
			priceMap.insert(stol(tempVector[0]), stod(tempVector[1]));
		}
		
	}
	cout << "DONE!" << endl;
}

void option1(HashMap<long, double> priceMap)
{

    cout << "Welcome to the bitcoin portfolio calculator!" << endl;
    cout << "Enter input in the following format: Month day, year time(military) [Amount of USD spent on bitcoin on that day]" << endl;
    cout << "Example: November 10, 2020 15:14 500.00" << endl;
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
    double totalBTC = 0.0;

    while (true)
    {
        getline(cin, month, ' ');

        if (month.compare("-1") == 0)
        {
            break;
        }

        getline(cin, day, ',');
        getline(cin, year, ' ');
        getline(cin, year, ' ');
        getline(cin, hour, ':');
        getline(cin, minute, ' ');
        getline(cin, USD, '\n');

        long timeStamp = generateTimeStamp(month, day, year, hour, minute);

        double purchaseBTCPrice = priceMap.access(timeStamp);
        totalBTC += stod(USD) / purchaseBTCPrice;

        //cout << timeStamp << "\n";
        //cout << totalBTC * btcPrice << endl;
    }

    cout << "You own " << totalBTC << " total bitcoin" << endl;
    cout << "Today, your portfolio is currently worth $" << fixed << setprecision(2) << totalBTC * btcPrice << endl;
}

void option2(ifstream& data)
{
    Heap<double> maxPrices("max");
    Heap<double> minPrices("min");
    cout << "Enter two dates(first date must be before the second)" << endl;
    cout << "Enter input in the following format: Month day, year time(military)" << endl;
    cout << "Example: November 10, 2020 15:14" << endl;
    cout << "The calculator will then tell you the top 10 highest and lowest Bitcoin prices on that interval." << endl;

    long timeStamp1 = 0;
    long timeStamp2 = 0;

    string month;
    string day;
    string year;
    string hour;
    string minute;

    for (int i = 0; i < 2; i++)
    {
        getline(cin, month, ' ');
        getline(cin, day, ',');
        getline(cin, year, ' ');
        getline(cin, year, ' ');
        getline(cin, hour, ':');
        getline(cin, minute, '\n');

        if (i == 0)
        {
            timeStamp1 = generateTimeStamp(month, day, year, hour, minute);
        }
        else
        {
            timeStamp2 = generateTimeStamp(month, day, year, hour, minute);
        }
        
    }
    long startPoint = (timeStamp1 - 1325317920) / 60;
    long endPoint = (timeStamp2 - 1325317920) / 60;

}

int main()
{
	ifstream data("data.csv");

    HashMap<long, double> priceMap;
    populateMap(priceMap, data);
    int option;

    cout << "Pick the feature you would like to use: " << endl;
    cout << "1. Bitcoin Portfolio calculator (Implemented via hashmap)" << endl;
    cout << "2. Top 10 highest and lowest prices on an interval (implemented via heap)" << endl;
    cin >> option;

    if (option == 1)
    {
        option1(priceMap);
    }
    else
    {
        option2(data);
    }
    

	return 0;
}


/*
void heapTest()
{
    int casesPassed = 0;
    //******************************** CASE 1 *****************************************************************
    Heap<double> test1("max");
    priority_queue<double> test1STL;
    vector<double> values = { 8.2, 100.8, 23.4, 54.1, 1000.0, 121.4, 8.1, 11.0, 7.9, 234.8 };
    for (int i = 0; i < values.size(); i++)
    {
        test1.insert(values[i]);
        test1STL.push(values[i]);
    }
    vector<double> sorted1;
    vector<double> sorted1STL;
    while (!test1STL.empty())
    {
        sorted1.push_back(test1.extractTop());
        double temp = test1STL.top();
        test1STL.pop();
        sorted1STL.push_back(temp);
    }
    if (sorted1 != sorted1STL)
    {
        cout << "CASE 1 FAILED: max heap sort" << endl;
    }
    else
    {
        casesPassed++;
    }
    //*********************************************** CASE 2 ***********************************************
    Heap<double> test2("max");
    test2.insert(3.14);
    test2.insert(3.13);
    test2.insert(3.141);
    test2.insert(3.139);
    test2.insert(3.12);
    test2.insert(3.13999);
    test2.insert(3.1401);
    if (test2.extractTop() == 3.141)
    {
        casesPassed++;
    }
    else
    {
        cout << "CASE 2 FAILED: extracting top in a max heap" << endl;
    }
    //******************************************** CASE 3 *********************************************
    Heap<double> test3("max");
    test3.insert(12.6);
    test3.insert(78.9);
    test3.insert(87.3);
    test3.insert(1.24);
    test3.extractTop();
    test3.insert(100.89);
    test3.extractTop();
    test3.extractTop();
    test3.extractTop();
    test3.insert(50.8);
    vector<double> answer = { 50.8, 1.24 };
    vector<double> testing3;
    while (!test3.empty())
    {
        testing3.push_back(test3.extractTop());
    }
    if (answer == testing3)
    {
        casesPassed++;
    }
    else
    {
        cout << "CASE 3 FAILED: mixing insertions and deletions " << endl;
    }
    //************************************************** CASE 4 ******************************************************
    Heap<double> test4("min");
    priority_queue<double, vector<double>, greater<double>> test4STL;
    vector<double> values2 = { 8.2, 100.8, 23.4, 54.1, 1000.0, 121.4, 8.1, 11.0, 7.9, 234.8 };
    for (int i = 0; i < values2.size(); i++)
    {
        test4.insert(values2[i]);
        test4STL.push(values2[i]);
    }
    vector<double> sorted4;
    vector<double> sorted4STL;
    while (!test4STL.empty())
    {
        sorted4.push_back(test4.extractTop());
        double temp = test4STL.top();
        test4STL.pop();
        sorted4STL.push_back(temp);
    }
    if (sorted4 != sorted4STL)
    {
        cout << "CASE 4 FAILED: min heap sort" << endl;
    }
    else
    {
        casesPassed++;
    }
    //*********************************************** CASE 5 ***********************************************
    Heap<double> test5("min");
    test5.insert(3.14);
    test5.insert(3.13);
    test5.insert(3.141);
    test5.insert(3.139);
    test5.insert(3.12);
    test5.insert(3.13999);
    test5.insert(3.1401);
    if (test5.extractTop() == 3.12)
    {
        casesPassed++;
    }
    else
    {
        cout << "CASE 5 FAILED: extracting top in a min heap" << endl;
    }
    //******************************************** CASE 6 *********************************************
    Heap<double> test6("min");
    test6.insert(12.6);
    test6.insert(78.9);
    test6.insert(87.3);
    test6.insert(1.24);
    test6.extractTop();
    test6.insert(100.89);
    test6.extractTop();
    test6.extractTop();
    test6.extractTop();
    test6.insert(50.8);
    vector<double> answer6 = { 50.8, 100.89 };
    vector<double> testing6;
    while (!test6.empty())
    {
        testing6.push_back(test6.extractTop());
    }
    if (answer6 == testing6)
    {
        casesPassed++;
    }
    else
    {
        cout << "CASE 6 FAILED: mixing insertions and deletions in min heap" << endl;
    }
    cout << "Passed " << casesPassed << "/6 cases" << endl;
}
void mapTest()
{
    int casesPassed = 0;
    //******************************** CASE 1 *****************************************************************
    HashMap<long,double> test1;
    test1.insert(1597262280, 11581.939197);
    test1.insert(1597262340, 11572.065746);
    cout << test1.access(8237489273492) << endl;
    cout << test1.access(1597262340) << endl;
    test1.print();
}
int main()
{
    cout << "Heap test cases: " << endl;
    heapTest();
    cout << "****************************************************************************************************************" << endl;
    cout << "Hashmap test cases: " << endl;
    mapTest();
    return 0;
}
*/