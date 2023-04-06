#include "game.hpp"

void EntityManager::refresh()
{
}

void EntityManager::clear()
{
}

void EntityManager::update()
{
    for (auto& e : allEntities)
    {
        e->update();
    }
}

void EntityManager::draw(sf::RenderWindow &window)
{
    for (auto& e : allEntities)
    {
        e->draw(window);
    }
}

Game::Game()
{
    gameWindow.setFramerateLimit(constants::frameRate);

    robotoFont.loadFromFile("./fonts/Roboto-Regular.ttf");

    stateText.setFont(robotoFont);
    stateText.setPosition(constants::window_width / 2.f, 100.f);
    stateText.setCharacterSize(35);
    stateText.setFillColor(sf::Color::White);
    stateText.setString("Paused");
}

void Game::reset()
{
    gameState = GameState::paused;

    // Destroy and re-create all entities
    entityManager.clear();

    entityManager.create<Player>(200.f, 600.f);

    for (int i = 0; i < 10; i++)
    {
        entityManager.create<Brick>((float) i * 50.f, constants::window_height - 100.f);
    }
}

void Game::run()
{
    while (gameWindow.isOpen()) {
		// Clear the screen
		gameWindow.clear(sf::Color::Black);

        // Check for any events since the last loop iteration
		sf::Event event;

		while (gameWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			gameWindow.close();
		}

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
		    break;
        }

        gameWindow.draw(stateText);

        entityManager.update();
        entityManager.refresh();
        entityManager.draw(gameWindow);

        gameWindow.display();
    }
}
