#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

void Game::draw(RenderTarget& target, RenderStates states, int x, int y, int width, int height)
{
	// Рисуем рамку игрового поля
	game_shape.setSize(Vector2f(18 * 20 + x, 18 * 40 + y));
	game_shape.setPosition(x, y);
	game_shape.setOutlineThickness(2.f);
	game_shape.setOutlineColor(Color::Red);
	game_shape.setFillColor(Color::Transparent);
	target.draw(game_shape, states);

	// Рисуем рамку с результатами
	stats_shape.setSize(Vector2f(target.getSize().x - game_shape.getSize().x - game_shape.getPosition().x - 20, game_shape.getSize().y));
	stats_shape.setPosition(game_shape.getPosition().x + game_shape.getSize().x + 10, game_shape.getPosition().y);
	stats_shape.setOutlineThickness(2.f);
	stats_shape.setOutlineColor(Color::Green);
	stats_shape.setFillColor(Color::Transparent);
	target.draw(stats_shape, states);
}
void Game::append_sprite(t_Point coord, IntRect rect)
{
	coords _ = std::make_pair(coord, rect);
	all_coords.push_back(_);
}