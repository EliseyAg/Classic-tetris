#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game/Game.h"
#include "Resources/Sprite.h"
#include "windows.h"
#include <ctime>

using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 750), "Tetris-Classic", Style::Close);
	window.setFramerateLimit(10);

	Event event;
	Music music;
	if (!music.openFromFile("Muzyka_iz_tetrisa.ogg"))
		return -1;
	music.setLoop(true);
	music.play();
	
	srand(time(0));
	
	// Часы (таймер)
	float timer = 0, step = 0.3;
	Clock clock;
	//m_BackgroundTexture.loadFromFile("background.jpg");

	Game& tet_game = Game::getInstance();
	Texture texture;
	texture.loadFromFile("Resources/Texture.JPG");
	tet_game.load_texture(texture);

	Font font;
	if (!font.loadFromFile("Resources/arial.ttf"))
		return -1;
	
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
			tet_game.draw(window, RenderStates::Default, 10, 10, 18, 18, font);
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
	Sleep(1500);
return 0;
}