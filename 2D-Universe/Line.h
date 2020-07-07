#pragma once

struct Line {
	sf::Vector2f a, b, diff;

	Line(float x1, float y1, float x2, float y2) {
		a = sf::Vector2f(x1, y1);
		b = sf::Vector2f(x2, y2);
		diff = b - a;
	}

	Line(sf::Vector2f v1, sf::Vector2f v2) {
		a = v1;
		b = v2;
		diff = b - a;
	}

	void show() {
		sf::Vertex line[] = { a, b };
		window.draw(line, 2, sf::Lines);
	}

	float intersects(Line other) {
		float u = (crossProd(a, diff) - crossProd(other.a, diff)) / crossProd(other.diff, diff);

		if (0 <= u && u <= 1) {
			float t = (crossProd(other.a, other.diff) - crossProd(a, other.diff)) / crossProd(diff, other.diff);
			if (t >= 0 && t <= 1)
				return t;
		}
		return -1;
	}
};
