#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <string>
#include <sstream>
#include <unordered_map>
#include <forward_list>
#include <iomanip>

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
		return heap[0];

	//Takes out the element at the top and returns it. Here you would need to implement heapify down which can be found in the slides.
	T extractTop() {
        T top = heap[0];
        heap[0] = heap[size - 1];
        heap.pop_back();
        size--;
        heapifyDown(0);
        return top;
	}

	//Inserts an element into the heap. Here you would need to write heapify up which can also be found in the slides.
	void insert(T val) {
        heap.push_back(val);
        size++;
        heapifyUp(size - 1);
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
};

//TODO: Implement HashMap
template <typename T1, typename T2>
class HashMap 
{
private:
	vector<forward_list<pair<T1, T2>>> hashTable[5]; //If you want to use seperate chaining, I think this will be the easiest way to implement the hashmap
										//But feel free to use open addressing if you want :)
    int size;
	double loadFactor;
    const double maxLoadFactor = 0.8;
public:
    //Constructor for HashMap
    HashMap()
    {
        size = 0;
        loadFactor = 0.0;
    }

    //Hash function
    int hasherFunc(T1 key)
    {
        return key % (hashTable.size() * 60) / 60;
    }

    //Creates an entirely new hashmap if load factor approached maxLoadFactor
    void rehash()
    {
        vector<forward_list<pair<T1, T2>>> originalTable = hashTable;
        hashTable.erase(hashTable.begin(), hashTable.end());
        hashTable.size() *= 2;
        size = 0;

        for (int i = 0; i < originalTable.size(); i++)
        {
            if (!originalTable[i].empty())
            {
                for (auto itr = originalTable[i].begin(); itr != originalTable[i].end(); itr++)
                {
                    insert(get<0>(*itr), get<1>(*itr));
                }
            }
        }
    }

	//Overloaded subscript operator that allows you to access and modify elements like this: testMap[key] = val;
    /* NOT DONE YET
	T2& operator[](T1 key)
	{
        int index = hasherFunc(key);

        auto itr = find(key);
        if (itr == hashTable[index].end())
        {
            insert(key, get<1>(*itr));
        }
        else
        {

        }
        return ;
	}
     */

	//Very similar to the [] operator
	void insert(T1 key, T2 val)
	{
        int index = hasherFunc(key);

        if (!hashTable[index].empty())
        {
            for (auto itr = hashTable[index].begin(); itr != hashTable[index].end(); itr++)
            {
                if (key == get<0>(*itr))
                {
                    return;
                }
            }
            hashTable[index].push_back(make_pair(key, val));
            size++;
        }
        else
        {
            hashTable[index] = {};
            hashTable[index].push_front(make_pair(key, val));
            size++;
        }

        loadFactor = (double) size / hashTable.size();
        if (loadFactor == maxLoadFactor)
        {
            rehash();
        }
	}

	//Removes a key from the hashmap
	void remove(T1 key)
	{
        int index = hasherFunc(key);

        if (!hashTable[index].empty())
        {
            for (auto itr = hashTable[index].begin(); itr != hashTable[index].end(); itr++)
            {
                if (key == get<0>(*itr))
                {
                    hashTable[index].remove(get<0, 1>(*itr));
                    return;
                }
            }
        }
	}

    //Finds a key from the hashmap
    typename forward_list<pair<T1, T2>>::iterator find(T1 key)
    {
        int index = hasherFunc(key);

        if (!hashTable[index].empty())
        {
            for (auto itr = hashTable[index].begin(); itr != hashTable[index].end(); itr++)
            {
                if (key == get<0>(*itr))
                {
                    return itr;
                }
            }
        }
        return hashTable[index].end();
    }

    //Returns 1 if key is found in map or 0 otherwise
    int count(T1 key)
    {
        int index = hasherFunc(key);

        auto itr = find(key);
        if (itr != hashTable[index].end())
        {
            return 1;
        }
        return 0;
    }

    //Returns # of elements in table
    int numElements()
    {
        return size;
    }

    //Returns bucket size
    int bucket_count()
    {
        return hashTable.size();
    }

    //Returns the loadFactor
    double load_factor()
    {
        return loadFactor;
    }

	//Feel free to write more functions but this is just a template to get started!
	//You could also build an iterator if you need something to do.
};

//Generates a timestamp. Works properly, has been tested using an online converter!
long generateTimeStamp(string month, string day, string year, string hour, string minute) 
{
	
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
void populateMap(unordered_map<long, double>& priceMap, ifstream& data) 
{
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
			priceMap[stol(tempVector[0])] = stod(tempVector[1]);
		}
		
	}
	cout << "DONE!" << endl;
}

int main()
{
	ifstream data("data.csv");

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

	unordered_map<long, double> priceMap;
	populateMap(priceMap, data);

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
		
		double purchaseBTCPrice = priceMap[timeStamp];
		totalBTC += stod(USD) / purchaseBTCPrice;

		//cout << timeStamp << "\n";
		//cout << totalBTC * btcPrice << endl;
	}
	
	cout << "You own " << totalBTC << " total bitcoin" << endl;
	cout <<  "Today, your portfolio is currently worth $" << fixed << setprecision(2) << totalBTC * btcPrice << endl;

	return 0;
}

