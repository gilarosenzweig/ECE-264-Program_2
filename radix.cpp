////
//// Created by GRosenzweig on 5/3/2021.
////
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <list>
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <ctime>
//#include <cmath>
//#include <cstring>
//#include <cctype>
//#include <cstdlib>
//using namespace std;
//// working on Radix sort for SSN, need to figure out how to populate a vector with the ssn
//void RadixSort(vector<string> &arr, int stringLen){
//    const int BUCKETS = 256;
//    int N = arr.size();
//    vector<string> buffer(N);
//    vector<string> *in = &arr;
//    vector<string> *out = &buffer;
//
//    for (int pos = stringLen-1; pos>=0; --pos){
//        vector<int> count(BUCKETS + 1);
//        for (int i=0; i < N; ++i)
//            ++count[(*in)[i][pos]+1];
//        for (int b = 1; b <= BUCKETS; ++b)
//            count[b] += count[b-1];
//        for (int i = 0; i < N; ++i)
//            (*out)[count[(*in)[i][pos]]++] = move((*in)[i]);
//        //swap in and out roles
//        swap(in, out);
//    }
//    //if odd number of passes, in is buffer, out is arr; so move back
//    if (stringLen % 2 == 1)
//        for (int i =0; i < arr.size(); ++i)
//            (*out)[i] = move((*in)[i]);
//}
//
//int main(){
//    vector<string> stupid{"104-90-7534", "104-80-7534", "104-70-7534", "105-90-7534", "105-90-7534"};
//
//    cout << "Executing sort...\n";
//    clock_t t1 = clock();
//    RadixSort(stupid, 11);
//    clock_t t2 = clock();
//    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
//
//    cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";
//    return 0;
//}
//
