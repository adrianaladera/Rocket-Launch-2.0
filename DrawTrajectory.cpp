//implementation file that uses "DrawTrajectory.h"
#include <iostream>
#include <cmath>

#include "DrawTrajectory.h"
#include "Projectile.h"
#include "Target.h"
int DrawTrajectory::scale_factor = 3;
/* scale_factor # = # of spots (per) : # of meters
 * scale_factor 1 = 1:10
 * scale_factor 2 = 1:8
 * scale_factor 3 = 1:5
 * scale_factor 4 = 1:4
 * scale_factor 5 = 1:2
 */

void DrawTrajectory::draw_trajectory(Projectile rocket, Target goal) {
    int rows = 40, cols = 40;
    int spots_per_meter = 5;
    const int max_distance = 250; //meters
    
    switch(scale_factor) {
        case 1:	
	    spots_per_meter = 10;
	    break;
        case 2:	
	    spots_per_meter = 8;
	    break;
        case 3:	
	    spots_per_meter = 5;
	    break;
        case 4:	
	    spots_per_meter = 4;
	    break;
        case 5:	
	    spots_per_meter = 2;
	    break;
    }

    // Creating grid
    //   - Note: #'s round up: 0's on scale_factor = 3 will show as 5 meters away. 249 will show as 250 meters away.
    //           250 meters rounds up to 260, so it will not be shown. Height will not show if < spots_per_meter.
    rows = max_distance/spots_per_meter;
    cols = max_distance/spots_per_meter;
    char display[rows][cols];

    // Finding markers
    int height_hit = rocket.find_max_height(rocket.get_gravity(), rocket.get_velocity(), rocket.get_angle());
    if (height_hit <= max_distance && height_hit >= spots_per_meter) // Height will not be shown if < spots_per_meter
	height_hit = cols - (height_hit/spots_per_meter); // Grid is "upside down" - 0 = top, 250 = bottom, use this to correct
    else
	height_hit = -1; // Off grid error

    int projectile_hit = rocket.find_range(rocket.get_gravity(), rocket.get_velocity(), rocket.get_angle());
    if (projectile_hit < max_distance && projectile_hit >= 0) // Projectile landing will not be shown if >= max_distance
   	 projectile_hit = projectile_hit/spots_per_meter;
    else
	projectile_hit = -1; // Off grid error

    int target_hit = ((-1 * compare_distance(goal, rocket)) + rocket.find_range(rocket.get_gravity(), rocket.get_velocity(), rocket.get_angle()))/spots_per_meter;
 
    // Drawing grid
    std::cout << std::endl;
    for(int row = 0; row < rows; ++row) {
        for(int col = 0; col < cols; ++col) {
	    display[row][col] = '.';
	    if(height_hit != -1)
	    	display[height_hit][projectile_hit/2] = '*';
	    if (target_hit == projectile_hit) {
		display[rows - 1][target_hit] = '#';
	    } else {
		if (projectile_hit != -1)
		    display[rows - 1][projectile_hit] = 'X';
		display[rows - 1][target_hit] = 'O';
	    }
	    std::cout << display[row][col] << " ";
	}
	std::cout << '\n';
    }

    // Scale & Legend
    std::cout << "Scale = 1:" << spots_per_meter <<" | 1 '.' represents " << spots_per_meter << " meters.\n";

    std::string hit = "Target & Projectile's Shared Location = # | ";
    std::string projectile_in = "Projectile's Final Location = X | ";
    std::string projectile_out = "Projectile's Final Location is Out of the Grid's Scope | ";
    std::string target_in = "Target's Location = O | ";
    std::string height_in = "Maximum Height of Projectile = *\n\n";
    std::string height_out = "Maximum Height of Projectile is Out of the Grid's Scope\n\n"; 
    if (target_hit == projectile_hit) { // Hit Legend Options
	if (height_hit == -1) {
	    std::cout << "\nLegend: " << hit << height_out;
	} else  {
	    std::cout << "\nLegend: " << hit << height_in;
	}
    } else { // Miss Legend Options
	if (projectile_hit == -1 && height_hit == -1) {
	    std::cout << "\nLegend: " << projectile_out << target_in << height_out;	
	} else if (height_hit == -1) {
	    std::cout << "\nLegend: " << projectile_in << target_in << height_out; 
	} else if (projectile_hit == -1) {
	    if (target_hit == projectile_hit/2 && height_hit == cols)
		std::cout << "\nLegend: " << projectile_out << "Target's Location & Maximum Height of Projectile = O\n\n";
	    else
		std::cout << "\nLegend: " << projectile_out << target_in << height_in;
	} else {
	    if (projectile_hit == projectile_hit/2 && height_hit == cols)
		std::cout << "\nLegend: Projectile's Final Location & Maximum Height of Projectile = X | " << target_in << "\n\n";
            else if (target_hit == projectile_hit/2 && height_hit == cols)
		std::cout << "\nLegend: " << projectile_in << "Target's Location & Maximum Height of Projectile = O\n\n";
	    else
	        std::cout << "\nLegend: " << projectile_in << target_in << height_in;
	}
    }    
}

// Scale up	
void DrawTrajectory::operator++() {
    if(scale_factor == 5)
	std::cout << "Already set to the largest scale.\n";
    else 
	++scale_factor;
}

// Scale down
void DrawTrajectory::operator--() {
    if(scale_factor == 1)
	std::cout << "Already set to the smallest scale.\n";
    else 
	--scale_factor;
}
