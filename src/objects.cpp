#include "objects.h"
#include <vector>
#include <SFML/Graphics.hpp>

Object::Object(WallType type) {

    if (type == WallType::L_SHAPE) {
        
        // Vertical Shape
        sf::RectangleShape vertical(sf::Vector2f(40.f, 120.f));
        vertical.setPosition({0.f, 0.f});
        vertical.setFillColor(sf::Color::Cyan);
        
        // horizontal Shape
        sf::RectangleShape horizontal(sf::Vector2f(80.f, 40.f));
        horizontal.setPosition({0.f, 80.f});
        horizontal.setFillColor(sf::Color::Cyan);

        m_shapes.push_back(vertical);
        m_shapes.push_back(horizontal);
    }
    else if (type == WallType::T_SHAPE) {
        
        // horizontal shape
        sf::RectangleShape horizontal(sf::Vector2f(120.f, 40.f));
        horizontal.setPosition({0.f, 0.f});
        horizontal.setFillColor(sf::Color::White);

        // vertical shape
        sf::RectangleShape vertical(sf::Vector2f(40.f, 80.f));
        vertical.setPosition({40.f, 40.f});
        vertical.setFillColor(sf::Color::White);

        m_shapes.push_back(horizontal);
        m_shapes.push_back(vertical);
    }
    else if (type == WallType::I_SHAPE) {
        // just one vertical for the I
        sf::RectangleShape vertical(sf::Vector2f(40.f, 120.f));
        vertical.setPosition({0.f, 0.f});
        vertical.setFillColor(sf::Color::Red);

        m_shapes.push_back(vertical);
    }
    else if (type == WallType::PLUS_SHAPE) {
        // vertical shape
        sf::RectangleShape vertical(sf::Vector2f(40.f, 120.f));
        vertical.setPosition({40.f, 0.f});
        vertical.setFillColor(sf::Color::Magenta);
        
        //horizontal shape
        sf::RectangleShape horizontal(sf::Vector2f(120.f, 40.f));
        horizontal.setPosition({0.f, 40.f});
        horizontal.setFillColor(sf::Color::Magenta);

        m_shapes.push_back(vertical);
        m_shapes.push_back(horizontal);
    }
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    states.transform *= getTransform();

    for (const auto& shape : m_shapes) {
        target.draw(shape, states);
    }
}

const std::vector<sf::RectangleShape>& Object::getShapes() const {
    return m_shapes;
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
        {0, 1, 0},
        {0, 1, 0}
    });
    T_SHAPES.push_back({ // 90°
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 1}
    });
    T_SHAPES.push_back({ // 180°
        {0, 1, 0},
        {0, 1, 0},
        {1, 1, 1}
    });
    T_SHAPES.push_back({ // 270°
        {1, 0, 0},
        {1, 1, 1},
        {1, 0, 0}
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