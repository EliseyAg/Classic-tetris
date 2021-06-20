#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Sprite.h"
#include "windows.h"
#include <ctime>
#include "Menu.h"

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(700, 760), "Tetris-Classic", Style::Close);
	window.setFramerateLimit(18);

	bool pause = false;

	Event event;
	Music music;
	if (!music.openFromFile("Resources/Muzyka_iz_tetrisa.ogg"))
		return -1;
	music.setLoop(true);
	
	srand(time(0));
	
	// Часы (таймер)
	float timer = 0, step = 0.3;
	Clock clock;
	//m_BackgroundTexture.loadFromFile("background.jpg");

	Game& tet_game = Game::getInstance();
	Texture texture, background;
	texture.loadFromFile("Resources/Texture.JPG");
	background.loadFromFile("Resources/table.png");
	tet_game.load_textures(texture, &background);

	Font font;
	if (!font.loadFromFile("Resources/arial.ttf"))
		return -1;
	tet_game.draw(window, RenderStates::Default, 10, 10, 18, 18, font);
	t_Sprite::Sprite_type tet_type = static_cast<t_Sprite::Sprite_type>(rand() % 7);
	t_Sprite tet = t_Sprite(tet_type, texture, rand() % 7 * 18, 0, 18, 18);

	Mouse mouse;

	Texture texture_menu;
	texture_menu.loadFromFile("Resources/Menu.png");
	Menu tet_menu = Menu(texture_menu);
	Texture texture_main_menu;
	texture_main_menu.loadFromFile("Resources/Main_Menu.png");
	Main_Menu tet_main_menu = Main_Menu(texture_main_menu);

	Texture texture_new_game_button;
	texture_new_game_button.loadFromFile("Resources/Button_New_Game.png");
	int new_game_button_x;
	int new_game_button_y;
	new_game_button_x = (Game::getInstance().Get_game_shape_Right_border() - Game::getInstance().Get_game_shape_Left_border()) / 1.5;
	new_game_button_y = (Game::getInstance().Get_game_shape_Bottom_border() - Game::getInstance().Get_game_shape_Top_border()) / 1.5;
	tet_Button tet_new_game_button = tet_Button(&texture_new_game_button, new_game_button_x, new_game_button_y);
	Texture texture_back_to_menu_button;
	texture_back_to_menu_button.loadFromFile("Resources/Button_Back_to_Main_menu.png");
	int back_to_menu_button_x;
	int back_to_menu_button_y;
	back_to_menu_button_x = (Game::getInstance().Get_game_shape_Right_border() - Game::getInstance().Get_game_shape_Left_border()) / 1.3;
	back_to_menu_button_y = (Game::getInstance().Get_game_shape_Bottom_border() - Game::getInstance().Get_game_shape_Top_border()) / 2.7;
	tet_Button tet_back_to_menu_button = tet_Button(&texture_back_to_menu_button, back_to_menu_button_x, back_to_menu_button_y);
	//texture_main_menu.loadFromFile("Resources/Game_Over.png");
	while (window.isOpen())
	{
		tet_main_menu.Draw(window);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				// Получаем нажатую клавишу - выполняем соответствующее действие
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
			if (mouse.isButtonPressed(mouse.Left))
			{
				if ((mouse.getPosition(window).x >= tet_new_game_button.x && mouse.getPosition(window).x <= tet_new_game_button.x + 200) && (mouse.getPosition(window).y >= tet_new_game_button.y && mouse.getPosition(window).y <= tet_new_game_button.y + 100))
				{
					tet_back_to_menu_button.isBack = false;
					music.play();
					while (!tet_back_to_menu_button.isBack)
					{
						step = 0.3;
						tet_type = static_cast<t_Sprite::Sprite_type>(rand() % 7);
						t_Sprite pre_tet = t_Sprite(tet_type, texture, rand() % 7 * 18, 0, 18, 18);

						while (!tet.stop)
						{
							float time = clock.getElapsedTime().asSeconds();
							clock.restart();
							timer += time;

							while (window.pollEvent(event))
							{
								if (event.type == sf::Event::Closed) window.close();
								if (event.type == sf::Event::KeyPressed)
								{
									// Получаем нажатую клавишу - выполняем соответствующее действие
									if (event.key.code == sf::Keyboard::Escape) window.close();
									if (event.key.code == sf::Keyboard::Left)
									{
										tet.Move(Direction::Left);
									}
									if (event.key.code == sf::Keyboard::Right)
									{
										tet.Move(Direction::Right);
									}
									if (event.key.code == sf::Keyboard::Down)
									{
										step = 0.05;
									}
									if (event.key.code == sf::Keyboard::Space)
									{
										tet.Flip();
									}
									if (event.key.code == sf::Keyboard::P)
									{
										pause = !pause;
										break;
									}
								}
							}
							if (!pause)
							{
								// Задаем цвет фона - белый
								window.clear(sf::Color::White);
								tet_game.draw(window, RenderStates::Default, 10, 10, 18, 18, font);
								tet.Draw(window);
								pre_tet.Draw(window, tet_game.Get_stats_shape_position());

								if (timer > step)
								{
									tet.Move_Down();
									timer = 0;
								}
							}
							else
							{
								tet_menu.Draw(window);
								tet_back_to_menu_button.Draw(window, RenderStates::Default);
								if (mouse.isButtonPressed(mouse.Left))
								{
									if ((mouse.getPosition(window).x >= tet_back_to_menu_button.x && mouse.getPosition(window).x <= tet_back_to_menu_button.x + 200) && (mouse.getPosition(window).y >= tet_back_to_menu_button.y && mouse.getPosition(window).y <= tet_back_to_menu_button.y + 100))
									{
										tet_back_to_menu_button.isBack = true;
										window.clear(sf::Color::White);
										Game::getInstance().all_coords.clear();
										pause = false;
										music.stop();
										break;
									}
								}
							}
							window.display();
							if (tet_back_to_menu_button.isBack)
							{
								break;
							}
						}
						if (!tet_back_to_menu_button.isBack)
						{
							tet_game.breaking_lines();
							tet = pre_tet;
							std::cout << (tet_game.Get_game_shape_position().y) << std::endl;
							//if (Game::getInstance().all_coords.find((tet_game.Get_game_shape_position().y + 18)) != Game::getInstance().all_coords.end())
							//{
							//	while (true)
							//	{
							//		window.clear(sf::Color::White);
							//		tet_main_menu.Draw(window);
							//	}
							//}
						}
					}
				}
			}
		}
		tet_new_game_button.Draw(window, RenderStates::Default);
		window.display();
		window.clear(sf::Color::White);
	}
	return 0;
}