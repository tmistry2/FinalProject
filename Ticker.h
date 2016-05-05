/*
*
*	Ticker object to count milliseconds
*	Not sure how it works, but it ain't broken...
*
*/
#include <chrono>
#include <ctime>

using namespace std::chrono;

// class object that counts time in milliseconds
class Ticker
{	
	high_resolution_clock::time_point ms1;
	double ms2;
	time_t s1;
	int s2;
public:
	// Ticker object gets counts milliseconds since last epoch
	Ticker()
	{
		ms1 = high_resolution_clock::now();
		s1 = time(NULL);
	}
	// gets milliseconds since last epoch (fraction of a second)
	double getMS()
	{
		high_resolution_clock::time_point ms = high_resolution_clock::now();
		duration<double> drt = ms.time_since_epoch();
		return drt.count();
	}
	// gets seconds since last epoch
	int getS(){ return time(NULL);}
	// records current time
	void start()
	{
		ms1 = high_resolution_clock::now();
		s1 = time(NULL);
	}
	// set a duration to pass (ms)
	void durationMS (int dur)
	{
		ms2 = getMS()+dur*0.001;
	}
	// check if duration (ms) has passed
	bool passMS()
	{
		return (getMS() >= ms2);
	}
	// set a duration to pass (s)
	void durationS(int dur)
	{
		s2 = getS()+dur;
	}
	// check if duration (s) has passed
	bool passS()
	{
		return (time(NULL) >= s2);
	}
};