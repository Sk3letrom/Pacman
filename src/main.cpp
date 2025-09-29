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

    unsigned seed = time(0);
    srand(seed);

    Entity player(380.f, 670.f, 20.f, 237, 234, 42);
    Entity boundbox(380.f, 670.f, 5.f, 237, 234, 42);
    
    std::vector<Object> allWalls;

    std::vector<sf::FloatRect> wallColisionBoxes;

    //============ SCANER ====================================
    
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
    bool otherType = false, moveSens;

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
        if(!loading){
            // Comparison
            size_t type = rand()%4;
            int attempts = 0;
        
            std::vector<Pattern> rotatedPatterns;
            WallType shapeTypes[] = {WallType::L_SHAPE, WallType::T_SHAPE, WallType::PLUS_SHAPE, WallType::I_SHAPE};
            Possibility possibilityChecker;
            
            do{
                if(otherType){
                    type++;

                    if(type > 3) {type = 0;}
                }
                otherType = false;
                switch(type){
                    case 0:
                        rotatedPatterns = possibilityChecker.getL_SHAPES(); break;
                    case 1:
                        rotatedPatterns = possibilityChecker.getT_SHAPES(); break;
                    case 2:
                        rotatedPatterns = possibilityChecker.getPlus_SHAPES(); break;
                    case 3:
                        rotatedPatterns = possibilityChecker.getI_SHAPES(); break;
                }

                int sensorI = 0;
                for(auto& sens : sensors){

                    bool sensor = sens.scan(wallColisionBoxes);
                    sens.comparison(sensor, sensorI);
                    sensorI++;
                    std::cout << "sensor " << sensorI << ": " << sensor << std::endl;
                }

                bool fitFound = false;
                int successfulRotationIndex = 0;
                std::optional<sf::Vector2i> allocatePieceResult;

                for (int i = 0; i < rotatedPatterns.size(); ++i) {
                    const Pattern& currentPattern = rotatedPatterns[i];
                    std::optional<sf::Vector2i> tempResult = sensors[0].checkFitAt(currentPattern);

                    if (tempResult) {
                        fitFound = true;
                        successfulRotationIndex = i;
                        allocatePieceResult = tempResult;
                        break;
                    }
                }
                
                if(fitFound){
                    loading = false;
                    sf::Vector2i coords = allocatePieceResult.value();
                    sf::Vector2f krummbel = sensors[(coords.x * 4) + coords.y].getPosition();

                    //================ WALL CREATION ================
                    Object& newWall = allWalls.emplace_back(shapeTypes[type]);
                    
                    newWall.setOrigin({0.f, 0.f});
                    // Rotation
                    newWall.setRotation(sf::degrees(successfulRotationIndex * 90.f));
                    std::cout << krummbel.x << " , " << krummbel.y<<std::endl;
                    if(type == 3 && successfulRotationIndex == 1){
                        krummbel.x += 120;
                    }
                    if(type == 0 && successfulRotationIndex == 3){
                        krummbel.y += 80;
                    }
                    if(type == 1 && successfulRotationIndex == 2){
                        krummbel.x += 120;
                        krummbel.y += 120;
                    }

                    newWall.setPosition(krummbel);
                    
                    //get the collision box
                    for (const auto& wall : allWalls) {

                        const sf::Transform& parentTransform = wall.getTransform();

                        for (const auto& shape : wall.getShapes()) {

                            const sf::Transform& childTransform = shape.getTransform();

                            sf::Transform finalTransform = parentTransform * childTransform;

                            sf::FloatRect localBounds = shape.getLocalBounds();

                            wallColisionBoxes.push_back(finalTransform.transformRect(localBounds));
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(4));
                }
                else { //none of the pieces fit
                    otherType = true; 
                    attempts++;
                }

                if(attempts >= 4){
                    moveSens = true;
                    attempts = 0;
                }

                if(moveSens){
                    int i = 0;
                    for(auto& newPosition : sensors){             
                        newPosition.setPosition({newPosition.getPosition().x + 120, newPosition.getPosition().y});
                        i++;
                        //std::cout << std::endl << "TUDO PRONTO COM O: " << i << newPosition.getPosition().x << " , " << newPosition.getPosition().y << std::endl;
                    }
                    if(sensors[3].getPosition().x > 800){
                        loading = true;
                    }
                    moveSens = false;
                }
            }while(otherType && !loading); 
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
            window.draw(wall);
        }
        

        window.display();
        

    }


}