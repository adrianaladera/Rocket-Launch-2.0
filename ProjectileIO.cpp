/* 	Implementation file for "ProjectileIO.h"
 	Stores previous projectile launch into a file, projectile.txt

	Places values in this order:
 	velocity, angle, range, height, time, gravity */
#include "Projectile.h"
#include "ProjectileIO.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <list>
using namespace std;
	
Projectile ProjectileIO::read_data() {
	Projectile rocket;
	string header, data;
	ifstream input_file;
	input_file.open("projectile.txt");
	if (input_file) {
		double velocity, elevation_angle, range, max_height, flight_time, gravity_accel;
		getline(input_file, header, '\n');
		getline(input_file, header, '\n');
		getline(input_file, header, '\n');
		while(input_file >> velocity >> elevation_angle >> range >> max_height >> flight_time >> gravity_accel);
		rocket.set_velocity(velocity);
		rocket.set_angle(elevation_angle);
		rocket.set_range(range);
		rocket.set_max_height(max_height);
	   	rocket.set_flight_time(flight_time);
		rocket.set_gravity(gravity_accel);
	}	
	input_file.close();	
	return rocket;
}

void ProjectileIO::write_data(Projectile rocket) {
	ofstream output_file;
	output_file.open("projectile.txt");
	output_file << fixed << setprecision(3);
	output_file << "Prior Projectile's Data:\n\n";
	output_file << fixed << right;
	output_file << setw(15) << "Velocity" << setw(15) << "Angle" << setw(15) << "Range" << setw(15) 
				<< "Height" << setw(15) << "Time" << setw(15) << "Gravity\n"
				<< setw(15) << rocket.get_velocity() << setw(15) << rocket.get_angle() << setw(15)
				<< rocket.find_range(rocket.get_gravity(), rocket.get_velocity(), rocket.get_angle()) << setw(15)
				<< rocket.find_max_height(rocket.get_gravity(), rocket.get_velocity(), rocket.get_angle()) << setw(15)
				<< rocket.find_flight_time(rocket.get_velocity(), rocket.get_gravity(), rocket.get_angle()) << setw(14)
				<< rocket.get_gravity() << '\n';
	output_file.close();
}
