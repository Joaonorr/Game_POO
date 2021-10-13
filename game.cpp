#include <iostream>
#include <SFML/Graphics.hpp>


int main(){

    // Laço para manter a janela aberta, Recebe 2 parâmetros: modo de vídeo e nome da janela.
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    // Enquanto a janela estiver aberta, limpe a tela e mostre o que houver nela.
    while(window.isOpen()){
        sf::Event event;
        //Módulo de tratamento de eventos
        while(window.pollEvent(event) ){ 
            if( event.type == sf::Event::Closed){
                window.close();
            }            
        }

        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(300, 300);
        shape.setOutlineColor(sf::Color(21, 43, 200));

        //módulo de atualizações e pintura
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}