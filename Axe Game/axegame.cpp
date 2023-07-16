#include <cstdio>
#include "raylib.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// <> C++ defaults
// "".h Imported libraries


/*
TODO

- Fix enemy border collisions
- Copy paste for green

*/

int main(){
    //Generate Seed
    srand((unsigned) time(NULL));

    //Game Properties
    int width = {500};
    int height = {500};
    int targetFPS = {120};
    float timer = {60};
    float timepass = {1.0/60.0};

    //Game Data
    int score = {0};
    int highscore = {0};

    //Game State
    bool gameRunning = {true};
    bool gameOver = {false};
    bool startScreen = {true};

    //Player Data
    int radius = {25};
    int speed = {4};

    //Player Position
    int centerX = {width/2};
    int centerY = {height/2};

    //Player collision
    int left_player_x = {centerX-radius};
    int right_player_x = {centerX+radius};
    int top_player_y = {centerY-radius};
    int bottom_player_y = {centerY+radius};

    //Point data
    int pointRadius = {10};

    //Point position
    int positionX = rand() % width-pointRadius;
    int positionY = rand() % height-pointRadius;

    //Point collision
    int left_point_x = {positionX-pointRadius};
    int right_point_x = {positionX+pointRadius};
    int top_point_y = {positionY-pointRadius};
    int bottom_point_y = {positionY+pointRadius};

    //RED
    int redRadius = {15};

    //RED position
    int red_positionX = rand() % width-redRadius;
    int red_positionY = rand() % height-redRadius;
    int red_direction = rand() % 8;
    int red_speed = {3};

    //RED collision
    int left_red_x = {red_positionX-redRadius};
    int right_red_x = {red_positionX+redRadius};
    int top_red_y = {red_positionY-redRadius};
    int bottom_red_y = {red_positionY+redRadius};

    //Green
    int greenRadius = {2};

    //Green position
    int green_positionX = rand() % width-greenRadius;
    int green_positionY = rand() % height-greenRadius;

    //Green collision
    int left_green_x = {green_positionX-greenRadius};
    int right_green_x = {green_positionX+greenRadius};
    int top_green_y = {green_positionY-greenRadius};
    int bottom_green_y = {green_positionY+greenRadius};

    //Start window and set FPS
    InitWindow(width,height,"Agar.io");
    SetTargetFPS(targetFPS);

    while(WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(WHITE);

        //Update ScoreString
        std::string scoreToString = "Score: " + std::to_string(score);
        const char* scoreString = scoreToString.c_str();


        //updateTime
        timer -= timepass;

        //Update TimerString
        std::string timerToString = "Timer: " + std::to_string(timer);
        const char* timeString = timerToString.c_str();

        //Update player
        left_player_x = {centerX-radius};
        right_player_x = {centerX+radius};
        top_player_y = {centerY-radius};
        bottom_player_y = {centerY+radius};

        //Update enemy
        left_red_x = {red_positionX-redRadius};
        right_red_x = {red_positionX+redRadius};
        top_red_y = {red_positionY-redRadius};
        bottom_red_y = {red_positionY+redRadius};

        //Update green
        left_green_x = {green_positionX-greenRadius};
        right_green_x = {green_positionX+greenRadius};
        top_green_y = {green_positionY-greenRadius};
        bottom_green_y = {green_positionY+greenRadius};

        //Player movement
        if(IsKeyDown(KEY_W) && (centerY - radius) > 0){
            centerY -= speed;
        }
        if (IsKeyDown(KEY_A) && (centerX - radius) > 0 ){
            centerX -= speed;
        }
        if (IsKeyDown(KEY_S) && (centerY + radius) < height){
            centerY += speed;
        }
        if (IsKeyDown(KEY_D) && (centerX + radius) < width ){
            centerX += speed;
        }

        //check collision with point, update it if collided
        if(bottom_point_y >= top_player_y && top_point_y <= bottom_player_y && left_point_x <= right_player_x && right_point_x >= left_player_x){
            //Generate new positions for point
            positionX = rand() % width-pointRadius;
            positionY = rand() % height-pointRadius;
            //Recalculate collision for point
            left_point_x = {positionX-pointRadius};
            right_point_x = {positionX+pointRadius};
            top_point_y = {positionY-pointRadius};
            bottom_point_y = {positionY+pointRadius};
            score+=1;
        }

        //check collision with green
        if(bottom_green_y >= top_player_y && top_green_y <= bottom_player_y && left_green_x <= right_player_x && right_green_x >= left_player_x){
            //Generate new positions for green
            green_positionX = rand() % width-greenRadius;
            green_positionY = rand() % height-greenRadius;
            //Recalculate collision for green
            left_green_x = {green_positionX-greenRadius};
            right_green_x = {green_positionX+greenRadius};
            top_green_y = {green_positionY-greenRadius};
            bottom_green_y = {green_positionY+greenRadius};

            score+=10;
        }

        //check collision with enemy
        if(bottom_red_y >= top_player_y && top_red_y <= bottom_player_y && left_red_x <= right_player_x && right_red_x >= left_player_x){
            gameRunning = false;
            gameOver = true;

            //Update highscore
            if (score > highscore){
                highscore = score;
            }

            //Randomize red for next game
            red_positionX = rand() % width-redRadius;
            red_positionY = rand() % height-redRadius;
            red_direction = rand() % 8;

            //Randomize point for next game
            positionX = rand() % width-pointRadius;
            positionY = rand() % height-pointRadius;
            left_point_x = {positionX-pointRadius};
            right_point_x = {positionX+pointRadius};
            top_point_y = {positionY-pointRadius};
            bottom_point_y = {positionY+pointRadius};

            //Randomize green for next game
            green_positionX = rand() % width-greenRadius;
            green_positionY = rand() % height-greenRadius;
            left_green_x = {green_positionX-greenRadius};
            right_green_x = {green_positionX+greenRadius};
            top_green_y = {green_positionY-greenRadius};
            bottom_green_y = {green_positionY+greenRadius};
        }

        //RedMovement
        if (red_direction == 0 && (red_positionY - redRadius) > 0){
            red_positionY -= red_speed;

            if (red_positionY - redRadius - 5 < 0){
                red_direction = rand() % 8;
            }

        } 
        else if (red_direction == 1 && (red_positionX + redRadius) < width && (red_positionY - redRadius) > 0){
            red_positionX += red_speed;
            red_positionY -= red_speed;

            if (red_positionX + redRadius + 5 > width || red_positionY - redRadius - 5 < 0){
                red_direction = rand() % 8;
            }

        }
        else if (red_direction == 2 && (red_positionX + redRadius) < width){
            red_positionX += red_speed;

            if (red_positionX + redRadius + 5 > 0){
                red_direction = rand() % 8;
            }

        }
        else if (red_direction == 3 && (red_positionX + redRadius) < width && (red_positionY + redRadius) < height){
            red_positionY += red_speed;
            red_positionX += red_speed;

            if (red_positionX + redRadius + 5 > width || red_positionY + redRadius + 5 > height){
                red_direction = rand() % 8;
            }

        } 
        else if (red_direction == 4 && (red_positionY + redRadius) < height){
            red_positionY += red_speed;

            if (red_positionY + redRadius + 5 > height){
                red_direction = rand() % 8;
            }

        }
        else if (red_direction == 5 && (red_positionY + redRadius) < height && (red_positionX - redRadius) > 0){
            red_positionY += red_speed;
            red_positionX -= red_speed;


            if (red_positionY + redRadius + 5 > height || red_positionX - redRadius - 5 < 0){
                red_direction = rand() % 8;
            }


        }
        else if (red_direction == 6 && (red_positionX - redRadius) > 0){
            red_positionX -= red_speed;

            if (red_positionX - redRadius - 5 < 0){
                red_direction = rand() % 8;
            }


        }
        else if (red_direction == 7 && (red_positionX - redRadius) > 0 || (red_positionY - redRadius) > 0){
            red_positionY -= red_speed;
            red_positionX -= red_speed;

            if (red_positionX - redRadius - 5 < 0 || red_positionY - redRadius - 5 < 0){
                red_direction = rand() % 8;
            }
        }


        if(timer <= 0.0){
            gameRunning = false;
            gameOver = true;

            //Update highscore
            if (score > highscore){
                highscore = score;
            }
        }

        //Draw by the end of frame
        if(startScreen){
            //Display start message
            DrawText("Welcome",width/2 - 50,height/2,20,RED);
            DrawText("Press enter to start.",width/2 - 50,height/2 + 30,10,RED);

            //Start game feature
            if(IsKeyDown(KEY_ENTER)){
                startScreen = false;
                gameOver = false;
                gameRunning = true;
                score=0;
            }
        }
        else if(gameRunning){
            DrawCircle(centerX,centerY,radius,BLUE);
            DrawCircle(positionX,positionY,pointRadius,YELLOW);
            DrawCircle(red_positionX,red_positionY,redRadius,RED);
            DrawCircle(green_positionX,green_positionY,greenRadius,GREEN);
            DrawText(scoreString,0,0,20,RED);
            DrawText(timeString,width-140,0,20,RED);
        }
        else if(gameOver){
            //Update highscore string
            std::string highscoreToString = "Highscore: " + std::to_string(highscore);
            const char* highscoreString = highscoreToString.c_str();

            //Display message
            DrawText("GAME OVER!",width/2 - 50,height/2,20,RED);
            DrawText("Press enter to restart.",width/2 - 50,height/2 + 30,10,RED);
            DrawText(highscoreString,width/2 - 50,height/2 + 50,20,RED);

            //Restart feature
            if(IsKeyDown(KEY_ENTER)){
                gameOver = false;
                gameRunning = true;
                score=0;
                timer=60.00;
            }
        }
        EndDrawing();
    }
}