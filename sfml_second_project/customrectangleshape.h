#ifndef CUSTOMRECTANGLESHAPE_H
#define CUSTOMRECTANGLESHAPE_H
#include <SFML/Graphics.hpp>


class CustomRectangleShape : public sf::RectangleShape
{
     public:
        CustomRectangleShape(const sf::Vector2f &size,sf::Vector2f position): sf::RectangleShape(size){
    setPosition(position);
}
int read_speed_x(){
    return speed_x_;
}
private:
int speed_x_=0;
int speed_y_=0;
bool is_selected=false;
};














#endif // CUSTOMRECTANGLESHAPE_H
