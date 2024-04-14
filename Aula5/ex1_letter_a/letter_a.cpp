/*******************************************/
/* Exercício 1 - Aula 5 - PSI5790          */
/* Nome: Jean Carlos Mello Xavier Faria    */
/* Nusp: 11259628                          */
/*******************************************/

#include <cekeikon.h>

#define WINDOW_SIZE (7)
#define NUM_NEIGHBORS (10)

int main() 
{
    Mat_<GRY> ax; le(ax,"lax.bmp");
    Mat_<GRY> ay; le(ay,"lay.bmp");
    Mat_<GRY> qx; le(qx,"lqx.bmp");

    if (ax.size()!=ay.size()) erro("Erro dimensao");

    Mat_<GRY> qp(qx.rows,qx.cols);

    Mat_<FLT> features(ax.rows*ax.cols,WINDOW_SIZE*WINDOW_SIZE);
    Mat_<FLT> saidas(ax.rows*ax.cols,1);
    
    int k=0;
    for (int l=0; l<ax.rows; l++)
        for (int c=0; c<ax.cols; c++) 
        {
            int w = 0;
            for(int i=-(WINDOW_SIZE-1)/2; i<=(WINDOW_SIZE-1)/2; i++)
            {
                for(int j=-(WINDOW_SIZE-1)/2; j<=(WINDOW_SIZE-1)/2; j++)
                {
                    features(k,w) = ax(l+i, c+j)/255.0;
                    w++;
                }
            }
    '   '
            saidas(k)=ay(l,c);
            k++;
        }

    flann::Index ind(features,flann::KDTreeIndexParams(4));

    Mat_<FLT> query(1,WINDOW_SIZE*WINDOW_SIZE);
    vector<int> indices(NUM_NEIGHBORS);
    vector<FLT> dists(NUM_NEIGHBORS);

    for (int l=0; l<qp.rows; l++)
        for (int c=0; c<qp.cols; c++) 
        {
            int w = 0;

            for(int i=-(WINDOW_SIZE-1)/2; i<=(WINDOW_SIZE-1)/2; i++)
            {
                for(int j=-(WINDOW_SIZE-1)/2; j<=(WINDOW_SIZE-1)/2; j++)
                {
                    query(w) = qx(l+i, c+j)/255.0;
                    w++;
                }
            }
            ind.knnSearch(query,indices,dists,NUM_NEIGHBORS,flann::SearchParams(0));
            qp(l,c)=saidas(indices[0]);
        }

    for (int l=0; l<qp.rows; l++)
        for (int c=0; c<qp.cols; c++)
        {
            if(qx(l,c) == 0 && qp(l,c) != 0)
            {
               qp(l,c) = 200;
            }
        }

    imp(qp, "lqy.png");
}