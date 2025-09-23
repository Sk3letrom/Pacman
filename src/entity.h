#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include <SFML/Graphics.hpp>

class Entity{

    public:
        Entity(float x, float y, float size, int r, int g, int b);
    
        float positionX;
        float positionY;
        float shapeSize;
        int r, g ,b;

        std::vector<int> colorVector(int r,int g,int b);

};

class Shadows{
    public:
        Shadows(float x, float y, bool UP, bool DOWN, bool LEFT, bool RIGHT, int ID);

        bool UP, DOWN, LEFT, RIGHT;

        float size = 10.f;

        int getId() const;

        const sf::CircleShape& getShape() const;
        const sf::FloatRect getBoundBox() const;
    
        private:
            sf::CircleShape shape;
            sf::FloatRect shadowBox;
            int ID;
            
};


#endif