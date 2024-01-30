#include "NeuralNetwork.h"
#include <iostream>

using namespace std;

int main() {

	int Layers = 2, Size[] = {9,2};

	

	NeuralNetwork Nn(Layers, Size);



	double input[9] = { 0,1,0,
						0,1,0,
						0,1,0};
	double output[2] = { 0,1 },ot = 1;

	double s = 0.0,e = 0.0;

	while (s < 0.7) {

		s = 0;
		e = 0;

		for (int i = 0; i < 10; i++) {
			Nn.SetInput(input);
			Nn.ForwardFeed();
			if (Nn.Predict() == ot) s++;
			Nn.BackPropogation(output,0.001);
			e += Nn.ErrorCounter(output);
		}
		
		s /= 10;
		e /= 10;

		cout << s << '\t' << e << '\n';

	}
	
	for (int i = 0; i < 9; i++) {
		cin >> input[i];
	}

	Nn.SetInput(input);
	Nn.ForwardFeed();

	cout << bool(Nn.Predict() == ot);

	return 0;
}