#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include "Camera.h"
#include <glm/glm.hpp>
#include "Solution.h"
#include "GeneticOptimizer.h"
#include "Config.h"

using namespace glm;
using namespace std;


void createEnv(std::vector<sf::Shape*>& shapes,sf::Vector2f start, sf::Vector2f end,sf::Vector2f worldSize,vector<Obstacle*> obstacles) {
	sf::RectangleShape* world=new sf::RectangleShape(worldSize);
	world->setOrigin(worldSize.x/2,worldSize.y/2);
	world->setPosition(0,0);

	world->setFillColor(sf::Color::White);
	shapes.push_back(world);


    sf::RectangleShape* startShape = new sf::RectangleShape(sf::Vector2f(1,1));
    startShape->setOrigin(0.5, 0.5);
    startShape->setPosition(start);
    startShape->setFillColor(sf::Color::Green);
    shapes.push_back(startShape);


    sf::RectangleShape* endShape = new sf::RectangleShape(sf::Vector2f(1, 1));
    endShape->setOrigin(0.5, 0.5);
    endShape->setPosition(end);
    endShape->setFillColor(sf::Color::Blue);
    shapes.push_back(endShape);

	for (auto obstacle : obstacles) {
		shapes.push_back(obstacle->shape);
	}
}

void drawEntities(sf::RenderWindow& window, std::vector<Solution>& solutions,sf::Vector2f start) {

	for (int i = 0; i < solutions.size(); i++) {
		sf::Vector2f position = start;
        sf::Vertex line[2];	
		for (int y = 0; y < SOLUTION_SIZE; y++) {
            line[0].color = sf::Color(123, 123, 123);
            line[0].position = position;

			line[1].color = sf::Color(123, 123, 123);
			float angle = solutions[i].steps[y];
			position+=sf::Vector2f(cos(angle) * STEP_SIZE, sin(angle) * STEP_SIZE);
			line[1].position = position;
            window.draw(line, 2, sf::Lines);

			sf::CircleShape circleShape(0.05);
			circleShape.setOrigin(0.05, 0.05);
			circleShape.setPosition(position.x, position.y);
			circleShape.setFillColor(sf::Color::Red);
			window.draw(circleShape);
		}
		
		sf::CircleShape entity;
        entity.setOrigin(0.1, 0.1);
		entity.setRadius(0.1);
		entity.setFillColor(sf::Color::Blue);
		entity.setPosition(position);
        window.draw(entity);
	}

}

void draw(sf::RenderWindow& window, std::vector<sf::Shape*>& shapes) {
	for (auto it = shapes.begin(); it != shapes.end(); it++)
		window.draw(**it);
}

int main() {

	sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BO Visual", sf::Style::Default, settings);
	window.setFramerateLimit(FPS);

	Camera cam(WINDOW_WIDTH, WINDOW_HEIGHT,window);


	GeneticOptimizer optimizer(POPULATION_SIZE, SOLUTION_SIZE);
	optimizer.addCircleObstacle(glm::vec2(5, -2), 1);
	optimizer.addCircleObstacle(glm::vec2(-5, -2), 1);
	optimizer.addCircleObstacle(glm::vec2(0, 0), 1);
	optimizer.addRectObstacle(glm::vec2(2.5, 3), glm::vec2(2,2));
	optimizer.addRectObstacle(glm::vec2(-2.5, 3), glm::vec2(2, 2));

	std::vector<sf::Shape*> env;
	//here load world size as rect centered on 0,0 and start/end points
	createEnv(env, sf::Vector2f(S.x, S.y), sf::Vector2f(T.x, T.y), sf::Vector2f(20, 20),optimizer.obstacles);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();



			cam.update(window,event);
			
			//other events
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Comma:
					//optimizer.step();
					break;
				}
			}
		}


		window.clear();
        draw(window, env);
        drawEntities(window, optimizer.current_generation.solutions, sf::Vector2f(S.x, S.y));
		
		//cout << optimizer.best_solution().cost << endl;
		optimizer.step();
		window.display();
	}

	return 0;
}