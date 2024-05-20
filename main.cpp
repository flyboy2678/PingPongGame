#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int player1_score = 0;
int player2_score = 0;

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    Ball(float x_val, float y_val, int speedX, int speedY, int r)
    {
        x = x_val;
        y = y_val;
        speed_x = speedX;
        speed_y = speedY;
        radius = r;
    }
    void draw()
    {
        DrawCircle(x, y, radius, Yellow);
    }

    void moveBall()
    {
        x += speed_x;
        y += speed_y;

        // Collission dection for the ball
        if (y + radius >= GetScreenHeight() || y - radius <= 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth())
        {
            speed_x *= -1;
            player1_score++;
            resetBall();
        }
        if (x - radius <= 0)
        {
            speed_x *= -1;
            player2_score++;
            resetBall();
        }
    }
    // rest ball to center after a point has been scored
    void resetBall()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int direction[2] = {1, -1};
        speed_x *= direction[GetRandomValue(0, 1)];
        speed_y *= direction[GetRandomValue(0, 1)];
    }
};

class Paddle
{
public:
    float x, y;
    int width, height;
    int speed;

    Paddle(float x_val, float y_val, int w, int h, int s)
    {
        x = x_val;
        y = y_val;
        width = w;
        height = h;
        speed = s;
    }

    void draw()
    {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void moveP1()
    {
        if (IsKeyDown(KEY_W))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_S))
        {
            y = y + speed;
        }
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

    void moveP2()
    {
        if (IsKeyDown(KEY_UP))
        {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            y = y + speed;
        }
        if (y <= 0)
        {
            y = 0;
        }
        if (y + height >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }
};
int main()
{
    cout << "Starting with game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;

    // create a window
    InitWindow(screen_width, screen_height, "Pong Game");
    // set the fps we want our game to run at
    SetTargetFPS(60);
    Ball ball(screen_width / 2, screen_height / 2, 3, 5, 20);
    Paddle player1(10, screen_height / 2 - 60, 25, 120, 6);
    Paddle player2(screen_width - 35, screen_height / 2 - 60, 25, 120, 6);

    while (WindowShouldClose() == false)
    {
        // make a blank canvas to start drawing game objects on
        BeginDrawing();
        // move the ball and paddles
        ball.moveBall();
        player1.moveP1();
        player2.moveP2();

        Vector2 v;
        v.x = ball.x;
        v.y = ball.y;
        Rectangle p1;
        Rectangle p2;
        p1.x = player1.x;
        p1.y = player1.y;
        p1.height = player1.height;
        p1.width = player1.width;
        p2.x = player2.x;
        p2.y = player2.y;
        p2.height = player2.height;
        p2.width = player2.width;
        // Checks for collision with the two paddle and if yes ball moves to the oposite direction
        if (CheckCollisionCircleRec(v, ball.radius, p1) || CheckCollisionCircleRec(v, ball.radius, p2))
        {
            ball.speed_x *= -1;
        }
        // Draw center line
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        // To clear previous drawings
        ClearBackground(Dark_Green);
        // Draw a ball
        ball.draw();
        // Draw the two paddles on the screen
        player1.draw();
        player2.draw();
        // Draw the scores on the window
        DrawText(TextFormat("%i", player1_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player2_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
        // Close the drawing canvas
        EndDrawing();
    }
    // close window
    CloseWindow();
    return 0;
}