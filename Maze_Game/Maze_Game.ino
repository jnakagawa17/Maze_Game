#include <MeggyJrSimple.h>
int playerX = 3;
int playerY = 3;
int playerColor = 1;
int screenColor = 0;
int savedX = 3;
int savedY = 3;
int savedColor = 0;
int e = 0;
int f = 0;
int g = 0;
int h = 0;
int checkFree = 0;
int directions = 0;
int gameState = 1;
int minionX = 0;
int minionY = 0;
int trail = 0;
int minionLives = 3;
int minionTurns = 8;
boolean deadEnd = false;

void setup()
{
  MeggyJrSimpleSetup();
  drawMaze();
  DrawPx(3, 3, 1);
  DisplaySlate();
}

void loop()
{
  if(gameState == 1)
  {
    shift(); 
  }
  if(gameState == 2)
  {
    heading();
  }
  if(gameState == 3)
  {
    screenSaver();
    DisplaySlate();
    delay(500);
  }
}

void drawMaze()
{
  for (int i = 0; i < 5; i++)
  {
    DrawPx(i, 7, Green);
  }
  for (int h = 3; h < 7; h++) 
  {
    DrawPx(2, h, Green);
  }
  for (int w = 0; w < 3; w++)
 { 
    DrawPx(w, 3, Green);
 }
  DrawPx(0, 4, Green);
}

void drawDot()
{
  DrawPx(savedX, savedY, savedColor);
  savedX = playerX;
  savedY = playerY;
  savedColor = ReadPx(playerX, playerY);
  DrawPx(playerX, playerY, playerColor); 
  DisplaySlate();
}

void shift()
{
  CheckButtonsPress();
  if(Button_Left)
  {
    CheckButtonsDown();
    if(Button_Up)
    {
      gamestate = 2;
      spawn();
    }
    if (playerX > 0)
      playerX = playerX - 1;
      drawDot();
  }
  if(Button_Right)
  {
    if (playerX < 7)
      playerX = playerX + 1;
      drawDot();
  }
  if(Button_Up)
    if (playerY < 7)
      playerY = playerY + 1;
      drawDot();
  if(Button_Down)
  {
    if (playerY > 0)
      playerY = playerY - 1;
      drawDot();
  }
  if(Button_B)
  {
    CheckButtonsDown();
    if(Button_A)
    {
      gameState = 3;
    }
    if (playerColor < 4)
      playerColor = playerColor + 1;
      drawDot();
    if (playerColor == 4)
      playerColor = 0;
      drawDot();
  }
  if(Button_A)
  {
    savedColor = playerColor;
  }
}

void screenSaver()
{
    for (int a = 1; a < 7; a++)
    {
      DrawPx(1, a, screenColor);
      DrawPx(a, 1, screenColor);
      DrawPx(a, 6, screenColor);
      DrawPx(6, a, screenColor);
      screenColor = random(0, 7);
    }
    for (int b = 0; b < 8; b++)
    {
      DrawPx(0, b, screenColor);
      DrawPx(b, 0, screenColor);
      DrawPx(b, 7, screenColor);
      DrawPx(7, b, screenColor);
      screenColor = random(0, 7);
    }
    for (int c = 2; c < 6; c++)
    {
      DrawPx(2, c, screenColor);
      DrawPx(c, 2, screenColor);
      DrawPx(c, 5, screenColor);
      DrawPx(5, c, screenColor);
      screenColor = random(0, 7);
    }
    for (int d = 0; d < 4; d++)
    {
      DrawPx(3, 3, screenColor);
      DrawPx(4, 3, screenColor);
      DrawPx(3, 4, screenColor);
      DrawPx(4, 4, screenColor);
      screenColor = random(0, 7);
    }
    CheckButtonsDown();
    if(Button_Up)
    {
      ClearSlate();
      playerX = 3;
      playerY = 3;
      playerColor = 1;
      drawMaze();
      DrawPx(3, 3, 1);
      DisplaySlate();
      gameState = 1;
    }
}

void spawn()
{
  for (int r = 0; r < 8; r++)
  {
    for (int s = 0; s < 8; s++)
    {
      if ( ReadPx(s, r) == Blue)
      {
        heading();
      }
      else
      {
        DrawPx(0, 0, Blue);
        minionX = 0;
        minionY = 0;
        DisplaySlate();
      }
    }
  }
}

void heading()
{
  if( ReadPx(minionX + 1, minionY) == 0)
  {
    h = h + 1;
  }
  if( ReadPx(minionX - 1, minionY) == 0)
  {
    h = h + 1;
  }
  if( ReadPx(minionX, minionY + 1) == 0)
  {
    h = h + 1;
  }
  if( ReadPx(minionX, minionY - 1) == 0)
  {
    h = h + 1;
  }
  if(h == 1)
  {
    deadEnd = true;
  }
  if(h > 1)
  {
    deadEnd = false;
  }
  directions = random(0, 4);
  if (directions == 0)
  {
    minionY = minionY + 1;
    if ( ReadPx(minionX, minionY) == 0)
      moveMinion();
  }
  if (directions == 1)
  {
    minionY = minionY - 1;
    if ( ReadPx(minionX, minionY) == 0)
      moveMinion();
  }
  if (directions == 2)
  {
    minionY = minionX + 1;
    if ( ReadPx(minionX, minionY) == 0)
      moveMinion();
  }
  if (directions == 3)
  {
    minionY = minionX - 1;
    if ( ReadPx(minionX, minionY) == 0)
      moveMinion();
  }
}

void moveMinion()
{
  if(deadEnd == true)
  {
    DrawPx(minionX, minionY, Red);
  }
  if(deadEnd == false)
  {
    DrawPx(minionX, minionY, Blue);
  }
}
