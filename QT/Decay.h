#pragma once
#include<cmath>
class Decay
{
public:
	Decay(long double step);

	virtual long double GetLearningRate(int batchSize);
protected:
	long double mInitLearningRate;
};

class ExponentialDecay : public Decay
{
public:
	ExponentialDecay(long double learningRate, long double decayRate, long double decayStep);

	long double GetLearningRate(int batchSize)override;
private:
	long double mDecayRate, mDecayStep;
};