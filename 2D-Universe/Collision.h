#pragma once
/*
void getCollisions(std::vector<Asteroid>& asteroids, std::vector<bool>& collisions) {
	for (int i = 0; i < objCount; i++) {
		collisions[i] = false;

		for (int j = 0; !collisions[i] && j < i; j++)
			collisions[i] = collisions[i] || asteroids[i].collides(asteroids[j]);
		for (int j = i + 1; !collisions[i] && j < objCount; j++)
			collisions[i] = collisions[i] || asteroids[i].collides(asteroids[j]);
	}
}
*/
void getCollisions(std::vector<Asteroid>& asteroids) {
	for (int i = 0; i < objCount; i++) {
		for (int j = 0;  j < i; j++)
			asteroids[i].collides(asteroids[j]);
		for (int j = i + 1; j < objCount; j++)
			asteroids[i].collides(asteroids[j]);
	}
}
