/* Uses the Projectile class to 
 read from and write to text file */
#ifndef PROJECTILEIO_H
#define PROJECTILEIO_H

#include "Projectile.h"

class ProjectileIO {

public: 
	static Projectile read_data();
	static void write_data(Projectile);
};
#endif
