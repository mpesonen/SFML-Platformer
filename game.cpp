#include "game.hpp"
#include "interactions.hpp"
#include <iostream>

void EntityManager::refresh()
{
    // We must clean up the alias pointers first, to avoid dangling pointers
	// We simply remove them from their vector
    for (auto& [type, alias_vector] : groupedEntities)
    {
		alias_vector.erase(remove_if(begin(alias_vector), end(alias_vector),
				[](const auto& p) { return p->isDestroyed(); }
				),
		end(alias_vector));    
    }

    // Now we can safely destroy the objects, now that there are no aliases to them
	allEntities.erase(remove_if(begin(allEntities), end(allEntities),
			[](const auto& p) { return p->isDestroyed(); }
			),
	end(allEntities));
}

void EntityManager::clear()
{
    for (auto& e : allEntities)
    {
        e->destroy();
    }
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
            case Constants::TILE_NONE:
                [[fallthrough]];
            default:
                break;
            case Constants::TILE_PLAYER:
                //std::cout << "\nPlayer at: " << std::get<0>(tile.first) << "," << std::get<1>(tile.first) << "\n";
                playerStartPos = sf::Vector2f{std::get<0>(tile.first) * Constants::tileDimension, std::get<1>(tile.first) * Constants::tileDimension};
                entityManager.create<Player>(
                    static_cast<float>(playerStartPos.x), 
                    static_cast<float>(playerStartPos.y));
                break;
            case Constants::TILE_BRICK:
                //std::cout << "\nBrick at: " << std::get<0>(tile.first) << "," << std::get<1>(tile.first) << "\n";
                entityManager.create<Brick>(
                    static_cast<float>(std::get<0>(tile.first)) * Constants::tileDimension, 
                    static_cast<float>(std::get<1>(tile.first)) * Constants::tileDimension);
                break;
            case Constants::TILE_BOX:
                //std::cout << "\nBox (not implemented) at: " << std::get<0>(tile.first) << "," << std::get<1>(tile.first) << "\n";                break;     
                break;
            case Constants::TILE_COIN:
                //std::cout << "\nCoin at: " << std::get<0>(tile.first) << "," << std::get<1>(tile.first) << "\n";
                entityManager.create<Coin>(
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

        entityManager.update();
        entityManager.apply_all<Player>([this](auto& player) {
            entityManager.apply_all<Brick>([&player](auto& brick) {
                handle_collision(player, brick);
            });
            entityManager.apply_all<Coin>([&player](auto& coin) {
                handle_collision(player, coin);
            });
        });
        
        auto playerPos = entityManager.get_all<Player>()[0]->getPosition();
        view.setCenter(sf::Vector2f{playerPos.x, Constants::window_height / 2.f});
        gameWindow.setView(view);

        if (playerPos.y > Constants::window_height)
        {
            entityManager.get_all<Player>()[0]->setPosition(playerStartPos);
        }

        entityManager.refresh();
        entityManager.draw(gameWindow);

        gameWindow.display();
    }
}
