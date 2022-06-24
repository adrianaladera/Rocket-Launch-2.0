/*	DrawTrajectory.h
	Creates grid that displays target location, 
	projectile landing location, and maximum height. */
#ifndef DRAWTRAJECTORY_H
#define DRAWTRAJECTORY_H

#include "Projectile.h"
#include "Target.h"

class DrawTrajectory {

private:
	static int scale_factor;
public: 
	void draw_trajectory(Projectile, Target);
	
	void operator++();
	void operator--();
};
#endif
