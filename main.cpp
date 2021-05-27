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
	// —оздаем окно размером 600 на 600 и частотой обновлени€ 60 кадров в секунду
	//sf::RenderWindow window(sf::VideoMode(360, 720), "Game");
	RenderWindow window(VideoMode(640, 760), "Game");
	window.setFramerateLimit(10);

	Event event;
	Music music;
	if (!music.openFromFile("Muzyka_iz_tetrisa.ogg"))
		return -1;
	music.setLoop(true);
	music.play();
	/*m_BackgroundTexture.loadFromFile("background.jpg");

	// —в€зываем спрайт и текстуру
	m_BackgroundSprite.setTexture(m_BackgroundTexture);*/
	while (window.isOpen())
	{
		for (int i = 0; i < 200; i++)
		{
			srand(time(0));
			t_Sprite::Sprite_type tet_type = static_cast<t_Sprite::Sprite_type>(rand() % 7);

			Game& tet_game = Game::getInstance();

			Texture texture;
			texture.loadFromFile("Resources/Texture.JPG");
			tet_game.load_texture(texture);
			t_Sprite tet = t_Sprite(tet_type, texture, rand() % 7 * 18, 0, 18, 18);

			for (int i = 0; i < 40; i++)
			{

				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed) window.close();
					if (event.type == sf::Event::KeyPressed)
					{
						// ѕолучаем нажатую клавишу - выполн€ем соответствующее действие
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
							/* !TODO реализовать ускоренное падение тетрамино*/
						}
						if (event.key.code == sf::Keyboard::Space)
						{
							tet.Flip();
						}
					}
				}
				// «адаем цвет фона - белый
				window.clear(sf::Color::White);
				tet.Move_Down();
				tet.Draw(window, i);
				tet_game.draw(window, RenderStates::Default, 10, 10, 18, 18);
				window.display();
				Sleep(500);
			}
			Sleep(1500);
		}
	}
	return 0;
}