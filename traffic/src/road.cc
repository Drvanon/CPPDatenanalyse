#include "traffic.h"
#include "car.h"

int LANE_WIDTH = CAR_WIDTH * 1.2 + 1;
int TOP_MARGIN = 25;
int LANE_MARGIN = 10;

int STRIPE_LENGTH = 8;
int GAP_LENGTH = 4;

Road::Road(int lanes): lanes(lanes) {
   this->repeats = (SCREEN_HEIGHT - TOP_MARGIN * 2) / (LANE_MARGIN + lanes * LANE_WIDTH);
   this->length = this->repeats * SCREEN_WIDTH;
}

void Road::display(SDL_Renderer* renderer) {
    for (int i=0; i<this->repeats; i++) {
        int height = i * (LANE_WIDTH + LANE_MARGIN)  + TOP_MARGIN;
        SDL_RenderDrawLine(renderer, 0, height, SCREEN_WIDTH, height);
        SDL_RenderDrawLine(renderer, 0, height + LANE_WIDTH, SCREEN_WIDTH, height);

        for (int j=1; j + 1 < this->lanes; j++ ) {
            int n_stripes = SCREEN_WIDTH / (STRIPE_LENGTH + GAP_LENGTH);
            for (int k=0; k < n_stripes; k++) {
                SDL_RenderDrawLine(renderer,
                        0, height + j * LANE_WIDTH,
                        SCREEN_WIDTH, height + j * LANE_WIDTH
                );
            }
        }
    }

}
