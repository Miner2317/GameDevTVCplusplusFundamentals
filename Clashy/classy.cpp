
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

/* Pointers

float* pointer = &variable; store adress in pointer
float howMuch = *pointer; get adress from pointer
howMuch->function(); call functions from pointer target

*/

int main(){
    int windowSize[2]{384,384};
    InitWindow(windowSize[0],windowSize[1],"Reeeeee");

    Texture2D map = LoadTexture("tiles/map.png");
    Vector2 mapPos{0,0};
    const float mapScale{3.5f};

    Character playerCharacter{windowSize[0],windowSize[1]};

    Enemy goblin{Vector2{1200.f,1200.f},LoadTexture("characters/goblin_idle_spritesheet.png"),LoadTexture("characters/goblin_run_spritesheet.png")};
    goblin.setTarget(&playerCharacter);

    Prop props[2]{
        Prop{Vector2{300.f,300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{600.f,600.f}, LoadTexture("nature_tileset/Log.png")}
    };

    Enemy slime{Vector2{1600.f,1600.f},LoadTexture("characters/slime_idle_spritesheet.png"),LoadTexture("characters/slime_run_spritesheet.png")};
    slime.setTarget(&playerCharacter);

    Enemy* enemies[]{
        &goblin, &slime
    };

    for(auto enemy : enemies){
        enemy->setTarget(&playerCharacter);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        float dT = GetFrameTime();

        mapPos =  Vector2Scale(playerCharacter.getworldPos(),-1);
        
        //Draw map
        DrawTextureEx(map,mapPos,0,mapScale,WHITE);
        //Draw props
        for(auto prop : props){
            prop.Render(playerCharacter.getworldPos());
        };

        //apply mofoka's movement
        playerCharacter.tick(dT);

        //Undo movement if mofoka trynna go out of the map
        if (playerCharacter.getworldPos().x < 0.f || playerCharacter.getworldPos().y < 0.f ||
            playerCharacter.getworldPos().x + windowSize[0] > map.width * mapScale ||
            playerCharacter.getworldPos().y + windowSize[1] > map.height * mapScale ){
            playerCharacter.undoMovement();
        }
        //Undo movement if mofoka trynna get on top of a rock
        for(auto prop : props){
            if(CheckCollisionRecs(playerCharacter.getCollisionRec(),prop.getCollisionRec(playerCharacter.getworldPos()))){
                playerCharacter.undoMovement();
            }
        };

        //Draw enemies
        for(auto enemy : enemies){
            enemy->tick(dT);
        };

        //Check weapon collision
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            for(auto enemy : enemies){
                if(CheckCollisionRecs(enemy->getCollisionRec(),playerCharacter.getWeaponCollisionRec())){
                    enemy->setAlive(false);
                }
            }
        }

        //Display heatth
        if(!playerCharacter.getAlive()){
            DrawText("GAME OVER!", 55.f, 45.f, 40, RED);

            EndDrawing();
            continue;
        } else {    
            std::string health = "Health: ";
            health = health.append(std::to_string(playerCharacter.getHealth()),0,5);
            DrawText(health.c_str(), 55.f, 45.f, 40, RED);
        } 

        EndDrawing();
    }
    UnloadTexture(map);
    UnloadTexture(playerCharacter.getTexture());
    UnloadTexture(playerCharacter.getIdle_Texture());
    UnloadTexture(playerCharacter.getRun_Texture());
    UnloadTexture(goblin.getTexture());
    UnloadTexture(goblin.getIdle_Texture());
    UnloadTexture(goblin.getRun_Texture());
}