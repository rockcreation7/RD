#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{

    class Projectile : public sf::CircleShape
    {
    public:
        Projectile(float radius, float speed, const sf::Vector2f &direction)
            : sf::CircleShape(radius), speed(speed), direction(direction)
        {
            setFillColor(sf::Color::Blue);
        }

        void update()
        {
            move(speed * direction.x, speed * direction.y);
        }

        bool isOutOfBounds(const sf::RenderWindow &window) const
        {
            const sf::Vector2f &pos = getPosition();
            return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
        }

    private:
        float speed;
        sf::Vector2f direction;
    };

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");

    // Create game objects
    sf::CircleShape playerShape(25);

    /* sf::ConvexShape playerShape;
    playerShape.setPointCount(4); // Triangle shape
    playerShape.setPoint(0, sf::Vector2f(-20, -20)); // Top point
    playerShape.setPoint(1, sf::Vector2f(-20, 20)); // Bottom left point
    playerShape.setPoint(2, sf::Vector2f(20, 20));
    playerShape.setPoint(3, sf::Vector2f(20, -20));  */
    playerShape.setFillColor(sf::Color::Green);

    playerShape.setPosition(400, 300);

    sf::CircleShape coinShape(15);
    coinShape.setFillColor(sf::Color::Yellow);
    coinShape.setPosition(200, 200);

    sf::CircleShape enemyShape(20);
    enemyShape.setFillColor(sf::Color::Red);
    enemyShape.setPosition(600, 400);

    float playerHealth = 100.0f;   // Player's initial health
    float collisionDamage = 10.0f; // Amount of damage taken upon collision
    sf::Clock damageTimer;         // Timer to track the duration of the damage effect

    std::vector<Projectile> projectiles;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        const float moveSpeed = 0.1f;
        // Player movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerShape.move(0, -moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            playerShape.move(0, moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerShape.move(-moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerShape.move(moveSpeed, 0);
        }

        // Shooting projectiles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            sf::Vector2f projectileDirection(1.0f, 0.0f); // Change the direction as needed
            float projectileSpeed = 0.3f;                 // Change the speed as needed
            projectiles.push_back(Projectile(5, projectileSpeed, projectileDirection));

            projectiles.back().setPosition(playerShape.getPosition());
        }

        // Update projectile positions
        for (auto &projectile : projectiles)
        {
            projectile.update();
                    // Check if projectile is out of bounds
            if (projectile.isOutOfBounds(window))
            {
                // projectile() ;// Move the projectile out of sight
            }
        }

        // Collision detection
        if (playerShape.getGlobalBounds().intersects(coinShape.getGlobalBounds()))
        {
            coinShape.setPosition(1000, 1000); // move the coin out of sight
            // Increase player's score or perform other actions
        }
        if (playerShape.getGlobalBounds().intersects(enemyShape.getGlobalBounds()))
        {

            // Check if enough time has passed since the last damage taken
            if (damageTimer.getElapsedTime().asSeconds() >= 1.0f) // Adjust the duration as desired
            {
                playerHealth -= collisionDamage;
                damageTimer.restart();
            }
            std::cout << playerHealth << std::endl;
            // Handle collision with enemy, e.g., decrease player's health
        }

        

        // Remove projectiles that are out of the window
        /*     projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
                                             [&](const Projectile &projectile)
                                             {
                                                 const sf::Vector2f &pos = projectile.getPosition();
                                                 return pos.x < 0 || pos.x > window.getSize().x || pos.y < 0 || pos.y > window.getSize().y;
                                             }),
                              projectiles.end()); */

    /*     projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
                                         [&](const Projectile &projectile)
                                         {
                                             const sf::Vector2f &pos = projectile.getPosition();
                                             return pos.x < -50 || pos.x > 850 || pos.y < -50 || pos.y > 650;
                                         }),
                          projectiles.end()); */
        window.clear();
        window.draw(playerShape);
        window.draw(coinShape);
        window.draw(enemyShape);
        for (const auto &projectile : projectiles)
        {
            window.draw(projectile);
        }
        window.display();
    }

    return 0;
}

// g++ game.cpp -o game -I SFML/include -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
