#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

void Game::draw(RenderTarget& target, RenderStates states, int x, int y, int width, int height, Font& font)
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
	stats_shape.setPosition(game_shape.getPosition().x + game_shape.getSize().x + 18, game_shape.getPosition().y);
	stats_shape.setOutlineThickness(2.f);
	stats_shape.setOutlineColor(Color::Blue);
	stats_shape.setFillColor(Color::Transparent);
	target.draw(stats_shape, states);

	//Рисуем результаты
	std::string str = "Points: " + std::to_string(points);
	Text text(str, font, 22);
	text.setFillColor(sf::Color::Cyan);
	text.setPosition(stats_shape.getPosition().x + (stats_shape.getSize().x / 4), 30);
	target.draw(text, states);

	for (auto i = all_coords.begin(); i != all_coords.end(); i++)
	{
		sprite.setTextureRect((i->second).second);
		sprite.setPosition((i->second).first.x, (i->second).first.y);
		target.draw(sprite);
	}
}

void Game::load_textures(Texture& tex, Texture* background)
{ 
	sprite.setTexture(tex);
	IntRect game_shape_rect(game_shape.getPosition().x, game_shape.getPosition().y, game_shape.getSize().x, game_shape.getSize().y);
	//game_shape_rect.
	//game_shape.setTextureRect(game_shape_rect);
	game_shape.setTexture(background);
}


void Game::append_sprite(t_Point coord, IntRect rect)
{
	coords _ = std::make_pair(coord, rect);
	all_coords.insert({ coord.y, _});
}
void Game::breaking_lines()
{
	for (int i = 40; i > 0; i--)
	{

		if (all_coords.begin() != all_coords.end())
		{
			int width = (all_coords.begin()->second).second.width;
 			auto col = all_coords.count(i * width + width);
			if (col >= 20)
			{
				points += 100;
 				auto range = all_coords.equal_range(i * width + width);
				all_coords.erase(range.first, range.second);

				copy_coords = all_coords;
				all_coords.clear();

				coords new_coord;
				int new_key;

				for (auto const& j : copy_coords)
				{
					new_coord = j.second;
					new_key = j.first;
					if (new_key < (i * width + width))
					{
						new_key += width;
						new_coord.first.y += width;
					}
					all_coords.insert(std::make_pair(new_key, new_coord));
				}
				i++;
			}
		}
	}
}