/*******************************************/
/* Exercício 1 - Aula 6 - PSI5790          */
/* Nome: Jean Carlos Mello Xavier Faria    */
/* Nusp: 11259628                          */
/*******************************************/

//compila mnist_svm -ocv -v3

#include "procimagem.h"

#define LOTES (2)


Mat_<uchar> rotation_image(Mat_<uchar> image)
{
    Mat_<uchar> output;
    
    double angle = 5.0;

    Point2f center(image.cols / 2.0, image.rows / 2.0);

    Mat rotation_matrix = getRotationMatrix2D(center, angle, 1.0);
    warpAffine(image, output, rotation_matrix, image.size());   
    
    return output;
}

using namespace ml;

int main() 
{
    MNIST mnist(10, true, false); //10x10 e sem Bounding Box
    mnist.le("/home/jean/cekeikon5/tiny_dnn/data");

    vector<Mat_<uchar>> AX;
    vector<float> valores;
    for(int i = 0; i < mnist.AX.size(); i++)
        AX.push_back(mnist.AX[i].clone());


    for(int j=0; j<mnist.ax.rows; j++)
        AX.push_back(rotation_image(mnist.AX[j]));
    
    Mat_<float> ax;
    Mat_<float> ay;

    ax.create(AX.size(), AX[0].total());
    for (int i=0; i<ax.rows; i++)
        for (int j=0; j<ax.cols; j++)
            ax(i,j)=AX[i](j)/255.0;

    for(int i = 0; i < LOTES; i++)
        for(int j = 0; j < mnist.AX.size(); j++)
            ay.push_back(mnist.AY[j]);

    Ptr<SVM> ind=SVM::create();
    double t1=tempo();
    ind->train(ax, ROW_SAMPLE, ay); // Treinamento da SVM
    double t2=tempo();

    for (int l=0; l<mnist.nq; l++)
        mnist.qp(l)=ind->predict(mnist.qx.row(l));

    double t3=tempo();

    printf("Erros=%10.2f%%\n",100.0*mnist.contaErros()/mnist.nq);
    printf("Tempo de treino: %f\n",t2-t1);
    printf("Tempo de predicao: %f\n",t3-t2);
}