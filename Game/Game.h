#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "../Resources/Sprite.h"

using namespace sf;
class Game
{
private:
	Game() {};
protected:
	//int field[20][40];
	Font font;
	RectangleShape game_shape;
	RectangleShape stats_shape;
	Sprite sprite;
	//IntRect tetramino;
public:
	static Game& getInstance() {
		static Game instance;
		return instance;
	};
	using coords = std::pair <t_Point, IntRect>;
	std::vector <coords> all_coords = {};
	void draw(RenderTarget& target, RenderStates states, int x, int y, int, int);
	int Get_game_shape_Left_border() { return (int) (game_shape.getPosition().x); };
	int Get_game_shape_Right_border() { return (int)(game_shape.getPosition().x + game_shape.getSize().x); };
	int Get_game_shape_Bottom_border() { return (int)(game_shape.getPosition().y + game_shape.getSize().y); };
	void append_sprite(t_Point, IntRect);
	void load_texture(Texture tex) { sprite.setTexture(tex); };
};