/**
 * bmp_emboss.c -- программа для наложения фильтра "Барельеф" на 
 * изображение в формате BMP
 *
 * Copyright (c) 2020, Vladislav Shkut <shkut@cs.petrsu.ru>
 *
 * This code is licensed under a MIT-style license.
 */ 

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

/* Накладывает на изображение фильтр "Барельеф" */
void bmp_emboss(bmp_image image)
{
    unsigned int i, j, m, n, k;

    /* Границы матрицы 5 х 5 */
    unsigned int x1, y1, x2, y2;
    
    /* Получаем линейные размеры изображения */
    unsigned int w = image.header.width;
    unsigned int h = image.header.height;

    /* 5 х 5 матрица весовых коэффициентов для фильтра "Барельеф" */
    double matrix[5][5] = 
    {
        {-1, -1, -1, -1,  0},
        {-1, -1, -1,  0,  1},
        {-1, -1,  0,  1,  1},
        {-1,  0,  1,  1,  1},
        { 0,  1,  1,  1,  1}
    };

    /* Создадим вспомогательное изображение 
        для записи промежуточных вычислений значений пикселей */
    bmp_image help_image;
    help_image.header.width = w;
    help_image.header.height = h;
    int help_image_size = w * h;

    /* Выделим необходимую память. Завершение программы, если не удалось выделить память */
    if ((help_image.pixel_array = (double *) malloc(help_image_size * sizeof(double) * 3)) == NULL) {
        fprintf(stderr, "No memory can be allocated, exiting.. \n");
        exit(EXIT_FAILURE);
    }

    /* Обнуляем значения всех пикселей вспомогательного изображения */
    /* Для всех строк пикселей */
    for (i = 0; i < h; i++) {
        /* Для каждого пикселя */
        for(j = 0; j < w; j++) {
            for (k = 0; k <= 2; k++) {
                help_image.pixel_array[k * h * w + i * w + j] = 0;
            }
        }
    }

    /* 
     * Заменим каждый пиксель вспомогательного изображения
     *  на увеличенную на 0.5 сумму произведений цветов соседних точек
     *  в пределах матрицы 5 x 5 на весовые коэффициенты в соответствии с матрицей
    */
    /* Для всех строк пикселей */
    for (i = 0; i < h; i++)
        /* Для каждого пикселя */
        for(j = 0; j < w; j++) {
            /* Ограничение матрицы 5 х 5, чтобы не выйти за ее границы */
            y1 = i - 2;
            x1 = j - 2;
            y2 = i + 2;
            x2 = j + 2;
            if (i == 0 || i == 1)
                y1 = 0;
            if (i == h - 2 || i == h - 1)
                y2 = h - 1;
            if (j == 0 || j == 1)
                x1 = 0;
            if (j == w - 2 || j == w - 1)
                x2 = w - 1;
        /* Сумма произведений цветов соседних точек
         *  в пределах матрицы 5 x 5 на весовые коэффициенты в соответствии с матрицей
        */
            for (m = y1; m <= y2; m++)
                for (n = x1; n <= x2; n++) {
                    for (k = 0; k <= 2; k++) {
                        help_image.pixel_array[k * h * w + i * w + j] += image.pixel_array[k * h * w + m * w + n] * matrix[m - i + 2][n - j + 2];
                    }
                }
        }

    /* Запишем значения пикселей нового изображения, увеличенные на 0.5 */
    /* Для всех строк пикселей */
    for (i = 0; i < h; i++)
        /* Для каждого пикселя */
        for(j = 0; j < w; j++) {
            for (k = 0; k <= 2; k++) {
            image.pixel_array[k * h * w + i * w + j] = help_image.pixel_array[k * h * w + i * w + j] + 0.5;
            if (image.pixel_array[k * h * w + i * w + j] > 1)
                image.pixel_array[k * h * w + i * w + j] = 1;
            else
                if (image.pixel_array[k * h * w + i * w + j] < 0)
                    image.pixel_array[k * h * w + i * w + j] = 0;
            }
        }

    /* Освобождаем выделенную память */
    free(help_image.pixel_array);
}
