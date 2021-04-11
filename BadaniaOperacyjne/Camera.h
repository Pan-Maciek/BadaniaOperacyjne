#pragma once
#include <SFML/Graphics.hpp>
class Camera {
public:
	sf::View view;
	float zoom;
	bool move;
	sf::Vector2f prev;
	sf::Vector2f size;

	void update(sf::RenderWindow& window, sf::Event e);
	Camera(int winw, int winh, sf::RenderWindow& window);

};
