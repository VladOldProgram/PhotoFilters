/**
 * filter.c -- программа для наложения фильтров на 
 * изображение в формате BMP
 *
 * Copyright (c) 2020, Vladislav Shkut <shkut@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{    
    int N;
 
    bmp_image image;
    
    if (argc < 3) {
        fprintf(stderr, "Usage: %s sourcefile destfile\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    image = bmp_read(argv[1]);

    fprintf(stdout, "Введите номер фильтра для наложения: \n");
    fprintf(stdout, "1 - Оттенки серого\n");
    fprintf(stdout, "2 - Барельеф\n");
    scanf("%d", &N);

    if (N == 1 || 2) {
        if (N == 1)
            bmp_gray(image);
        if (N == 2) {
            bmp_gray(image);
            bmp_emboss(image);
        }
    }
    else {
        fprintf(stderr, "Некорректно указан номер фильтра\n");
        exit(EXIT_FAILURE);
    }

    bmp_write(argv[2], image);
    
    fprintf(stdout, "Фильтр успешно применен.\n");

    return 0;
}
