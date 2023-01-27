#ifndef __segment__
#define __segment__
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class segment{
public:
segment (vector<pair<float,float>> SEG2={{0.0,0.0}, {0.0,0.0}}); // constructor
~segment() = default; // destructor
segment (const segment& othersegment); // copy constructor
const segment& operator= (const segment& othersegment); // copy assignment

void Dump() const; // Escrever valores



private:
vector<pair<float,float>> SEG;
};


#endif
