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
using Pattern = std::vector<std::vector<bool>>;
class Possibility{

    public:
        Possibility();

        const std::vector<Pattern>& getL_SHAPES() const;
        const std::vector<Pattern>& getT_SHAPES() const;
        const std::vector<Pattern>& getPlus_SHAPES() const;
        const std::vector<Pattern>& getI_SHAPES() const;

    private:

        // L_SHAPE
        std::vector<Pattern> L_SHAPES;
        std::vector<Pattern> T_SHAPES;
        std::vector<Pattern> PLUS_SHAPES;
        std::vector<Pattern> I_SHAPES;

};


#endif