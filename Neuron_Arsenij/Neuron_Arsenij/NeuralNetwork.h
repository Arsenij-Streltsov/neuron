#pragma once
#include "Neuron.h"
#include <ctime>
#include <stdlib.h>
class NeuralNetwork
{
public:

	int Layers;
	int* Size;
	Neuron** Neurons;
	double*** Weigth;
	
	NeuralNetwork(int L, int* S);
	~NeuralNetwork();

	void SetInput(double* input);

	void ForwardFeed();

	void GetOut();

	void BackPropogation(double*,double);

	int Predict();

	double ErrorCounter(double*);

};

