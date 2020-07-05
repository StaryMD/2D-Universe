#pragma once

struct Asteroid {
	sf::ConvexShape polygon;
	sf::Vector2f pos, speed;
	std::vector<sf::Vector2f> vertices;
	float radius;
	float rotAngle;
	float mass;

	Asteroid(float x_, float y_, float radius_) {
		radius = radius_;
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

	void show(float Scale, sf::Vector2f offset) {
		for (int i = 0; i < int(vertices.size()); i++)
			polygon.setPoint(i, (pos - offset  + vertices[i]) * Scale);

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

void getScale(std::vector<Asteroid>& asteroids, float& scale, sf::Vector2f& offset) {
	float x0 = 0, y0 = 0, x1 = screenWidth, y1 = screenHeight;

	for (Asteroid& ast : asteroids) {
		x0 = std::min(x0, ast.pos.x - 2 * ast.radius);
		y0 = std::min(y0, ast.pos.y - 2 * ast.radius);
		x1 = std::max(x1, ast.pos.x + 2 * ast.radius);
		y1 = std::max(y1, ast.pos.y + 2 * ast.radius);
	}
	x1 -= x0;
	y1 -= y0;
	x1 = std::abs(x1);
	y1 = std::abs(y1);

	float ratioX = screenWidth / x1, ratioY = screenHeight / y1;
	if (ratioX < ratioY) {
		scale = ratioX;
		offset = { x0, y0 };
	}
	else {
		scale = ratioY;
		offset = { x0 , y0 };
	}
}
