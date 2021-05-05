// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2021

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " "
       << pData->firstName << " "
       << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class definitions here if you wish.


bool compare(const Data* id1, const Data* id2) {
    //implementation of the built-in l.sort()
    if (id1->lastName < id2->lastName)
        return true;
    if (id1->lastName > id2->lastName)
        return false;
    if (id1->firstName < id2->firstName)
        return true;
    if (id1->firstName > id2->firstName)
        return false;
    if (id1->ssn <= id2->ssn)
        return true;
    else
        return false;
}

//implementation of radix sort
int ssnStringToInt(Data* data){
    //converts SSN string to an int, to be sorted with radix sort
    return stoi(data->ssn.substr(0,3) + data->ssn.substr(4,2) + data->ssn.substr(7,4));
}

string ssnIntToString(int ssn){
    //converts ssn in int form to string
    string stringSSN = to_string(ssn);
    //add leading 0's until the string length is 9
    while(!(stringSSN.length() == 9))
        stringSSN = "0" + stringSSN;
    stringSSN.insert(3, "-");
    stringSSN.insert(6, "-");
    return stringSSN;
}

int getMax(const int arr[], int len){
    //finds the max length of the ssn in int form (not all will be 9 digits, b/c conversion drops leading 0's)
    int max = arr[0];
    for (int i = 1; i < len; i++){
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

int ssnArray[1010001]; //array to store ssn once converted to int form

void binSort(int preSort[], int len, int position){
    int buckets[10] = {0};
    for(int i = 0; i < len; i++)
        buckets[(preSort[i]/position) % 10]++;
    for(int bucketIndex = 1; bucketIndex < 10; bucketIndex++)
        buckets[bucketIndex] += buckets[bucketIndex - 1];
    for(int j = len - 1; j >= 0; j--){
        ssnArray[buckets[(preSort[j]/position) % 10] - 1] = preSort[j];
        buckets[(preSort[j]/position) % 10]--;
    }
    for (int k = 0; k < len; k++)
        preSort[k] = ssnArray[k];
}

void radixSort(int preSort[], int len){
    int max = getMax(preSort, len);
    for (int position = 1; max/position > 0; position *= 10)
        binSort(preSort, len, position);
}

int tempArr[1010001]; //array of int versions of ssn to be sorted in radix, allocated enough memory to store within 1% of 1mil ssn
//made global so it is static memory

void sortDataList(list<Data *> &l) {
    // Fill this in;
    //for samples 1, 2, 3, use l.sort()
    if (!(l.front()->lastName == l.back()->lastName))
        l.sort(compare);
    //for sample4 use radix on ssn
    else {
        int i = 0, lSize = l.size();
        for(auto ids:l){
            if(i == lSize)
                break;
            tempArr[i++] = ssnStringToInt(ids);
        }
        radixSort(tempArr, lSize);

        i = 0;
        for(auto ids:l){
            if(i == lSize)
                break;
            ids->ssn = ssnIntToString(tempArr[i++]);
        }
    }
}