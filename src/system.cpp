#include <vector>
#include <cmath>
#include "system.hpp"


System::System(double initDensity, double radius, double l):length(l)
{
	const double pi = 3.1415926;
	density = initDensity;
	number = int(density / (pi * radius * radius));

	while (particles.size() < number)
	{
		double x = length*(std::rand() / double(RAND_MAX));
		double y = length*(std::rand() / double(RAND_MAX));
		Particle particle(x, y, radius);
		addParticle(particle);
	}
}

bool System::addParticle(Particle particle)
{
	bool overlap = false;
	for (std::size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i].isOverlap(particle))
		{
			overlap = true;
			break;
		}
	}
	if (!overlap)
	{
		particles.push_back(particle);
		return true;
	}
	else
		return false;
}

double System::getEnergy()
{
	double energy = 0;
	const double k = 0;
	
	for (std::size_t i = 0; i < particles.size(); i++)
	{
		for (std::size_t j = i + 1; j < particles.size(); j++)
		{
			energy += k * particles[i].distance(particles[j]);
		}
	}
	
	return energy;
}

std::vector<std::vector<double>> System::coordinates()
{
	std::vector<std::vector<double>> coords;
	
	for (std::size_t i = 0; i < particles.size(); i++)
	{
		std::vector<double> coord = { particles[i].getX(), particles[i].getY() };
		coords.push_back(coord);
	}
	
	return coords;
}

double System::g2(double r, double sizeBin)
{
	const double pi = 3.1415926;
	std::vector<double> distanceForG2;
	int numberForG2 = 0;           //For recoring the particle numbers between r and delta r.
	double g2Value;
	double deltaR = sizeBin*r;

	for (std::size_t i = 0; i < particles.size(); i++)
	{
		for (std::size_t j = i + 1; j < particles.size(); j++)
		{
			distanceForG2.push_back(particles[i].boundaryDistance(particles[j], length));
		}
	}

	for (std::size_t i = 0; i < distanceForG2.size(); i++)
	{
		if (distanceForG2[i] <= (r + deltaR / 2) && distanceForG2[i] >= (r - deltaR / 2))
			numberForG2 += 2;
	}

	g2Value = numberForG2 / (particles.size() * (particles.size()/(length*length)) * 2 * pi * r * deltaR);
	return g2Value;
}

/*void System::envolve(System state, double moveRange)
{
double dx, dy;
std::vector<std::vector<double>> oldCoords = state.coordinates();
for (std::size_t i = 0; i < particles.size(); i++)
{
dx = moveRange*length*(std::rand() / double(RAND_MAX) - 0.5);
dy = moveRange*length*(std::rand() / double(RAND_MAX) - 0.5);
particles[i].move(dx, dy);
}
for (std::size_t i = 0; i < particles.size; i++)
{
for (std::size_t j = 0; j < particles.size; j++)\
{
if (particles[i].isOverlap(particles[j])


}
}
}*/