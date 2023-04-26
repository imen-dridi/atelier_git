#define fonction
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
    SDL_Surface *spriteSheet;
    SDL_Rect Clips[8];
    int frames;
    int clipLoaded;
} animation;

typedef struct
{
    SDL_Surface *img_background;
    SDL_Rect pos_background;

    SDL_Surface *img_minimap;
    SDL_Rect pos_minimap;

    SDL_Surface *img_minimain;
    SDL_Rect pos_minimain;

    SDL_Surface *mask;
    SDL_Rect pos_mask;
 
    animation obstacle;

    animation animation;
} minimap;

typedef struct
{
    SDL_Rect pos_time;
    TTF_Font *font;
} time;

void draw(SDL_Surface *screen, SDL_Surface *textSurface, char string[], int size, int x, int y, int fR, int fG, int fB, TTF_Font *font);

void init_time(time *timeingame);
void initminimap(minimap *m);

void afficherTemps(time *timeingame, SDL_Surface *screen);
void afficherminimap(minimap m, SDL_Surface *screen);

void MAJMinimap(SDL_Rect posJoueur, minimap *m, SDL_Rect camera, int redimensionnement);
void clean(time *timeingame, minimap *m);
SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y);
int collisionPP(SDL_Rect p, SDL_Surface *Masque);
void afficherEnigme(SDL_Surface *screen, int startTime);
