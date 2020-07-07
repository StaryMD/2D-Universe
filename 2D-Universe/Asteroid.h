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
			float x = radius * sin(angle);
			float y = radius * cos(angle);
			vertices.push_back({x, y});
		}

		polygon.setPointCount(vertCount);
		polygon.setFillColor(sf::Color(51, 51, 51));
		polygon.setOutlineThickness(1);
		polygon.setPosition(0, 0);
	}

	void show(float scale, sf::Vector2f offset, sf::Color color = sf::Color::White) {
		sf::Vector2f trueOffset = pos - offset;
		polygon.setOutlineColor(color);

		for (int i = 0; i < int(vertices.size()); i++)
			polygon.setPoint(i, (vertices[i] + trueOffset) * scale);

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

	bool collides(Asteroid other) {
		for (auto& vertex : vertices) {
			Line line1(pos, vertex + pos);

			sf::Vector2f points[] = { other.vertices.back() + other.pos, other.vertices.back() + other.pos };
			bool step = 0;
			for (auto& vertex2 : other.vertices) {
				points[step = !step] = vertex2 + other.pos;

				Line line2(points[0].x, points[0].y, points[1].x, points[1].y);
				float t = line1.intersects(line2);
				if (t != -1) { // Happens upo collision

					pos -= (vertex) * (1 - t);
					speed *= -.3f;
					other.speed *= -.3f;
				}
			}
		}
		return false;
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
