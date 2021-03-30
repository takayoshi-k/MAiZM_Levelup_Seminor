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

int mouse_x;
int mouse_y;

// テキストを見ながら、ステージの3x3のマスの中身を覚えておく配列変数を書いてみよう。

// テキストを見ながら、作った3x3の配列変数の全ての値を0にする関数を書いてみよう。


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
            // テキストを見ながら、配列の値にしたがって画像を表示するように修正してみよう。
            // 各変数の中身は、
            //    0が入っていたらそのマスは空っぽ（何も書かない）
            //    1が入っていたらそのマスには〇が入っている
            //    2が入っていたらそのマスには×が入っている
            // となるようにします。
            SDL_RenderCopy(render, maru_tex, &marubatsu_rect, &drawRect);
        }
    }

    SDL_RenderPresent(render);
}

int main(int argc, char **argv)
{
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("○×ゲーム", 100, 100, 400, 400, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    maru = IMG_Load("data/maru.png");
    maru_tex = SDL_CreateTextureFromSurface(render, maru);

    batsu = IMG_Load("data/batsu.png");
    batsu_tex = SDL_CreateTextureFromSurface(render, batsu);

    marubatsu_rect = (SDL_Rect){0,0,130,130};

    // テキストを見ながら、作成した配列変数を0にする関数を呼び出してみよう。

    stage_kaku();

    while(1) {
        if (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                SDL_Rect rect;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                rect = (SDL_Rect){mouse_x, mouse_y, 130, 130};
                SDL_RenderCopy(render, batsu_tex, &marubatsu_rect, &rect);
                SDL_RenderPresent(render);
            }
        }
    }

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