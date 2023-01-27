#include "Exercicio32_segment.h"
#include <cstdio>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

segment::segment (vector<pair<float,float>> SEG2) : SEG(SEG2) {}

segment::segment(const segment& othersegment) : SEG(othersegment.SEG) {}

const segment& segment::operator= (const segment& othersegment){

  if (this != &othersegment)
    SEG = othersegment.SEG;

  return *this;
}

void segment::Dump()const {
  //printf("Dump(): this=%p {(%f, %f), (%f, %f)} (%p)\n", this, SEG[0][0], SEG[0][1], SEG[1][0], SEG[1][1], SEG);
}
