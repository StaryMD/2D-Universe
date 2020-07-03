#pragma once

#include <cstdlib>
#include <ctime>

int randomi(int a, int b) {
	return rand() % (b - a + 1) + a;
}

float randomf(float a, float b) {
	float ratio = randomi(0, 10000) / 1e4f;
	return a + (b - a) * ratio;
}

float crossProd(sf::Vector2f a, sf::Vector2f b) {
	return a.x * b.y - a.y * b.x;
}
