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
	music.play();
	
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

	Texture texture_menu;
	texture_menu.loadFromFile("Resources/Menu.png");
	Menu tet_menu = Menu(texture_menu);
	Texture texture_main_menu;
	Texture texture_new_game_button;
	texture_main_menu.loadFromFile("Resources/Main_Menu.png");
	texture_new_game_button.loadFromFile("Resources/New_Game.png");
	Main_Menu tet_main_menu = Main_Menu(texture_main_menu);
	Mouse::Button tet_new_game_button;
	while (window.isOpen())
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
			}
			//auto range = Game::getInstance().all_coords.equal_range(0);
			//auto end = range.second;
			//if (end.second == )
			window.display();
		}
		tet_game.breaking_lines();
		std::cout << (tet_game.Get_game_shape_position().y) << std::endl;
		if (Game::getInstance().all_coords.find((tet_game.Get_game_shape_position().y + 18)) != Game::getInstance().all_coords.end())
		{
			break;
		}
		tet = pre_tet;
	}
	return 0;
}