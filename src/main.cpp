#include <SFML/Graphics.hpp>
#include "entity.h"
#include "objects.h"
#include "sensor.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

int main(){

    sf::RenderWindow window(sf::VideoMode({800, 800}), "My cute window");

    window.setFramerateLimit(60);

    Entity player(380.f, 670.f, 20.f, 237, 234, 42);
    Entity boundbox(380.f, 670.f, 5.f, 237, 234, 42);
    
    //========== MOTHERS WALLS ==============
    std::vector<Object> allWalls;
    allWalls.emplace_back(WallType::L_SHAPE).setPosition(100.f, 500.f);
    allWalls.emplace_back(WallType::T_SHAPE).setPosition(300.f, 500.f);
    allWalls.emplace_back(WallType::I_SHAPE).setPosition(500.f, 500.f);
    allWalls.emplace_back(WallType::PLUS_SHAPE).setPosition(700.f, 500.f);

    std::vector<sf::FloatRect> wallColisionBoxes;
    /*
    //WALL COLISION BOX
    for (auto& WCB : allWalls){
        for(auto& shape : WCB.getShapes()){
              wallColisionBoxes.push_back(shape.getGlobalBounds());
        }
    }
    */

    //===============================

    //============ SCANER ====================================
    sf::RectangleShape scaner({160.f, 160.f});
    scaner.setPosition({0.f, 0.f});
    scaner.setFillColor(sf::Color::Red);
    sf::FloatRect scanerBox = scaner.getGlobalBounds();
    
    sf::Vector2f size = {40.f, 40.f};
    std::vector<Sensor> sensors;
    const int sensorsPerRow = 4;
    const int sensorsPerCol = 4;
    const float spacing = 40.f;

    for (int y = 0; y < sensorsPerCol; ++y) {
        for (int x = 0; x < sensorsPerRow; ++x) {

            Sensor& newSensor = sensors.emplace_back(size);        
            
            newSensor.setPosition({x * spacing, y * spacing});
    
        }
    }
    //=========================================================

    
    //move direction
    int moveDirection = 0;  
    bool comeBack;
    bool U = false, D = false, L = false, R = false;
    
    //player
    sf::CircleShape pacman(player.shapeSize);
    pacman.setFillColor(sf::Color(player.r, player.g, player.b));
    pacman.setPosition({player.positionX, player.positionY});
    //player posission
    sf::Vector2f currentPosition;
    currentPosition.x = player.positionX;
    currentPosition.y = player.positionY;

    //playerBoundBox
    sf::CircleShape playerBoundBox(boundbox.shapeSize);
    playerBoundBox.setFillColor(sf::Color::Green);
    playerBoundBox.setPosition({player.positionX, player.positionY});
    //playerBoundBox position
    sf::Vector2f currentPositionBOX;
    currentPositionBOX.x = player.positionX;
    currentPositionBOX.y = player.positionY;

    //move permission colisor

    std::vector<Shadows> allShadows;
    allShadows.push_back(Shadows(400.f, 690.f, false, false, true, true, 0));
    allShadows.push_back(Shadows(45.f, 690.f, true, false, false, true, 1));
    allShadows.push_back(Shadows(45.f, 624.f, false, true, false, true, 2));
    allShadows.push_back(Shadows(173.f, 624.f, true, false, true, false, 3));
    allShadows.push_back(Shadows(177.f, 500.f, true, true, false, true, 4));
    allShadows.push_back(Shadows(177.f, 437.f, true, true, true, false, 5));
    allShadows.push_back(Shadows(179.f, 250.f, true, true, true, true, 6));
    allShadows.push_back(Shadows(44.f, 246.f, true, false, false, true, 7));
    allShadows.push_back(Shadows(44.f, 100.f, false, true, false, true, 8));
    allShadows.push_back(Shadows(312.f, 100.f, false, true, true, false, 9));
    allShadows.push_back(Shadows(320.f, 250.f, true, false, true, true, 10));
    allShadows.push_back(Shadows(250.f, 256.f, false, true, true, true, 11));
    allShadows.push_back(Shadows(250.f, 360.f, true, false, false, true, 12));
    allShadows.push_back(Shadows(310.f, 365.f, false, true, true, false, 13));
    allShadows.push_back(Shadows(317.f, 432.f, true, false, true, true, 14));
    allShadows.push_back(Shadows(245.f, 440.f, false, true, false, true, 15));
    allShadows.push_back(Shadows(245.f, 500.f, true, true, true, false, 16));
    allShadows.push_back(Shadows(250.f, 628.f, true, false, false, true, 17));
    allShadows.push_back(Shadows(312.f, 100.f, false, true, true, false, 9));
    
    //colision box vector
    std::vector<sf::FloatRect> colisionBoxes;

    //wall colision box
    
    bool loading = false;
    while (window.isOpen()){

        while (const std::optional event = window.pollEvent()){

            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        //std::cout << sf::Mouse::getPosition(window).x << "," << sf::Mouse::getPosition(window).y << std::endl;
        //move permission
        bool permUP = false, permDOWN = false, permLEFT = false, permRIGHT = false;

        //player bounding box
        sf::FloatRect boundingBox({currentPosition.x + 20, currentPosition.y + 20}, {5.f, 5.f});
        
        
        //===================================== SCAN ACTION! =======================================
        unsigned seed = time(0);
        srand(seed);
        if(!loading){
            // Comparison
            size_t type = rand()%2;
        
            std::vector<std::vector<bool>> check;
            
            Possibility typeL, typeT;
            
            switch(type){
                case 0:
                    check = typeL.getL_SHAPE(); break;
                case 1:
                    check = typeT.getT_SHAPE(); break;
            }

            int sensorI = 0;
            for(auto& sens : sensors){

                bool sensor = sens.scan(wallColisionBoxes);
                sens.comparison(sensor, sensorI);
                sensorI++;
                std::cout << "sensor " << sensorI << ": " << sensor << std::endl;
            }
            std::optional<sf::Vector2i> allocatePiece = sensors[0].checkFitAt(check);
            if(allocatePiece){
                loading = false;
                sf::Vector2i coords = allocatePiece.value();
                std::cout << coords.x << ", " << coords.y << std::endl;
                sf::Vector2f krummbel = sensors[(coords.x * 4) + coords.y].getPosition();

                //====== WALLS CREATION ======
                switch(type){
                    case 0:
                        allWalls.emplace_back(WallType::L_SHAPE).setPosition(krummbel.x, krummbel.y);
                        std::cout << std::endl <<"criou um L" << std::endl; break;
                    case 1:
                        allWalls.emplace_back(WallType::T_SHAPE).setPosition(krummbel.x + 40, krummbel.y);
                        std::cout << std::endl <<"criou um T" << std::endl; break;
                }
                
                for (auto& WCB : allWalls){
                    for(auto& shape : WCB.getShapes()){
                        wallColisionBoxes.push_back(shape.getGlobalBounds());
                    }
                }
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            else {loading = true;}    
        }
        //=========================================================================================


        //COLISION BOXES
        comeBack = true;
        for(auto& SB : allShadows){
            sf::FloatRect shadowBox = SB.getBoundBox();
    
            if(boundingBox.findIntersection(shadowBox)){
                comeBack = false;
                if(SB.LEFT) {permLEFT = true;}
                if(SB.RIGHT) {permRIGHT = true;}
                if(SB.UP) {permUP = true;}
                if(SB.DOWN) {permDOWN = true;}
            }
        }
        
        //
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            L = true;
            R = false;
            U = false;
            D = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            L = false;
            R = true;
            U = false;
            D = false;
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
            L = false;
            R = false;
            U = true;
            D = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
            L = false;
            R = false;
            U = false;
            D = true;
        }
        //
        
        if (L && permLEFT) {moveDirection = 1;}
        if (R && permRIGHT) {moveDirection = 2;}
        if (U && permUP) {moveDirection = 3;}
        if (D && permDOWN) {moveDirection = 4;}

        if(moveDirection == 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {moveDirection = 2;}
        if(moveDirection == 2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {moveDirection = 1;}
        if(moveDirection == 3 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {moveDirection = 4;}
        if(moveDirection == 4 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {moveDirection = 3;}

        switch(moveDirection){
            case 1:
                if(currentPosition.x < 0.f){
                    pacman.move({0.f, 0.f});
                    moveDirection = 0;
                    break;
                }else{
                    pacman.move({-2.f, 0.f});
                    currentPosition = pacman.getPosition();
                    break;
                }
            case 2:
                if(currentPosition.x > 700.f){
                    pacman.move({0.f, 0.f});
                    moveDirection = 0;
                    break;
                }else{
                    pacman.move({2.f, 0.f});
                    currentPosition = pacman.getPosition();
                    break;
                }
            case 3:
                if(currentPosition.y < 0.f){
                    pacman.move({0.f, 0.f});
                    moveDirection = 0;
                    break;
                }else{
                    pacman.move({0.f, -2.f});
                    currentPosition = pacman.getPosition();
                    break;
                    
                }
            case 4:
                if(currentPosition.y > 700.f){
                    pacman.move({0.f, 0.f});
                    moveDirection = 0;
                    break;
                }else{
                    pacman.move({0.f, 2.f});
                    currentPosition = pacman.getPosition();
                    break;
                }
        }

        sf::RenderTexture renderTexture({500,500});
        
        window.clear(sf::Color::Black);

        window.draw(scaner);
        
        for(auto& sensor : sensors){
            const auto& sensorForDraw = sensor.getShapes();
            for(const auto& sfd : sensorForDraw){
                window.draw(sfd);
            }
        }

        window.draw(pacman);

        for(const auto& s : allShadows){
            window.draw(s.getShape());
        }
        
        for(const auto& wall : allWalls){
            const auto& wallForDraw = wall.getShapes();

            for(const auto& wfd : wallForDraw){
                window.draw(wfd);
            }
        }
        

        window.display();
        

    }


}