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

    // テキストを見ながら、以下のコードをfor文を使って書き直してみよう。
    drawRect = (SDL_Rect){0,0,130,130};
    SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);
    drawRect = (SDL_Rect){0,135,130,130};
    SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);
    drawRect = (SDL_Rect){0,270,130,130};
    SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);

    drawRect = (SDL_Rect){135,0,130,130};
    SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);
    drawRect = (SDL_Rect){135,135,130,130};
    SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);
    drawRect = (SDL_Rect){135,270,130,130};
    SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);

    drawRect = (SDL_Rect){270,0,130,130};
    SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);
    drawRect = (SDL_Rect){270,135,130,130};
    SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);
    drawRect = (SDL_Rect){270,270,130,130};
    SDL_RenderCopy(renderer, maru_tex, &marubatsu_rect, &drawRect);

    SDL_RenderPresent(renderer);
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("○×ゲーム", 100, 100, 400, 400, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    maru = IMG_Load("data/maru.png");
    maru_tex = SDL_CreateTextureFromSurface(renderer, maru);

    batsu = IMG_Load("data/batsu.png");
    batsu_tex = SDL_CreateTextureFromSurface(renderer, batsu);

    marubatsu_rect = (SDL_Rect){0,0,130,130};

    stage_kaku();

    SDL_Delay(3000);

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
