#include <stdio.h>

int hito;

// テキストを見て、ここに変数hitoの数字によって表示する内容が異なる関数を追加してみよう。

int main(int argc, char **argv)
{
    hito = 0;

    // テキストを見て、
    // 追加した関数を使って0～4全ての人にHelloを表示するプログラムを書いてみよう。
    if (hito == 0) {
        printf("Hello A-san\n");
    } else if (hito == 1) {
        printf("Hello B-san\n");
    } else if (hito == 2) {
        printf("Hello C-san\n");
    } else if (hito == 3) {
        printf("Hello D-san\n");
    } else if (hito == 4) {
        printf("Hello E-san\n");
    }

    return 0;
}