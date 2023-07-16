#include <cstdio>
#include "raylib.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


/*
TODO 

- Add S downforce
- Add restart
- add flying mob

*/

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float update_time;
    float running_time;
};

bool groundCheck(AnimData scarfyAnim,int windowHeight){
    if(scarfyAnim.pos.y >= windowHeight-scarfyAnim.rec.height){
        return true;
    } else {
        return false;
    }
};


AnimData updateAnim(AnimData data, int maxFrame, float dT){
    //update running time
    data.running_time += dT;
    if (data.running_time >= data.update_time){
        data.running_time = 0;
        //update animation frame
        data.rec.x = data.frame*data.rec.width;
        data.frame++;
        if (data.frame > maxFrame){
            data.frame = 0;
        }
    }
    return data;
}

main (){
    srand((unsigned) time(NULL));

    //Game Properties
    int windowSize[2]{512,380};

    //Set window
    InitWindow(windowSize[0],windowSize[1],"Dapper");
    SetTargetFPS(60);

    int velocity = {60}; // pixels/sec
    int jumpvelocity = {-600};
    const int gravity = {1000}; 
    bool onAir = {false};

    //Load textures
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Texture2D hazard = LoadTexture("textures/12_nebula_spritesheet.png");
    Texture2D textureBackground = LoadTexture("textures/far-buildings.png");
    Texture2D textureMidground = LoadTexture("textures/back-buildings.png");
    Texture2D textureForeground = LoadTexture("textures/foreground.png");

    int numberTextures = {4};
    Texture2D textureArray[numberTextures]{scarfy,hazard,textureBackground,textureMidground,textureForeground};

    AnimData scarfyAnim{ 
        {0.0,0.0, scarfy.width/6, scarfy.height},                               //Rectangle
        {windowSize[0]/2 - scarfyAnim.rec.width/2, scarfyAnim.rec.height  },    //Vector2
        0,                                                                      //frame
        1.0/16.0,                                                               //update_time
        0                                                                       //running_time
        };

    //Nebula data
    const int nebulaNumber = 2;
    int nebulaVelocity = {-350}; //pixels per second
    AnimData nebulaData[nebulaNumber];

    //Generate nebulas at constant increment
    int increment = 500;
    int randomizer = rand() % 500;
    for(int i = 0; i<nebulaNumber; i++){
        nebulaData[i].rec = {0.0,0.0,hazard.width/8,  hazard.height/8 };
        nebulaData[i].pos = { windowSize[0] + increment*i + randomizer, windowSize[1] - nebulaData[i].rec.height};
        nebulaData[i].frame = 0;
        nebulaData[i].update_time = 1.0/12.0;
        nebulaData[i].running_time = 0;
        randomizer = rand() % 500;
    }

    float bgX{};
    float midX{};
    float foreX{};

    int bgXspeed = {20};
    int midXspeed = {40};
    int foreXspeed = {80};


    float finishLine{nebulaData[nebulaNumber-1].pos.x};

    bool collision = {false};
   
    while(!WindowShouldClose()){
        //time since last frame
        float dT{GetFrameTime()};

        BeginDrawing();
        ClearBackground(WHITE);

        //Draw Background
        bgX -= bgXspeed * dT;
        if(bgX <= -textureBackground.width*2){
            bgX = 0.0;
        }
        Vector2 bgPos{bgX,0.0};
        Vector2 bgPos2{bgX + textureBackground.width*2 ,0.0};
        DrawTextureEx(textureBackground,bgPos,0.0,2.0,WHITE);
        DrawTextureEx(textureBackground,bgPos2,0.0,2.0,WHITE);

        //Draw Midground
        midX -= midXspeed * dT;
        if(midX <= -textureMidground.width*2){
            midX = 0.0;
        }
        Vector2 midPos{midX,0.0};
        Vector2 midPos2{midX + textureMidground.width*2 ,0.0};
        DrawTextureEx(textureMidground,midPos,0.0,2.0,WHITE);
        DrawTextureEx(textureMidground,midPos2,0.0,2.0,WHITE);

        //Draw Foreground
        foreX -= foreXspeed * dT;
        if(foreX <= -textureForeground.width*2){
            foreX = 0.0;
        }
        Vector2 forePos{foreX,0.0};
        Vector2 forePos2{foreX + textureForeground.width*2 ,0.0};
        DrawTextureEx(textureForeground,forePos,0.0,2.0,WHITE);
        DrawTextureEx(textureForeground,forePos2,0.0,2.0,WHITE);


        //Ground check
        if (groundCheck(scarfyAnim,windowSize[1])){
            velocity = 0;
            onAir = false;
        } else {
            //Apply gravity
            velocity += gravity * dT;
        }

        //Jump
        if(IsKeyPressed(KEY_SPACE) && !onAir){
            velocity+= jumpvelocity;
            onAir = true;
        }


        //move nebulas
        for(int i = 0; i<nebulaNumber; i++){
            nebulaData[i].pos.x += nebulaVelocity * dT;
        }

        //move
        scarfyAnim.pos.y += velocity * dT;
        finishLine += nebulaVelocity *dT;
        
        //Update animation frame when scarfy is on the floor and enough time has passed since last update
        if(!onAir){
            scarfyAnim = updateAnim(scarfyAnim, 5, dT);
        }

        //Update all the nebula animations in the array
        for(int i = 0; i<nebulaNumber; i++){
            nebulaData[i] = updateAnim(nebulaData[i],7,dT);
        }

        for (AnimData nebula : nebulaData){
            float pad{20};

            Rectangle nebulaRec{
                nebula.pos.x + pad,
                nebula.pos.y + pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad
            };

            Rectangle scarfyRec{
                scarfyAnim.pos.x,
                scarfyAnim.pos.y,
                scarfyAnim.rec.width,
                scarfyAnim.rec.height
            };

            if(CheckCollisionRecs(nebulaRec,scarfyRec)){
                collision = true;
            }
        }

        if(collision){
            //lose game
            bgXspeed = 0;
            midXspeed = 0;
            foreXspeed = 0;
            DrawText("GAME OVER!",windowSize[0]/2 - 150,windowSize[1]/2,50,WHITE);
        } else if (scarfyAnim.pos.x >= finishLine){
            //win game
            bgXspeed = 120;
            midXspeed = 240;
            foreXspeed = 360;
            DrawText("YOU WIN!",windowSize[0]/2 - 150,windowSize[1]/2,50,WHITE);
        } else {
            //Draw all the nebulas
            for(int i = 0; i<nebulaNumber; i++){
                DrawTextureRec(hazard,nebulaData[i].rec,nebulaData[i].pos,WHITE);
            }
            //Draw the player
            DrawTextureRec(scarfy, scarfyAnim.rec, scarfyAnim.pos, WHITE);
        }

        //checkVictory





        EndDrawing();
    }

    //Unloading all textures 
    for (int i=0; i<numberTextures; i++){
        UnloadTexture(textureArray[i]);
    }
    CloseWindow();
}