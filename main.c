#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct
{
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct
{
    int width, height;
    RGB *img;
} Img;

// Protótipos
void load(char *name, Img *pic);

// Carrega uma imagem para a struct Img
void load(char *name, Img *pic)
{
    int chan;
    pic->img = (unsigned char *)SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if (!pic->img)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

int main(int argc, char **argv)
{
    Img pic;
    char *p;
    if (argc == 2)
    {
        printf("loader [img] [fator reducao]\n");
        exit(1);
    }
    load(argv[1], &pic);
    int fatorReducao = strtol(argv[2], &p, 10);
    fatorReducao = 100 - fatorReducao;
    // printf("%d\n", fatorReducao);

    int alturaOriginal = pic.height;
    int alturaProporcional = alturaOriginal * (fatorReducao / 100.0);
    int alturaArredondada = alturaProporcional / 5 * 5; //arredonda com 5 + fator de reducao devido ao caracter
    int alturaReduzida = alturaArredondada / 5;         //usar fator de reducao
    printf("           Original | Proporcional  | Arredondada   | Reduzida\n");
    printf("ALTURAS -     %d    |     %d        |      %d       |   %d\n", alturaOriginal, alturaProporcional, alturaArredondada, alturaReduzida);
    int larguraOriginal = pic.width;
    int larguraProporcional = larguraOriginal * (fatorReducao / 100.0);
    int larguraArredondada = larguraProporcional / 4 * 4;   //mesma coisa da altura
    int larguraReduzida = larguraArredondada / 4;
    printf("LARGURAS -    %d    |     %d        |      %d       |   %d\n", larguraOriginal, larguraProporcional, larguraArredondada, larguraReduzida);

    RGB pixelMediano;
    pixelMediano.b = pixelMediano.g = pixelMediano.r;

    RGB novoRGB[alturaReduzida * larguraReduzida];
    Img novaImg;
    novaImg.height = alturaReduzida;
    novaImg.width = larguraReduzida;
    novaImg.img = novoRGB;

    RGB(*picMatriz) //transforma array de pixels em matriz
    [pic.width] = (RGB(*)[pic.width])pic.img;

    RGB(*novaImgMatriz)
    [novaImg.width] = (RGB(*)[novaImg.width])novaImg.img;

    //acinzentar pixels com media do rgb
    int cinza = 0;
    for (int i = 0; i < alturaOriginal; i++)
    {
        for (int j = 0; j < larguraOriginal; j++)
        {
            cinza = (0.3 * picMatriz[i][j].r + 0.59 * picMatriz[i][j].g + 0.11 * picMatriz[i][j].b);
            picMatriz[i][j].r = picMatriz[i][j].g = picMatriz[i][j].b = cinza;
        }
    }

    //diminui a imagem
    int cinzaMediano = 0;
    int index = 0;
    //ta cortando o final e a parte de baixo da imagem quando fator de reducao for diferente de 0
    double aux = 2 -  (fatorReducao / 100.0);
    int preSaltoAltura = 5 * aux;
    int preSaltoLargura = 4 * aux;
    for (int i = 0, saltoAltura = i; i < alturaReduzida; i++, saltoAltura = i * (5 * aux))
    {
        // printf("%d - ",saltoAltura);
        for (int j = 0, saltoLargura = j; j < larguraReduzida; j++, saltoLargura = j * (4 * aux))
        {
            //dois primeiros for vai "pulando pixels" pra fazer cinza mediado do tamanho do caracter (5x4)
            for (int altura = saltoAltura; altura < saltoAltura + 5; altura++)
            {
                for (int largura = saltoLargura; largura < saltoLargura + 4; largura++)
                {
                    //percorre os 20 pixels do caracter somando o valor rgb do cinza
                    // printf("(%d,%d) - ", altura, largura);
                    cinzaMediano = cinzaMediano + picMatriz[altura][largura].r;
                }
                // printf("\n");
            }
            //faz a media do somatorio dos cinzas e seta num novo pixel
            cinzaMediano = cinzaMediano / 20;
            pixelMediano.r = pixelMediano.b = pixelMediano.g = cinzaMediano;
            cinzaMediano = 0;

            novoRGB[index] = pixelMediano;
            index++;
        }
    }
    SOIL_save_image("outOriginal.bmp", SOIL_SAVE_TYPE_BMP, pic.width, pic.height,
                    3, (const unsigned char *)pic.img);
    SOIL_save_image("outNovoReduzido.bmp", SOIL_SAVE_TYPE_BMP, novaImg.width, novaImg.height,
                    3, (const unsigned char *)novaImg.img);
    // Exemplo: gravando um arquivo saida.html
    FILE *arq = fopen("saida.html", "w"); // criar o arquivo: w
    if (arq == NULL)                      // 0, falso
    {
        printf("Erro abrindo arquivo de saída\n");
        exit(1);
    }

    //escalas de cinza
    char escala0 = ' ';
    char escala1 = '.';
    char escala2 = ',';
    char escala3 = ':';
    char escala4 = ';';
    char escala5 = 'o';
    char escala6 = 'x';
    char escala7 = '$';
    char escala8 = '#';
    char escala9 = '@';

    //escreve o arquivo html
    fprintf(arq, "<html><head></head><body style=\"background: black\"; leftmargin=0 topmargin=0><style>pre {color: white;font-family: Courier;font-size: 8px;}</style><pre>");
    for (int i = 0; i < novaImg.height; i++)
    {
        for (int j = 0; j < novaImg.width; j++)
        {
            cinza = novaImgMatriz[i][j].r;
            if (cinza < 26)
            {
                fprintf(arq, "%c", escala0);
            }
            else if (cinza < 51)
            {
                fprintf(arq, "%c", escala1);
            }
            else if (cinza < 77)
            {
                fprintf(arq, "%c", escala2);
            }
            else if (cinza < 102)
            {
                fprintf(arq, "%c", escala3);
            }
            else if (cinza < 128)
            {
                fprintf(arq, "%c", escala4);
            }
            else if (cinza < 153)
            {
                fprintf(arq, "%c", escala5);
            }
            else if (cinza < 179)
            {
                fprintf(arq, "%c", escala6);
            }
            else if (cinza < 204)
            {
                fprintf(arq, "%c", escala7);
            }
            else if (cinza < 230)
            {
                fprintf(arq, "%c", escala8);
            }
            else
            {
                fprintf(arq, "%c", escala9);
            }
        }
        fprintf(arq, "\n"); //quebra a linha
    }
    fprintf(arq, "\n</pre>\n");
    fprintf(arq, "</body>\n");
    fprintf(arq, "</html>\n");
    fclose(arq);
    free(pic.img);
}
