#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include "particle.hpp"

class System
{
public:
	System(double,double,double);
	bool addParticle(Particle newParticle);
	// void getDistance();
	double getEnergy();
	std::vector<std::vector<double>> coordinates();
	double g2(double,double);
	// void envolve(System state, double moveRange);
private:
	std::vector<Particle> particles;
	std::vector<double> distances;
	double density;
	const double length;
	std::size_t number; //The number of particles
};



#endif
