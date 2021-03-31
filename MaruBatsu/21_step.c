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

SDL_Surface* win_image;
SDL_Texture* win_tex;
SDL_Surface* draw_image;
SDL_Texture* draw_tex;
SDL_Rect windraw_rect;

int mouse_x;
int mouse_y;

int stage[3][3];

int player;
int winner;

// テキストを見ながら、効果音のための変数を追加してみよう。

void stage_wo_0(void)
{
    for (int tate=0; tate<3; tate++) {
        for (int yoko=0; yoko<3; yoko++) {
            stage[tate][yoko] = 0;
        }
    }
}

void stage_kousinn(void)
{
    for (int tate=0; tate<3; tate++) {
        for (int yoko=0; yoko<3; yoko++) {
            if ((135*tate) <= mouse_y && mouse_y < (130+135*tate)) {
                if ((135*yoko) <= mouse_x && mouse_x < (130+135*yoko)) {
                    if (stage[tate][yoko] == 0) {
                        stage[tate][yoko] = player;
                        // テキストを見ながら、ここで効果音を鳴らしてみよう。
                        if (player == 1) {
                            player = 2;
                        } else if (player == 2) {
                            player = 1;
                        }
                    }
                }
            }
        }
    }
}

void winnner_hantei(void)
{
    if (    (1 == stage[0][0]) && (1 == stage[0][1]) && (1 == stage[0][2])
       ||   (1 == stage[1][0]) && (1 == stage[1][1]) && (1 == stage[1][2])
       ||   (1 == stage[2][0]) && (1 == stage[2][1]) && (1 == stage[2][2])

       ||   (1 == stage[0][0]) && (1 == stage[1][0]) && (1 == stage[2][0])
       ||   (1 == stage[0][1]) && (1 == stage[1][1]) && (1 == stage[2][1])
       ||   (1 == stage[0][2]) && (1 == stage[1][2]) && (1 == stage[2][2])

       ||   (1 == stage[0][0]) && (1 == stage[1][1]) && (1 == stage[2][2])
       ||   (1 == stage[0][2]) && (1 == stage[1][1]) && (1 == stage[2][0]) ) {
            winner = 1;
    } else if ( (2 == stage[0][0]) && (2 == stage[0][1]) && (2 == stage[0][2])
             || (2 == stage[1][0]) && (2 == stage[1][1]) && (2 == stage[1][2])
             || (2 == stage[2][0]) && (2 == stage[2][1]) && (2 == stage[2][2])

             || (2 == stage[0][0]) && (2 == stage[1][0]) && (2 == stage[2][0])
             || (2 == stage[0][1]) && (2 == stage[1][1]) && (2 == stage[2][1])
             || (2 == stage[0][2]) && (2 == stage[1][2]) && (2 == stage[2][2])

             || (2 == stage[0][0]) && (2 == stage[1][1]) && (2 == stage[2][2])
             || (2 == stage[0][2]) && (2 == stage[1][1]) && (2 == stage[2][0]) ) {
            winner = 2;
    } else {
        winner = 3;
        for (int tate=0; tate<3; tate++) {
            for (int yoko=0; yoko<3; yoko++) {
                if (stage[tate][yoko] == 0) {
                    winner = 0;
                }
            }
        }
    }
}

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
            if (stage[tate][yoko] == 1) {
                SDL_RenderCopy(render, maru_tex, &marubatsu_rect, &drawRect);
            } else if (stage[tate][yoko] == 2) {
                SDL_RenderCopy(render, batsu_tex, &marubatsu_rect, &drawRect);
            }
        }
    }

    if (winner != 0) {
        drawRect = (SDL_Rect){(400-390)/2, (400-150)/2, 390, 150};
        if (winner == 3) {
            SDL_RenderCopy(render, draw_tex, &windraw_rect, &drawRect);
        }else{
            SDL_RenderCopy(render, win_tex, &windraw_rect, &drawRect);
            drawRect = (SDL_Rect){(400-390)/2+5, (400-150)/2+5, 130, 130};
            if (winner == 1){
                SDL_RenderCopy(render, maru_tex, &marubatsu_rect, &drawRect);
            }else{
                SDL_RenderCopy(render, batsu_tex, &marubatsu_rect, &drawRect);
            }
        }
    }

    SDL_RenderPresent(render);
}

int main(int argc, char **argv)
{
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_PNG);

    // テキストを見ながら、効果音を扱うためにSDL_mixerの準備のコードを書いてみよう。

    window = SDL_CreateWindow("○×ゲーム", 100, 100, 400, 400, SDL_WINDOW_SHOWN);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    maru = IMG_Load("data/maru.png");
    maru_tex = SDL_CreateTextureFromSurface(render, maru);

    batsu = IMG_Load("data/batsu.png");
    batsu_tex = SDL_CreateTextureFromSurface(render, batsu);

    marubatsu_rect = (SDL_Rect){0,0,130,130};

    win_image = IMG_Load("data/win.png");
    win_tex = SDL_CreateTextureFromSurface(render, win_image);

    draw_image = IMG_Load("data/draw.png");
    draw_tex = SDL_CreateTextureFromSurface(render, draw_image);

    windraw_rect = (SDL_Rect){0, 0, 390, 150};

    // テキストを見ながら、効果音の音声ファイルを読み込むコードを書いてみよう。

    stage_wo_0();

    player = 1;
    winner = 0;

    while(1) {
        stage_kaku();

        if (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (winner == 0) {
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    stage_kousinn();
                }
            }
        }

        winnner_hantei();
    }

    // テキストを見ながら、読み込んだ効果音を片付けるコードを書いてみよう。

    SDL_DestroyTexture(draw_tex);
    SDL_FreeSurface(draw_image);
    SDL_DestroyTexture(win_tex);
    SDL_FreeSurface(win_image);
    SDL_DestroyTexture(batsu_tex);
    SDL_FreeSurface(batsu);
    SDL_DestroyTexture(maru_tex);
    SDL_FreeSurface(maru);

    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    // テキストを見ながら、SDL_mixerを片付けるコードを書いてみよう。

    IMG_Quit();
    SDL_Quit();
    return 0;
}