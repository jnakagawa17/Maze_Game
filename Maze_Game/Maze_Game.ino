#include <MeggyJrSimple.h>
int playerX = 2;
int playerY = 2;
int playerColor = 1;
int screenColor = 0;
int savedX = 3;
int savedY = 3;
int savedColor = 0;
int h = 0;
int directions = 0;
int gameState = 1;
int minionX = 4;
int minionY = 4;
int formerX = 4;
int formerY = 4;
int minionLives = 3;
int minionTurns = 8;
int startX = 0;
int startY = 0;
int endX = 7;
int endY = 7;
boolean deadEnd = false;

void setup()
{
  MeggyJrSimpleSetup();
  drawMaze();
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
    h = 0;
    DrawPx(startX, startY, 7);
    DrawPx(endX, endY, Green);
    DisplaySlate();
    delay(1000);
    checkFree();
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
  for (int i = 2; i < 7; i++)
  {
    DrawPx(i, 5, Green);
    DrawPx(i, 2, Green);
  }
  for (int i = 2; i < 6; i++) 
  {
    DrawPx(6, i, Green);
    DrawPx(2, i, Green);
  }
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
      gameState = 2;
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
  if(minionLives > 0)
  {
    DrawPx(4, 4, Blue);
    minionX = 4;
    minionY = 4;
    formerX = 4;
    formerY = 4;
    minionLives = minionLives - 1;
  }
  else
  {
    ClearSlate();
    DisplaySlate();
    gameState = 1;
  }
}

void checkFree()
{
  if(minionX < 7)
  {
    if( ReadPx(minionX + 1, minionY) == 0)
    {
      h = h + 1;
    }
  }
  if(minionX > 0)
  {
    if( ReadPx(minionX - 1, minionY) == 0)
    {
      h = h + 1;
    }
  }
  if(minionY < 7)
  {
    if( ReadPx(minionX, minionY + 1) == 0)
    {
      h = h + 1;
    }
  }
  if(minionY > 0)
  {
    if( ReadPx(minionX, minionY - 1) == 0)
    {
      h = h + 1;
    }
  }
  if(h == 1)
  {
    deadEnd = true;
  }
  if(h > 1)
  {
    deadEnd = false;
  }
}

void heading()
{
  directions = random(0, 4);
  if (directions == 0)
  {
    if(minionY < 7)
   { 
      minionY = minionY + 1;
      if ( ReadPx(minionX, minionY) == 0)
      {
        moveMinion();
      }
      else
      {
        minionY = minionY - 1;
        heading();
      } 
   }
    else
    {
      heading();
    }
  }
  if (directions == 1)
  {
    if(minionY > 0)
   { 
      minionY = minionY - 1;
      if ( ReadPx(minionX, minionY) == 0)
      {
        moveMinion();
      }
      else
      {
        minionY = minionY + 1;
        heading();
      } 
   }
    else
    {
      heading();
    }
  }
  if (directions == 2)
  {
    if(minionX < 7)
   { 
      minionX = minionX + 1;
      if ( ReadPx(minionX, minionY) == 0)
      {
        moveMinion();
      }
      else
      {
        minionX = minionX - 1;
        heading();
      } 
   }
    else
    {
      heading();
    }
  }
  if (directions == 3)
  {
    if(minionX > 0)
   { 
      minionX = minionX - 1;
      if ( ReadPx(minionX, minionY) == 0)
      {
        moveMinion();
      }
      else
      {
        minionX = minionX + 1;
        heading();
      } 
   }
    else
    {
      heading();
    }
  }
}

void moveMinion()
{
  if(minionX == endX)
  {
    if(minionY == endY)
    {
      ClearSlate();
      DisplaySlate();
      gameState = 2;
    }
  }
  if(deadEnd == true)
  {
    DrawPx(minionX, minionY, Blue);
    DrawPx(formerX, formerY, Red);
    formerX = minionX;
    formerY = minionY;
  }
  if(deadEnd == false)
  {
    DrawPx(minionX, minionY, Blue);
    DrawPx(formerX, formerY, 0);
    formerX = minionX;
    formerY = minionY;
  }
  minionTurns = minionTurns - 1;
  if(minionTurns == 0)
  {
    DrawPx(minionX, minionY, 0);
    deadEnd = false;
    spawn();
  }
}
