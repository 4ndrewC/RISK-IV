#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

typedef uint16_t u16;

const int WIDTH = 256;
const int HEIGHT = 256;

// Create a 2D vector to store pixel data as 16-bit hex codes
vector<vector<u16>> pixels(HEIGHT, vector<u16>(WIDTH));

// Function to set a pixel in the SDL window based on a 16-bit hex code
void setPixelFromHex(SDL_Renderer* renderer, int x, int y, uint16_t hex) {
    // Extract color components from the 16-bit hex code (assuming RGB order)
    Uint8 r = ((hex >> 8) & 0xFF);
    Uint8 g = (hex & 0xFF);
    Uint8 b = 0; // Assuming unused bits are 0 (modify for different color formats)

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

void init(){
    // Set all pixels to black initially (0x0000)
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            pixels[y][x] = 0x0000;
        }
    }
}

void display_run() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("16-bit Hex Screen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Could not create window! SDL Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Create renderer for the window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Could not create renderer! SDL Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Main loop
    Uint32 then = SDL_GetTicks();
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Update pixel data (replace with your logic to update hex codes)
        // For now, let's change a single pixel to red each frame

        int frameCount = SDL_GetTicks() / 1000;
        int x = frameCount % WIDTH;
        int y = frameCount % HEIGHT;

        // Render the updated window based on the hex codes
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                setPixelFromHex(renderer, x, y, pixels[y][x]);
            }
        }

        // Render the updated window
        SDL_RenderPresent(renderer);

        // Frame rate control
        u16 fcontrol = 1000/30;
        Uint32 now = SDL_GetTicks();
        Uint32 elapsed = now - then;
        if (elapsed < fcontrol) {
            SDL_Delay(fcontrol - elapsed);
        }
        then = now;
    }

    // Cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
