//inherits from Calculations class to store projectile data
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <ctime>
#include <cstdlib>
#include "Calculations.h"

class Projectile : public Calculations {

private:
	static int count;
public:

	static int get_count() {
	    return count;
	}

	void set_count();

	//overriding function in Calculations class
	double randomize(char choice) override 
	{
	    srand(time(nullptr));
	    double random_variable;
            switch(choice) 
            {
	        case 'v': //velocity, 400m/s = v max
			random_variable = rand() % 400;
                    	break;
            	case 'a': //angle, 90 degrees = a max
            		random_variable = rand() % 90; 
		    	break;
            }
	    return random_variable;
	}
};
#endif
