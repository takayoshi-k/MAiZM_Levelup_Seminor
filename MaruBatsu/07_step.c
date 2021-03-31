#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* render;

// テキストを見て、ここに画面を描く関数を記載してみよう。

int main(int argc, char **argv)
{
    // テキストを見て、この変数を作成する関数側に移動させよう。
    SDL_Rect drawRect;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    window = SDL_CreateWindow("○×ゲーム", 100, 100, 400, 400, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // テキストを見て、以下の部分を作成する関数に移動させて、作った関数を呼び出してみよう。
    SDL_SetRenderDrawColor(render, 128, 128, 128, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);

    SDL_SetRenderDrawColor(render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    drawRect=(SDL_Rect){130,0,5,400};
    SDL_RenderFillRect(render, &drawRect);
    drawRect=(SDL_Rect){265,0,5,400};
    SDL_RenderFillRect(render, &drawRect);
    drawRect=(SDL_Rect){0,130,400,5};
    SDL_RenderFillRect(render, &drawRect);
    drawRect=(SDL_Rect){0,265,400,5};
    SDL_RenderFillRect(render, &drawRect);

    SDL_RenderPresent(render);

    SDL_Delay(3000);

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}