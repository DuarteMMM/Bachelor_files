#ifndef __box__
#define __box__

class Box {

private:

   float x, y, z;
									
public:

   Box (float fx = 1., float fy = 1., float fz = 1.);

   ~Box() = default;
	
   Box (const Box& otherBox);

   const Box& operator= (const Box& otherBox);
   
   const Box operator+ (const Box& otherBox);
   
   float getVolume();
   
   Box* Add (const Box* otherBox);
};

#endif
