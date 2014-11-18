#include <MeggyJrSimple.h>
int x = 3;
int y = 3;
int z = 1;
int a = 3;
int b = 3;
int c = 0;
int d = 0;
int e = 0;

void setup()
{
  MeggyJrSimpleSetup();
  drawJ();
  drawN();
  DrawPx(3, 3, 1);
  DisplaySlate();
}

void loop()
{
  shift(); 
}

void drawJ()
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

void drawN()
{
  for (int r = 0; r < 4; r++)
  {
    DrawPx(7, r, Green);
  }
  for (int h = 0; h < 4; h++) 
  {
    DrawPx(4, h, Green);
  } 
  for (int l = 0; l < 2; l++) 
  {
    DrawPx(5 + l, 2 - l, Green);
  }
}

void drawDot()
{
  DrawPx(a, b, c);
  a = x;
  b = y;
  c = ReadPx(x, y);
  DrawPx(x, y, z); 
  DisplaySlate();
}

void shift()
{
  CheckButtonsPress();
  if(Button_Left)
  {
    if (x > 0)
      x = x - 1;
      drawDot();
  }
  if(Button_Right)
  {
    if (x < 7)
      x = x + 1;
      drawDot();
  }
  if(Button_Up)
    if (y < 7)
      y = y + 1;
      drawDot();
  if(Button_Down)
  {
    if (y > 0)
      y = y - 1;
      drawDot();
  }
  if(Button_B)
  {
    CheckButtonsDown();
    if(Button_A)
    {
      ScreenSaver();
    }
    if (z < 4)
      z = z + 1;
      drawDot();
    if (z == 4)
      z = 0;
      drawDot();
  }
  if(Button_A)
  {
    c = z;
  }
}

void ScreenSaver()
{
      for (int a = 1; a < 7; a++)
    {
      DrawPx(1, a, x);
      DrawPx(a, 1, x);
      DrawPx(a, 6, x);
      DrawPx(6, a, x);
      x = random(0, 7);
    }
    for (int b = 0; b < 8; b++)
    {
      DrawPx(0, b, x);
      DrawPx(b, 0, x);
      DrawPx(b, 7, x);
      DrawPx(7, b, x);
      x = random(0, 7);
    }
    for (int c = 2; c < 6; c++)
    {
      DrawPx(2, c, x);
      DrawPx(c, 2, x);
      DrawPx(c, 5, x);
      DrawPx(5, c, x);
      x = random(0, 7);
    }
    for (int d = 0; d < 4; d++)
    {
      DrawPx(3, 3, x);
      DrawPx(4, 3, x);
      DrawPx(3, 4, x);
      DrawPx(4, 4, x);
      x = random(0, 7);
    }
    CheckButtonsDown();
    if(Button_A)
    {
      shift();
    }
    ScreenSaver();
    DisplaySlate();
    delay(500);
    ScreenSaver();
}
