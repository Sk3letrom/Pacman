#include "objects.h"
#include <vector>
#include <SFML/Graphics.hpp>

Object::Object(WallType type) {

    if (type == WallType::L_SHAPE) {

        this->Type = type;
        //vertical rectangle
        sf::RectangleShape vertical;
        vertical.setSize(sf::Vector2f(40.f, 120.f));
        
        vertical.setFillColor(sf::Color::Cyan);
        
        //horizontal rectangle
        sf::RectangleShape horizontal;
        horizontal.setSize(sf::Vector2f(80.f, 40.f));
        horizontal.setPosition({0.f, 80.f});
        
        this->x = 0;
        this->y = 80;

        horizontal.setFillColor(sf::Color::Cyan);

        shapes.push_back(vertical);
        shapes.push_back(horizontal);

    }

    if(type == WallType::T_SHAPE){
        this->Type = type;
        //vertical rectangle
        sf::RectangleShape vertical;
        vertical.setSize(sf::Vector2f(40.f, 120.f));

        vertical.setFillColor(sf::Color::White);

        //horizontal rectangle
        sf::RectangleShape horizontal;
        horizontal.setSize(sf::Vector2f(120.f, 40.f));
        horizontal.setPosition({-40.f, 0.f});

        this->x = -40;
        this->y = 0;

        horizontal.setFillColor(sf::Color::White);

        shapes.push_back(vertical);
        shapes.push_back(horizontal);
    }

    if(type == WallType::I_SHAPE){
        this->Type = type;
        //2 rectangles so as not to break the logic
        //vertical rectangle
        sf::RectangleShape vertical;
        vertical.setSize(sf::Vector2f(40.f, 120.f));

        vertical.setFillColor(sf::Color::Green);

        sf::RectangleShape vertical2;
        vertical.setSize(sf::Vector2f(40.f, 120.f));

        vertical.setFillColor(sf::Color::Green);

        shapes.push_back(vertical);
        shapes.push_back(vertical2);

    }

    if(type == WallType::PLUS_SHAPE){
        this->Type = type;
        //vertical rectangle
        sf::RectangleShape vertical;
        vertical.setSize(sf::Vector2f(40.f, 120.f));

        vertical.setFillColor(sf::Color::Magenta);

        //horizontal rectangle
        sf::RectangleShape horizontal;
        horizontal.setSize(sf::Vector2f(120.f, 40.f));
        horizontal.setPosition({-40.f, 40.f});

        this->x = -40;
        this->y = 40;

        horizontal.setFillColor(sf::Color::Magenta);

        shapes.push_back(vertical);
        shapes.push_back(horizontal);
    }
    
}

const std::vector<sf::RectangleShape>& Object::getShapes() const {
    return this->shapes;
}

void Object::setPosition(const float& offsetX, const float& offsetY){
    this->tempX = offsetX;
    this->tempY = offsetY;
    
    for(int i = 0; i < this->shapes.size(); i++){
        if(i % 2 == 1){
            this->shapes[i].setPosition({offsetX + this->x, offsetY + this->y});
        }
        else{
            this->shapes[i].setPosition({offsetX, offsetY});
        }
    }
}

void Object::setRotation(const sf::Angle& angle){
    for(auto& shape : this->shapes){

        shape.setPosition({this->tempX, this->tempY});       

        shape.setRotation(angle);

        for(int i = 0; i < this->shapes.size(); i++){
            if(i % 2 == 1){
                if(this->Type == WallType::L_SHAPE){
                    if(angle == sf::degrees(90)){
                        this->shapes[i].setPosition({this->tempX + -this->y, this->tempY + this->x});
                    }
                    if(angle == sf::degrees(180)){
                        this->shapes[i].setPosition({this->tempX + this->x, this->tempY + -this->y});
                    }
                    if(angle == sf::degrees(270)){
                        this->shapes[i].setPosition({this->tempX + this->y, this->tempY + this->x});
                    }
                }
                if(this->Type == WallType::T_SHAPE){
                    if(angle == sf::degrees(90)){
                        this->shapes[i].setPosition({this->tempX + this->y, this->tempY + this->x});
                    }
                    if(angle == sf::degrees(180)){
                        this->shapes[i].setPosition({this->tempX + -this->x, this->tempY + this->y});
                    }
                    if(angle == sf::degrees(270)){
                        this->shapes[i].setPosition({this->tempX + this->y, this->tempY + -this->x});
                    }
                }
            }
        }

    }
}

std::vector<sf::Vector2f> Object::getPosition() const{
    std::vector<sf::Vector2f> positions;
    for(auto& shape : this->shapes){
        positions.push_back(shape.getPosition());
    }
    return positions;
}

std::vector<std::vector<bool>>& Possibility::getL_SHAPE(){
    return this->L_SHAPE;
}

std::vector<std::vector<bool>>& Possibility::getT_SHAPE(){
    return this->T_SHAPE;
}