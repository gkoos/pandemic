typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
} App;

typedef struct {
	float x;
	float y;
	float destX;
	float destY;
	float dx;
	float dy;
	int color;
	int length;
} Entity;
