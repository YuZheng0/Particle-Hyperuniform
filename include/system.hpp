#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include "particle.hpp"

class System
{
public:
	System(double,double,double);
	System();
	int numberOfParticles();
	bool addParticle(Particle newParticle);
	// void getDistance();
	double getEnergy();
	std::vector<std::vector<double>> coordinates();
	//System & operator=(const System& other);
	double g2(double,double);
	void evolve(double, int);
private:
	std::vector<Particle> particles;
	//std::vector<double> distances;
	double density;
	double length;
	std::size_t number; //The number of particles
};



#endif
