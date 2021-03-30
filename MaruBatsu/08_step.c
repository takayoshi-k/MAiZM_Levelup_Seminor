#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>

SDL_Window* window;
SDL_Renderer* render;

// テキストを見て、〇と×の画像を読み込ませるための変数をここに記載してみましょう。

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

    SDL_RenderPresent(render);
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // テキストを見て、SDL_imageを使うための準備のコードを書いてみよう。

    window = SDL_CreateWindow("○×ゲーム", 100, 100, 400, 400, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // テキストを見て、〇と×の画像を読み込ませるプログラムを書いてみよう。

    stage_kaku();

    SDL_Delay(3000);

    // テキストを見て、読み込んだ〇と×の画像を片付けるコードを書いてみよう。

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    // テキストを見て、SDL_imageを片付けるコードを書いてみよう。

    SDL_Quit();
    return 0;
}