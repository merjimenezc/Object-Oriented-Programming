#ifndef Game_hpp
#define Game_hpp

#include "AppComponent.h"
#include "AnimatedRect.h"
#include "Timer.h"

#include <deque>
class Game: public AppComponent, private Timer{
    AnimatedRect* enemy;
    AnimatedRect* enemy2;
    AnimatedRect* enemy3;
    AnimatedRect* enemy4;
    AnimatedRect* enemy5;
    //Rect* projectile;
    AnimatedRect* player;
    TexRect* background;
    AnimatedRect* explosion;
    AnimatedRect* explosion2;
    AnimatedRect* projectile;

    
    
    std::deque<TexRect*> holes;
    
    bool playerVisible;
    bool enemyVisible;
    bool backgroundVisible;
    bool projectileVisible;
    bool explosionVisible;
    bool up;
    bool down;
    bool space;
    bool left;
    bool right;
    bool hit;
    float theta;
    float deg;
    bool enemyUp;
    bool enemyUp2;
    bool enemyUp3;
    bool enemyUp4;
    bool enemyUp5;
public:
    
    //AnimatedRect* projectile;
    Game();
    
    void draw() const ;
    void handleKeyDown(unsigned char, float, float);
    void handleKeyUp(unsigned char, float, float);
    
    void action();
    
    void idle();

    ~Game();

};

#endif 
