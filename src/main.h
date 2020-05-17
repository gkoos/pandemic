#include <time.h>

#include "common.h"

extern void cleanup(void);
extern void initSDL(void);
extern SDL_Texture *loadTexture(char *filename);
extern void prepareScene(void);
extern void presentScene(void);
extern void blit(SDL_Texture *texture, int x, int y);
extern void doInput(void);

App app;

Entity dots[NUM_DOTS];

SDL_Texture *textures[3];

llist_node_t *grid[SCREEN_WIDTH/CELL_SIZE][SCREEN_HEIGHT/CELL_SIZE];
