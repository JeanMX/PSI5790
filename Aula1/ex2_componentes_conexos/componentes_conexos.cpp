/*******************************************/
/* Exercício 2 - Aula 1 - PSI5790          */
/* Nome: Jean Carlos Mello Xavier Faria    */
/* Nusp: 11259628                          */
/*******************************************/

#include <cekeikon.h>
#include <queue>

void fill(Mat_<GRY>& img, int ls, int cs, int label)
{
    int rows = img.rows;
    int cols = img.cols;

    queue<int> q;
    q.push(ls);
    q.push(cs);

    while(!q.empty())
    {
        int current_row = q.front();
        q.pop();
        int current_col = q.front();
        q.pop();

        if(current_row >= 0 && current_row < rows && current_col < cols >= 0 && current_col < cols && img(current_row, current_col) == 0)
        {
            img(current_row, current_col) = label;
            for(int i = -1; i <= 1; i++)
                for(int j = -1; j <= 1; j++)
                    if(i != 0 || j != 0)
                    {
                        q.push((current_row + i));
                        q.push((current_col + j));
                    }
        }
    }
}

int components(Mat_ <GRY>& img)
{
    Mat_ <GRY> labeld_img;

    int comp_conexos = 1;

    for(int i = 0; i < img.rows; ++i)
        for(int j = 0; j < img.cols; ++j)
            if(img(i,j) == 0)
            {   
                fill(img, i, j, comp_conexos);
                comp_conexos++;
            }

    return (comp_conexos-1);
}

int main()
{
    bool finalizacao = 1;
    while(finalizacao != 0)
    {
        Mat_<GRY> img;
        std::string name;

        cout << "Nome da imagem para encontrar o número de componentes conexos: ";
        cin >> name;
        le(img, name);

        int comp_conexos = components(img);
        
        cout << "Número de componentes conexos = " << comp_conexos << endl;

        cout << "Coloque 1 para tentar novamente ou 0 para finalizar o programa: ";

        cin >> finalizacao;
    }

}