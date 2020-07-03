#pragma once

struct Asteroid {
	sf::ConvexShape polygon;
	sf::Vector2f pos, speed;
	std::vector<sf::Vector2f> vertices;
	float rotAngle;
	float mass;

	Asteroid(float x_, float y_, float radius_) {
		pos = {x_, y_};
		speed = { 0, 0 };
		rotAngle = randomf(-PI / 100, PI / 100);
		mass = randomf(75, 125);

		int vertCount = randomi(3, 6);

		for (int i = 0; i < vertCount; i++) {
			float angle = 2 * PI / vertCount * i;
			float x = radius_ * sin(angle);
			float y = radius_ * cos(angle);
			vertices.push_back({x, y});
		}

		polygon.setPointCount(vertCount);
		polygon.setOutlineColor(sf::Color::White);
		polygon.setFillColor(sf::Color(51, 51, 51));
		polygon.setOutlineThickness(2);
		polygon.setPosition(0, 0);
	}

	void show(float Scale = 1.0f) {
		for (int i = 0; i < int(vertices.size()); i++)
			polygon.setPoint(i, (pos + vertices[i]) * Scale);

		window.draw(polygon);
	}

	void rotate() {
		float cosA = cos(rotAngle);
		float sinA = sin(rotAngle);
		for (sf::Vector2f& vertex : vertices) {
			float x = vertex.x * cosA - vertex.y * sinA;
			float y = vertex.x * sinA + vertex.y * cosA;
			vertex = { x, y };
		}
	}

	void update() {
		pos += speed;
		rotate();
	}

};