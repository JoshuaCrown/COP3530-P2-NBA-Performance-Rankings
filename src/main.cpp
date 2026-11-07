#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "CSVReader.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include "HeapSort.h"
#include "MergeSort.h"

using namespace std;
using namespace sf;

void SetTextPosition(Text& text, const float& x, const float& y){
    FloatRect textRect = text.getLocalBounds();
    text.setOrigin({textRect.position.x + textRect.size.x / 2.0f,
                        textRect.position.y + textRect.size.y / 2.0f});
    text.setPosition(Vector2f(x, y));
}

void FormatButtonAndText(RectangleShape& button, Text& text, const Vector2f& pos, const Vector2f& size) {
    int buttonWidth = size.x;
    int buttonHeight = size.y;

    button.setSize(Vector2f(buttonWidth, buttonHeight));
    button.setFillColor(Color::Black);
    button.setOutlineColor(Color::White);
    button.setOutlineThickness(2);
    button.setPosition(pos);

    text.setStyle(Text::Bold);
    // center text
    SetTextPosition(text, pos.x + button.getSize().x/2, pos.y + button.getSize().y/2);
}

void DrawTable(RenderWindow& window, const Font& font, void(*SetTextPosition)(Text &text, const float& x, const float& y), vector<PlayerPerformance>& players) {
    int width = window.getSize().x;

    Text title(font, "Sorted Table", 20);
    title.setStyle(Text::Bold | Text::Underlined);
    SetTextPosition(title, width/2, 50);

    // vector of strings: [0] = number, [1] = name, [2] = points, [3] = rebounds, [4] = assists, [5] = playerID, [6] = gameID, [7] = team
    vector<string> entries = {"\n\n", "Name\n\n", "Points\n\n", "Rebounds\n\n", "Assists\n\n", "Player ID\n\n", "Game ID\n\n", "Team\n\n"};
    for (int i = 0; i < 10; i++) {
        entries[0] += to_string(i+1) + "." + "\n\n";
        entries[1] += players[i].playerName + "\n\n";

        string pointsStr = to_string(players[i].points);
        pointsStr = pointsStr.substr(0, pointsStr.find('.') + 3);
        entries[2] += pointsStr + "\n\n";

        string reboundsStr = to_string(players[i].rebounds);
        reboundsStr = reboundsStr.substr(0, reboundsStr.find('.') + 3);
        entries[3] += reboundsStr + "\n\n";

        string assistsStr = to_string(players[i].assists);
        assistsStr = assistsStr.substr(0, assistsStr.find('.') + 3);
        entries[4] += assistsStr + "\n\n";

        entries[5] += to_string(players[i].playerId) + "\n\n";
        entries[6] += to_string(players[i].gameId) + "\n\n";
        entries[7] += players[i].team + "\n\n";
    }

    vector<int> offsetsFromLeft = {0, 50, 350, 450, 550, 650, 775, 900};
    window.draw(title);
    for (int i = 0; i < entries.size(); i++) {
        sf::String unicodeText = sf::String::fromUtf8(entries[i].begin(), entries[i].end());
        Text column(font, unicodeText, 20);
        column.setStyle(Text::Bold);
        column.setPosition(Vector2f(50 + offsetsFromLeft[i], 100));
        window.draw(column);
    }
}

int main() {
    vector<PlayerPerformance> players = readCSV("../resources/games_details.csv");
    vector<PlayerPerformance> tablePlayers;
    cout << "Loaded " << players.size() << " NBA performances." << endl;

    string rankSelected = "";
    string sortSelected = "";

    // Create window
    unsigned int windowWidth = 800;
    unsigned int windowHeight = 600;

    RenderWindow render_window(VideoMode({windowWidth, windowHeight}), "NBA Performance Rankings", Style::Titlebar | Style::Close);
    RenderWindow tableWindow;
    bool tableOpen = false;

    Color backgroundColor(5, 50, 150);
    Font font;
    if (!font.openFromFile("../resources/font.ttf")) return -1;

    // Text display
    Text title(font, "NBA Performance Rankings", 24);
    title.setStyle(Text::Bold | Text::Underlined);
    SetTextPosition(title, windowWidth/2, 100);

    Text rankPrompt(font, "What would you like to rank by?", 20);
    rankPrompt.setStyle(Text::Bold);
    SetTextPosition(rankPrompt, windowWidth/2, 150);

    Text sortPrompt(font, "What would you like to sort by?", 20);
    sortPrompt.setStyle(Text::Bold);
    SetTextPosition(sortPrompt, windowWidth/2, 300);

    // Create buttons
    Vector2f buttonSize = Vector2f(100, 50);
    Vector2f centerPos = Vector2f(windowWidth/2 - buttonSize.x/2, windowHeight/2 - buttonSize.y/2);

    // Map for changing color
    unordered_map<string, RectangleShape*> buttons;

    RectangleShape pointsButton;
    Text pointsText(font, "Points", 20);
    FormatButtonAndText(pointsButton, pointsText, Vector2f(centerPos.x - 150, 200), buttonSize);
    buttons["points"] = &pointsButton;

    RectangleShape reboundsButton;
    Text reboundsText(font, "Rebounds", 20);
    FormatButtonAndText(reboundsButton, reboundsText, Vector2f(centerPos.x, 200), buttonSize);
    buttons["rebounds"] = &reboundsButton;

    RectangleShape assistsButton;
    Text assistsText(font, "Assists", 20);
    FormatButtonAndText(assistsButton, assistsText, Vector2f(centerPos.x + 150, 200), buttonSize);
    buttons["assists"] = &assistsButton;

    RectangleShape heapButton;
    Text heapText(font, "Heap", 20);
    FormatButtonAndText(heapButton, heapText, Vector2f(centerPos.x - 75, 350), buttonSize);
    buttons["heap"] = &heapButton;

    RectangleShape mergeButton;
    Text mergeText(font, "Merge", 20);
    FormatButtonAndText(mergeButton, mergeText, Vector2f(centerPos.x + 75, 350), buttonSize);
    buttons["merge"] = &mergeButton;

    RectangleShape sortButton;
    Text sortText(font, "Sort", 20);
    FormatButtonAndText(sortButton, sortText, Vector2f(centerPos.x, 450), buttonSize);
    buttons["sort"] = &sortButton;

    Text timingText(font, "Choose a statistic and an algorithm, then click Sort.", 18);
    SetTextPosition(timingText, windowWidth / 2.0f, 545.0f);

    while (render_window.isOpen()) {
        while (const optional event = render_window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                render_window.close();
            }
            if (const auto* mousePress = event->getIf<Event::MouseButtonPressed>()) {
                if (mousePress->button == Mouse::Button::Left) {
                    // press points button
                    if (pointsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(render_window)))) {
                        // color previously selected button black
                        if (!rankSelected.empty()) {
                            buttons[rankSelected]->setFillColor(Color::Black);
                        }
                        rankSelected = "points";
                        buttons[rankSelected]->setFillColor(Color(200, 120, 0));
                    }
                    // press rebounds button
                    if (reboundsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(render_window)))) {
                        if (!rankSelected.empty()) {
                            buttons[rankSelected]->setFillColor(Color::Black);
                        }
                        rankSelected = "rebounds";
                        buttons[rankSelected]->setFillColor(Color(200, 120, 0));
                    }
                    // press assists button
                    if (assistsButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(render_window)))) {
                        if (!rankSelected.empty()) {
                            buttons[rankSelected]->setFillColor(Color::Black);
                        }
                        rankSelected = "assists";
                        buttons[rankSelected]->setFillColor(Color(200, 120, 0));
                    }
                    if (heapButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(render_window)))) {
                        if (!sortSelected.empty()) {
                            buttons[sortSelected]->setFillColor(Color::Black);
                        }
                        sortSelected = "heap";
                        buttons[sortSelected]->setFillColor(Color(200, 120, 0));
                    }
                    if (mergeButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(Mouse::getPosition(render_window)))) {
                        if (!sortSelected.empty()) {
                            buttons[sortSelected]->setFillColor(Color::Black);
                        }
                        sortSelected = "merge";
                        buttons[sortSelected]->setFillColor(Color(200, 120, 0));
                    }
                    if (sortButton.getGlobalBounds().contains(
                            static_cast<sf::Vector2f>(Mouse::getPosition(render_window)))) {
                        std::string message;

                        if (rankSelected.empty() || sortSelected.empty()) {
                            message = "Choose a statistic and an algorithm first.";
                        } else if (players.empty()) {
                            message = "No player records were loaded. Check the CSV path.";
                        } else {
                            std::string stat = "PTS";
                            if (rankSelected == "rebounds") {
                                stat = "REB";
                            } else if (rankSelected == "assists") {
                                stat = "AST";
                            }
                            // Each run starts with the same original records.
                            auto rankedPlayers = players;
                            const bool useMergeSort = sortSelected == "merge";

                            using Clock = std::chrono::steady_clock;
                            const auto start = Clock::now();

                            if (useMergeSort) {
                                MergeSort::mergeSort(rankedPlayers, stat);
                            } else {
                                HeapSort::heapSort(rankedPlayers, stat);
                            }

                            const auto end = Clock::now();
                            const double elapsedMs =
                                std::chrono::duration<double, std::milli>(end - start).count();

                            std::ostringstream output;
                            output << (useMergeSort ? "Merge Sort" : "Heap Sort")
                                << " by " << rankSelected << ": "
                                << std::fixed << std::setprecision(2) << elapsedMs
                                << " ms (" << rankedPlayers.size() << " records)";
                            message = output.str();
                            tablePlayers.swap(rankedPlayers);
                            tableWindow.create(VideoMode({1050, windowHeight-100}), "Table", Style::Titlebar | Style::Close);
                            tableOpen = true;
                        }

                        timingText.setString(message);
                        SetTextPosition(timingText, windowWidth / 2.0f, 545.0f);
                        std::cout << message << '\n';
                    }
                }
            }
        }
        if (tableOpen && tableWindow.isOpen()) {
            while (const optional lbEvent = tableWindow.pollEvent()) {
                if (lbEvent->is<Event::Closed>()) {
                    tableWindow.close();
                    tableOpen = false;
                }
            }
        }

        // Draw elements
        render_window.clear(backgroundColor);
        render_window.draw(title);
        render_window.draw(rankPrompt);
        render_window.draw(sortPrompt);

        render_window.draw(pointsButton);
        render_window.draw(pointsText);
        render_window.draw(reboundsButton);
        render_window.draw(reboundsText);
        render_window.draw(assistsButton);
        render_window.draw(assistsText);

        render_window.draw(heapButton);
        render_window.draw(heapText);
        render_window.draw(mergeButton);
        render_window.draw(mergeText);

        render_window.draw(sortButton);
        render_window.draw(sortText);

        render_window.draw(timingText);
        render_window.display();

        if (tableOpen && tableWindow.isOpen()) {
            tableWindow.clear(backgroundColor);
            DrawTable(tableWindow, font, SetTextPosition, tablePlayers);
            tableWindow.display();
        }
    }

    return 0;
}
