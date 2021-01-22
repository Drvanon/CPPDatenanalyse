#include "road.h"
#include <iostream>

int LANE_WIDTH = 8 * 1.2 + 1; // ASSUMING 8 to be car width!
int TOP_MARGIN = 25;
int LANE_MARGIN = 10;

int STRIPE_LENGTH = 8;
int GAP_LENGTH = 4;

Road::Road(int lanes): lanes(lanes) {
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto screen_height = DM.h;
    auto screen_width = DM.w;
    this->repeats = (screen_height - TOP_MARGIN * 2) / (LANE_MARGIN + lanes * LANE_WIDTH);
    this->length = this->repeats * screen_width;
}

void Road::display(SDL_Renderer* renderer) {
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int screen_height = DM.h;
    int screen_width = DM.w;

    for (int i=0; i<this->repeats; i++) {
        int height = i * (LANE_WIDTH + LANE_MARGIN)  + TOP_MARGIN;
        std::cout << "height: " << height << std::endl;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, 0, height, screen_width, height);
        SDL_RenderDrawLine(renderer, 0, height + LANE_WIDTH, screen_width, height + LANE_WIDTH);

        for (int j=1; j + 1 < this->lanes; j++ ) {
            int n_stripes = screen_width / (STRIPE_LENGTH + GAP_LENGTH);
            for (int k=0; k < n_stripes; k++) {
                SDL_RenderDrawLine(renderer,
                        0, height + j * LANE_WIDTH,
                        screen_width, height + j * LANE_WIDTH
                );
            }
        }
    }

}
