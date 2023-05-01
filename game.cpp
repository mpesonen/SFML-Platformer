#include "game.hpp"
#include "interactions.hpp"
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

    auto player = this->get_all<Player>()[0];
    player->resetCollisionDirections();

    for (auto& brick : groupedEntities)
    {

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
    gameWindow.setFramerateLimit(Constants::frameRate);
    
    auto robotoFont = sf::Font();
    auto success = robotoFont.loadFromFile("./fonts/Roboto-Regular.ttf");
    stateText = std::make_unique<sf::Text>(sf::Text{robotoFont, "Paused", 35U});
    
    if (success)
    {
        stateText->setFont(robotoFont);
        stateText->setPosition(sf::Vector2f{Constants::window_width / 2.f, 100.f});
        stateText->setCharacterSize(35);
        stateText->setFillColor(sf::Color::White);
        stateText->setString("Paused");
    }

    this->level = std::make_unique<Map>("./maps/map01.json");
}

void Game::reset()
{
    gameState = GameState::paused;

    // Destroy and re-create all entities
    entityManager.clear();

    for (const auto &tile : this->level->getMapTiles())
    {
        int currentTile = tile.second;

        switch (currentTile)
        {
            case 0:
                std::cout << "\nUnexpected 0 at: " << std::get<0>(tile.first) << "," << std::get<1>(tile.first) << "\n";
                [[fallthrough]];
            default:
                break;
            case 1:
                std::cout << "\nPlayer at: " << std::get<0>(tile.first) << "," << std::get<1>(tile.first) << "\n";
                entityManager.create<Player>(
                    static_cast<float>(std::get<0>(tile.first)) * Constants::tileDimension, 
                    static_cast<float>(std::get<1>(tile.first)) * Constants::tileDimension);
                break;
            case 2:
                std::cout << "\nBrick at: " << std::get<0>(tile.first) << "," << std::get<1>(tile.first) << "\n";
                entityManager.create<Brick>(
                    static_cast<float>(std::get<0>(tile.first)) * Constants::tileDimension, 
                    static_cast<float>(std::get<1>(tile.first)) * Constants::tileDimension);
                break;
        }
    }

    for (int idxH = 0; idxH < this->level->getHeight(); ++idxH)
    {
        for (int idxW = 0; idxW < this->level->getWidth(); ++idxW)
        {
            int currentTile = this->level->getTileAt(idxW, idxH);
        }

        std::cout <<  "\n";
    }
}

void Game::run()
{
    // View for enabling scrolling
    sf::View view;
    view.reset(sf::FloatRect(sf::Vector2f{0.f, 0.f}, sf::Vector2f{Constants::window_width, Constants::window_height}));
    view.setViewport(sf::FloatRect(sf::Vector2f{0.f, 0.f}, sf::Vector2f{1.0f, 1.0f}));

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
        entityManager.apply_all<Player>([this](auto& player) {
            entityManager.apply_all<Brick>([&player](auto& brick) {
                handle_collision(player, brick);
            });
        });
        
        auto playerPos = entityManager.get_all<Player>()[0]->getPosition();
        view.setCenter(sf::Vector2f{playerPos.x, Constants::window_height / 2.f});
        gameWindow.setView(view);

        if (playerPos.y > Constants::window_height)
        {
            playerPos.y = 0;
        }

        entityManager.refresh();
        entityManager.draw(gameWindow);

        gameWindow.display();
    }
}
