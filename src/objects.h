#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <SFML/Graphics.hpp>

enum class WallType{

    L_SHAPE,
    T_SHAPE,
    PLUS_SHAPE,
    I_SHAPE

};

class Object{
    
    public:
        Object(WallType type);

        const std::vector<sf::RectangleShape>& getShapes() const;

        void setPosition(const float& offsetX, const float& offsetY);
        void setRotation(const sf::Angle& angle);

        std::vector<sf::Vector2f> getPosition() const;

        float x = 0;
        float y = 0;

        float tempX;
        float tempY;
    
    private:
        std::vector<sf::RectangleShape> shapes;
        WallType Type;


};

class Possibility{

    public:
        std::vector<std::vector<bool>>& getL_SHAPE();
        std::vector<std::vector<bool>>& getT_SHAPE(); 
    private:

        // L_SHAPE
        std::vector<std::vector<bool>> L_SHAPE{
            {true, false},
            {true, false},
            {true, true}
        };
       
        // T_SHAPE
        std::vector<std::vector<bool>> T_SHAPE{
            {true, true, true},
            {false, true, false},
            {false, true, false}
        };
        
        // PLUS_SHAPE
        std::vector<std::vector<bool>> PLUS_SHAPE{  // VERIFICAR PRIMEIRO QUAIS ENCAIXAM E DPS MANDAR AS OPÇÕES!
            {false, true, false},
            {true, true, true},
            {false, true, false}
        };

        // I_SHAPE
        std::vector<std::vector<bool>> I_SHAPE{
            {true},
            {true},
            {true}
        };

};


#endif