#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Surface* maru;
SDL_Texture* maru_tex;
SDL_Surface* batsu;
SDL_Texture* batsu_tex;
SDL_Rect marubatsu_rect;

int mouse_x;
int mouse_y;

int stage[3][3];

void stage_wo_0(void)
{
    for (int tate=0; tate<3; tate++) {
        for (int yoko=0; yoko<3; yoko++) {
            stage[yoko][tate] = 0;
        }
    }
}

void stage_kousinn(void)
{
    // テキストを見ながら、for文を使って書き換えてみよう。
    if (0 <= mouse_y && mouse_y < 130) {
        if (0 <= mouse_x && mouse_x < 130) {
            stage[0][0] = 1;
        } else if (135 <= mouse_x && mouse_x < 265) {
            stage[1][0] = 1;
        } else if (270 <= mouse_x && mouse_x < 400) {
            stage[2][0] = 1;
        }
    } else if (135 <= mouse_y && mouse_y < 265) {
        if (0 <= mouse_x && mouse_x < 130) {
            stage[0][1] = 1;
        } else if (135 <= mouse_x && mouse_x < 265) {
            stage[1][1] = 1;
        } else if (270 <= mouse_x && mouse_x < 400) {
            stage[2][1] = 1;
        }
    } else if (270 <= mouse_y && mouse_y < 400) {
        if (0 <= mouse_x && mouse_x < 130) {
            stage[0][2] = 1;
        } else if (135 <= mouse_x && mouse_x < 265) {
            stage[1][2] = 1;
        } else if (270 <= mouse_x && mouse_x < 400) {
            stage[2][2] = 1;
        }
    }
}

void stage_kaku(void)
{
    SDL_Rect drawRect;

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    drawRect = (SDL_Rect){130,0,5,400};
    SDL_RenderFillRect(renderer, &drawRect);
    drawRect = (SDL_Rect){265,0,5,400};
    SDL_RenderFillRect(renderer, &drawRect);
    drawRect = (SDL_Rect){0,130,400,5};
    SDL_RenderFillRect(renderer, &drawRect);
    drawRect = (SDL_Rect){0,265,400,5};
    SDL_RenderFillRect(renderer, &drawRect);

    for (int tate=0; tate<3; tate++) {
        for (int yoko=0; yoko<3; yoko++) {
            drawRect = (SDL_Rect){(130+5)*yoko,(130+5)*tate,130,130};
            if (stage[yoko][tate] == 1) {
                SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);
            } else if (stage[yoko][tate] == 2) {
                SDL_RenderCopy(renderer, batsu_tex, &marubatsu_rect, &drawRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("○×ゲーム", 100, 100, 400, 400, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    maru = IMG_Load("data/maru.png");
    maru_tex = SDL_CreateTextureFromSurface(renderer, maru);

    batsu = IMG_Load("data/batsu.png");
    batsu_tex = SDL_CreateTextureFromSurface(renderer, batsu);

    marubatsu_rect = (SDL_Rect){0,0,130,130};

    stage_wo_0();

    while(1) {
        stage_kaku();

        if (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                mouse_x = event.button.x;
                mouse_y = event.button.y;
                stage_kousinn();
            }
        }
    }

    SDL_DestroyTexture(batsu_tex);
    SDL_FreeSurface(batsu);
    SDL_DestroyTexture(maru_tex);
    SDL_FreeSurface(maru);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    return 0;
}
