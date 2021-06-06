#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Sprite.h"
#include "windows.h"
#include <ctime>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(700, 800), "Tetris-Classic", Style::Close);
	window.setFramerateLimit(18);

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

	tet_game.draw(window, RenderStates::Default, 14, 14, 18, 18, font);
	while (window.isOpen())
	{
		t_Sprite::Sprite_type tet_type = static_cast<t_Sprite::Sprite_type>(rand() % 7);
		t_Sprite tet = t_Sprite(tet_type, texture, rand() % 7 * 18, 0, 18, 18);
		step = 0.3;

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
				}
			}
			// Задаем цвет фона - белый
			window.clear(sf::Color::White);
			tet_game.draw(window, RenderStates::Default, 14, 14, 18, 18, font);
			tet.Draw(window);
			if (timer > step)
			{
				tet.Move_Down();
				timer = 0;
			}
			window.display();
		}
		tet_game.breaking_lines();
	}
	Sleep(1000);
return 0;
}