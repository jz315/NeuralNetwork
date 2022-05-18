#include "Decay.h"

Decay::Decay(long double step):
	mInitLearningRate(step)
{
}

long double Decay::GetLearningRate(int batchSize)
{
	return mInitLearningRate;
}

ExponentialDecay::ExponentialDecay(long double learningRate, long double decayRate, long double decayStep) :
	Decay(learningRate),
	mDecayRate(decayRate),
	mDecayStep(decayStep)
{
}

long double ExponentialDecay::GetLearningRate(int batchSize)
{
	return mInitLearningRate * pow(mDecayRate, batchSize / mDecayStep);
}
