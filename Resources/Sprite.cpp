#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "../Game/Game.h"

using namespace sf;

t_Sprite::t_Sprite(t_Sprite::Sprite_type type, Texture &texture, int x, int y, int width, int height)
{
	sprite = Sprite(texture);
	tetramino_type = type;
	tetramino = IntRect(x, y, width, height);

	int figures[7][4] =
	{
		{1,3,5,7}, // I
		{2,4,5,7}, // Z
		{3,5,4,6}, // S
		{3,5,4,7}, // T
		{2,3,5,7}, // L
		{3,5,7,6}, // J
		{2,3,4,5}, // O
	};

	for (int i = 0; i < 4; i++)
	{
		coord[i].x = 200 + tetramino.width * (figures[tetramino_type][i] % 2);
		coord[i].y = tetramino.height * (figures[tetramino_type][i] / 2); 0;
	}
};

void t_Sprite::Move(Direction direction)
{
	for (int i = 0; i < 4; i++)
	{
		if (direction == Direction::Left)
		{
			coord[i].x = coord[i].x - tetramino.width;
			if (coord[i].x <= Game::getInstance().Get_game_shape_Left_border())
			{
				for (int i = 0; i < 4; i++)
				{
					coord[i].x = coord[i].x + tetramino.width;
				}
			}
		}
		if (direction == Direction::Right)
		{
			coord[i].x = coord[i].x + tetramino.width;
			if (coord[i].x >= Game::getInstance().Get_game_shape_Right_border())
			{
				for (int i = 0; i < 4; i++)
				{
					coord[i].x = coord[i].x - tetramino.width;
				}
			}
		}
	}
};

void t_Sprite::Move_Down()
{
	int Bottom = Game::getInstance().Get_game_shape_Bottom_border();
	for (int i = 0; i < 4; i++)
	{
		coord[i].y = coord[i].y + tetramino.height;
		if (coord[i].y >= Bottom - tetramino.height)
		{
			for (int j = 0; j < 4; j++)
			{
				coord[j].y = coord[j].y - tetramino.height;
			}
		}
	}

}
void t_Sprite::Flip()
{
	int right = Game::getInstance().Get_game_shape_Right_border();
	int left = Game::getInstance().Get_game_shape_Left_border();
	if (tetramino_type != t_Sprite::O)
	{
		for (int i = 0; i < 4; i++)
		{
			int x = coord[i].y - com.y;
			int y = coord[i].x - com.x;
			coord[i].x = com.x - x;
			coord[i].y = com.y + y;
		}
		for (int i = 0; i < 4; i++)
		{
			if (coord[i].x + tetramino.width > right)
			{
				for (int j = 0; j < 4; j++)
				{
					coord[j].x = coord[j].x - tetramino.width;
				}
			}
			if (coord[i].x < left)
			{
				for (int j = 0; j < 4; j++)
				{
					coord[j].x = coord[j].x + tetramino.width;
				}
			}
		}
	}
}
void t_Sprite::Draw(RenderWindow& window, int j)
{
	for (int i = 0; i < 4; i++)
	{
		com.x = coord[1].x;
		com.y = coord[1].y;
		sprite.setTextureRect(tetramino);
		sprite.setPosition(coord[i].x, coord[i].y);
		window.draw(sprite);
	}
};
