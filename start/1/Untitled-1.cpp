#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "My window");
    window.setPosition({10, 50});

    // 1. Define your objects BEFORE the loop
    sf::CircleShape shape(90.f);
    shape.setFillColor(sf::Color(100, 25, 50));
    shape.setPosition({375.f, 275.f}); // Center it roughly

    sf::CircleShape shape2(50.f);
    shape2.setFillColor(sf::Color(100,25,50));
    shape2.setPosition({330.f, 200.f}); // Center it roughly

    sf::RectangleShape login_button({150.f,50.f});
    login_button.setFillColor(sf::Color(100,25,50));
    login_button.setPosition({20.f,300.f});


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();


            if(const auto* mouseButton =event ->getIf<sf::Event::MouseButtonPressed>())
            {

                sf::Vector2i mousepos =sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousepos);
                
                if (login_button.getGlobalBounds().contains(worldPos))
                {
                    std::cout<<"Login Click"<<std::endl;
                }
            }
        }

        // 2. Rendering happens INSIDE the loop every frame
        window.clear(sf::Color::Black); 
        
        window.draw(shape);
        
        window.draw(shape2);
        window.draw(login_button);// You need to actually call draw
        
        window.display(); 
    }

    return 0;
}

