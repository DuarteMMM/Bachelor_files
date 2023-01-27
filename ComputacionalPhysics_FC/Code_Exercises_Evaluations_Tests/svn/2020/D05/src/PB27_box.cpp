#include "PB27_box.h"


Box::Box(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}


Box::Box(const Box& otherBox) : x(otherBox.x), y(otherBox.y), z(otherBox.z) {}


const Box& Box::operator= (const Box& otherBox) {

  if (this != &otherBox) {
    x = otherBox.x;
    y = otherBox.y;
    z = otherBox.z;
  }
  
  return *this;
}


 const Box Box::operator+ (const Box& otherBox) {

   Box return_box (x + otherBox.x , y + otherBox.y, z + otherBox.z);
   
  return return_box;

}


float Box::getVolume() {

  return x * y * z;

}


Box* Box::Add (const Box* p_otherBox) {

  Box* return_box = new Box(x + p_otherBox->x , y + p_otherBox->y, z + p_otherBox->z);

  return return_box;
  
}
