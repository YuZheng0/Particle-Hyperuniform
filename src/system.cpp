#include <vector>
#include <cmath>
#include <ctime>
#include "..\include\system.hpp"


System::System() {}

System::System(double initDensity, double radius, double l, int N)
{
	const double pi = 3.1415926;
	length = l;
	density = initDensity;
	number = N;

	srand((unsigned int)(time(NULL)));
	while (particles.size() < number)
	{
		double x = length*(std::rand() / double(RAND_MAX));
		double y = length*(std::rand() / double(RAND_MAX));
		Particle particle(x, y, radius);
		addParticle(particle);
	}
}

int System::numberOfParticles()
{
	int i;
	i = particles.size();
	return i;
}

bool System::addParticle(Particle particle)
{
	bool overlap = false;
	for (std::size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i].isOverlap(particle, length))
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

/*double System::g2(double r, double sizeBin)
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
}*/

void System::evolve(double moveRange, int k)
{
	double dx, dy, oldX, oldY, delta;
	oldX = particles[k].getX();
	oldY = particles[k].getY();
	delta = 1e-10;
	
	srand((unsigned int)(time(NULL)));
	while (std::abs(oldX-particles[k].getX())<delta && std::abs(oldY-particles[k].getY())<delta)
	{
		dx = moveRange*(std::rand() / double(RAND_MAX) - 0.5);
		dy = moveRange*(std::rand() / double(RAND_MAX) - 0.5);

		particles[k].move(dx, dy);
		// Consider the boundary conditions.
		if (particles[k].getX() < 0)
		{
			particles[k].move(length, 0);
			dx = dx + length;
		}
		if (particles[k].getX() > length)
		{
			particles[k].move(-length, 0);
			dx = dx - length;
		}
		if (particles[k].getY() < 0)
		{
			particles[k].move(0, length);
			dy = dy + length;
		}
		if (particles[k].getY() > length)
		{
			particles[k].move(0, -length);
			dy = dy - length;
		}

		for (std::size_t i = 0; i < particles.size(); i++)
		{
			if (k!=i && particles[k].isOverlap(particles[i], length))
				particles[k].move(-dx, -dy);
		}
	}
	
}