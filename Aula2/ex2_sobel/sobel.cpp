/*******************************************/
/* Exercício 1 - Aula 2 - PSI5790          */
/* Nome: Jean Carlos Mello Xavier Faria    */
/* Nusp: 11259628                          */
/*******************************************/

#include <cekeikon.h>

int main() 
{
    Mat_<float> a = imread("circulo.png",0);
    Mat_<float> sx,sy,ox,oy;

    Sobel(a,sx,-1,1,0,3); 
    Sobel(a,sy,-1,0,1,3); 
    
    ox = sx/4.0+128; 
    imwrite("ox.png",ox);
    
    oy = sy/4.0+128; 
    imwrite("oy.png",oy);
    
    Mat_<float> tx;
    Mat_<float> ty;
    pow(sx, 2, tx);
    pow(sy,2,ty);

    Mat_<float> ver_todo;
    pow(tx, 0.5, ver_todo);
    imwrite("ver_todo.png", ver_todo);

    Mat_<float> hor_todo;
    pow(ty, 0.5, hor_todo);
    imwrite("hor_todo.png", hor_todo);

    imwrite("ver_esq.png", sx);

    Mat_<float> ver_dir;
    ver_dir = ver_todo-sx;
    imwrite("ver_dir.png", ver_dir);

    imwrite("hor_sup.png", sy);

    Mat_<float> hor_inf;
    hor_inf = hor_todo - sy;
    imwrite("hor_inf.png", hor_inf);

    Mat_<float> modulo;
    pow(tx+ty, 0.5, modulo);
    imwrite("modulo.png", modulo);

    // Combinar as imagens
    Mat_<float> combined_hor_1, combined_hor_2, combined_hor_3, combined_hor_4, combined_ver;
    Mat_<float> img_white = Mat::ones(modulo.rows, modulo.cols, CV_8UC3)*255;
    
    hconcat(a, ox, combined_hor_1);
    hconcat(combined_hor_1, oy, combined_hor_1);

    hconcat(ver_todo, sx, combined_hor_2);
    hconcat(combined_hor_2, ver_dir, combined_hor_2);

    hconcat(hor_todo, sy, combined_hor_3);
    hconcat(combined_hor_3, hor_inf, combined_hor_3);

    hconcat(modulo, img_white, combined_hor_4);
    hconcat(combined_hor_4, img_white, combined_hor_4);


    vconcat(combined_hor_1, combined_hor_2, combined_ver);
    vconcat(combined_ver, combined_hor_3, combined_ver);
    vconcat(combined_ver, combined_hor_4, combined_ver);

    imwrite("imagens_combinadas.png", combined_ver);

}