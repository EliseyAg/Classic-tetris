#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum class Direction { Left = 0, Right = 1 };

struct t_Point
{
	int x, y;
};

class t_Sprite
{
public:
	enum Sprite_type
	{
		I,
		Z,
		S,
		T,
		L,
		J,
		O
	};
	int figures[7][4];
	t_Sprite(t_Sprite::Sprite_type type, Texture &texture, int x, int y, int width, int height);
	bool stop = false;
	struct t_Point coord[4];
	struct t_Point com;
	Sprite sprite;
	IntRect tetramino;
	Sprite_type tetramino_type;
	void Draw(RenderWindow& window);
	void Move(Direction direction);
	void Move_Down();
	void Flip();
};
