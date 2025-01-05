#include <string.h>

#define SDL_MAIN_USE_CALLBACKS 1 // Use the callbacks instead of main()
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

// We will use this renderer to draw into this window every frame
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *helloTexture = NULL;
static SDL_Texture *cyrillicTexture = NULL;

// This function runs once at startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Initialize the TTF library
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize TTF: %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Cyrillic text in C and SDL3",
        500, 500, 0, &window, &renderer)) //
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    TTF_Font *arialFont = TTF_OpenFont("assets/fonts/arial.ttf", 48);

    const char *helloText = "Hello, World!";
    SDL_Color helloTextColor = (SDL_Color){ 255, 255, 255 };
    int helloAmount = strlen(helloText);
    SDL_Surface *helloSurface = TTF_RenderText_Blended(arialFont, helloText, helloAmount, helloTextColor);
    helloTexture = SDL_CreateTextureFromSurface(renderer, helloSurface);
    SDL_DestroySurface(helloSurface);

    const char *cyrillicText = "Привет, Мир!";
    SDL_Color cyrillicTextColor = (SDL_Color){ 20, 200, 20 };
    SDL_Surface *cyrillicSurface = TTF_RenderText_Blended(arialFont, cyrillicText, 21, cyrillicTextColor);
    cyrillicTexture = SDL_CreateTextureFromSurface(renderer, cyrillicSurface);
    SDL_DestroySurface(cyrillicSurface);

    return SDL_APP_CONTINUE; // Carry on with the program!
}

// This function runs when a new event (mouse input, keypresses, etc) occurs
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  // End the program, reporting success to the OS
    }
    return SDL_APP_CONTINUE; // Carry on with the program!
}

// This function runs once per frame, and is the heart of the program
SDL_AppResult SDL_AppIterate(void *appstate)
{
    // Create a rectangle to hold the texture dimensions
    SDL_FRect rect;

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw "Hello, World"
    SDL_GetTextureSize(helloTexture, &rect.w, &rect.h);
    rect.x = 10.f;
    rect.y = 10.f;
    // Draw the text
    SDL_RenderTexture(renderer, helloTexture, NULL, &rect);

    // Draw a cyrillic text
    SDL_GetTextureSize(cyrillicTexture, &rect.w, &rect.h);
    rect.x = 10.f;
    rect.y = 70.f;
    // Draw the text
    SDL_RenderTexture(renderer, cyrillicTexture, NULL, &rect);

    // Update the screen
    SDL_RenderPresent(renderer);
    return SDL_APP_CONTINUE; // Carry on with the program!
}

// This function runs once at shutdown
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    // SDL will clean up the window/renderer for us
    TTF_Quit();
    SDL_Quit();
}
