#include "NeuralNetwork.h"
#include "Neuron.h"
#include <ctime>
#include <stdlib.h>
#include <iostream>
NeuralNetwork :: NeuralNetwork(int L, int* S) {

	srand(time(NULL));

	Layers = L;
	Size = new int[L];

	Neurons = new  Neuron * [L];
	Weigth = new double** [L - 1];

	for (int i = 0; i < L; i++) {
		Size[i] = S[i];
		Neurons[i] = new Neuron[S[i]];

		if (i > L - 2) continue;
		Weigth[i] = new double* [S[i]];
		for (int j = 0; j < S[i]; j++) {

			Weigth[i][j] = new double[S[i + 1]];


			for (int k = 0; k < S[i+1]; k++) {
				Weigth[i][j][k] = double(rand() % 100) * 0.01;
			}
		}

	}



}

NeuralNetwork :: ~NeuralNetwork() {
	delete[] Size;
	delete[] Weigth;
	delete[] Neurons;
}

void NeuralNetwork::SetInput(double* input)
{
	for (int j = 0; j < Size[0]; j++) {
		Neurons[0][j].ActiveValue = input[j];
	}
}

void NeuralNetwork::ForwardFeed()
{
	for (int i = 1; i < Layers; i++) {
		for (int j = 0; j < Size[i]; j++)
		{
			Neurons[i][j].Value = 0.0;

			for (int k = 0; k < Size[i - 1]; k++) {
				Neurons[i][j].Value += Neurons[i - 1][k].ActiveValue * Weigth[i - 1][j][k];
			}
			Neurons[i][j].Activate();
		}
	}
}

void NeuralNetwork::GetOut()
{
	for (int j = 0; j < Size[Layers - 1]; j++) {
		std::cout << Neurons[Layers - 1][j].ActiveValue <<' ';
	}
}

void NeuralNetwork::BackPropogation(double* y,double ls)
{
	for (int i = 0; i < Size[Layers - 1]; i++) {
		Neurons[Layers - 1][i].Error = 2 * (Neurons[Layers - 1][i].ActiveValue - y[i]);
	}
	for (int k = Layers - 2; k >= 0; k--) {
		for (int i = 0; i < Size[k]; i++) {
			Neurons[k][i].Error = 0.0;
			for (int j = 0; j < Size[k + 1]; j++) {
				Neurons[k][i].Error += Neurons[k+1][j].Error * Neurons[k+1][j].Diff() * Weigth[k][i][j];
				Weigth[k][i][j]  -= ls*Neurons[k+1][j].Error * Neurons[k+1][j].Diff() * Neurons[k][i].ActiveValue;
			
			}
		}
	}
}

int NeuralNetwork::Predict()
{
	int ind = 0;
	double mx = 0;
	for (int i = 0; i < Size[Layers - 1]; i++) {
		if(mx < Neurons[Layers-1][i].ActiveValue){
			mx = Neurons[Layers - 1][i].ActiveValue;
			ind = i;
		}
	}
	return ind;
}

double NeuralNetwork::ErrorCounter(double* y)
{
	double ans = 0;
	for (int i = 0; i < Size[Layers - 1]; i++) {
		ans += pow((y[i] - Neurons[Layers - 1][i].ActiveValue),2);
	}
	return ans;
}
