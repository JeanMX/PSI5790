/*******************************************/
/* Exercício 1 - Aula 2 - PSI5790          */
/* Nome: Jean Carlos Mello Xavier Faria    */
/* Nusp: 11259628                          */
/*******************************************/

#include <cekeikon.h>

int main() {
    Mat_<GRY> in_1, in_2;
    Mat_<GRY> dst_1, dst_2; 
    le(in_1,"fever-1.pgm");
    le(in_2,"fever-2.pgm");

    medianBlur(in_1,dst_1, 15);
    medianBlur(in_2,dst_2, 15);
    
    Mat_<COR> out_1, out_2; 
    Mat_<COR> in_conv_1, in_conv_2;
    
    converte(dst_1,out_1);
    converte(dst_2,out_2);          
    
    converte(in_1,in_conv_1);
    converte(in_2,in_conv_2);

    Mat_<COR> combined_hor_1, combined_hor_2;
    Mat_<COR> combined_ver;

    hconcat(in_conv_1, out_1, combined_hor_1);
    hconcat(in_conv_2, out_2, combined_hor_2);

    vconcat(combined_hor_1, combined_hor_2, combined_ver);

    imp(combined_ver, "Imagens_filtradas.png");
}
