#include <stdio.h>
#include <stdlib.h>
#include "fonction.h"

void main()
{

    SDL_Rect perso;
    perso.x = 0;
    perso.y = 650;
    perso.h = 100;
    perso.w = 100;

    SDL_Rect birdPos;
    birdPos.x = 100;
    birdPos.y = 230;

    SDL_Rect obstacleOne;
    obstacleOne.x = 180;
    obstacleOne.y = 70;
    SDL_Rect obstacleTwo;
    obstacleTwo.x = 700;
    obstacleTwo.y = 70;

    SDL_Rect camera;
    camera.x = 0;
    camera.y = 0;

    minimap m;

    time timeingame;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Surface *screen;
    screen = SDL_SetVideoMode(1200, 750, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);

    if (TTF_Init() == -1)
    {
        return;
    }
    TTF_Font *font = NULL;
    font = TTF_OpenFont("./font/Roboto.ttf", 100);
    if (font == NULL)
        return;

    initminimap(&m);
    init_time(&timeingame);

    SDL_Event event;
    int quit = 1;
    int start_Time;
    while (quit)
    {
        afficherminimap(m, screen);

        SDL_FillRect(screen, &perso, 0x032a852);

        afficherTemps(&timeingame, screen);

        SDL_BlitSurface(m.animation.spriteSheet, &m.animation.Clips[m.animation.clipLoaded], screen, &birdPos);

        if ((SDL_GetTicks()) % 5 == 0)
        {
            if (m.animation.clipLoaded < m.animation.frames)
            {
                m.animation.clipLoaded++;
            }
            else
                m.animation.clipLoaded = 0;
        }

        SDL_BlitSurface(m.obstacle.spriteSheet, &m.obstacle.Clips[m.obstacle.clipLoaded], screen, &obstacleOne);
        SDL_BlitSurface(m.obstacle.spriteSheet, &m.obstacle.Clips[m.obstacle.clipLoaded], screen, &obstacleTwo);

        if ((SDL_GetTicks()) % 5 == 0)
        {
            if (m.obstacle.clipLoaded < m.obstacle.frames)
            {
                m.obstacle.clipLoaded++;
            }
            else
                m.obstacle.clipLoaded = 0;
        }

        if (perso.x > 850)
        {
            perso.x = 0;
            perso.y = 650;
            start_Time = SDL_GetTicks() / 1000;
            afficherEnigme(screen, start_Time);
        }

        SDL_Flip(screen);

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    perso.y -= 15;
                    if (collisionPP(perso, m.mask) == 1)
                        perso.y += 15;
                    break;
                case SDLK_DOWN:
                    perso.y += 15;
                    if (collisionPP(perso, m.mask) == 1)
                        perso.y -= 15;
                    break;
                case SDLK_RIGHT:
                    perso.x += 15;
                    if (collisionPP(perso, m.mask) == 1)
                        perso.x -= 15;

                    break;
                case SDLK_LEFT:
                    perso.x -= 15;
                    if (collisionPP(perso, m.mask) == 1)
                        perso.x += 15;
                    break;
                }
            }
        }
        MAJMinimap(perso, &m, camera, 20);
    }
    SDL_FreeSurface(screen);
    clean(&timeingame, &m);
    TTF_CloseFont(font);
    SDL_Quit();
    return;
}
