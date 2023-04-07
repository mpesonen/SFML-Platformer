#include "game.hpp"
#include <iostream>

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
    
    /*auto success = robotoFont.loadFromFile("./fonts/Roboto-Regular.ttf");
    this->stateText = sf::Text(sf::String{"Paused"}, robotoFont);
    if (success)
    {
        stateText.setFont(robotoFont);
        stateText.setPosition(sf::Vector2f{constants::window_width / 2.f, 100.f});
        stateText.setCharacterSize(35);
        stateText.setFillColor(sf::Color::White);
        stateText.setString("Paused");
    }*/

    this->level = std::make_unique<Map>("./maps/map01.json");
}

void Game::reset()
{
    gameState = GameState::paused;

    // Destroy and re-create all entities
    entityManager.clear();

    //entityManager.create<Player>(200.f, 600.f);

    for (int idxH = 0; idxH < this->level->getHeight(); ++idxH)
    {
        for (int idxW = 0; idxW < this->level->getWidth(); ++idxW)
        {
            int currentTile = this->level->getTileAt(idxW, idxH);

            std::cout << idxH << "," << idxW << ": " << currentTile;

            /*switch (currentTile)
            {
                case 0:
                    [[fallthrough]];
                default:
                    std::cout << "d,";
                    break;
                case 1:
                    std::cout << "\nPlayer at: " << idxW << ", " << idxH << "\n";
                    entityManager.create<Player>(
                        static_cast<float>(idxW) * constants::tileDimension, 
                        static_cast<float>(idxH) * constants::tileDimension);
                    break;
                case 2:
                    entityManager.create<Brick>(
                        static_cast<float>(idxW) * constants::tileDimension, 
                        static_cast<float>(idxH) * constants::tileDimension);
                    break;
            }*/
        }

        std::cout <<  "\n";
    }

    /*for (int i = 0; i < 10; i++)
    {
        entityManager.create<Brick>((float) i * 50.f, constants::window_height - 100.f);
    }*/
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

        //gameWindow.draw(stateText);

        entityManager.update();
        entityManager.refresh();
        entityManager.draw(gameWindow);

        gameWindow.display();
    }
}
