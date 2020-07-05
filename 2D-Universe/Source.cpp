#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>

const int objCount = 1000;
const int fps = 60;
const float gravConst = 10.0f;
const float PI = atanf(1) * 4.0f;

sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "2D Universe", sf::Style::Fullscreen);
const float screenWidth = (float)window.getSize().x;
const float screenHeight = (float)window.getSize().y;
unsigned long long frameCount;

#include "random.h"
#include "Asteroid.h"
#include "Gravity.h"

int main() {
	srand(unsigned(time(NULL)));

	std::vector<Asteroid> asteroids;
	for (int i = 0; i < objCount; i++) {
		float x = randomf(0, screenWidth);
		float y = randomf(0, screenHeight);
		float r = randomf(75, 125);

		asteroids.push_back(Asteroid(x, y, r));
	}

	sf::Event event;
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	while (window.isOpen()) {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> interval = now - start;

		if (interval.count() >= 1000 / fps) {
			frameCount++;
			start = now;

			while (window.pollEvent(event)) 
				if (event.type == sf::Event::Closed)
					window.close();

			window.clear(sf::Color(51, 51, 51));

			float scale;
			sf::Vector2f offset;
			getScale(asteroids, scale, offset);
			for (Asteroid& asteroid : asteroids)
				asteroid.show(scale, offset);

			window.display();

			for (Asteroid& asteroid : asteroids)
				asteroid.update();

			applyGravity(asteroids);
		}
	}

	return 0;
}
