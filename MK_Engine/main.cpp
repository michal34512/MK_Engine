#include <SFML/Graphics.hpp>
#include "Physic.h"

int main(int argc, char *argv[])
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "Engine demo!");
    window.setFramerateLimit(60);
    mk::Physic::setWindow(window); // Setting up window handle for quick and easy access

        //Creating object
    mk::Object floor;
        //Adding component responsible for displaying convex shape
        //Note that all verticies have to be declared in clockwise order
    floor.addComponent<mk::Convex>().setVertices({sf::Vector2f(0,0), sf::Vector2f(1000,0), sf::Vector2f(1000,20), sf::Vector2f(0,20)}); 
        //Adding component responsible for movement
    floor.addComponent<mk::Rigidbody>();
    floor.getComponent<mk::Rigidbody>()->setMass(0); //Locking linear motion by setting mass to 0
    floor.getComponent<mk::Rigidbody>()->setInertia(0); //Locking rotational motion by setting inertia to 0
    floor.getComponent<mk::Rigidbody>()->restitution = 0.8f; //setting coefficient of restitution
        //Adding component responsible for collisions
    floor.addComponent<mk::Convex_Collider>();
        //Setting object position (default object origin is set at it's center of mass)
    floor.getComponent<mk::Convex>()->setPosition(sf::Vector2f(500,480));
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed )
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mk::Object *obj = new mk::Object;
                    obj->addComponent<mk::Convex>().setVertices({ sf::Vector2f(0,0), sf::Vector2f(100,0), sf::Vector2f(100,100), sf::Vector2f(0,100) });
                    obj->addComponent<mk::Rigidbody>().setGravity(new sf::Vector2f(0, 400));
                    obj->getComponent<mk::Rigidbody>()->restitution = 0.8f;
                    obj->addComponent<mk::Convex_Collider>();
                    obj->getComponent<mk::Convex>()->setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
                }else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    mk::Object* obj = new mk::Object;
                    obj->addComponent<mk::Circle>().setRadius(50);
                    obj->addComponent<mk::Rigidbody>().setGravity(new sf::Vector2f(0, 400));
                    obj->getComponent<mk::Rigidbody>()->restitution = 0.8f;
                    obj->addComponent<mk::Circle_Collider>();
                    obj->getComponent<mk::Circle>()->setPosition((sf::Vector2f)sf::Mouse::getPosition(window));
                }
            }
        }

        window.clear();
        mk::Physic::Update(); //Update physic engine
        window.display();
    }
    return 0;
}