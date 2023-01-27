#ifndef __motion1d__
#define __motion1d__

class Motion1D{
	public:
	Motion1D (int N=0);
	virtual ~Motion1D();

	void SetMotion (float* t, float* x, int);
	int GetN() const; // returns number of points
	float* GetTimes() const; // returns array of times
	float* GetPositions() const; // returns array of positions
	
	virtual void Print();
	virtual float TotalDistance(); // total distance
	virtual float MeanVelocity(); // mean velocity
	
	protected:
	int N; // number of points
	float* t; // time array
	float* x; // position array
};

#endif
