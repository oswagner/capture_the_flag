//
//  main.cpp
//  Capture_the_Flag
// Renata Soria e Wagner Santos
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Player.h"

using namespace std;

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"

class Player : public sf::CircleShape {
    
public:
    // construtor
    Player(sf::Color color, float x_inicial, float i_inicial, float radius = 30): sf::CircleShape(radius) {
        setFillColor(color);
        setPosition(x_inicial, i_inicial);
    }
    
    // colisão entre os players
    bool isColiding(const Player& other) const {
        sf::FloatRect self = getGlobalBounds();
        return self.intersects(other.getGlobalBounds());
    }
    
    // teclas de movimentação de cada player
    void setKeys(sf::Keyboard::Key upkey, sf::Keyboard::Key downkey, sf::Keyboard::Key leftkey, sf::Keyboard::Key rightkey) {
        key_up = upkey;
        key_down = downkey;
        key_left = leftkey;
        key_right = rightkey;
    }
    // ultima direção que o player se movimentou
    sf::Vector2<float> lastDirection() const {
        return last_direction;
    }
    
    bool handleKey() {
        if (sf::Keyboard::isKeyPressed(key_up)) {
            move(last_direction = Up);
            
        } else if (sf::Keyboard::isKeyPressed(key_down)) {
            move(last_direction = Down);
        } else if (sf::Keyboard::isKeyPressed(key_left)) {
            move(last_direction = Left);
        } else if (sf::Keyboard::isKeyPressed(key_right)) {
            move(last_direction = Right);
        } else {
            return false;
        }
        return true;
    }
    
private:
    sf::Keyboard::Key key_up, key_down, key_left, key_right;
    sf::Vector2<float> last_direction;
    const sf::Vector2<float> Up{0, -5.0};
    const sf::Vector2<float> Down{0, +5.0};
    const sf::Vector2<float> Left{-5.0, 0};
    const sf::Vector2<float> Right{+5.0, 0};

};


// TODO: Refatorar para mover player para outro arquivo


int main(int, char const**) {
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "Capture the Flag!!");
    window.setFramerateLimit(60);
    
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "background.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    
    unsigned int winX =  window.getSize().x;
    unsigned int winY =  window.getSize().y;
    
    
    Player player_one {sf::Color::Red, 45.0, winY/2.f , 30};
    player_one.setKeys(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
    
    Player player_two {sf::Color::Blue, 1165.0, winY/2.f, 30};
    player_two.setKeys(sf::Keyboard::I, sf::Keyboard::K, sf::Keyboard::J, sf::Keyboard::L);
    
    
    Player flag_player_one {sf::Color::Red, 125.0, winY/2.f , 10};
    Player flag_player_two {sf::Color::Blue, 1135.0, winY/2.f, 10};
    
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        
        // Clear screen
        window.clear();
        
        // Draw the sprite
        window.draw(sprite);
        
        window.draw(player_one);
        window.draw(player_two);
        
        window.draw(flag_player_one);
        window.draw(flag_player_two);
        
        // Update the window
        window.display();
        
        if (player_one.handleKey()) {
            if(player_one.isColiding(flag_player_two)){
                cout << "Player 1 colidiu com Flag Player 2" << endl;
                //TODO: parar o jogo e marcar ponto para o player
            }
            player_one.move(player_one.lastDirection());
        }
        
        if (player_two.handleKey()) {
            if (player_two.isColiding(flag_player_one)) {
                cout << "Player 2 colidiu com Flag Player 1" << endl;
                //TODO: parar o jogo e marcar ponto para o player
            }
            player_two.move(player_two.lastDirection());
        }
        
    }
    
    return EXIT_SUCCESS;
}
