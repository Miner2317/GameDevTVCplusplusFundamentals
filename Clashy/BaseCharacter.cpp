#include "BaseCharacter.h"
#include "raymath.h"
#include "raylib.h"

BaseCharacter::BaseCharacter(){

}

void BaseCharacter::undoMovement(){
    worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::getCollisionRec(){
    return Rectangle{getScreenPos().x,getScreenPos().y, width*scale, height*scale};
}

void BaseCharacter::tick(float deltaTime){

    worldPosLastFrame = worldPos;

    //animate
    runningTime += GetFrameTime();

    if (runningTime >= updateTime){
        runningTime = 0.f;
        frame++;
        if (frame>maxFrames) frame = 0.f;
    }

    
    if(Vector2Length(velocity) != 0.0){
        //Apply movement
        worldPos = Vector2Add(worldPos,Vector2Scale(Vector2Normalize(velocity),speed));
        //    if                  do             else do
        velocity.x <0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    } else {
        texture = idle;
    }
    velocity = {0.f,0.f};

    Rectangle sourceRec{static_cast<float>(idle.width)/6.f * frame, 0.f, rightLeft*width, height};
    Rectangle destRec{getScreenPos().x,getScreenPos().y, scale*width, scale*height};
    DrawTexturePro(texture,sourceRec,destRec,Vector2{0.f,0.f},0.f,WHITE);

}