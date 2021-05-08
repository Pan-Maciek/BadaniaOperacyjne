#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "nuklear/nuklear.h"

class UI {
private:
	sf::RenderWindow* window;
	sf::Font cascadia;
	struct nk_user_font font;
	struct nk_context ctx;


	void nuklearSfmlDrawRectFilled(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawText(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawScissor(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawRectOutline(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawCircleFilled(const nk_command* cmd, sf::RenderWindow& window);
	void nuklearSfmlDrawTriangleFilled(const nk_command* cmd, sf::RenderWindow& window);
	
public:
	UI(sf::RenderWindow* window);
	void eventsToGui(sf::Event* evt);
	void draw();


};