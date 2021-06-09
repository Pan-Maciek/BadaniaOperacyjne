#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <vector>
#include "Camera.h"
#include <glm/glm.hpp>
#include "Solution.h"
#include "GeneticOptimizer.h"
#include "config.h"
#include "UI.h"
#include <thread>
#include <future>
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

	sf::Vertex* lines = new sf::Vertex[2 * SOLUTION_SIZE* solutions.size()];
	sf::VertexArray quads(sf::Quads, 4* SOLUTION_SIZE * solutions.size());
	for (int i = 0; i < solutions.size(); i++) {
		sf::Vector2f position = start;
        
		for (int y = 0; y < 2* SOLUTION_SIZE; y+=2) {
            lines[i* 2* SOLUTION_SIZE+y].color = sf::Color(123, 123, 123);
            lines[i *2* SOLUTION_SIZE + y].position = position;

			lines[i *2* SOLUTION_SIZE + y+1].color = sf::Color(123, 123, 123);
			float angle = solutions[i].steps[y/2];
			position+=sf::Vector2f(cos(angle) * STEP_SIZE, sin(angle) * STEP_SIZE);
			lines[i *2* SOLUTION_SIZE + y+1].position = position;
            

			sf::RectangleShape rectShape(sf::Vector2f(0.05, 0.05));
			rectShape.setOrigin(0.025, 0.025);
			rectShape.setPosition(position.x, position.y);
			rectShape.setFillColor(sf::Color::Red);
		
			auto size = rectShape.getSize();

			quads[4*i* SOLUTION_SIZE+y*2].position = rectShape.getPosition()+ sf::Vector2f(-size.x / 2, -size.y / 2);
			quads[4 * i * SOLUTION_SIZE + y*2].color = sf::Color::Red;
			quads[4 * i * SOLUTION_SIZE + y*2+1].position = rectShape.getPosition() + sf::Vector2f(size.x / 2, -size.y / 2);
			quads[4 * i * SOLUTION_SIZE + y*2+1].color = sf::Color::Red;
			quads[4 * i * SOLUTION_SIZE + y*2+2].position = rectShape.getPosition() + sf::Vector2f(size.x / 2, size.y / 2);
			quads[4 * i * SOLUTION_SIZE + y*2+2].color = sf::Color::Red;
			quads[4 * i * SOLUTION_SIZE + y*2+3].position = rectShape.getPosition() + sf::Vector2f(-size.x / 2, size.y / 2);
			quads[4 * i * SOLUTION_SIZE + y*2+3].color = sf::Color::Red;

		}

		sf::CircleShape entity;
        entity.setOrigin(0.1, 0.1);
		entity.setRadius(0.1);
		entity.setFillColor(sf::Color::Blue);
		entity.setPosition(position);
        window.draw(entity);
		
	}
	window.draw(lines, 2 * SOLUTION_SIZE * solutions.size(), sf::Lines);
	delete[] lines;

	window.draw(quads);
}

void draw(sf::RenderWindow& window, std::vector<sf::Shape*>& shapes) {
	for (auto it = shapes.begin(); it != shapes.end(); it++)
		window.draw(**it);
}
GeneticOptimizer initOptimizer(){
	GeneticOptimizer optimizer(POPULATION_SIZE, SOLUTION_SIZE);
	optimizer.addCircleObstacle(glm::vec2(5, -2), 1);
	optimizer.addCircleObstacle(glm::vec2(-5, -2), 1);
	optimizer.addCircleObstacle(glm::vec2(0, 0), 1);
	optimizer.addRectObstacle(glm::vec2(2.5, 3), glm::vec2(2, 2));
	optimizer.addRectObstacle(glm::vec2(-2.5, 3), glm::vec2(2, 2));
	return optimizer;
}
bool calculate(GeneticOptimizer& optimizer) {
	optimizer.step();
	return true;
}

int main() {

	sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "BO Visual", sf::Style::Default, settings);
	//window.setFramerateLimit(FPS);

	Camera cam(WINDOW_WIDTH, WINDOW_HEIGHT,window);
	//UI
	UI ui(&window);

	GeneticOptimizer optimizer = initOptimizer();

	std::vector<sf::Shape*> env;
	//here load world size as rect centered on 0,0 and start/end points
	createEnv(env, sf::Vector2f(S.x, S.y), sf::Vector2f(T.x, T.y), sf::Vector2f(20, 20),optimizer.obstacles);

	std::future<bool> future;
	std::vector<Solution> currentEntities;
	future = std::async(calculate, std::ref(optimizer));
	while (window.isOpen())
	{
		sf::Event event;
		nk_input_begin(&ui.ctx);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();



			cam.update(window,event);
			
			//other events
			ui.eventsToGui(&event,window);
			
			
		}
		nk_input_end(&ui.ctx);

		
		window.clear();
		draw(window, env);
		drawEntities(window, currentEntities, sf::Vector2f(S.x, S.y));
		if (future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
			currentEntities = optimizer.current_generation.solutions;
			if (ui.upload) {
				optimizer = initOptimizer();
				ui.upload = false;
			}
			future = std::async(calculate, std::ref(optimizer));
		}
		auto view=window.getView();
		window.setView(window.getDefaultView());
		ui.draw();
		window.setView(view);
		//cout << optimizer.best_solution().cost << endl;
		
		window.display();
	}

	return 0;
}