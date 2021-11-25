#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include "Game.h"

Game::Game(){
    
    // Some cross-platform compatimility stuff
    
    const char* enemyFileName;
    const char* enemy2FileName;
    const char* explosionFileName;
    const char* explosion2FileName;
    const char* playerFileName;
    const char* backgroundFileName;
    const char* projectileFileName;
    
    // In Windows (Visual Studio only) the image files are found in the enclosing folder in relation to the project
    // In other environments the image files are in the same folder as the project
    
#if defined WIN32
    enemyFileName = "../Textures/enemy_sprites.png";
    enemy2FileName = "../Textures/enemy2_sprites.png"
    explosionFileName = "../Textures/explosion.png";
    explosion2FileName = "../Textures/explosion2.png";
    playerFileName = "../Textures/player_right.png";
    backgroundFileName = "../Textures/background.png";
    projectileFileName = "../Textures/projectile2.png";
#else
    enemyFileName = "Textures/enemy_sprites.png";
    enemy2FileName = "Textures/enemy2_sprites.png";
    explosionFileName = "Textures/explosion.png";
    explosion2FileName = "Textures/explosion2.png";
    playerFileName = "Textures/player_right.png";
    backgroundFileName = "Textures/background.png";
    projectileFileName = "Textures/projectile2.png";
    
#endif
    enemy = new AnimatedRect(enemyFileName, 1, 2, 255, true, true, -0.63, -0.08, 0.1, 0.1);
    enemy2 = new AnimatedRect(enemyFileName, 1, 2, 255, true, true, 0.80, -0.01, 0.1, 0.1);
    enemy3 = new AnimatedRect(enemy2FileName, 1, 2, 255, true, true, 0.17, 0.25, 0.1, 0.1);
    enemy4 = new AnimatedRect(enemy2FileName, 1, 2, 255, true, true, -0.46, -0.85, 0.1, 0.1);
    enemy5 = new AnimatedRect(enemy2FileName, 1, 2, 255, true, true, 0.50, -0.53, 0.1, 0.1);
    player = new AnimatedRect(playerFileName, 1, 2, 255, true, true, -0.15, -0.39, 0.1, 0.1);
    explosion = new AnimatedRect(explosionFileName, 1, 4, 255, false, false, -0.25, 0.8, 0.5, 0.5);
    background = new TexRect(backgroundFileName, -2, 1, 4, 2);
    projectile = new AnimatedRect(projectileFileName, 1, 1, 255, true, true, -0.15, -0.39, 0.1, 0.1);
    
    space = false;
    up = false;
    left = false;
    right = false;
    down = false;
    playerVisible = true;
    enemyVisible = true;
    backgroundVisible = true;
    projectileVisible = true;
    explosionVisible = false;
    enemyUp = true;
    enemyUp2 = true;
    enemyUp3 = true;
    enemyUp4 = true; 
    
    holes.push_back(new TexRect("Textures/hole.png", player->getX() - 0.05, player->getY()+0.05, 0.17, 0.17));
    
    theta = 0;
    deg = 0;
    hit = false;
    
    setRate(1);
    start();
}



void Game::idle(){
    if (left || right || up || down) {
        holes.push_back(new TexRect("Textures/hole.png", player->getX()-0.05 , player->getY()+0.05, 0.17, 0.17));
        
    }
}


void Game::action(){
    float mx = 0.5;
    float my = 0;
    
    if (theta >= 2* M_PI) theta = 0;
    if (deg >= 360) deg = 0;
    
    mx = 0.0 * cos(theta);
    my = 0.4 * sin(theta);
    
    
    //    if (left)
    //        mx -= 0.0005;
    //    else
    //        mx += 0.0005;
    //
    //    if (mx < -1.6f){
    //        left = false;
    //    }
    //    if (mx > 1.6 - mushroom->getW()){
    //        left = true;
    //    }
    
//    enemy->setY(mx-enemy->getG() - 0.0);
//    enemy->setY(my-enemy->getH() + 0.01);

//Enemy 1 Coordinates/Location
    if (enemyUp){
        enemy->setY(enemy->getY() + 0.0001);
    }
    else{
        enemy->setY(enemy->getY() - 0.0001);
    }
    
    if (enemy->getY() > 0.25){
        enemyUp = false;
    }
    if (enemy->getY() < -0.05){
        enemyUp = true;
    }
    //Enemy 2 Coordinates/Location
    if (enemyUp2){
        enemy2->setY(enemy2->getY() + 0.0001);
    }
    else{
        enemy2->setY(enemy2->getY() - 0.0001);
    }
    if (enemy2->getY() > 0.1){
        enemyUp2 = false;
    }
    if (enemy2->getY() < -0.2){
        enemyUp2 = true;
    }
    //Enemy 3 coordinates
    if (enemyUp3){
        enemy3->setX(enemy3->getX() + 0.0001);
    }
    else{
        enemy3->setX(enemy3->getX() - 0.0001);
    }
    
    if (enemy3->getX() > 0.32){
        enemyUp3 = false;
    }
    if (enemy3->getX() < 0.01){
        enemyUp3 = true;
    }
    //Enemy 4 coordinates
    if (enemyUp4){
        enemy4->setX(enemy4->getX() + 0.0001);
    }
    else{
        enemy4->setX(enemy4->getX() - 0.0001);
    }
    if (enemy4->getX() > -0.30){
        enemyUp4 = false;
    }
    if (enemy4->getX() < -0.63){
        enemyUp4 = true;
    }
    
    if (enemyUp5){
        enemy5->setX(enemy5->getX() + 0.0001);
    }
    else{
        enemy5->setX(enemy5->getX() - 0.0001);
    }
    if (enemy5->getX() > 0.60){
        enemyUp5 = false;
    }
    if (enemy5->getX() < 0.40){
        enemyUp5 = true;
    }

    theta += 0.001;
    deg += 0.1;
    
    
    //Explosion
    if (!hit && space){
        float ypos = projectile->getY();
        ypos +=0.005;
        projectile->setY(ypos);
        
        if (enemy->contains(0, ypos-0.005)){
            space = false;
            hit = true;
            projectileVisible = false;
            enemyVisible = false;
            //explosionVisible = true;
            explosion->setX(enemy->getX());
            explosion->setY(enemy->getY());
            explosion->playOnce();
        }
    }
    if (hit){
        explosion->setY(explosion->getY()-0.0001);
        //explosionVisible = false;
    }
    
    //Screen Boundaries
    if (right){
      float  px = player->getX();
        px += 0.001;
        if (px > 1.0){
            px = 1.0;
        
        }
        //player->setX(player->getX() + 0.001)
        player->setX(px);
        player->resume();
    
        float  ppx = projectile->getX();
        ppx += 0.001;
        if (ppx > 1.0){
            ppx = 1.0;
        }
        //player->setX(player->getX() + 0.001)
        projectile->setX(ppx);
        projectile->resume();
    
    }
    else {
        player->pause();
    }
    
    if (left){
       float px = player->getX();
        px -= 0.001;
        if (px < (-1.1)){
            px = -1.1;
        }
        //player->setX(player->getX() - 0.001);
        player->setX(px);
        player->resume();
        
        float ppx = projectile->getX();
        ppx -= 0.001;
        if (ppx < (-1.1)){
            ppx = -1.1;
        }
        //player->setX(player->getX() - 0.001);
        projectile->setX(ppx);
        projectile->resume();
    }
    else {
        //player->pause();
    }
    if (up) {
      float  py = player->getY();
        py += 0.001;
        if (py > 0.67){
            py = 0.67;
    }
        //player->setY(player->getY() + 0.001);
        player->setY(py);
        player->resume();
        
        float  ppy = projectile->getY();
        ppy += 0.001;
        if (ppy > 0.67){
            ppy = 0.67;
        }
        //player->setY(player->getY() + 0.001);
        projectile->setY(ppy);
        projectile->resume();
    }
    else {
        //player->pause();
    }

    if (down) {
       float py = player->getY();
        py -= 0.001;
        if (py < (-0.9)){
            py = -0.9;
        }
        //player->setY(player->getY() - 0.001);
        player->setY(py);
        player->resume();
        
        float ppy = projectile->getY();
        ppy -= 0.001;
        if (ppy < (-0.9)){
            ppy = -0.9;
        }
        //player->setY(player->getY() - 0.001);
        projectile->setY(ppy);
        projectile->resume();    }
    else {
        //player->pause();
    }
    
}

void Game::draw() const {
    
    background->draw(-0.1);
    
    
    for (int i = 0; i < holes.size(); i++) {
        holes[i]->draw(0.1 + i*0.00001);
    }
    
    if (playerVisible){
        player->draw(1);
    }
    if (enemyVisible){
        enemy->draw(0.2);
        enemy2->draw(0.2);
        enemy3->draw(0.2);
        enemy4->draw(0.2);
        enemy5->draw(0.2);
    }
    if (projectileVisible){
        projectile->draw(0.3);
    }
    if (explosionVisible){
    explosion->draw(0.4);
    }
}

void Game::handleKeyDown(unsigned char key, float x, float y){
    
    if (key == ' '){
        space = true;
    }
    else if (key == 'a'){
        left = true;
        holes.push_back(new TexRect("Textures/hole.png", player->getX()-0.05 , player->getY()+0.05, 0.17, 0.17));
    }
    else if (key == 'd'){
        right = true;
        holes.push_back(new TexRect("Textures/hole.png", player->getX()-0.05 , player->getY()+0.05, 0.17, 0.17));
    }
    else if (key == 'w'){
        up = true;
        holes.push_back(new TexRect("Textures/hole.png", player->getX()-0.05 , player->getY()+0.05, 0.17, 0.17));
    }
    else if (key == 's'){
        down = true;
        holes.push_back(new TexRect("Textures/hole.png", player->getX()-0.05 , player->getY()+0.05, 0.17, 0.17));
    }
    else if (key == 'p'){
        stop();
    }
    else if (key == 'r'){
        start();
    }
}


void Game::handleKeyUp(unsigned char key, float x, float y){
    if (key == ' ') {
        space = false;
        //explosionVisible = false;
    }
    else if (key == 'a') {
        left = false;
    }
    else if (key == 'd') {
        right = false;
    }
    else if (key == 'w') {
        up = false;
    }
    else if (key == 's') {
        down = false;
    }
}



Game::~Game(){
    stop();
    delete enemy;
    delete enemy2;
    delete enemy3;
    delete explosion;
    //delete player;
    delete projectile;
}
