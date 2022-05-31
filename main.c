#include <stdlib.h>
#include <GL\gl.h>
#include <GL\freeglut_std.h>

//Для компиляции
//gcc main.c -Wall -o main.exe -lopengl32 -lglu32 -lfreeglut

#include "life.h"

byte *F1, *F2;

byte Frame[FRAME_H][FRAME_W][3];
double Zoom = 3;

int GetCell( byte *F, int X, int Y )
{
  X = (X + FRAME_W) % FRAME_W;
  Y = (Y + FRAME_H) % FRAME_H;
  return F[Y * FRAME_W + X];
}

void FieldInit( byte *F )
{
  int x, y;

  for (x = 0; x < FRAME_W; x++)
    for (y = 0; y < FRAME_H; y++)
      F[y * FRAME_W + x] = rand() % 2 ? 255 : 0;
}

void FieldDraw( byte *F )
{
  int x, y;
  
  for (y = 0; y < FRAME_H; y++)
    for (x = 0; x < FRAME_W; x++) //идем по полю
      //если клетка не мертва  то цвет от бирюзового до синего
      PutPixel(x, y, 0, GetCell(F, x, y), GetCell(F, x, y) ? 255 : 0);
}

int GetNeighbours( byte *F, int x, int y )
{
  return !!GetCell(F, x - 1, y - 1) + !!GetCell(F, x, y - 1) + !!GetCell(F, x + 1, y - 1) +
         !!GetCell(F, x - 1, y) + !!GetCell(F, x + 1, y) +
         !!GetCell(F, x - 1, y + 1) + !!GetCell(F, x, y + 1) + !!GetCell(F, x + 1, y + 1);
}

void SetCell( byte *F, int x, int y, int Value )
{
  x = (x + FRAME_W) % FRAME_W;
  y = (y + FRAME_H) % FRAME_H;
  F[y * FRAME_W + x] = Value;
}

void NewGeneration( byte *F1, byte *F2 )
{
  int x, y, value, n;
  unsigned char life;

  for (y = 0; y < FRAME_H; y++)
    for (x = 0; x < FRAME_W; x++)
    {
      n = GetNeighbours(F1, x, y); //количество соседей
      life = GetCell(F1, x, y); //значение в клетке
      if (life) //если жива
        //если окружили или мало друзей умирает 
        //если два или 3 соседа синеет
        value = (n < 2 || n > 3)? 0 : life - 1;
      else
        //схлопнулись или без изменений
        value = (n == 3)? 255 : 0; 
      SetCell(F2, x, y, value); 
    }
}

void NewRunner( byte *F, int X, int Y )
{
  int f = rand() % 4;

  if (f == 0)
  {
    SetCell(F, X - 1, Y - 1, 255);
    SetCell(F, X, Y - 1, 255);
    SetCell(F, X + 1, Y - 1, 255);

    SetCell(F, X - 1, Y, 0);
    SetCell(F, X, Y, 0);
    SetCell(F, X + 1, Y, 255);

    SetCell(F, X - 1, Y + 1, 0);
    SetCell(F, X, Y + 1, 255);
    SetCell(F, X + 1, Y + 1, 0);
  }
  else if (f == 1)
  {
    SetCell(F, X - 1, Y + 1, 255);
    SetCell(F, X, Y + 1, 255);
    SetCell(F, X + 1, Y + 1, 255);

    SetCell(F, X - 1, Y, 0);
    SetCell(F, X, Y, 0);
    SetCell(F, X + 1, Y, 255);

    SetCell(F, X - 1, Y - 1, 0);
    SetCell(F, X, Y - 1, 255);
    SetCell(F, X + 1, Y - 1, 0);
  }
  else if (f == 2)
  {
    SetCell(F, X + 1, Y - 1, 255);
    SetCell(F, X, Y - 1, 255);
    SetCell(F, X - 1, Y - 1, 255);

    SetCell(F, X + 1, Y, 0);
    SetCell(F, X, Y, 0);
    SetCell(F, X - 1, Y, 255);

    SetCell(F, X + 1, Y + 1, 0);
    SetCell(F, X, Y + 1, 255);
    SetCell(F, X - 1, Y + 1, 0);
  }
  else if (f == 3)
  {
    SetCell(F, X + 1, Y + 1, 255);
    SetCell(F, X, Y + 1, 255);
    SetCell(F, X - 1, Y + 1, 255);

    SetCell(F, X + 1, Y, 0);
    SetCell(F, X, Y, 0);
    SetCell(F, X - 1, Y, 255);

    SetCell(F, X + 1, Y - 1, 0);
    SetCell(F, X, Y - 1, 255);
    SetCell(F, X - 1, Y - 1, 0);
  }
}
void Disaster( byte *F, int X, int Y, int W, int H )
{
  int i, j;

  for (i = X; i < X + W; i++)
    for (j = Y; j < Y + H; j++)
      SetCell(F, i, j, 0);
}

void BornUp( byte *F, int X, int Y, int W, int H )
{
  int i, j;

  for (i = X - W / 2; i < X + W / 2; i++)
    for (j = Y - H / 2; j < Y + H / 2; j++)
      SetCell(F, i, j, 255);
}

void NewCircle( byte *F, int X, int Y, int R )
{
  int i, j, R2 = R * R;

  for (i = X - R; i < X + R; i++)
    for (j = Y - R; j < Y + R; j++)
      if ((i - X) * (i - X) + (j - Y) * (j - Y) <= R2 && (i - X) * (i - X) + (j - Y) * (j - Y) >= (R - 1) * (R - 1))
        SetCell(F, i, j, 255);
}

void PutPixel( int X, int Y, int R, int G, int B )
{
  if (X < 0 || Y < 0 || X >= FRAME_W || Y >= FRAME_H)
    return;
  Frame[Y][X][0] = B;
  Frame[Y][X][1] = G;
  Frame[Y][X][2] = R;
}

void Display( void )
{
  byte *tmp = F1;

  glClearColor(0.3, 0.5, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  FieldDraw(F1);
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
  else if (Key == 'f') 
    glutFullScreen();
  else if (Key == 'r')
    NewRunner(F1, rand() % FRAME_W, rand() % FRAME_H);
  else if (Key == 'R')
    NewRunner(F1, X, Y);
  else if (Key == 'd')
    Disaster(F1, rand() % FRAME_W, rand() % FRAME_H, rand() % (FRAME_W / 2), rand() % (FRAME_H / 2));
  else if (Key == ' ')
    BornUp(F1, X / Zoom, Y / Zoom, rand() % (FRAME_W / 2), rand() % (FRAME_H / 2));
  else if (Key == '.')
    SetCell(F, X, Y, 255);
  else if (Key == 'c')
    NewCircle(F1, X / Zoom, Y / Zoom, rand() % (FRAME_W / 5));
  else if (Key == 'x')
    Disaster(F1, 0, 0, FRAME_W, FRAME_H);
  else if (Key == 'i')
    FieldInit(F1);

}


int main( int argc, char *argv[] )
{
  F1 = (byte*) malloc(FRAME_W * FRAME_H);
  F2 = (byte*) malloc(FRAME_W * FRAME_H);

  FieldInit(F1);

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



