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

        vertical.setFillColor(sf::Color::Red);

        sf::RectangleShape vertical2;
        vertical2.setSize(sf::Vector2f(40.f, 120.f));

        vertical2.setFillColor(sf::Color::Red);

        this->x = 0;
        this->y = 0;

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

Possibility::Possibility(){
    // L_SHAPE
    L_SHAPES.push_back({ // 0°
        {1, 0},
        {1, 0},
        {1, 1}
    });
    L_SHAPES.push_back({ // 90°
        {1, 1, 1},
        {1, 0, 0}
    });
    L_SHAPES.push_back({ // 180°
        {1, 1},
        {0, 1},
        {0, 1}
    });
    L_SHAPES.push_back({ // 270°
        {0, 0, 1},
        {1, 1, 1}
    });
    
    // T_SHAPES
    T_SHAPES.push_back({ // 0°
        {1, 1, 1},
        {0, 1, 0}
    });
    T_SHAPES.push_back({ // 90°
        {0, 1},
        {1, 1},
        {0, 1}
    });
    T_SHAPES.push_back({ // 180°
        {0, 1, 0},
        {1, 1, 1}
    });
    T_SHAPES.push_back({ // 270°
        {1, 0},
        {1, 1},
        {1, 0}
    });

    I_SHAPES.push_back({ // 0°
        {1},
        {1},
        {1},
        {1}
    });
    I_SHAPES.push_back({ // 90°
        {1, 1, 1, 1}
    });
    I_SHAPES.push_back({ // 180°
        {1},
        {1},
        {1},
        {1}
    });
    I_SHAPES.push_back({ // 270°
        {1, 1, 1, 1}
    });

    // PLUS_SHAPES
    Pattern plusPattern = { // 0°, 90°, 180°, 270°
        {0, 1, 0},
        {1, 1, 1},
        {0, 1, 0}
    };
    PLUS_SHAPES.push_back(plusPattern);
    PLUS_SHAPES.push_back(plusPattern);
    PLUS_SHAPES.push_back(plusPattern);
    PLUS_SHAPES.push_back(plusPattern);
}

const std::vector<Pattern>& Possibility::getL_SHAPES() const {
    return this->L_SHAPES;
}

const std::vector<Pattern>& Possibility::getT_SHAPES() const {
    return this->T_SHAPES;
}

const std::vector<Pattern>& Possibility::getPlus_SHAPES() const {
    return this->PLUS_SHAPES;
}

const std::vector<Pattern>& Possibility::getI_SHAPES() const {
    return this->I_SHAPES;
}