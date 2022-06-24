//Implementation file for "Projectile.h"
//Counts the number of projectiles created
#include "Projectile.h"

int Projectile::count = 0;

void Projectile::set_count() {
	++count;
}
