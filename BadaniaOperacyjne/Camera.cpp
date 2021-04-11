#include "Camera.h"
#include <iostream>

Camera::Camera(int winw,int winh) {
	view.setCenter(0, 0);
	view.setSize(10, 10);
	zoom = 0.01;
	move = false;
}

void Camera::update(sf::RenderWindow& window,sf::Event e) {
	switch (e.type) {

		case sf::Event::MouseButtonPressed:
			if (e.mouseButton.button == 0) {
				move = true;
				prev = sf::Vector2f(sf::Mouse::getPosition(window));
			}
			break;

		case sf::Event::MouseButtonReleased:
			if (e.mouseButton.button == 0) {
				move = false;
			}
			break;

		case sf::Event::MouseMoved:
		{
			if (!move)
				break;
			sf::Vector2f next = sf::Vector2f(e.mouseMove.x, e.mouseMove.y);
			sf::Vector2f delta = prev - next;

			delta.x *= zoom;
			delta.y *= zoom;

			
			std::cout << e.mouseMove.x << " " << e.mouseMove.y << std::endl;
			view.move(delta);
			window.setView(view);

			prev = next;
		}
			break;

		case sf::Event::MouseWheelScrolled:
			if (move)
				break;

			if (e.mouseWheelScroll.delta <= -1)
				zoom = zoom * 1.1;
			else if (e.mouseWheelScroll.delta >= 1)
				zoom = zoom * 0.9;

			std::cout << "total zoom: " << zoom << std::endl;

		
			view.setSize(window.getDefaultView().getSize());
			view.zoom(zoom);
			window.setView(view);

			break;
	}

}