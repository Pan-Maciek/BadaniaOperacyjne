#pragma once
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
class Obstacle {
public:
	glm::vec2 pos;
	sf::Shape* shape;
	virtual bool testAgainst(glm::vec2 pos)=0;
};