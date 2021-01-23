#include "road.h"
#include <iostream>

int LANE_WIDTH = 8 * 1.2 + 1; // ASSUMING 8 to be car width!
int TOP_MARGIN = 25;
int LANE_MARGIN = 10;

int STRIPE_LENGTH = 8;
int GAP_LENGTH = 4;

Road::Road(int lanes, SDL_Renderer* rend, SDL_Texture* texture):
    lanes(lanes), rend(rend), texture(texture)
{
    int w, h;
    SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);
    this->repeats = (h - TOP_MARGIN * 2) / (LANE_MARGIN + lanes * LANE_WIDTH);
    this->length = this->repeats * w;

    this->fill_texture();
}

void Road::fill_texture() {
    int w, h;
    SDL_QueryTexture(this->texture, NULL, NULL, &w, &h);

    SDL_Texture* prev_target = SDL_GetRenderTarget(rend);
    if (SDL_SetRenderTarget(this->rend, this->texture) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set render target: %s", SDL_GetError());
    }

    for (int i=0; i<this->repeats; i++) {
        int height = i * (lanes * LANE_WIDTH + LANE_MARGIN) + TOP_MARGIN;
        std::cout << "height: " << height << std::endl;

        SDL_SetRenderDrawColor(this->rend, 255, 255, 255, 255);
        SDL_RenderDrawLine(this->rend, 0, height, w, height);
        SDL_RenderDrawLine(this->rend, 0, height + lanes * LANE_WIDTH, w, height + lanes * LANE_WIDTH);

        for (int j=1; j<this->lanes; j++ ) {
            int n_stripes = w / (STRIPE_LENGTH + GAP_LENGTH);
            for (int k=0; k - 1 < n_stripes; k++) {
                SDL_RenderDrawLine(
                        this->rend,
                        k * (STRIPE_LENGTH + GAP_LENGTH), height + j * LANE_WIDTH,
                        k * (STRIPE_LENGTH + GAP_LENGTH) + STRIPE_LENGTH, height + j * LANE_WIDTH
                );
            }
        }
    }

    if (SDL_SetRenderTarget(this->rend, prev_target) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set render target: %s", SDL_GetError());
    }
}

void Road::display(SDL_Renderer* rend) {
    if (SDL_SetRenderTarget(rend, NULL) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't set render target: %s", SDL_GetError());
    }

    if (SDL_RenderCopy(rend, this->texture, NULL, NULL) != 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not copy the texture to the screen: %s", SDL_GetError());
    };
}

Road::~Road() {
    std::cout << "Destroying the texture" << std::endl;
    SDL_DestroyTexture(this->texture);
}
