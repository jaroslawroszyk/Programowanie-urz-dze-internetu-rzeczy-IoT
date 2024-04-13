#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h> // Include the SoftwareSerial library for Bluetooth communication

#define OLED_ADDR 0x3C // 0x3D
#define OLED_SDA A5
#define OLED_SCL A4
#define JOY_X A1
#define JOY_Y A0
#define JOY_PIN 2
#define BUZZER_PIN 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define SNAKE_SIZE 4
#define MAX_SNAKE_SIZE 100
#define OLED_RESET 4

// Define the Bluetooth module pins
#define BLUETOOTH_RX 0 // RX pin of Bluetooth module connected to digital pin 10
#define BLUETOOTH_TX 1 // TX pin of Bluetooth module connected to digital pin 11

// Create a SoftwareSerial object for Bluetooth communication
SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR);

int snakeX[MAX_SNAKE_SIZE];
int snakeY[MAX_SNAKE_SIZE];
int snakeSize = SNAKE_SIZE;
int snakeDir = 1;
int foodX = 1, foodY = 1;
bool gameOver = false;
bool gamePaused = false;
int score = 0;

void updateScore() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Score: ");
    display.print(score);
    display.display();
}

void initSnake()
{
    score = 0;
    int startX = SCREEN_WIDTH / 2;
    int startY = SCREEN_HEIGHT / 2;
    for (int i = 0; i < snakeSize; i++)
    {
        snakeX[i] = startX - i * 4; // Adjusted to align with grid
        snakeY[i] = startY;
    }
    foodX = random(0, SCREEN_WIDTH / 4) * 4; // Adjusted to align with grid
    foodY = random(0, SCREEN_HEIGHT / 4) * 4; // Adjusted to align with grid
}

void updateSnake()
{
    int newHeadX = snakeX[0];
    int newHeadY = snakeY[0];
    switch (snakeDir)
    {
    case 0: // up
        newHeadY--;
        break;
    case 1: // right
        newHeadX++;
        break;
    case 2: // down
        newHeadY++;
        break;
    case 3: // left
        newHeadX--;
        break;
    }

    if (!gamePaused) {
        if (newHeadX < 0 || newHeadX >= SCREEN_WIDTH || newHeadY < 0 || newHeadY >= SCREEN_HEIGHT)
        {
            gameOver = true;
            return;
        }

        for (int i = 1; i < snakeSize; i++)
        {
            if (newHeadX == snakeX[i] && newHeadY == snakeY[i])
            {
                gameOver = true;
                return;
            }
        }

        if (newHeadX == foodX && newHeadY == foodY)
        {
            snakeSize++;
            if (snakeSize > MAX_SNAKE_SIZE)
            {
                snakeSize = MAX_SNAKE_SIZE;
            }
            foodX = random(0, SCREEN_WIDTH);
            foodY = random(0, SCREEN_HEIGHT);
            score++;
            updateScore();
            tone(BUZZER_PIN, 1500, 100); // Play tone when food is collected
        }
        else
        {
            for (int i = snakeSize - 1; i > 0; i--)
            {
                snakeX[i] = snakeX[i - 1];
                snakeY[i] = snakeY[i - 1];
            }
        }
        snakeX[0] = newHeadX;
        snakeY[0] = newHeadY;
    }
}

void drawGame()
{
    display.clearDisplay();
    for (int i = 0; i < snakeSize; i++)
    {
        display.fillRect(snakeX[i], snakeY[i], 4, 4, WHITE); // Adjusted to align with grid
    }
    display.fillRect(foodX, foodY, 4, 4, WHITE); // Adjusted to align with grid
    display.display();
}

void setup()
{
    randomSeed(analogRead(0));
    Wire.begin();
    display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(20, 10);
    display.println("SNAKE GAME");
    display.display();
    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    pinMode(JOY_PIN, INPUT_PULLUP);
    pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
    bluetooth.begin(9600); // Start Bluetooth communication at 9600 baud rate
    delay(2000);
    initSnake();
}

void loop()
{
    if (digitalRead(JOY_PIN) == LOW)
    {
        delay(50); // Debounce
        if (gameOver) {
            // Start new game
            gameOver = false;
            gamePaused = false; // Ensure the game is not paused when starting a new game
            initSnake();
            updateScore();
            drawGame(); // Draw initial state of the game
            tone(BUZZER_PIN, 2000, 200); // Play tone when new game starts
        } else {
            gamePaused = !gamePaused; // Toggle game pause state
            if (gamePaused) {
                display.clearDisplay();
                display.setTextColor(WHITE);
                display.setTextSize(2);
                display.setCursor(30, SCREEN_HEIGHT / 2 - 10);
//                display.println("Paused");
//                display.display();
                updateScore();
            } else {
                updateScore();
            }
        }
        while (digitalRead(JOY_PIN) == LOW)
        {
            delay(50); // Wait for button release
        }
    }

    if (!gameOver && !gamePaused)
    {
        updateSnake();
        drawGame();
        int joyX = analogRead(JOY_X);
        int joyY = analogRead(JOY_Y);

        if (joyX < 100 && snakeDir != 1)
        {
            snakeDir = 3; // Left
        }
        else if        (joyX > 900 && snakeDir != 3)
        {
            snakeDir = 1; // Right
        }
        else if (joyY < 100 && snakeDir != 0)
        {
            snakeDir = 2; // Down
        }
        else if (joyY > 900 && snakeDir != 2)
        {
            snakeDir = 0; // Up
        }
    }

    delay(50); // Adjust game speed
    if (gameOver)
    {
        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setTextSize(2);
        display.setCursor(10, SCREEN_HEIGHT / 2 - 10);
        display.println("Game Over");
        display.display();
        tone(BUZZER_PIN, 100, 1000); // Play tone when game over

        // Send game over information over Bluetooth
        bluetooth.print("Game Over! Score: ");
        bluetooth.println(score);
    }
}
