#include "Menu.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

Menu::Menu(Texture& texture_menu)
{
	menu = Sprite(texture_menu);

	menu_x = (Game::getInstance().Get_game_shape_Right_border() - Game::getInstance().Get_game_shape_Left_border()) / 3;
	menu_y = (Game::getInstance().Get_game_shape_Bottom_border() - Game::getInstance().Get_game_shape_Top_border()) / 4;
}
void Menu::Draw(RenderWindow& window)
{
	menu.setPosition(menu_x, menu_y);
	window.draw(menu);
}
Main_Menu::Main_Menu(Texture& texture_main_menu)
{
	main_menu = Sprite(texture_main_menu);

	new_game = false;
}
void Main_Menu::Draw(RenderWindow& window)
{
	main_menu.setPosition(0, 0);
	window.draw(main_menu);
}