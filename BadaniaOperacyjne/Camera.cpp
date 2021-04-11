#include "Camera.h"
#include <iostream>

Camera::Camera(int winw,int winh, sf::RenderWindow& window) {
	view.setCenter(0, 0);
	view.setSize(window.getDefaultView().getSize());
	size = view.getSize();
	zoom = 0.03;
	move = false;
	view.zoom(zoom);
	window.setView(view);
}

void Camera::update(sf::RenderWindow& window,sf::Event e) {
	switch (e.type) {
		case sf::Event::Resized:
			size = sf::Vector2f(e.size.width, e.size.height);
			view.setSize(size);
			view.zoom(zoom);
			window.setView(view);
			break;

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


		
			view.setSize(size);
			view.zoom(zoom);
			window.setView(view);

			break;
	}

}