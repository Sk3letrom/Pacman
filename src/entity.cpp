#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"

Entity::Entity(float x, float y, float size, int r, int g, int b){

    this->positionX = x;
    this->positionY = y;
    
    this->shapeSize = size;
    this->r = r;
    this->g = g;
    this->b = b;
}

std::vector<int> Entity::colorVector(int r, int g, int b){
    std::vector<int> colorArray = {r,g,b};
    return colorArray;
}


Shadows::Shadows(float x, float y, bool UP, bool DOWN, bool LEFT, bool RIGHT, int ID){

    this->UP = UP;
    this->DOWN = DOWN;
    this->LEFT = LEFT;
    this->RIGHT = RIGHT;
    this->ID = ID;

    this->shape.setRadius(5.f);
    this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition({x, y});
}

const sf::CircleShape& Shadows::getShape() const {
    return this->shape;
}

int Shadows::getId() const {
    return this->ID;
}

const sf::FloatRect Shadows::getBoundBox() const{
    return this->shape.getGlobalBounds();
}

