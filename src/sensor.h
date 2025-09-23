#ifndef SENSOR_H
#define SENSOR_H
#include <SFML/Graphics.hpp>
#include <vector>

class Sensor{

    public:
        Sensor(sf::Vector2f size);

        const std::vector<sf::RectangleShape>& getShapes() const;
        const sf::FloatRect& getSensorBox() const;

        void setPosition(const sf::Vector2f offset);
        sf::Vector2f getPosition() const;

        void comparison(bool active, int sensorI);
       
        std::optional<sf::Vector2i> checkFitAt(std::vector<std::vector<bool>> pattern);

        bool scan(const std::vector<sf::FloatRect>& wallColisionBoxes) const;

        sf::Vector2f size;

    private:
        std::vector<sf::RectangleShape> shapes;
        sf::FloatRect sensorBox;

        static bool s[16];   

};





#endif