#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "config.h"
#include "nuklear/nuklear.h"

class UI {
private:
	sf::RenderWindow* window;
	sf::Font cascadia;
	struct nk_user_font font;
	

	float STEP_SIZE_UI = STEP_SIZE;
	float MUTATION_CHANCE_UI = MUTATION_CHANCE;
	float MUTATION_ANGLE_UI = MUTATION_ANGLE;
	float KEEP_BEST_UI = KEEP_BEST;
	int POPULATION_SIZE_UI = POPULATION_SIZE;
	int SOLUTION_SIZE_UI = SOLUTION_SIZE;
	

	void nuklearSfmlDrawRectFilled(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawText(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawScissor(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawRectOutline(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawCircleFilled(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawTriangleFilled(const nk_command* cmd, sf::RenderWindow& window);
	
public:
	struct nk_context ctx;
	bool upload = false;
	UI(sf::RenderWindow* window);
	void eventsToGui(sf::Event* evt, sf::RenderWindow& window);
	void draw();


};