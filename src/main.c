#include "main.h"

void setMovement(float x, float y, float *destX, float *destY, float *dx, float *dy)
{
  *destX = rand() % (SCREEN_WIDTH + 1);
  *destY = rand() % (SCREEN_HEIGHT + 1);

  float distX = *destX - x, distY = *destY - y;

  float dist = sqrt(distX * distX + distY * distY);
  float speed;

  do
  {
    speed = rand() % 400 / 100;
  } while (speed == 0);

  float cos = distX / dist, sin = distY / dist;

  *dx = speed * cos;
  *dy = speed * sin;
}

bool isCollision(float x1, float y1, float x2, float y2)
{
  return (abs(x1 - x2) < 16) && (abs(y1 - y2) < 16);
}

void setHealth(int i, int j)
{
  if (!isCollision(dots[i].x, dots[i].y, dots[j].x, dots[j].y)) return;

  if (dots[i].color == 1 && (rand() % 100) < INFECTION_PCTG) 
  {
    dots[j].color = 1;
    dots[j].length = rand() % MIN_LENGTH + VAR_LENGTH;
  }
  
  if (dots[j].color == 1 && (rand() % 100) < INFECTION_PCTG) {
    dots[i].color = 1;
    dots[i].length = rand() % MIN_LENGTH + VAR_LENGTH;
  }
}

void detectInfection()
{
  // create grid
  for (int i=0; i<NUM_DOTS; i++)
  {
    if (dots[i].color == 1)
    {
      --dots[i].length;
      if (dots[i].length <= 0)
      {
        dots[i].color = 2;
      }
    }

    if (dots[i].color != 2)
    {
      float x = dots[i].x / CELL_SIZE;
      float y = dots[i].y / CELL_SIZE;
      llist_insert(&grid[(int)x][(int)y], i);

      float x1 = x + 8 / CELL_SIZE; if (x1 >= SCREEN_WIDTH / CELL_SIZE) x1 = SCREEN_WIDTH / CELL_SIZE - 1;
      float y1 = y + 8 / CELL_SIZE; if (y1 >= SCREEN_WIDTH / CELL_SIZE) y1 = SCREEN_WIDTH / CELL_SIZE - 1;

      if ((int)x1 >(int)x) llist_insert(&grid[(int)x1][(int)y], i);
      if ((int)y1 > (int)y) llist_insert(&grid[(int)x][(int)y1], i);
      if (((int)x1 > (int)x) && ((int)y1 > (int)y)) llist_insert(&grid[(int)x1][(int)y1], i);
    }
  }

  for (int i=0; i<SCREEN_WIDTH/CELL_SIZE; i++)
  {
    for (int j=0; j<SCREEN_HEIGHT/CELL_SIZE; j++)
    {
      llist_getPairs(grid[i][j], setHealth);
      llist_destroy(grid[i][j]);
      grid[i][j] = NULL;
    }
  }
}

int main(int argc, char *argv[])
{
  int seed = time(NULL);
  srand(seed);

  memset(&app, 0, sizeof(App));

  initSDL();

  textures[0] = loadTexture("gfx/green.png");
  textures[1] = loadTexture("gfx/red.png");
  textures[2] = loadTexture("gfx/orange.png");

  atexit(cleanup);

  for (int i = 0; i < NUM_DOTS; ++i)
  {
    dots[i].x = rand() % (SCREEN_WIDTH + 1);
    dots[i].y = rand() % (SCREEN_HEIGHT + 1);

    dots[i].color = rand() % 100 < INIT_INFECTED_PCTG ? 1 : 0;
    if (dots[i].color == 1)
    {
      dots[i].length = rand() % MIN_LENGTH + VAR_LENGTH;
    }

    setMovement(dots[i].x, dots[i].y, &dots[i].destX, &dots[i].destY, &dots[i].dx, &dots[i].dy);
  }

  while (1)
  {
    prepareScene();

    doInput();

    detectInfection();

    for (int i = 0; i < NUM_DOTS; ++i)
    {
      if (isCollision(dots[i].x, dots[i].y, dots[i].destX, dots[i].destY))
      {
        setMovement(dots[i].x, dots[i].y, &dots[i].destX, &dots[i].destY, &dots[i].dx, &dots[i].dy);
      }
      
      dots[i].x += dots[i].dx;
      dots[i].y += dots[i].dy;

      blit(textures[dots[i].color], (int)dots[i].x, (int)dots[i].y);
    }

    presentScene();

    SDL_Delay(16);
  }

  return 0;
}
