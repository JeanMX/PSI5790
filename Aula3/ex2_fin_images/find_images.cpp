/*******************************************/
/* Exercício 2 - Aula 3 - PSI5790          */
/* Nome: Jean Carlos Mello Xavier Faria    */
/* Nusp: 11259628                          */
/*******************************************/

#include <cekeikon.h>

bool flag;

Mat_<float> rotacao(Mat_<float> ent, double graus, Point2f centro, Size tamanho) {
    Mat_<double> m=getRotationMatrix2D(centro, graus, 1.0);
    Mat_<float> sai;
    warpAffine(ent, sai, m, tamanho, INTER_LINEAR, BORDER_CONSTANT, Scalar(255));
    return sai;
}

Mat_<float> drawRotatedRectangle(Mat_<Vec3f> ent, double graus, Point2f centro, Size2f size, Scalar color, int thickness)
{
    RotatedRect rotatedRect(centro, size, graus);
    Point2f vertices[4];
    rotatedRect.points(vertices);
    for (int i = 0; i < 4; ++i) {   
        line(ent, vertices[i], vertices[(i + 1) % 4], color, thickness);
    }
    Point2f midPoint = (vertices[1] + vertices[(2) % 4]) * 0.5;
    line(ent, centro, midPoint, color, thickness);
    
    return ent;
}

Mat_<Vec3f> writeOnImage(Mat_<Vec3f> a_color, int number, double angle, Size2f size, int c, int l)
{
    a_color = drawRotatedRectangle(a_color, (360 - angle), Point2f(c,l), size, Scalar(0,0,255), 2);
    rectangle(a_color, Point(c-1,l-1), Point(c+1,l+1), Scalar(0,255,0), 3);
    putText(a_color, to_string(number), Point(c+2,l+2), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255,0,0), 1.5);
    flag = true;
    return a_color;
}

int main()
{   
    Mat_<float> a = imread("a1.jpg", 0);
    
    Mat_<Vec3f> a_color;
    cvtColor(a, a_color, COLOR_GRAY2BGR); // Convertendo para imagem colorida

    vector<Mat_<float>> qMatrix(13);

    for(int i = 0; i < 13; ++i)
    {
        if(i < 10)
        {
            qMatrix[i] = imread("q0" + to_string(i) + ".jpg",0);
        }
        else
        {
            qMatrix[i] = imread("q" + to_string(i) + ".jpg",0);
        }
    }
    
    for(int img = 1; img < 13; ++img)
    {
        flag = false;
        for(int angle = 0; angle < 360; angle+10)
        {
            Mat_<float> q1_rotation = rotacao(qMatrix[img],angle,(Point2f(qMatrix[img].size()) * 0.5),qMatrix[img].size());
            Mat_<float> p = matchTemplateSame(a, q1_rotation, TM_CCOEFF_NORMED);
            p = abs(p);
            
            for(int l = 0; l <= a.rows; l++)
            {
                for(int c=0; c <= a.cols; c++)
                {
                    if(p(l,c) >= 0.9)
                    {
                        writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                    }

                    switch(img)
                    {
                        case 1:
                        {
                            if(p(l,c) >= 0.9)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 2:
                        {
                            if(p(l,c) >= 0.75)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 3:
                        {
                            if(p(l,c) >= 0.9)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 4:
                        {
                            if(p(l,c) >= 0.7)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 5:
                        {
                            if(p(l,c) >= 0.8)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 6:
                        {
                            if(p(l,c) >= 0.7)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 7:
                        {
                            if(p(l,c) >= 0.9)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 8:
                        {
                            if(p(l,c) >= 0.7)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 9:
                        {
                            if(p(l,c) >= 0.75)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 10:
                        {
                            if(p(l,c) >= 0.85)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 11:
                        {
                            if(p(l,c) >= 0.9)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                        case 12:
                        {
                            if(p(l,c) >= 0.6)
                            {
                                writeOnImage(a_color, img, angle, qMatrix[img].size(), c, l);
                            }
                            break;
                        }
                    }
                    if(flag)
                        break;
                }
                if(flag)
                    break;
            }
            if(flag)
                    break;
        }
    }
    
    imwrite("out.jpg", a_color);
}