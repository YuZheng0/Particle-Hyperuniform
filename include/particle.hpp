#ifndef PARTICLE_HPP
#define PARTICLE_HPP


class Particle
{
public:
	Particle(double, double, double);
	void move(double, double);
	bool isOverlap(Particle, double);          
	double distance(Particle);         //It is the distance between two particle.
	double boundaryDistance(Particle, double); //It is the distance beteween two particle after considering about boundary condition.
	double getX();
	double getY();
private:
	double x, y;  //It is the position of particles
	double radius;
};

#endif