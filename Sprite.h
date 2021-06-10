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
	//int figures[7][4];
	int figures[7][4] =
	{
		{2,4,6,8}, // I
		{2,4,5,7}, // Z
		{3,5,4,6}, // S
		{3,5,4,7}, // T
		{2,3,5,7}, // L
		{3,5,7,6}, // J
		{2,3,4,5}  // O
	};
	t_Sprite(t_Sprite::Sprite_type type, Texture &texture, int x, int y, int width, int height);
	bool stop = false;
	struct t_Point coord[4];
	struct t_Point com;
	Sprite sprite;
	IntRect tetramino;
	Sprite_type tetramino_type;
	void Draw(RenderWindow& window);
	void Draw(RenderWindow& window, Vector2f vec);
	void Move(Direction direction);
	void Move_Down();
	void Flip();
	t_Sprite & operator=(t_Sprite const& a);
};
