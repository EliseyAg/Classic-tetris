#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Sprite.h"

using namespace sf;
class Game
{
private:
	Game() {};
protected:
	RectangleShape game_shape;
	RectangleShape stats_shape;
	Sprite sprite;
	IntRect game_shape_rect;
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	};
	using coords = std::pair <t_Point, IntRect>;
	std::multimap<int, coords>all_coords = {};
	std::multimap<int, coords>copy_coords = {};
	int points = 0;
	void draw(RenderTarget& target, RenderStates states, int x, int y, int, int, Font& font);
	int Get_game_shape_Left_border() { return (int) (game_shape.getPosition().x); };
	int Get_game_shape_Right_border() { return (int)(game_shape.getPosition().x + game_shape.getSize().x); };
	int Get_game_shape_Bottom_border() { return (int)(game_shape.getPosition().y + game_shape.getSize().y); };
	int Get_game_shape_Top_border() { return (int)(game_shape.getPosition().y); };
	void append_sprite(t_Point, IntRect);
	void breaking_lines();
	void load_textures(Texture& tex, Texture* background);
};