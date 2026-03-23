#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>


void Box1();

void Box2();

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Focus Example");

    sf::Font font;
    if (!font.openFromFile("ARIAL.TTF")) {
    std::cerr << "Error: Could not load ARIAL.TTF!" << std::endl;
    return -1; // Exit the program if the font is missing
}



    sf::RectangleShape input_box({200.f, 50.f});
    input_box.setPosition({100.f, 100.f});
    input_box.setFillColor(sf::Color(50, 50, 50));
    input_box.setOutlineThickness(2);

    sf::RectangleShape input_box2({200.f, 50.f});
    input_box2.setPosition({100.f, 100.f});
    input_box2.setFillColor(sf::Color(50, 50, 50));
    input_box2.setOutlineThickness(2);


    sf::Text display_text(font, "", 24);
    display_text.setPosition({110.f, 110.f});

    std::string current_input = "";
    
    // NEW: Tracking focus state
    bool isFocused = false;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            // STEP 1: Detect Click to Focus
            if (const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()) {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                
                if (input_box.getGlobalBounds().contains(worldPos)) {
                    isFocused = true;
                    input_box.setOutlineColor(sf::Color::Blue); // Visual hint
                } else {
                    isFocused = false;
                    input_box.setOutlineColor(sf::Color::White);
                }
            }

            // STEP 2: Detect Enter Key to Stop Input
            if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPress->code == sf::Keyboard::Key::Enter) {
                    isFocused = false;
                    input_box.setOutlineColor(sf::Color::White);
                    std::cout << "Input Locked: " << current_input << std::endl;
                }
            }

            // STEP 3: Only take text if Focused
            if (isFocused) {
                if (const auto* textevent = event->getIf<sf::Event::TextEntered>()) {
                    if (textevent->unicode == 8) { // Backspace
                        if (!current_input.empty()) current_input.pop_back();
                    } 
                    else if (textevent->unicode >= '0' && textevent->unicode <= '9') {
                        current_input += static_cast<char>(textevent->unicode);
                    }
                    display_text.setString(current_input);
                }
            }
        }

        window.clear();
        window.draw(input_box);
        window.draw(display_text);
        window.display();
    }
    return 0;
}


