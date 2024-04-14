/*******************************************/
/* Exercício 2 - Aula 5 - PSI5790          */
/* Nome: Jean Carlos Mello Xavier Faria    */
/* Nusp: 11259628                          */
/*******************************************/

#include <cekeikon.h>

#define WINDOW_SIZE (3)
#define NUM_NEIGHBORS (1)

int main() 
{
    Mat_<GRY> ax; le(ax,"janei.pgm");
    Mat_<GRY> ay; le(ay,"janei-1.pgm");
    Mat_<GRY> qx; le(qx,"julho.pgm");

    if (ax.size()!=ay.size()) erro("Erro dimensao");

    Mat_<GRY> qp(qx.rows,qx.cols);

    Mat_<FLT> features(ax.rows*ax.cols,WINDOW_SIZE*WINDOW_SIZE);
    Mat_<FLT> saidas(ax.rows*ax.cols,1);
    
    // Cria as estruturas de dados para alimentar OpenCV    
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

            saidas(k)=ay(l,c);
            k++;
        }

    flann::Index ind(features,flann::KDTreeIndexParams(4)); // 4 arvores criadas

    Mat_<FLT> query(1,WINDOW_SIZE*WINDOW_SIZE);
    vector<int> indices(NUM_NEIGHBORS);
    vector<FLT> dists(NUM_NEIGHBORS);

    for (int l=0; l<qp.rows; l++)
    {
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
            qp(l,c)=255*saidas(indices[0]);
        }
    }
    
    medianBlur(qp,qp, WINDOW_SIZE*WINDOW_SIZE);
    Mat_<COR> d; 
    converte(qp,d);
    Mat_<COR> output; 
    converte(qx,output);

    for (int l=0; l<qp.rows; l++)
        for (int c=0; c<qp.cols; c++)
        {
            if (qp(l,c) == 0)
                d(l,c) = output(l,c) + COR(0,0,255);
            else
                d(l,c) = output(l,c);

        }

    imp(d, "julho-c1.png");
}