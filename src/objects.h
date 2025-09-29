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

class Object : public sf::Drawable, public sf::Transformable {
public:
    Object(WallType type);

    const std::vector<sf::RectangleShape>& getShapes() const;

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    std::vector<sf::RectangleShape> m_shapes; 
    
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