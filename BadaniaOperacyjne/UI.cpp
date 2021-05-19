#include "UI.h"
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#include "nuklear/nuklear.h"
#include <iostream>
#include "Config.h"

float width_calculation(nk_handle handle, float height, const char* text, int len)
{
	sf::Font* type = (sf::Font*)handle.ptr;
	sf::Text temp;
	temp.setFont(*type);
	temp.setString(text);
	temp.setCharacterSize(height);
	float text_width = temp.findCharacterPos(len).x - temp.findCharacterPos(0).x;
	//float text_width = temp.getLocalBounds().width;

	return text_width;
}

void UI::nuklearSfmlDrawRectFilled(const nk_command* cmd, sf::RenderWindow& window) {
	nk_command_rect_filled* p = (nk_command_rect_filled*)cmd;
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color(p->color.r, p->color.g, p->color.b, p->color.a));
	rectangle.setSize(sf::Vector2f(p->w, p->h));
	rectangle.setPosition(p->x, p->y);
	window.draw(rectangle);
}

void UI::nuklearSfmlDrawText(const nk_command* cmd, sf::RenderWindow& window) {
	nk_command_text* p = (nk_command_text*)cmd;
	sf::Font* font = (sf::Font*)p->font->userdata.ptr;
	sf::Text text;
	text.setFont(*font);
	text.setString(p->string);
	text.setCharacterSize(p->height);
	text.setFillColor(sf::Color(p->foreground.r, p->foreground.g, p->foreground.b, p->foreground.a));
	text.setPosition(sf::Vector2f(p->x, p->y));
	window.draw(text);

}

void UI::nuklearSfmlDrawScissor(const nk_command* cmd, sf::RenderWindow& window) {

	nk_command_scissor* p = (nk_command_scissor*)cmd;
	glEnable(GL_SCISSOR_TEST);
	glScissor(
		(GLint)(p->x),
		(GLint)((window.getSize().y - (GLint)(p->y + p->h))),//bottom left corner
		(GLint)(p->w),
		(GLint)(p->h));
}

void UI::nuklearSfmlDrawRectOutline(const nk_command* cmd, sf::RenderWindow& window) {
	nk_command_rect* p = (nk_command_rect*)cmd;
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(p->w, p->h));
	rect.setPosition(sf::Vector2f(p->x, p->y));
	rect.setOutlineThickness(p->line_thickness);
	rect.setFillColor(sf::Color(0, 0, 0, 0));
	rect.setOutlineColor(sf::Color(p->color.r, p->color.g, p->color.b, p->color.a));
	window.draw(rect);
}

void UI::nuklearSfmlDrawCircleFilled(const nk_command* cmd, sf::RenderWindow& window) {
	nk_command_circle_filled* p = (nk_command_circle_filled*)cmd;
	sf::CircleShape circle;
	circle.setRadius(p->h / 2);
	circle.setPosition(sf::Vector2f(p->x, p->y));
	circle.setFillColor(sf::Color(p->color.r, p->color.g, p->color.b, p->color.a));
	window.draw(circle);

}

void UI::nuklearSfmlDrawTriangleFilled(const nk_command* cmd, sf::RenderWindow& window) {
	nk_command_triangle_filled* p = (nk_command_triangle_filled*)cmd;
	sf::ConvexShape convex;
	convex.setPointCount(3);
	convex.setPoint(0, sf::Vector2f(p->a.x, p->a.y));
	convex.setPoint(1, sf::Vector2f(p->b.x, p->b.y));
	convex.setPoint(2, sf::Vector2f(p->c.x, p->c.y));
	convex.setFillColor(sf::Color(p->color.r, p->color.g, p->color.b, p->color.a));
	window.draw(convex);

}

void UI::eventsToGui(sf::Event* evt, sf::RenderWindow& window) {
	
	if (evt->type == sf::Event::MouseButtonPressed || evt->type == sf::Event::MouseButtonReleased) {
		int down = evt->type == sf::Event::MouseButtonPressed;
		const int x = (double)evt->mouseButton.x / window.getSize().x * 920, y = (double)evt->mouseButton.y / window.getSize().y * 920;
		if (evt->mouseButton.button == sf::Mouse::Left)
			nk_input_button(&ctx, NK_BUTTON_LEFT, x, y, down);
		if (evt->mouseButton.button == sf::Mouse::Middle)
			nk_input_button(&ctx, NK_BUTTON_MIDDLE, x, y, down);
		if (evt->mouseButton.button == sf::Mouse::Right)
			nk_input_button(&ctx, NK_BUTTON_RIGHT, x, y, down);

	}
	else if (evt->type == sf::Event::MouseMoved) {
		nk_input_motion(&ctx, (double)evt->mouseMove.x/window.getSize().x*920, (double)evt->mouseMove.y/ window.getSize().y*920);

	}
	else if (evt->type == sf::Event::KeyPressed || evt->type == sf::Event::KeyReleased) {
		int down = evt->type == sf::Event::KeyPressed;

		if (evt->key.code == sf::Keyboard::Backspace) {
			nk_input_key(&ctx, NK_KEY_BACKSPACE, down);
			nk_input_key(&ctx, NK_KEY_BACKSPACE, 0);
		}

		if (down == 1)
			if (evt->key.code >= sf::Keyboard::Num0 && evt->key.code <= sf::Keyboard::Num9)
				nk_input_char(&ctx, evt->key.code + 22);
			else if (evt->key.code == sf::Keyboard::Period)
				nk_input_char(&ctx, 46);
			else if (evt->key.code == sf::Keyboard::Dash)
				nk_input_char(&ctx, 45);
			else if (evt->key.code == sf::Keyboard::Space)
				nk_input_char(&ctx, 32);
			else if (evt->key.code >= sf::Keyboard::A && evt->key.code <= sf::Keyboard::Z) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					nk_input_char(&ctx, evt->key.code + 65);
				else
					nk_input_char(&ctx, evt->key.code + 97);

			}
	}
	

}

UI::UI(sf::RenderWindow* window) {
	this->window = window;
	cascadia.loadFromFile("Cascadia.ttf");
	font.userdata.ptr = &cascadia;
	font.height = 15;
	font.width = width_calculation;
	nk_init_default(&ctx, &font);

}

void UI::draw() {
	if (nk_begin(&ctx, "UpPanel", nk_rect(0,0, window->getSize().x, 100), NK_WINDOW_BORDER| NK_WINDOW_NO_SCROLLBAR)) {

		
		nk_layout_row_begin(&ctx, NK_STATIC, 23, 7);
		{
			nk_layout_row_push(&ctx, 140);
			nk_label(&ctx, "Step size:", NK_TEXT_LEFT);
			nk_layout_row_push(&ctx, 120);
			nk_slider_float(&ctx, 0.1, &STEP_SIZE_UI, 10.0f, 0.1f);
			font.height = 13;
			nk_layout_row_push(&ctx, 70);
			nk_property_float(&ctx, "#", 0.1f, &STEP_SIZE_UI, 10.0f, 0.1f, 0);
			font.height = 15;
			nk_layout_row_push(&ctx, 20);
			nk_label(&ctx, "", NK_TEXT_LEFT);
			nk_layout_row_push(&ctx, 140);
			nk_label(&ctx, "Mutation chance:", NK_TEXT_LEFT);
			nk_layout_row_push(&ctx, 120);
			nk_slider_float(&ctx, 0.1, &MUTATION_CHANCE_UI, 1.0f, 0.1f);
			font.height = 13;
			nk_layout_row_push(&ctx, 70);
			nk_property_float(&ctx, "#", 0.1f, &MUTATION_CHANCE_UI, 1.0f, 0.1f, 0);
			nk_layout_row_end(&ctx);
		}

		nk_layout_row_begin(&ctx, NK_STATIC, 23, 7);
		{
			font.height = 15;
			nk_layout_row_push(&ctx, 140);
			nk_label(&ctx, "Mutation angle:", NK_TEXT_LEFT);
			nk_layout_row_push(&ctx, 120);
			nk_slider_float(&ctx, 0.02f, &MUTATION_ANGLE_UI, 1.0f, 0.01f);
			font.height = 13;
			nk_layout_row_push(&ctx, 70);
			nk_property_float(&ctx, "#", 0.02f, &MUTATION_ANGLE_UI, 1.0f, 0.01f, 0);
			font.height = 15;
			nk_layout_row_push(&ctx, 20);
			nk_label(&ctx, "", NK_TEXT_LEFT);
			nk_layout_row_push(&ctx, 140);
			nk_label(&ctx, "Keep best:", NK_TEXT_LEFT);
			nk_layout_row_push(&ctx, 120);
			nk_slider_float(&ctx, 0.f, &KEEP_BEST_UI, 1.0f, 0.1f);
			font.height = 13;
			nk_layout_row_push(&ctx, 70);
			nk_property_float(&ctx, "#", 0.f, &KEEP_BEST_UI, 1.0f, 0.1f, 0);
			nk_layout_row_end(&ctx);
		}
		nk_layout_row_begin(&ctx, NK_STATIC, 23, 7);
		{
			font.height = 15;
			nk_layout_row_push(&ctx, 140);
			nk_label(&ctx, "Population size:", NK_TEXT_LEFT);
			nk_layout_row_push(&ctx, 120);
			nk_slider_int(&ctx, 10, &POPULATION_SIZE_UI, 200, 1);
			font.height = 13;
			nk_layout_row_push(&ctx, 70);
			nk_property_int(&ctx, "#", 10, &POPULATION_SIZE_UI, 200, 1, 0);
			font.height = 15;
			nk_layout_row_push(&ctx, 20);
			nk_label(&ctx, "", NK_TEXT_LEFT);
			nk_layout_row_push(&ctx, 140);
			nk_label(&ctx, "Solution size:", NK_TEXT_LEFT);
			nk_layout_row_push(&ctx, 120);
			nk_slider_int(&ctx, 10, &SOLUTION_SIZE_UI, 200, 1);
			font.height = 13;
			nk_layout_row_push(&ctx, 70);
			nk_property_int(&ctx, "#", 10, &SOLUTION_SIZE_UI, 200, 1, 0);
			nk_layout_row_end(&ctx);
		}
		font.height = 15;

		nk_layout_space_begin(&ctx, NK_STATIC, 50, 1);
		nk_layout_space_push(&ctx, nk_layout_space_rect_to_local(&ctx,nk_rect(735, 20, 150, 50)));

		if (nk_button_label(&ctx, "Upload")) {
			STEP_SIZE = STEP_SIZE_UI;
			MUTATION_CHANCE = MUTATION_CHANCE_UI;
			MUTATION_ANGLE = MUTATION_ANGLE_UI;
			KEEP_BEST = KEEP_BEST_UI;
			POPULATION_SIZE = POPULATION_SIZE_UI;
			SOLUTION_SIZE = SOLUTION_SIZE_UI;
			upload = true;
		}
	}
	nk_end(&ctx);



	
	
	const struct nk_command* cmd = 0;
	nk_foreach(cmd, &ctx) {
		switch (cmd->type) {
		case NK_COMMAND_RECT_FILLED:
			nuklearSfmlDrawRectFilled(cmd, *window);
			break;
		case NK_COMMAND_TEXT:
			nuklearSfmlDrawText(cmd, *window);
			break;
		case NK_COMMAND_SCISSOR:
			//nuklearSfmlDrawScissor(cmd, *window);
			break;
		case NK_COMMAND_RECT:
			nuklearSfmlDrawRectOutline(cmd, *window);
			break;
		case NK_COMMAND_CIRCLE_FILLED:
			nuklearSfmlDrawCircleFilled(cmd, *window);
			break;
		case NK_COMMAND_TRIANGLE_FILLED:
			nuklearSfmlDrawTriangleFilled(cmd, *window);
			break;

		}

	}
	nk_clear(&ctx);
}