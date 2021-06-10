#include "Menu.h"
#include "Game.h"

Menu::Menu()
{
	menu_x = (Game::getInstance().Get_game_shape_Right_border() - Game::getInstance().Get_game_shape_Left_border()) / 2 + Game::getInstance().Get_game_shape_Left_border();
	menu_y = Game::getInstance().Get_game_shape_Top_border() - Game::getInstance().Get_game_shape_Bottom_border();
}
void Menu::Draw(RenderWindow& window)
{
	menu.setPosition(menu_x, menu_y);
}