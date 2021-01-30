#include "road.h"
#include "math.h"
#include <iostream>

int LANE_WIDTH = 8 * 1.2 + 1; // ASSUMING 8 to be car width!
int TOP_MARGIN = 25;
int LANE_MARGIN = 10;

int STRIPE_LENGTH = 8;
int GAP_LENGTH = 4;

typedef Eigen::Vector2f vec2f;

Road::Road(int lanes, SDL_Manager* sdl): sdl(sdl), lanes(lanes) {
    this->repeats = (sdl->h - TOP_MARGIN * 2) / (LANE_MARGIN + lanes * LANE_WIDTH);
    this->length = this->repeats * sdl->w;

    this->fill_texture();
}

void Road::fill_texture() {
    this->sdl->draw_to_road_texture();
    int w = this->sdl->w;
    int h = this->sdl->h;

    for (int i=0; i<this->repeats; i++) {
        int height = i * (lanes * LANE_WIDTH + LANE_MARGIN) + TOP_MARGIN;

        SDL_SetRenderDrawColor(this->sdl->rend, 255, 255, 255, 255);
        SDL_RenderDrawLine(this->sdl->rend, 0, height, w, height);
        SDL_RenderDrawLine(this->sdl->rend, 0, height + lanes * LANE_WIDTH, w, height + lanes * LANE_WIDTH);

        for (int j=1; j<this->lanes; j++ ) {
            int n_stripes = w / (STRIPE_LENGTH + GAP_LENGTH);
            for (int k=0; k - 1 < n_stripes; k++) {
                SDL_RenderDrawLine(
                        this->sdl->rend,
                        k * (STRIPE_LENGTH + GAP_LENGTH), height + j * LANE_WIDTH,
                        k * (STRIPE_LENGTH + GAP_LENGTH) + STRIPE_LENGTH, height + j * LANE_WIDTH
                );
            }
        }
    }
}

vec2f Road::get_display_position(vec2f pos) {
    int w = this->sdl->w;
    int h = this->sdl->h;

    vec2f ret_pos(
        fmod(pos(0), w),
        (int)(pos(0) / w) * (this->lanes * LANE_WIDTH + LANE_MARGIN) + TOP_MARGIN + pos(1) + 3
    );

    return ret_pos;
}
