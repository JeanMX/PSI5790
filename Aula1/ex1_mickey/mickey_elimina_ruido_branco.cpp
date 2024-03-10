/*******************************************/
/* Exercício 1 - Aula 1 - PSI5790          */
/* Nome: Jean Carlos Mello Xavier Faria    */
/* Nusp: 11259628                          */
/*******************************************/

#include <cekeikon.h>

int main()
{
    Mat_ <GRY> imagem;
    le(imagem, "mickey.bmp");

    for(int i = 1; i < (imagem.rows - 2); i++)
    {
        for(int j = 1; j < (imagem.cols - 2); j++)
        {
            if((imagem((i-1), j) == 0) && imagem(i+1, j) == 0)
            {
                imagem(i,j) = 0;
            }
        }
    }

    imp(imagem, "Mickey_sem_ruido_branco.bmp");
}