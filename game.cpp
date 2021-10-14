#include <iostream>
#include <SFML/Graphics.hpp>

void setSize(sf::Sprite& sprite, int width, int height) {
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

struct Entity{
    int x {0}; //atributos
    int y {0};
    int step {0};
    sf::Sprite sprite;

    Entity(int x, int y, int step, sf::Texture& texture ):
        x {x}, y {y}, step {step}, sprite(texture) {
    }

    void draw(sf::RenderWindow& window){
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }

};

struct Board {
    int nc {0};
    int nl {0};
    int step {0};
    sf::Sprite sprite;
    sf::RectangleShape rect;
    Board(int nc, int nl, int step, sf::Texture& texture) {
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step);
        this->sprite.setPosition(0, 0);

        this->rect.setSize(sf::Vector2f(step, step));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(0.5);
    }
void draw(sf::RenderWindow& window){
    window.draw(this->sprite);
     for (int i = 0; i < nc; i++) {
            for (int j = 0; j < nl; j++) {
                rect.setPosition(i * step, j * step);
                window.draw(rect);
            }
        }
}

};

void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys) {
    if( key == move_keys[0] && entity.x > 0){
        entity.x--;
    }
    else if( key == move_keys[1] && entity.y > 0){
        entity.y--;
    }
    else if( key == move_keys[2] && entity.y < 4){
        entity.y++;
    }
    else if( key == move_keys[3] && entity.x < 6){
        entity.x++;
    }
}


sf::Texture loadTexture(std::string path) {
    sf::Texture texture;
    if(!texture.loadFromFile(path)){
        std::cout << "ERROR LOADING TEXTURE" << "\n";
    }

    return texture;
}


int main(){

    // Laço para manter a janela aberta, Recebe 2 parâmetros: modo de vídeo e nome da janela.
    sf::Texture rocket_tex{ loadTexture("rocket.png")};
    sf::Texture asteroid_tex{ loadTexture("asteroid.png")};
    sf::Texture space_tex{ loadTexture("space.jpg")};

    const int STEP {100};

    Entity rocket( 0, 0, STEP, rocket_tex);
    Entity asteroid( 6, 4, STEP, asteroid_tex);
    Board board(7, 5, STEP, space_tex);

    sf::RenderWindow window(sf::VideoMode(board.nc * STEP, board.nl * STEP), "SFML works!");

    // Enquanto a janela estiver aberta, limpe a tela e mostre o que houver nela.
    while(window.isOpen()){
        sf::Event event;
        //Módulo de tratamento de eventos
        while(window.pollEvent(event) ){ 
            if( event.type == sf::Event::Closed){
                window.close();
            } else if(event.type == sf::Event::KeyPressed){
                moveEntity(event.key.code, rocket, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D});
                moveEntity(event.key.code, asteroid, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Right});
            }  
            if(rocket.x == asteroid.x && rocket.y == asteroid.y){
                window.close();
            }
           

            

        }

        //módulo de atualizações e pintura
        window.clear();
        board.draw(window);
        rocket.draw(window);
        asteroid.draw(window);
        window.display();
    }

    return 0;
}