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

void RadixSort(vector<string> &arr, int stringLen){
    const int BUCKETS = 256;
    int N = arr.size();
    vector<string> buffer(N);
    vector<string> *in = &arr;
    vector<string> *out = &buffer;

    for (int pos = stringLen-1; pos>=0; --pos){
        vector<int> count(BUCKETS + 1);
        for (int i=0; i < N; ++i)
            ++count[(*in)[i][pos]+1];
        for (int b = 1; b <= BUCKETS; ++b)
            count[b] += count[b-1];
        for (int i = 0; i < N; ++i)
            (*out)[count[(*in)[i][pos]]++] = move((*in)[i]);
        //swap in and out roles
        swap(in, out);
    }
    //if odd number of passes, in is buffer, out is arr; so move back
    if (stringLen % 2 == 1)
        for (int i =0; i < arr.size(); ++i)
            (*out)[i] = move((*in)[i]);
}

void sortDataList(list<Data *> &l) {
    // Fill this in;
    l.sort(compare);
    vector<string> SSN(l.size());
    cout << "list size" << l.size() << "\n";
//    for (int i=0; i<l.size(); i++){
//       SSN[i] = l->ssn;
//    }
    for (auto pData:l)

        RadixSort(SSN, l.size());
}