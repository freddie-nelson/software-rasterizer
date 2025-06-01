#include "SDL3/SDL_stdinc.h"
#define SDL_MAIN_USE_CALLBACKS 1

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_video.h"

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *buffer = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Software Rasterizer", "1.0", "com.software-rasterizer");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Software Rasterizer", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    buffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!buffer) {
        SDL_Log("Couldn't create texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE; 
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS; 
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    // const double now = ((double)SDL_GetTicks()) / 1000.0;

    SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE_FLOAT);
    SDL_RenderClear(renderer);

    Uint32 *pixels;
    int pitch;
    SDL_LockTexture(buffer, NULL, (void **)&pixels, &pitch);

    for (int i = 0; i < buffer->w * buffer->h; i++) {
        Uint8 a = 255;
        Uint8 r = 255;
        Uint8 g = 0;
        Uint8 b = 0;
        pixels[i] = (a << 24U) | (b << 16U) | (g << 8U) | r;
    }

    SDL_UnlockTexture(buffer);

    if (!SDL_RenderTexture(renderer, buffer, NULL, NULL)) {
        SDL_Log("Couldn't render texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
}
