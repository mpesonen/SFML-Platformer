#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <typeinfo>
#include <vector>

#include "entity.hpp"
#include "player.hpp"
#include "brick.hpp"
#include "constants.hpp"

class EntityManager {
private:
    std::vector<std::unique_ptr<Entity>> allEntities;

    // Map for Entities grouped by type
    std::map<size_t, std::vector<Entity *>> groupedEntities;
public:
    // Variadic template for entities
    template <typename T, typename... Args>
    T& create(Args&&... args) {
        // Assert that it's derived from Entity
        static_assert(std::is_base_of<Entity, T>::value,
        R"("T" type parameter in create() must be derived from "entity")");

        // Create a unique_ptr for the entity
        auto ptr{std::make_unique<T>(std::forward<Args>(args)...)};

        // Make an alias pointer to the allocated memory, which will be stored in entity_type_vector
        auto ptr_alias = ptr.get();

        auto hash = typeid(T).hash_code();

        // Alias pointer into the grouped map
        groupedEntities[hash].emplace_back(ptr_alias);

        // Object pointer into Entity vector
        allEntities.emplace_back(std::move(ptr));

        return *ptr_alias;
    }

    // Function to scan all entities and clean up destroyed ones
    void refresh();

    // Destroys all entities
    void clear();

    // Get all by type
    template<typename T>
    auto& get_all() {
        return groupedEntities[typeid(T).hash_code()];
    }

    // Apply a function to all entities of given type
    template <typename T, typename Func>
    void apply_all(const Func& func) {
        auto& entityGroup{get_all<T>()};

        for (auto ptr : entityGroup)
        {
            // Dynamic cast is used to cast a pointer to base class object
            // to a pointer to derived class object
            func(*dynamic_cast<T*>(ptr));
        }
    }

    void update();
    void draw(sf::RenderWindow& window);
};

class Game {
    enum class GameState { paused, running };

    sf::RenderWindow gameWindow{{constants::window_width, constants::window_height},
		"SFML Platformer"};

    EntityManager entityManager;

    sf::Font robotoFont;
    sf::Text stateText;
    
    GameState gameState{GameState::paused};
public:
    Game();
    void reset();
    void run();
};

#endif