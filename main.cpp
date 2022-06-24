/*	
Names: 		 Nisa Phelps and Adriana Ladera
Assignment:  COP 3331-002 Flex Project
Description: This program is a physics engine-type game in which the user
			 can try to make a projectile hit a designated target by choosing either 
			 angle or velocity to randomize, providing the remaining unrandomized
 			 angle of elevation or velocity, then LAUNCH! 
*/
#include <iomanip>
#include <iostream>
#include <limits>
#include "Calculations.h"
#include "Projectile.h"
#include "Target.h"
#include "ProjectileIO.h"
#include "DrawTrajectory.h"
using namespace std;

double get_gravity(int index); 
double compare_distance(const Target& target, const Calculations& projectile);
void display_results(Projectile rocket, Target target);
string surface_terrain(int index);
string suffix(Projectile rocket);

int main()
{
    //variable declarations
    int selection;
    double gravity, angle, velocity, target_distance;
    char random_var, play_again, target_choice, difficulty, zoom, draw_again, show_prior;
    bool repeat = false;
    string terrain;
    DrawTrajectory draw;
    Projectile projectile;

    cout << endl << "Hello! It seems as if you've just stumbled into the coolest physics engine ever!"
         << endl << "Ever have the sudden urge to throw something at a target far away?"
         << endl << "Look no further! Here, when given a selection of random velocity or elevation angle, "
         << endl << "you can launch a rocket at a target distance, and choose the terrain to launch it on!"
         << endl << "\nThe moon? Neptune? You name it, we (most likely) got it!";

    while(true) //end when user no longer wants to play (endgame == 'n')
    {
	projectile.set_count();
	cout << "\n========================================================\n";
	cout << "This will be your " << projectile.get_count() << suffix(projectile) << " time launching this round!";
	cout << "\n========================================================\n";

	// Choose Terrain
	while(true) {
	    cout << endl << "Terrains: " << endl
		 << endl << "1. Mercury"
	 	 << endl << "2. Venus"
		 << endl << "3. Earth"
	 	 << endl << "4. Moon"
		 << endl << "5. Mars"
		 << endl << "6. Jupiter"
		 << endl << "7. Saturn"
		 << endl << "8. Uranus"
		 << endl << "9. Neptune"
		 << endl << "10. Pluto\n";
	    cout << endl << "Choose a terrain to get started (enter number of terrain): ";
	    cin >> selection;
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    try {
	        if(cin.fail()) {
		    cout << "Invalid number.  Input must be an integer between 1 and 10, inclusively. Try again.";
		    cin.clear();
		    cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    continue;
		} else if((selection < 1 || selection > 10)) {
		    throw invalid_argument("Invalid input. Must be an integer between 1 and 10, inclusively. Try again.");
		} else {
		    break;
    	        }
	    } catch(const invalid_argument& kermit_the_frog) {
		cout << kermit_the_frog.what();
	    }
	}//end terrain choice input validation
        selection--;
        gravity = get_gravity(selection); //get acceleration due to gravity
	terrain = surface_terrain(selection); //get name of launch terrain

	// Set Target Distance
	while(true) {
	    cout << "\nWould you like to choose your own target distance? (y/n):  ";
	    cin >> target_choice;
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    try {
	        if(tolower(target_choice) == 'y' || tolower(target_choice) == 'n')
		    break;
		else
		    throw invalid_argument("Character selection must be y or n. Please try again.\n");
	     } catch(const invalid_argument& e) {
		cout << e.what();
	     }
	}//end target choice input validation
	if(tolower(target_choice) == 'y') { //user chooses their own target distance
	    while(true) {
		cout << "Enter your desired distance (< 250 meters): ";
		cin >> target_distance;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		try {
		    if (cin.fail()) {
		        cout << "Invalid number. Distance must be a double value between 0 and 250 meters. Try again.\n\n";
		        cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    } else if(target_distance < 0 || target_distance >= 250) {
			throw invalid_argument("Invalid distance. Distance must be a double value between 0 and 250 meters. Try again.\n");
		    } else {
			Target target;
			target.set_position(target_distance);
			break;
		    }
		} catch (const invalid_argument& kermit_the_frog) {
		    cout << endl << kermit_the_frog.what() << endl;
		}
	    }//end target distance validation
	}//end user choice of target distance
	else if(tolower(target_choice) == 'n'){ //create random target distance
		cout << endl<< "A randomized target distance will be created for you.\n\n";
	    while(true) {
		    cout << "Choose your difficulty (e = easy, m = medium, h = hard): ";
		cin >> difficulty;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		try {
		    if(difficulty == 'e' || difficulty == 'm' || difficulty == 'h') {
		        Target target;
			target_distance = target.randomize(difficulty);
		    	target.set_position(target_distance); 
		    	break;								
		    } 
		    else 	
			throw invalid_argument("Invalid difficulty. Please try again!"); 
	 	} catch(const invalid_argument& kermit_the_frog) {
		    cout << kermit_the_frog.what() << endl;
		}
	    }//end difficulty validation
	}//end randomizement of target	
		
	// Choose a Variable to Randomize
	while(true) { 
	    cout << "\nVariables to randomize: "
		 << endl << "v - velocity"
		 << endl << "a - angle" << endl << endl;	
	    cout << "Enter the character of the variable you would like to randomize: ";
	    cin >> random_var;
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    try{
		if(tolower(random_var) == 'v') {
		    velocity = projectile.randomize(random_var);
		    cout << "\nYour launching surface: " << terrain;
		    cout << "\nAcceleration due to gravity: " << gravity << " m/s^2" << endl;
		    cout << "Velocity: " << velocity << " m/s" << endl
			 << "Target Distance: " << target_distance << " m\n"
			 << "\nFind the optimal angle to hit the target at the given distance.\n";
		    break;
		} else if(tolower(random_var) == 'a') {
		    angle = projectile.randomize(random_var);
		    cout << "\nYour launching surface: " << terrain;
		    cout << "\nAcceleration due to gravity: " << gravity << " m/s^2 " << endl;
		    cout << "Angle: " << angle << " degrees" << endl
		         << "Target Distance: " << target_distance << " m\n"
			 << "\nFind the optimal velocity to hit the target at the given distance.\n";
		    break;
		} else {
		    throw invalid_argument("\nInvalid input. Please try again!");
		}
	    } catch(const invalid_argument& kermit_the_frog) {
		cout << kermit_the_frog.what() << endl;
	    }
	}//end randomized variable validation

	// View Prior Prediction
	ProjectileIO projectileIO;
	while(true) {
	    cout << "\nWould you like to view your last launch before making your predictions? (y/n): ";
	    cin >> show_prior;
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    try{
		if(show_prior != 'y' && show_prior != 'n')
		    throw invalid_argument("Input must be y for yes or n for no. Try again.\n");
		else
		    break;
	    }
	    catch (const invalid_argument& kermit_the_frog) {
		cout << kermit_the_frog.what();
	    }
	}//end prior prediction choice validation
	if(show_prior == 'y') { //display prior prediction
	    Projectile prior;
	    prior = projectileIO.read_data();
  	    Target target;
	    target.set_position(target_distance);
	    display_results(prior, target);
	}

	// Make Predictions
	if(tolower(random_var) == 'a') {
	    while(true) {
		cout << "\nType in your predicted velocity (m/s): ";
		cin >> velocity;
		if (cin.fail()) {
		    cout << "Invalid input. Please enter a number with or without decimal points.\n";
		    cin.clear();
		    cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} 
		else 
		    break;
	    }//end velocity prediction validation
	} else {
	    while(true) {
		cout << "\nType in your predicted angle (degrees): ";
		cin >> angle;
		if (cin.fail()) {
		    cout << "Invalid input. Please enter a number with or without decimal points.\n";
		    cin.clear();
		    cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else
		    break;
	    }//end angle prediction validation
	}//end predictions

	cout << "\n\nHere are your results: \n";

	projectile.set_velocity(velocity);
	projectile.set_angle(angle);
	projectile.set_gravity(gravity);
	projectileIO.write_data(projectile);	
	projectile.set_range(projectile.find_range(gravity, velocity, angle)); //needed for display_results()

	// Display Results & Plot Trajectory Calculations
	do {
	    Target target;
	    target.set_position(target_distance); //redefining target for display_results()
	    display_results(projectile, target);
	    draw.draw_trajectory(projectile, target);	
		
	    //user-select scale settings for projectile display
	    while(true) {
		cout << "Scale up or scale down? Warning: if the grid does not look even, please scale down.\n"
		     << "(+ = scale up, - = scale down, n = do not change the scale): ";
		cin >> zoom;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		try {
		    if(zoom == '+') {
			++draw;
			break;
		    } else if(zoom == '-') {
			--draw;
			break;
 		    } else if(zoom == 'n') {
			cout << "No scale change will be made.\n";
			repeat = false;
			break;
	 	    } else {
			throw invalid_argument("Input must be +, -, or n. Please try again.\n");
	 	    }
		} catch(invalid_argument& kermit_the_frog) {
		    cout << kermit_the_frog.what() << endl;
		}
	    }//end scaling choice validation
	
	    //choose to redraw with new scale
	    if(zoom == '+' || zoom == '-') {
	    	while(true) {
		    cout << "Draw again? (y/n): ";
	   	    cin >> draw_again;
		    cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    try {
		    	if(draw_again == 'y') {
			    repeat = true;
			    cout << "\nDrawing again:\n\n";
			    break;
		    	} else if(draw_again == 'n') {
			    repeat = false;
			    break;
		        } else {
			    throw invalid_argument("Input must be y or n. Please try again.\n");
		        }	
		    } catch(invalid_argument& kermit_the_frog) {
		        cout << kermit_the_frog.what() << endl;
		    }  
	        }//end redraw input validation
	    }//end choice to redraw
    	} while(repeat == true);//end display of results	

	// Play Again?
	while(true) {
			cout << "\nDo you want to play again (y/n)? ";
			cin >> play_again;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			try {
				if(play_again == 'n')
				{
					cout << "\nThanks for joining us in rocket launching, space cowboy! It really IS rocket science huh?"
					<< endl << "Have a great day, partner!\n\n";
					break;
				}	
				else if(play_again != 'y' && play_again != 'n') {
						throw invalid_argument("That is not a selection. Please try again.");
				}
				else if(play_again == 'y')
					break;				
			}
			catch(const invalid_argument& kermit_the_frog) {
				cout << endl << kermit_the_frog.what() << endl;
			}
		}//end "play again" input validation
		if(play_again =='n')
			break;
	}//end game loop
    return 0;
}//end main

//get acceleration due to gravity in m/s^2
double get_gravity(int index) 
{
    double terrain[10];
    terrain[0] = 3.7; //mercury
    terrain[1] = 8.87; //venus
    terrain[2] = 9.8; //earth
    terrain[3] = 1.62; //moon
    terrain[4] = 3.711; //mars
    terrain[5] = 24.79; //jupiter
    terrain[6] = 10.44; //saturn
    terrain[7] = 8.69; //uranus
    terrain[8] = 11.15; //neptune
    terrain[9] = 0.62; //pluto
    double gravity = terrain[index];

    return gravity;
}

//name of launch terrain
string surface_terrain(int index)
{
    string terrain;
    switch(index)
    {
	case 0: terrain = "Mercury";
		break;
	case 1: terrain = "Venus";
		break;
	case 2: terrain = "Earth";
	        break;
	case 3: terrain = "Moon";
		break;
	case 4: terrain = "Mars";
		break;
	case 5: terrain = "Jupiter";
		break;
	case 6: terrain = "Saturn";
		break;
	case 7: terrain = "Uranus";
		break;
	case 8: terrain = "Neptune";
		break;
	case 9: terrain = "Pluto";
		break;
	}
    return terrain;
}

//find distance between target and projectile landing
double compare_distance(const Target& target, const Calculations& projectile) 
{
    return projectile.range - target.position;
}

//format output
void display_results(Projectile rocket, Target target){
    double time, height, range, skew;
    time = rocket.find_flight_time(rocket.get_velocity(), rocket.get_gravity(), rocket.get_angle());
    height = rocket.find_max_height(rocket.get_gravity(), rocket.get_velocity(), rocket.get_angle());
    range = rocket.find_range(rocket.get_gravity(), rocket.get_velocity(), rocket.get_angle());
    skew = compare_distance(target, rocket);	
    cout << fixed << setprecision(3)
         << "Acceleration due to gravity: " << rocket.get_gravity() << endl
         << "Velocity: " << rocket.get_velocity() << " m/s" << endl
         << "Angle: " << rocket.get_angle() << " degrees" << endl
         << "Flight time: " << time << " seconds" << endl
         << "Maximum height: " << height << " meters" << endl
         << "Range: " << range << " meters" << endl
         << "Distance between current target and projectile: " << skew << " meters" << endl
         << "(- means you undershot, + means you overshot)" << endl;
}

//provide proper suffix
string suffix (Projectile rocket) {
    string suffix;
    switch(rocket.get_count())
    {
	case 1: suffix = "st";
		break;
	case 2: suffix = "nd";
		break;
	case 3: suffix = "rd";
		break;
	default: suffix = "th";
		 break;
    }
    return suffix;
}
