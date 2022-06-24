/* inherits from Calculations class to return
 target distance that the user must hit */
#ifndef TARGET_H
#define TARGET_H

#include <cstdlib>
#include <ctime>
#include "Calculations.h"

class Target : public Calculations {

private:
	double position;
public:
	void set_position(double position)
        {
            this->position = position;
        }

	//overriding function in Calculations class
	double randomize(char choice) override 
	{
	    srand(time(nullptr));
	    double target_distance;
            switch(choice) {
	        case 'e': //easy
		    target_distance = rand() % 51; //target is between 10m - 50m
		    if (target_distance < 10)
			target_distance += 10; //avoid giving distance < 10
	            break;
            	case 'm': //medium	
            	    target_distance = rand() % 101;
        	    if (target_distance < 50) //target is between 50m - 100m
		        target_distance += 50;
		    break;
            	case 'h': //hard
            	    target_distance = rand() % 201;
            	    if (target_distance < 100) //target is between 100m - 200m
		        target_distance += 100;
		    break;
            }
	    return target_distance;
	}

	friend double compare_distance(const Target&, const Calculations&);
};
#endif


