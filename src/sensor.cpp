#include "sensor.h"
#include "objects.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

bool Sensor::s[16];

Sensor::Sensor(sf::Vector2f size){

    this->size = size;

    sf::RectangleShape sensor(size);
    sensor.setFillColor(sf::Color::Green);
    sf::FloatRect sensorBox = sensor.getGlobalBounds();

    shapes.push_back(sensor);
    this->sensorBox = sensorBox;



}

const std::vector<sf::RectangleShape>& Sensor::getShapes() const{
    return this->shapes;
}

const sf::FloatRect& Sensor::getSensorBox() const{
    return this->sensorBox;
}

void Sensor::setPosition(const sf::Vector2f offset){

    this->shapes[0].setPosition(offset);

    // recalculate the sensorBox
    this->sensorBox = this->shapes[0].getGlobalBounds(); 

}

sf::Vector2f Sensor::getPosition() const {
    return this->shapes[0].getPosition();
}

bool Sensor::scan(const std::vector<sf::FloatRect>& wallColisionBoxes) const {

    for(auto& colision : wallColisionBoxes){

        if(this->sensorBox.findIntersection(colision)){
            
            return false;
        }
        
        
    }
    return true;
}

void Sensor::comparison(bool active, int sensorI){
    this->s[sensorI] = active;  
}

std::optional<sf::Vector2i> Sensor::checkFitAt(const std::vector<std::vector<bool>> pattern) {

    std::vector<std::vector<bool>> grid = {
        { Sensor::s[0],  Sensor::s[1],  Sensor::s[2],  Sensor::s[3]  },
        { Sensor::s[4],  Sensor::s[5],  Sensor::s[6],  Sensor::s[7]  },
        { Sensor::s[8],  Sensor::s[9],  Sensor::s[10], Sensor::s[11] },
        { Sensor::s[12], Sensor::s[13], Sensor::s[14], Sensor::s[15] }
    };

    int n = (int)grid.size();
    int m = (int)grid[0].size();
    int pr = (int)pattern.size();
    if (pr == 0) return std::nullopt;
    int pc = (int)pattern[0].size();

    for (int i = 0; i <= n - pr; ++i) {
        for (int j = 0; j <= m - pc; ++j) {
            bool match = true;

            for (int r = 0; r < pr && match; ++r) {
                for (int c = 0; c < pc; ++c) {
                    if (pattern[r][c] == true) {
                        if (grid[i + r][j + c] == false) {
                            match = false;
                            break;
                        }
                    }
                }
            }

            if (match) {
                return sf::Vector2i{i, j};
            }
        }
    }

    return std::nullopt;
}
