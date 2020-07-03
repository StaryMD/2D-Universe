#pragma once

void applyGravity(std::vector<Asteroid>& asteroids) {
	for (auto& ast1 : asteroids) {
		sf::Vector2f resultingAcc;

		for (auto& ast2 : asteroids) {
			float D = distSquared(ast1.pos, ast2.pos);

			if (D != 0.0f) {
				D = sqrt(D);

				float F = gravConst * ast1.mass * ast2.mass / D;
				sf::Vector2f acc = (ast2.pos - ast1.pos) / D * F / ast1.mass;

				resultingAcc += acc;
			}
		}

		ast1.speed += resultingAcc;
	}
}
