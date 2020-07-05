#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>

const int objCount = 1000;
const int fps[] = { 1, 2, 5, 10, 15, 20, 30, 45, 60, 90, 120, 180, 240, 480, 960 , 1920};
const float gravConst = 0.1f;
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

	int fpsIdx = 8;

	std::vector<Asteroid> asteroids;
	for (int i = 0; i < objCount; i++) {
		float x = randomf(-2 * screenWidth, 2 * screenWidth);
		float y = randomf(-2 * screenHeight, 2 * screenHeight);
		float r = randomf(75, 125);

		asteroids.push_back(Asteroid(x, y, r));
	}

	sf::Event event;
	std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
	while (window.isOpen()) {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		std::chrono::duration<double, std::milli> interval = now - start;

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && interval.count() >= 1000 / fps[fpsIdx]) {
			frameCount++;
			start = now;

			while (window.pollEvent(event))
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
					window.close();
				else
					if(event.type == sf::Event::KeyReleased) {
						if(event.key.code == sf::Keyboard::Up && fpsIdx < 15)
							fpsIdx++;
						if (event.key.code == sf::Keyboard::Down && fpsIdx > 0)
							fpsIdx--;
					}

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
