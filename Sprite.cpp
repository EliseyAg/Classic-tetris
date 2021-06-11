#include <iostream>
#include <SFML/Graphics.hpp>
#include "Sprite.h"
#include "Game.h"

using namespace sf;

t_Sprite::t_Sprite(t_Sprite::Sprite_type type, Texture &texture, int x, int y, int width, int height)
{
	sprite = Sprite(texture);
	tetramino_type = type;
	tetramino = IntRect(x, y, width, height);

	int t_x = (Game::getInstance().Get_game_shape_Right_border() - Game::getInstance().Get_game_shape_Left_border()) / 2 + Game::getInstance().Get_game_shape_Left_border();
	int t_y = Game::getInstance().Get_game_shape_Top_border();
	for (int i = 0; i < 4; i++)
	{
		coord[i].x = tetramino.width * (figures[tetramino_type][i] % 2) + t_x;
		coord[i].y = tetramino.height * (figures[tetramino_type][i] / 2) + t_y - tetramino.height;
	}
};

void t_Sprite::Move(Direction direction)
{
	int left = Game::getInstance().Get_game_shape_Left_border();
	int right = Game::getInstance().Get_game_shape_Right_border();
	int step = 0;
	if (direction == Direction::Left)
		step = -tetramino.width;
	if (direction == Direction::Right)
		step = tetramino.width;
	for (int i = 0; i < 4; i++)
	{		
		if (((coord[i].x + step) < left) || ((coord[i].x + step) >= right))
		{
			return;
		}
		auto range = Game::getInstance().all_coords.equal_range(coord[i].y);
		for (auto k = range.first; k != range.second; ++k)
		{
			if (coord[i].x + step == (k->second).first.x)
			{
				return;
			}
		}
	}
	for (int j = 0; j < 4; j++)
	{
		coord[j].x = coord[j].x + step;
	}
};

void t_Sprite::Move_Down()
{
	int Bottom = Game::getInstance().Get_game_shape_Bottom_border();
	for (int i = 0; i < 4; i++)
	{
		coord[i].y = coord[i].y + tetramino.height;
		if (coord[i].y >= Bottom - tetramino.height)
			stop = true;
		for (auto j = Game::getInstance().all_coords.begin(); j != Game::getInstance().all_coords.end(); j++)
		{
			if (coord[i].x == (j->second).first.x && (j->second).first.y - coord[i].y == tetramino.height)
			{
				stop = true;
				break;
			}
		}
	}
	if (stop)
	{
		for (int j = 0; j < 4; j++)
		{
			Game::getInstance().append_sprite(coord[j], tetramino);
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

void t_Sprite::Draw(RenderWindow& window)
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

void t_Sprite::Draw(RenderWindow& window, Vector2f vec)
{
	for (int i = 0; i < 4; i++)
	{
		coord[i].x = tetramino.width * (figures[tetramino_type][i] % 2) + vec.x + 108;
		coord[i].y = tetramino.height * (figures[tetramino_type][i] / 2) + vec.y + 180;
		sprite.setTextureRect(tetramino);
		sprite.setPosition(coord[i].x, coord[i].y);
		window.draw(sprite);
	}
};

t_Sprite & t_Sprite::operator=(t_Sprite const& a)
{
	sprite = a.sprite;
	tetramino_type = a.tetramino_type;
	tetramino = a.tetramino;
	int t_x = (Game::getInstance().Get_game_shape_Right_border() - Game::getInstance().Get_game_shape_Left_border()) / 2 + Game::getInstance().Get_game_shape_Left_border();
	int t_y = Game::getInstance().Get_game_shape_Top_border();
	for (int i = 0; i < 4; i++)
	{
		coord[i].x = tetramino.width * (figures[tetramino_type][i] % 2) + t_x;
		coord[i].y = tetramino.height * (figures[tetramino_type][i] / 2) + t_y - tetramino.height;
	}
	stop = false;
	return *this;
}
