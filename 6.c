#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double get_value(char card[])
{
    if (strcmp(card, "A") == 0) return 1;
    if (strcmp(card, "J") == 0) return 0.5;
    if (strcmp(card, "Q") == 0) return 0.5;
    if (strcmp(card, "K") == 0) return 0.5;

    return atof(card);   // 2~10
}

int main()
{
    char card[10];
    double X = 0;
    double Y = 0;

    // X玩家
    for (int i = 0; i < 3; i++)
    {
        scanf("%s", card);
        X += get_value(card);
    }

    // Y玩家
    for (int i = 0; i < 3; i++)
    {
        scanf("%s", card);
        Y += get_value(card);
    }

    if (X > 10.5) X = 0;
    if (Y > 10.5) Y = 0;

    printf("%g\n", X);
    printf("%g\n", Y);

    if (X > Y)
        printf("X Win\n");
    else if (Y > X)
        printf("Y Win\n");
    else
        printf("Tie\n");

    return 0;
}