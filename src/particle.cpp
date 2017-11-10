#include <cmath>
#include "particle.hpp"
#include "system.hpp"


Particle::Particle(double initX, double initY, double initRadius): radius(initRadius)
{
	x = initX;
	y = initY;
}

/*void Particle::move(double dx, double dy)
{
	x += dx;
	y += dy;
}*/

double Particle::distance(Particle other)
{
	return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

double Particle::boundaryDistance(Particle other, double length)
{
	double tempx, tempy;
	tempx = std::abs(other.x - x);
	tempy = std::abs(other.y - y);
	if (tempx >= length / 2)
		tempx = length - tempx;
	if (tempy >= length / 2)
		tempy = length - tempy;
	return std::sqrt(tempx * tempx + tempy * tempy);
}

bool Particle::isOverlap(Particle other)
{
	if (distance(other) < radius + other.radius)
		return true;
	else
		return false;
}

double Particle::getX()
{
	return x;
}

double Particle::getY()
{
	return y;
}