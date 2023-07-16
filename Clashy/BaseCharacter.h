

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H
#include "raylib.h"
/*
    Definir a classe

*/

class BaseCharacter{
public:
    BaseCharacter();
    Vector2 getworldPos() const { return worldPos;}
    Texture2D getTexture() const { return texture;}
    Texture2D getIdle_Texture() const { return idle;}
    Texture2D getRun_Texture() const { return run;}
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getScreenPos() = 0;
    bool getAlive() const {return alive;};
    void setAlive(bool isAlive){alive = isAlive;}; 

protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};

    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};

    float rightLeft{1.f}; // 1 = Right, -1 = Left
    int frame{};
    const int maxFrames{6};
    float runningTime{};
    const float updateTime{1.f/12.f};
    float speed{6.f};
    const float scale{4.f};

    float width{};
    float height{};

    Vector2 velocity{};

    bool alive{true};
};

#endif
