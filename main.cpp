#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include "raylib.h"

class Pipe {
 public:
    float posX;
    float posY;
};

float RandomFloat(float min, float max)    
{    
    return (min + 1) + (((float) rand()) / (float) RAND_MAX) * (max - (min + 1));    
}

int main() {
    
    int screenWidth = 800;
    int screenHeight = 600;
    
    bool dead = false;
    
    InitWindow(screenWidth, screenHeight, "Okno climy");
    
    SetTargetFPS(60);
    
    
    Pipe groundPipes[4];
    Pipe ceilingPipes[4];
    
    float pipeWidth = 90;
    float pipeNormalHeight = 300;
    float pipeCeilingHeight = 320;
    
    bool collision = false;
    bool collision2 = false;
    
    float speed = 1;
    
    Rectangle groundPipesRec[4];
    Rectangle ceilingPipesRec[4];
    
    Rectangle floor = { 0, screenHeight - 25, 10000, 50 };
    
    float birdPosY = 90;
    float birdSpeed = 0;
    float gravity = .1;
    
    bool collidedWithFloor = false;
    
    srand(time(NULL));
    
    for(int i = 0; i < 4; i++) {
        groundPipes[i].posX = 250*i + screenWidth;
        groundPipes[i].posY = RandomFloat(screenHeight / 1.5, screenHeight / 2);
        
        groundPipesRec[i] = { groundPipes[i].posX, groundPipes[i].posY, pipeWidth, pipeNormalHeight };
        
        ceilingPipes[i].posX = groundPipes[i].posX;
        ceilingPipes[i].posY = groundPipes[i].posY - 300 - 130;
        
        ceilingPipesRec[i] = { groundPipes[i].posX, ceilingPipes[i].posY, pipeWidth, pipeCeilingHeight };
        
        std::cout << groundPipes[i].posY;
    }
     
    while(!WindowShouldClose()) {
        
        float deltaTime = GetFrameTime();
        
        Rectangle bird = { 77, birdPosY, 50, 30 };
        
        BeginDrawing();
            
            ClearBackground(RAYWHITE);
            
            DrawRectangleRec(floor, MAROON);
            
            DrawRectangleRec(bird, MAROON);
            
            for(int i = 0; i < 4; i++) {
                DrawRectangleRec( groundPipesRec[i], GREEN);
                DrawRectangleRec( ceilingPipesRec[i], GREEN);
                
                collision = CheckCollisionRecs(bird, groundPipesRec[i]);
                collision2 = CheckCollisionRecs(bird, ceilingPipesRec[i]);
                bool collision3 = CheckCollisionRecs(bird, floor);
                
                if (collision == true) {
                    dead = true;
                    speed = 0;
                    DrawText("Przegrales! Zrestartuj gre", screenWidth / 2, screenHeight / 2, 20, BLACK);
                }
                
                if (collision2 == true)  {
                    dead = true;
                    speed = 0;
                    DrawText("Przegrales! Zrestartuj gre", screenWidth / 2, screenHeight / 2, 20, BLACK);
                }
                
                if (collision3 == true)  {
                    dead = true;
                    collidedWithFloor = true;
                    speed = 0;
                    DrawText("Przegrales! Zrestartuj gre", screenWidth / 2, screenHeight / 2, 20, BLACK);
                }
                
                if (collidedWithFloor == true)  {
                    birdPosY = floor.y - 30;
                    speed = 0;
                }
                
                if (dead == true) {
                    speed = 0;
                    DrawText("Przegrales! Zrestartuj gre", screenWidth / 2, screenHeight / 2, 20, BLACK);
                }
                
                groundPipes[i].posX -= 2;
                ceilingPipes[i].posX -= 2;
                
                if(groundPipes[i].posX + 90 < 0) { 
                    groundPipes[i].posX = 1.1
                    
                    * screenWidth;
                    groundPipes[i].posY = RandomFloat(screenHeight / 1.5, screenHeight / 2);
        
                    ceilingPipes[i].posX = groundPipes[i].posY;
                    ceilingPipes[i].posY = groundPipes[i].posY - 300 - 130;
                    
                    groundPipesRec[i] = { groundPipes[i].posX, groundPipes[i].posY, pipeWidth, pipeNormalHeight };
                    
                    ceilingPipesRec[i] = { groundPipes[i].posX, ceilingPipes[i].posY, pipeWidth, pipeCeilingHeight };
                }
                
                groundPipesRec[i] = { groundPipes[i].posX, groundPipes[i].posY, pipeWidth, pipeNormalHeight };
                    
                ceilingPipesRec[i] = { groundPipes[i].posX, ceilingPipes[i].posY, pipeWidth, pipeCeilingHeight };
            }
            
            if(IsKeyDown(KEY_SPACE) && dead == false) birdSpeed = -2.6f;
            
            if (speed > 0 && collidedWithFloor == false) {
                birdPosY += birdSpeed;
                birdSpeed += gravity;
            } else if(speed = 0 && collidedWithFloor == false){
                birdPosY += birdSpeed;
                birdSpeed += gravity;
            } else {
                birdPosY = floor.y - 30;
            }
            
        
        EndDrawing();
        
    }
    
    CloseWindow();
    
    return 0;
}
