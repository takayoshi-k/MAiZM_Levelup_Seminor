#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* render;

SDL_Surface* maru;
SDL_Texture* maru_tex;
SDL_Surface* batsu;
SDL_Texture* batsu_tex;
SDL_Rect marubatsu_rect;

// テキストを見ながら、マウスのイベントが起きた時のマウスの位置を覚えておく変数を追加しよう。

void stage_kaku(void)
{
    SDL_Rect drawRect;

    SDL_SetRenderDrawColor(render, 128, 128, 128, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);

    SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    drawRect = (SDL_Rect){130,0,5,400};
    SDL_RenderFillRect(render, &drawRect);
    drawRect = (SDL_Rect){265,0,5,400};
    SDL_RenderFillRect(render, &drawRect);
    drawRect = (SDL_Rect){0,130,400,5};
    SDL_RenderFillRect(render, &drawRect);
    drawRect = (SDL_Rect){0,265,400,5};
    SDL_RenderFillRect(render, &drawRect);

    for (int tate=0; tate<3; tate++) {
        for (int yoko=0; yoko<3; yoko++) {
            drawRect = (SDL_Rect){(130+5)*yoko,(130+5)*tate,130,130};
            SDL_RenderCopy(render, maru_tex, &marubatsu_rect, &drawRect);
        }
    }

    SDL_RenderPresent(render);
}

int main(int argc, char **argv)
{
    // テキストを見ながら、マウスのイベントを受けるための変数を追加しよう。

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("○×ゲーム", 100, 100, 400, 400, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    maru = IMG_Load("data/maru.png");
    maru_tex = SDL_CreateTextureFromSurface(render, maru);

    batsu = IMG_Load("data/batsu.png");
    batsu_tex = SDL_CreateTextureFromSurface(render, batsu);

    marubatsu_rect = (SDL_Rect){0,0,130,130};

    stage_kaku();

    // テキストを見ながら、マウスのイベントを取得して、
    // その場所に×を表示するプログラムを書いてみよう。
    // SDL_Delay()は待つ必要が無くなるので削除しよう。

    SDL_Delay(3000);

    SDL_DestroyTexture(batsu_tex);
    SDL_FreeSurface(batsu);
    SDL_DestroyTexture(maru_tex);
    SDL_FreeSurface(maru);

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
    return 0;
}