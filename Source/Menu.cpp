
// Menu.cpp
//
// This file contains the implementation of the functions
// which are used to handle the game menu.
//
// Author:    Johan Öfverstedt

//Game headers:
#include "Main.h"
#include "Menu.h"

// Variable singlePlayerButton
//
// Pointer to the single player button surface.

SDL_Surface *singlePlayerButton = 0;

// Variable splitScreenButton
//
// Pointer to the split screen button surface.

SDL_Surface *splitScreenButton = 0;

// Variable exitButton
//
// Pointer to the exit button surface.

SDL_Surface *exitButton = 0;

SDL_Surface *uncheckedSound = 0;
SDL_Surface *checkedSound = 0;
SDL_Surface *uncheckedMusic = 0;
SDL_Surface *checkedMusic = 0;

// Variable drawErrorMenu
//
// Flag that makes sure, drawing errors
// are reported only once.

bool drawErrorMenu = false;

// Variable buttonSound
//
// Pointer to a sound-clip
// of type FSOUND_SAMPLE that plays
// when user presses a menu-button.

FSOUND_SAMPLE *buttonSound = 0;

// List of menu options.
enum {
    MENU_ONE_PLAYER,
    MENU_TWO_PLAYER,
    MENU_EXIT,
    NUM_MENU_CHOICES,
};
// Currently selected menu option.
static int menuChoice = 0;

// Function loadMenu()
//
// Loads the menu resources.
// Returns false if loading of any of the
// files failed to load.

bool loadMenu()
{
    singlePlayerButton = loadImg(GFX_PATH, "menusingleplayer.png");

    if(!singlePlayerButton)
    {
        return false;
    }

    SDL_SetColorKey(singlePlayerButton, SDL_SRCCOLORKEY, 0xFFFFFF);

    splitScreenButton = loadImg(GFX_PATH, "menusplitscreen.png");

    if(!splitScreenButton)
    {
        return false;
    }

    SDL_SetColorKey(splitScreenButton, SDL_SRCCOLORKEY, 0xFFFFFF);

    exitButton = loadImg(GFX_PATH, "menuexit.png");

    if(!exitButton)
    {
        return false;
    }

    SDL_SetColorKey(exitButton, SDL_SRCCOLORKEY, 0xFFFFFF);

    if(!uncheckedSound)
        uncheckedSound = loadImg(GFX_PATH, "uncheckedsound.png");

    if(!uncheckedSound)
    {
        return false;
    }

    SDL_SetColorKey(uncheckedSound, SDL_SRCCOLORKEY, 0xFFFFFF);

    if(!checkedSound)
        checkedSound = loadImg(GFX_PATH, "checkedsound.png");

    if(!checkedSound)
    {
        return false;
    }

    SDL_SetColorKey(checkedSound, SDL_SRCCOLORKEY, 0xFFFFFF);

    if(!uncheckedMusic)
        uncheckedMusic = loadImg(GFX_PATH, "uncheckedmusic.png");

    if(!uncheckedMusic)
    {
        return false;
    }

    SDL_SetColorKey(uncheckedMusic, SDL_SRCCOLORKEY, 0xFFFFFF);

    if(!checkedMusic)
        checkedMusic = loadImg(GFX_PATH, "checkedmusic.png");

    if(!checkedMusic)
    {
        return false;
    }

    SDL_SetColorKey(checkedMusic, SDL_SRCCOLORKEY, 0xFFFFFF);

    buttonSound = loadSound(SND_PATH, "Button.ogg");

    return true;
}

// Function drawMenu()
//
// Draws all the menu buttons.
// Returns false if drawing of any
// of the buttons failed.

bool drawMenu()
{
    SDL_Rect buttonRect;
    SDL_Rect selectRect;
    uint32_t selectColor;

    SDL_SetAlpha(singlePlayerButton, SDL_SRCALPHA, 198);
    SDL_SetAlpha(splitScreenButton, SDL_SRCALPHA, 198);
    SDL_SetAlpha(exitButton, SDL_SRCALPHA, 198);

    buttonRect.x = g_screen->w - singlePlayerButton->w - 30;
    buttonRect.y = g_screen->h - singlePlayerButton->h - splitScreenButton->h - exitButton->h - 50;
    buttonRect.w = singlePlayerButton->w;
    buttonRect.h = singlePlayerButton->h;

    selectRect = buttonRect;
    selectRect.x -= 60;
    selectRect.w = 60;
    selectColor = (menuChoice == MENU_ONE_PLAYER) ? 0xffffffff : 0;

    if(SDL_BlitSurface(singlePlayerButton, 0, g_screen, &buttonRect) < 0)
        return false;
    if(SDL_FillRect(g_screen, &selectRect, selectColor) < 0)
        return false;

    buttonRect.x = g_screen->w - splitScreenButton->w - 30;
    buttonRect.y = g_screen->h - splitScreenButton->h - exitButton->h - 40;
    buttonRect.w = splitScreenButton->w;
    buttonRect.h = splitScreenButton->h;

    selectRect = buttonRect;
    selectRect.x -= 60;
    selectRect.w = 60;
    selectColor = (menuChoice == MENU_TWO_PLAYER) ? 0xffffffff : 0;

    if(SDL_BlitSurface(splitScreenButton, 0, g_screen, &buttonRect) < 0)
        return false;
    if(SDL_FillRect(g_screen, &selectRect, selectColor) < 0)
        return false;

    buttonRect.x = g_screen->w - exitButton->w - 30;
    buttonRect.y = g_screen->h - exitButton->h - 30;
    buttonRect.w = exitButton->w;
    buttonRect.h = exitButton->h;

    selectRect = buttonRect;
    selectRect.x -= 60;
    selectRect.w = 60;
    selectColor = (menuChoice == MENU_EXIT) ? 0xffffffff : 0;

    if(SDL_BlitSurface(exitButton, 0, g_screen, &buttonRect) < 0)
        return false;
    if(SDL_FillRect(g_screen, &selectRect, selectColor) < 0)
        return false;

    buttonRect.x = 20;
    buttonRect.y = g_screen->h - uncheckedSound->h - 30;
    buttonRect.w = uncheckedSound->w;
    buttonRect.h = uncheckedSound->h;

    if(g_soundEnabled)
    {
        if(SDL_BlitSurface(checkedSound, 0, g_screen, &buttonRect) < 0)
        {
            return false;
        }
    } else {
        if(SDL_BlitSurface(uncheckedSound, 0, g_screen, &buttonRect) < 0)
        {
            return false;
        }
    }

    buttonRect.x = 20;
    buttonRect.y = g_screen->h - uncheckedMusic->h - uncheckedSound->h - 40;
    buttonRect.w = uncheckedSound->w;
    buttonRect.h = uncheckedSound->h;

    if(g_musicEnabled)
    {
        if(SDL_BlitSurface(checkedMusic, 0, g_screen, &buttonRect) < 0)
        {
            return false;
        }
    } else {
        if(SDL_BlitSurface(uncheckedMusic, 0, g_screen, &buttonRect) < 0)
        {
            return false;
        }
    }

    if(SDL_Flip(g_screen) < 0)
    {
        return false;
    }

    return true;
}

// Function menuLoop
//
// Handles event handling and updating during menu display.

void menuLoop()
{
    SDL_Event e;

    while(SDL_PollEvent(&e)) {
    switch(e.type) {
        case SDL_QUIT:
            g_inGame = false;
            g_quitGame = true;
            break;
            case SDL_KEYDOWN:
            switch (e.key.keysym.sym) {
            case SDLK_s:        // Press S to toggle sound.
                g_soundEnabled = !g_soundEnabled;
                FSOUND_PlaySound(FSOUND_FREE, buttonSound);
                break;
            case SDLK_m:        // Press M to toggle music.
                g_musicEnabled = !g_musicEnabled;
                if(g_musicEnabled)
                    FSOUND_SetLoopMode(g_musicChannel = FSOUND_PlaySound(FSOUND_FREE, g_backgroundMusic), FSOUND_LOOP_NORMAL);
                else
                    FSOUND_StopSound(g_musicChannel);
                if(g_soundEnabled)
                    FSOUND_PlaySound(FSOUND_FREE, buttonSound);
                break;
            case SDLK_UP:       // Press up to go up the menu.
                --menuChoice;
                if (menuChoice < 0)
                    menuChoice = NUM_MENU_CHOICES - 1;
                break;
            case SDLK_DOWN:     // Press down to go down the menu.
                ++menuChoice;
                if (menuChoice >= NUM_MENU_CHOICES)
                    menuChoice = 0;
                break;
            case SDLK_ESCAPE:   // Press escape to quit.
                g_inGame = false;
                g_quitGame = true;
                break;
            case SDLK_RETURN:   // Press return to select menu option.
                switch (menuChoice) {
                case MENU_ONE_PLAYER:
                    g_inGame = true;
                    g_players = 1;
                    break;
                case MENU_TWO_PLAYER:
                    g_inGame = true;
                    g_players = 2;
                    break;
                case MENU_EXIT:
                    g_quitGame = true;
                    break;
                default:
                    fprintf(stderr, "Invalid menu choice: %d", menuChoice);
                    break;
                }
                if(g_soundEnabled)
                    FSOUND_PlaySound(FSOUND_FREE, buttonSound);
                break;
            }
            break;
        }
    };

    if(SDL_BlitSurface(g_gameBGR, 0, g_screen, 0) < 0)
    {
        if(!drawErrorMenu)
        {
            writeLog("Failed to draw game background.\n");
        }

        drawErrorMenu = true;
    }

    if(!drawMenu())
    {
        if(!drawErrorMenu)
        {
            writeLog("Failed to draw menu.\n");
        }

        drawErrorMenu = true;
    }

    SDL_Delay(80);
}

// Function destroyMenu()
//
// Unloads the menu resources.

void destroyMenu()
{
    if(singlePlayerButton)
    {
        SDL_FreeSurface(singlePlayerButton);

        singlePlayerButton = 0;
    }

    if(splitScreenButton)
    {
        SDL_FreeSurface(splitScreenButton);

        splitScreenButton = 0;
    }

    if(exitButton)
    {
        SDL_FreeSurface(exitButton);

        exitButton = 0;
    }

    if(uncheckedSound)
    {
        SDL_FreeSurface(uncheckedSound);

        uncheckedSound = 0;
    }

    if(checkedSound)
    {
        SDL_FreeSurface(checkedSound);

        checkedSound = 0;
    }

    if(uncheckedMusic)
    {
        SDL_FreeSurface(uncheckedMusic);

        uncheckedMusic = 0;
    }

    if(checkedMusic)
    {
        SDL_FreeSurface(checkedMusic);

        checkedMusic = 0;
    }

    if(buttonSound)
    {
        FSOUND_Sample_Free(buttonSound);

        buttonSound = 0;
    }
}