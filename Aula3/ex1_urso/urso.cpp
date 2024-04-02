/*******************************************/
/* Exercício 1 - Aula 3 - PSI5790          */
/* Nome: Jean Carlos Mello Xavier Faria    */
/* Nusp: 11259628                          */
/*******************************************/

#include <cekeikon.h>
 
int main()
{
    Mat_<float> a = imread("a.png",0);
    a /= 255.0;

    Mat_<float> q = imread("q.png", 0);
    q /= 255.0;
    
    Mat_<float> p = matchTemplateSame(a, q, TM_CCOEFF_NORMED);
    Mat_<Vec3f> d;                                  
    
    cvtColor(a,d,COLOR_GRAY2RGB);
    
    p = abs(p);
    for(int l = 0; l <= d.rows; l++)
        for(int c=0; c <= d.cols; c++)
            if(p(l,c) >= 0.9)
                rectangle(d,Point(c,l),Point(c,l),Scalar(0,0,1),3);
    imwrite("output.png", 255*d); 
}
