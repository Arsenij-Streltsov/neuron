#pragma once
#
class Neuron
{
public :

	double Value, ActiveValue,Error;
	
	double Diff();

	void Activate();
};

