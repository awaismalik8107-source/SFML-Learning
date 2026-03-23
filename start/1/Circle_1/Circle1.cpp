#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <algorithm> // for std::clamp

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Gradient Ball");
    window.setFramerateLimit(60);

    const float ballRadius = 30.f;
    
    // --- Create a Gradient Image (SFML 3 syntax) ---
    // In SFML 3, we can initialize size directly in the constructor
    sf::Image gradientImage({100, 100}, sf::Color::Black); 
    
    for (unsigned int y = 0; y < 100; ++y) {
        for (unsigned int x = 0; x < 100; ++x) {
            float dx = (float)x - 35.f; // Highlight offset
            float dy = (float)y - 35.f;
            float distance = std::sqrt(dx * dx + dy * dy);
            
            // Sphere shading logic
            int intensity = static_cast<int>(255.f * (1.f - (distance / 70.f)));
            intensity = std::clamp(intensity, 40, 255); 
            
            gradientImage.setPixel({x, y}, sf::Color(intensity, intensity / 5, intensity / 5));
        }
    }

    sf::Texture ballTexture;
    // Using the result to satisfy the [[nodiscard]] warning
    if (!ballTexture.loadFromImage(gradientImage)) {
        return -1;
    }
    ballTexture.setSmooth(true);

    // Ball Setup
    sf::CircleShape ball(ballRadius);
    ball.setOrigin({ballRadius, ballRadius});
    ball.setTexture(&ballTexture);
    
    // Physics
    float velocity_y = 0.0f;
    float velocity_x = 0.0f;
    float pos_x = 400.f, pos_y = 100.f;
    bool isGrounded = false;

    const float gravity = 1200.f;
    const float jumpForce = -600.f;
    const float floorY = 580.f;
    

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        float dt = 1.f / 60.f;
        
        // Input Handling
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity_x = -300.f;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity_x = 300.f;
        else velocity_x *= 0.90f; // Friction

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isGrounded) {
            velocity_y = jumpForce;
            isGrounded = false;
        }

        // Physics Update
        velocity_y += gravity * dt;
        pos_y += velocity_y * dt;
        pos_x += velocity_x * dt;
        
        // Collision
        if (pos_y + ballRadius >= floorY) {
            pos_y = floorY - ballRadius;
            velocity_y *= -0.5f; 
            if (std::abs(velocity_y) < 40.f) {
                velocity_y = 0;
                isGrounded = true;
            }
        } else {
            isGrounded = false;
        }

        // Visual Polish: Squash and Stretch
        if (!isGrounded) {
            float stretch = 1.0f + (std::abs(velocity_y) / 2500.f);
            ball.setScale({1.0f / stretch, stretch});
        } else {
            ball.setScale({1.0f, 1.0f});
        }
        
        ball.setPosition({pos_x, pos_y});

        window.clear(sf::Color(10, 10, 20));
        window.draw(ball);
        window.display();
    }

    return 0;
}