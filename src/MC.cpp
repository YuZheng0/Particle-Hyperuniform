#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <chrono>
#include "particle.hpp"
#include "system.hpp"


const double K = 1.38e-23;
const double T = 300;

std::vector<double> g2Function(System state, double rInitial, double rStep, double sizeBin, double boxLength)
{
	std::vector<double> g2function;

	for (double r = rInitial; r <= boxLength / 2; r += rStep)
	{
		g2function.push_back(state.g2(r,sizeBin));
	}
	return g2function;
}

bool isAccepted(System state, System anotherState)                    //It is for testing whether the nwe state can be accepted or not.
{
	double deltaEnergy = anotherState.getEnergy() - state.getEnergy();  //It is the energy diffence between two state.
	double relativePossibility = exp(-deltaEnergy / (K*T));
	double test = std::rand() / double(RAND_MAX);
	if (test < relativePossibility)
		return true;
	else return false;
}

std::vector<std::vector<double>> averageOfg2(std::vector<System> systems, double rInitial, double rStep, double sizeBin, double boxLength)
{
	std::vector<std::vector<double>> aveOfg2;
	std::vector<double> sumYs(int((boxLength/2 - rInitial)/rStep), 0.);

	std::cout << "Calculating average of g2...\n";

	std::vector<double> g2s;
	for (std::size_t i = 0; i < systems.size(); i++)
	{
		g2s = g2Function(systems[i], rInitial, rStep, sizeBin, boxLength);

		std::cout << "\r   g2 function for system " << i+1 << '/' << systems.size() << " processed." << std::flush;

		for (std::size_t j = 0; j < sumYs.size(); j++)
			sumYs[j] += g2s[j];
	}
	std::cout << std::endl;

	double r = rInitial;
	for (std::size_t i = 0; i < sumYs.size(); i++)
	{
		std::vector<double> coord = { r, sumYs[i] / systems.size() };
		aveOfg2.push_back(coord);
		r += rStep;
	}
	return aveOfg2;
}
	
void saveData(std::vector<std::vector<double>> &coords, std::string nameOfFile)
{
	std::ofstream file;
	file.open(nameOfFile + ".txt");
	for (std::size_t i = 0; i < coords.size(); i++)
	{
		file << coords[i][0] << ' ' << coords[i][1] << '\n';
	}
	file.close();
}

int main()
{
	// Declare variables.
	double density;
	double radius;
	const int length = 1;
	int numberOfMC;
	std::vector<System> systems;

	std::cout << "Enter the density of partiles: ";
	std::cin >> density;
	std::cout << "Enter the radius of particles: ";
	std::cin >> radius;
	std::cout << "How many times to run MC: ";
	std::cin >> numberOfMC;

	System state(density, radius, length);            //It is a initial configuration.
	//saveData(g2Function(state, 0.01, 0.01, length),"g2");
	systems.push_back(state);

	for (int i = 0; i < numberOfMC; i++)               //It is the MC method.  
	{
		System anotherState(density, radius, length);
		std::cout << "\r   State " << i + 2 << '/' << numberOfMC+1 << "  has been generated." << std::flush;
		if (isAccepted(state, anotherState))
			systems.push_back(anotherState);
		else systems.push_back(state);
	}

	std::cout << std::endl;
	saveData(averageOfg2(systems, 0.01, 0.01, 0.05, length),"density-0.5_radius-0.05_sizebin-0.05-averageOfg2");
	
}


