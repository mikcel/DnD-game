#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	window.setFramerateLimit(60); // Sets the frame rate

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen()) // Game loop
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}