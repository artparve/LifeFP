#include <stdlib.h>
#include <GL\gl.h>
#include <GL\freeglut_std.h>

//Для компиляции
//gcc main.c -Wall -o main.exe -lopengl32 -lglu32 -lfreeglut

#include "life.h"

byte *F1, *F2;

byte Frame[FRAME_H][FRAME_W][3];
double Zoom = 3;

//значение в клетке
int GetCell( byte *F, int X, int Y )
{
  X = (X + FRAME_W) % FRAME_W;
  Y = (Y + FRAME_H) % FRAME_H;
  return F[Y * FRAME_W + X];
}

//задать значение клетке (x,y)
void SetCell( byte *F, int x, int y, int Value )
{
  x = (x + FRAME_W) % FRAME_W;
  y = (y + FRAME_H) % FRAME_H;
  F[y * FRAME_W + x] = Value;
}

//Новое поколение 
void NewGeneration( byte *F1, byte *F2 )
{
  int x, y, value, n;
  unsigned char life;

  for (y = 0; y < FRAME_H; y++)
    for (x = 0; x < FRAME_W; x++)
    {
      n = 0; //количество соседей
      if GetCell(F, x - 1, y - 1):
        n++;
      if GetCell(F, x, y - 1):
        n++;
      if GetCell(F, x + 1, y - 1):
        n++;
      if GetCell(F, x + 1, y):
        n++;
      if GetCell(F, x - 1, y):
        n++;
      if GetCell(F, x - 1, y + 1):
        n++;
      if GetCell(F, x, y + 1):
        n++;
      if GetCell(F, x + 1, y + 1):
        n++;

      life = GetCell(F1, x, y); //значение в клетке
      if (life) //если жива
        if (n < 2 || n > 3) //если окружили или мало друзей
          value = 0; //умирает
        else //если два или 3 соседа
          value = life - 1; //синеет
      else
        if (n == 3) //схлопнулись
          value = 255; 
        else
          value = 0; //без изменений
      SetCell(F2, x, y, value); 
    }
}

void Display( void )
{
  byte *tmp = F1;

  glClearColor(0.3, 0.5, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  int x, y;

  for (y = 0; y < FRAME_H; y++)
    for (x = 0; x < FRAME_W; x++) //идем по полю
      if(GetCell(F1, x, y)) //если клетка не мертва
        //то цвет от желтого до красного
        Frame[y][x][0] = 0;
        Frame[y][x][1] = GetCell(F1, x, y);
        Frame[y][x][2] = 255;
      else
      //черная
        Frame[y][x][0] = 0;
        Frame[y][x][1] = 0;
        Frame[y][x][2] = 0; 
  
  NewGeneration(F1, F2);
  F1 = F2;
  F2 = tmp;

  glRasterPos2d(-1, 1);
  glPixelZoom(Zoom, -Zoom);
  //glDrawPixels(FRAME_W, FRAME_H, GL_UNSIGNED_BYTE, Frame);
  glDrawPixels(FRAME_W, FRAME_H, GL_RGB, GL_UNSIGNED_BYTE, Frame);

  glFinish();

  glutSwapBuffers();

  glutPostRedisplay();
}

void Keyboard( unsigned char Key, int X, int Y )
{
  if (Key == 27)
    exit(0);
  //на весь экран
  else if (Key == 'f') 
    glutFullScreen();
}


int main( int argc, char *argv[] )
{
  F1 = (byte*) malloc(FRAME_W * FRAME_H);
  F2 = (byte*) malloc(FRAME_W * FRAME_H);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(800, 800);
  glutCreateWindow("CGSG forever!");

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glutFullScreen();
  glutMainLoop();
  return 0;
}



