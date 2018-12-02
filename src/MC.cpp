#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <chrono>
#include <complex>
#include <cmath>
#include <ctime>
#include "..\include\particle.hpp"
#include "..\include\system.hpp"


const double K = 1.38e-23;
const double T = 300;

/*std::vector<double> g2Function(System state, double rInitial, double rStep, double sizeBin, double boxLength)
{
	std::vector<double> g2function;

	for (double r = rInitial; r <= boxLength / 2; r += rStep)
	{
		g2function.push_back(state.g2(r,sizeBin));
	}
	return g2function;
}*/

/*std::vector<std::vector<double>> averageOfg2(std::vector<System> systems, double rInitial, double rStep, double sizeBin, double boxLength)
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
}*/

bool isAcceptedE(System state, System anotherState)                    //It is for testing whether the nwe state can be accepted or not.
{
	double deltaEnergy = anotherState.getEnergy() - state.getEnergy();  //It is the energy diffence between two state.
	double relativePossibility = exp(-deltaEnergy / (K*T));
	srand((unsigned int)(time(NULL)));
	double test = std::rand() / double(RAND_MAX);
	if (test < relativePossibility)
		return true;
	else return false;
}

double sk(System state, double kx, double ky)
{
	std::vector<std::vector<double>> coordinates=state.coordinates();
	std::vector<std::vector<double>> kTimesCoordinates();
	const std::complex<double> i(0, 1);
	std::complex<double> ek(0, 0);
	double sk;
	for (int i = 0; i < state.numberOfParticles(); i++)
	{	
		ek = exp(i*(kx*coordinates[i][0]+ ky*coordinates[i][1]));
		ek = ek + ek;
	}
	sk = norm(ek)/state.numberOfParticles();
	return sk;
}

bool isAcceptedSk(System state, System anotherState, double kx, double ky)
{
	double deltaEnergy = sk(anotherState, kx, ky) - sk(state, kx, ky);  //It is the sk diffence between two state.
	double relativePossibility = exp(-deltaEnergy / (K*T));
	srand((unsigned int)(time(NULL)));
	double test = std::rand() / double(RAND_MAX);
	if (test < relativePossibility)
		return true;
	else return false;
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
	const double pi = 3.1415926;
	double density;
	//density = 0.5;
	double radius;
	//radius = 0.02;
	const int length = 1;
	int numberOfMC, number; //number is the number of particles.
	numberOfMC = 100;

	std::vector<System> systems;

	/*std::cout << "Enter the density of partiles: ";
	std::cin >> density;
	std::cout << "Enter the radius of particles: ";
	std::cin >> radius;
	*/

		radius = 0.02;
		density = 0.5;
		number = int(density / (pi * radius * radius));

		//saveData(g2Function(state, 0.01, 0.01, length),"g2");
		System state(density, radius, length, number);            //It is a initial configuration.
		systems.push_back(state);
		System stateOld;
		stateOld = state;
		double kx = (2 * pi) / length;
		double ky = (2 * pi) / length;

		srand((unsigned int)(time(NULL)));
		for (int i = 0; i < numberOfMC*number; i++)               //It is the MC method.  
		{
			int k;
			k = std::rand() % number;
			state.evolve(0.1, k);
			std::cout << "\r   Particles " << i + 1 << '/' << numberOfMC*number + 1 << "  is moving." << std::flush;
			if (isAcceptedSk(stateOld, state, kx, ky))
			{
				//systems.push_back(state);
				stateOld = state;

			}
			/*else
			{
				//systems.push_back(stateOld);
				state = stateOld;
			}*/
		}

		std::cout << std::endl;
		//int n = systems.size();
		//saveData(systems[n - 1].coordinates(), "density_" + std::to_string(density) + "-radius_" + std::to_string(radius) + "-number_" + std::to_string(number) + "-numberMC_" + std::to_string(numberOfMC));
		saveData(stateOld.coordinates(), "density_" + std::to_string(density) + "-radius_" + std::to_string(radius) + "-number_" + std::to_string(number) + "-numberMC_" + std::to_string(numberOfMC));

}


