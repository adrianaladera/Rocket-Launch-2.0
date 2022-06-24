// Calculations.h
// Performs projectile-trajectory calculations.
#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <cmath>
#include <ctime>
#include <cstdlib>

class Target;

class Calculations {

    private:
        double velocity;
        double elevation_angle;
        double range;
        double max_height;
        double flight_time;
        double gravity_accel;

    public:
        void set_angle(double angle)
        {   
            elevation_angle = angle;
        }

        void set_velocity(double v)
        {
            velocity = v;
        }

        void set_gravity(double gravity)
        {
            gravity_accel = gravity;
        }

        void set_range(double r)
        {
            range = r;
        }

        void set_max_height(double height)
        {
            max_height = height;
        }

        void set_flight_time(double time)
        {
            flight_time = time;
        }

        double get_angle()
        {
            return elevation_angle;
        }

        double get_velocity()
        {
            return velocity;
        }

        double get_gravity()
        {
            return gravity_accel;
        }

        //convert input radians to use with sin()/cos()
        double degrees_to_radians(double theta)
        {                                       
            double factor = 3.1415926535 / 180;
            theta *= factor;
            return theta;
        }

        double find_flight_time(double v, double a, double theta)
        {
            theta = degrees_to_radians(theta);
            double time = (2 * v * sin(theta)) / a;
            return time;
        }

        double find_max_height(double a, double v, double theta)
        {
            theta = degrees_to_radians(theta);
            double height = (pow(v, 2) * pow(sin(theta), 2)) / (2 * a);
            return height;
        }

        double find_range(double a, double v, double theta)
        {
            theta = degrees_to_radians(theta);
            double range = (2 * pow(v, 2) * sin(theta) * cos(theta)) / a;
            return range;
        }

        virtual double randomize(char choice) = 0;
        
	friend double compare_distance(const Target&, const Calculations&);
};
#endif
