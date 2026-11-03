#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

void SetTextPosition(Text& text, const float& x, const float& y){
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                        textRect.position.y + textRect.size.y / 2.0f});
    text.setPosition(Vector2f(x, y));
}

void FormatButtonAndText(RectangleShape& button, Text& text, const int offsetFromMiddle, const unsigned int& windowWidth, const unsigned int& windowHeight) {
    int buttonWidth = 120;
    int buttonHeight = 50;

    button.setSize(Vector2f(buttonWidth, buttonHeight));
    button.setFillColor(Color::Black);
    button.setOutlineColor(Color::White);
    button.setOutlineThickness(2);
    Vector2f buttonPosition = Vector2f(windowWidth/2 - buttonWidth/2 + offsetFromMiddle, windowHeight/2 - buttonHeight/2);
    button.setPosition(buttonPosition);

    text.setStyle(Text::Bold);
    SetTextPosition(text, buttonPosition.x + button.getSize().x/2, buttonPosition.y + button.getSize().y/2);
}

int main() {
    unsigned int windowWidth = 800;
    unsigned int windowHeight = 600;

    RenderWindow render_window(VideoMode({windowWidth, windowHeight}), "NBA Performance Rankings", Style::Titlebar | Style::Close);

    Color backgroundColor(5, 50, 150);
    Font font;
    if (!font.openFromFile("files/font.ttf")) return -1;

    // Text display
    Text title(font, "NBA Performance Rankings", 24);
    title.setStyle(Text::Bold | Text::Underlined);
    SetTextPosition(title, windowWidth/2, windowHeight/2 - 150);

    Text prompt(font, "What would you like to rank by?", 20);
    prompt.setStyle(Text::Bold);
    SetTextPosition(prompt, windowWidth/2, windowHeight/2 - 75);

    RectangleShape pointsButton;
    Text pointsText(font, "Points", 20);
    FormatButtonAndText(pointsButton, pointsText, -150, windowWidth, windowHeight);

    RectangleShape reboundsButton;
    Text reboundsText(font, "Rebounds", 20);
    FormatButtonAndText(reboundsButton, reboundsText, 0, windowWidth, windowHeight);

    RectangleShape assistsButton;
    Text assistsText(font, "Assists", 20);
    FormatButtonAndText(assistsButton, assistsText, 150, windowWidth, windowHeight);

    while (render_window.isOpen()) {
        while (const optional event = render_window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                render_window.close();
            }
            if (const auto* mousePress = event->getIf<Event::MouseButtonPressed>()) {
                if (mousePress->button == Mouse::Button::Left) {
                    if (pointsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(render_window)))) {
                        // TODO: points button logic here
                        cout << "points button pressed" << endl;
                    }
                    if (reboundsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(render_window)))) {
                        // TODO: rebounds button logic here
                        cout << "rebounds button pressed" << endl;
                    }
                    if (assistsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(render_window)))) {
                        // TODO: assists button logic here
                        cout << "assists button pressed" << endl;
                    }
                }
            }
        }
        render_window.clear(backgroundColor);
        render_window.draw(title);
        render_window.draw(prompt);

        render_window.draw(pointsButton);
        render_window.draw(pointsText);
        render_window.draw(reboundsButton);
        render_window.draw(reboundsText);
        render_window.draw(assistsButton);
        render_window.draw(assistsText);

        render_window.display();
    }

    return 0;
}