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

float sqr(float a) {
	return a * a;
}

float distSquared(sf::Vector2f a, sf::Vector2f b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}

float dist(sf::Vector2f a, sf::Vector2f b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
