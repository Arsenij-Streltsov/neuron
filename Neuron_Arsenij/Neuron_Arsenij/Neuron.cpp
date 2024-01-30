#include "Neuron.h"
#include <cmath>

double Neuron::Diff() {

	return ActiveValue * (1 - ActiveValue);

}

void Neuron::Activate() {

	ActiveValue = 1 / (1 + exp(-Value));

}