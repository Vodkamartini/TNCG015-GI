#include "../include/Utilities.h"

double uniformRand() {
	return DISTR(GENERATOR);
}

double randMinMax(const double& min, const double& max) {
	return min + uniformRand() * (max - min);
}
