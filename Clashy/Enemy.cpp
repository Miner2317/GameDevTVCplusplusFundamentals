#include "Enemy.h"
#include "raymath.h"
#include "raylib.h"

/*      Definir as funções                       */

Enemy::Enemy(Vector2 pos,Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = static_cast<float>(texture.width)/maxFrames;
    height = texture.height;
    speed = 5.5f;
}

void Enemy::tick(float deltaTime){
    if(!getAlive()) return;
    //get toTarget B = C - A 
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());

    if (Vector2Length(velocity) < radius) velocity = {};

    BaseCharacter::tick(deltaTime);

    //damage player
    if(CheckCollisionRecs(getCollisionRec(), target->getCollisionRec())){
        target->takeDamage(damagePerSec * deltaTime);
    }

}

Vector2 Enemy::getScreenPos(){
    //Set enemy on the correct map position
    return Vector2Subtract(worldPos,target->getworldPos());
}

