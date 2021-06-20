#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Menu
{
public:
	Menu(Texture& texture_menu);
	Sprite menu;
	int menu_x;
	int menu_y;
	void Draw(RenderWindow& window);
};
class Main_Menu
{
public:
	Main_Menu(Texture& texture_main_menu);
	Sprite main_menu;
	void Draw(RenderWindow& window);
};
class tet_Button
{
public:
	tet_Button(Texture* texture_button, int, int);
	int x;
	int y;
	bool isBack;
	RectangleShape button;
	void Draw(RenderTarget& target, RenderStates states);
};