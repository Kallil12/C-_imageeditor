#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>

using namespace std;

#define MAX 512
/*
struct orientada pelo documento, onde nl e nc sao
os numeros de linha e coluna, respectivamente
*/
struct Img{

    int cores[MAX][MAX][3];
    int nl;
    int nc;
};

void abre_img(char nome[], Img& img );
void salva_img(char nome[], Img img);
void corta_rgb(Img img_in, Img& img_out, int li, int ci, int lf, int cf);
void aumenta_tamanho(Img img_in, Img& img_out);
void rotaciona_horario (Img img_in, Img& img_out);
void equaliza_histograma(Img img_in, Img& img_out);
void converte_para_cinza(Img img_in, Img& img_out);
void binariza (Img img_in, Img& img_out, int limiar);


int main(){
    char nome[50];
    char nome_out[50];
    Img img_in, img_out;
    char resposta;
    cout << " ____   _             _          ____         _               " << endl;
    cout << "|  _ \ | |__    ___  | |_  ___  |  _ \  ___  | |__   _ __  ___  " << endl;
    cout << "| |_) || '_ \  / _ \ | __ / _ \ | |_)  / _ \ | '_ \ | '__ / _ \ " << endl;
    cout << "|  __/ | | | |  (_)  | |_  (_)  |  __ / (_)  | |_)  | |  |  __/ " << endl;
    cout << "|_|    |_| |_| \___/  \__ \___/ |_|    \___/ |_.__/ |_|   \___| " << endl;

    cout << "Bem vindo ao PhotoPobre 1.2 \n";
    cout << "Digite o nome do arquivo: \n";

    cin.getline(nome,50);
    strcat(nome,".ppm");
    abre_img(nome,img_in);

    resposta = 'y';

while(resposta == 'y'){
    int opcao;

    cout << "Escolha a edicao desejada: \n";
    cout << "1 Crop (recortar imagem) \n";
    cout << "2 Aumenta tamanho \n";
    cout << "3 Equalizacao de histograma \n";
    cout << "4 Rotacionar a imagem \n";
    cout << "5 Converter para cinza \n";
    cout << "6 Binarizar a imagem \n";

    cin >> opcao;


    if(opcao == 1){
        ///corta imagem
        cin.ignore();
        cout << "Insira o nome do novo arquivo: \n";
        cin.getline(nome_out,50);
        int li,ci,lf,cf;
        cout << "Insira a linha e a coluna iniciais (respectivamente) \n";
        cin >> li >> ci;
        cout << "Agora insira a linha e coluna finais (respectivamente) \n";
        cin >> lf >> cf;
        corta_rgb(img_in,img_out,li,ci,lf,cf);
        salva_img(nome_out,img_out);

    }

    else if(opcao == 2){
        ///aumentar o tamanho
        cin.ignore();
        cout << "Insira o nome do novo arquivo: \n";
        cin.getline(nome_out,50);
        aumenta_tamanho(img_in,img_out);
        salva_img(nome_out,img_out);
    }

    else if (opcao == 3){
        ///equalizacao de histograma
        cin.ignore();
        cout << "Insira o nome do novo arquivo: \n";
        cin.getline(nome_out,50);
        equaliza_histograma(img_in,img_out);
        salva_img(nome_out,img_out);
    }

    else if(opcao == 4){
        ///rotacionar imagem
        cin.ignore();
        cout << "Insira o nome do novo arquivo: \n";
        cin.getline(nome_out,50);
        rotaciona_horario (img_in,img_out);
        salva_img(nome_out,img_out);
    }

    else if(opcao == 5){
        ///converte pra cinza
        cin.ignore();
        cout << "Insira o nome do novo arquivo: \n";
        cin.getline(nome_out,50);
        converte_para_cinza(img_in,img_out);
        salva_img(nome_out,img_out);
    }

    else if(opcao == 6){
        ///binariza
        int limiar;
        cin.ignore();
        cout << "Insira o nome do novo arquivo: \n";
        cin.getline(nome_out,50);
        cout << "Insira o limiar: \n";
        cin >> limiar;
        binariza (img_in,img_out,limiar);
        salva_img(nome_out,img_out);
    }

    cout << "Deseja realizar outra operacao? (y/n) \n";
    cin >> resposta;
    if(resposta == 'n'){
        exit(0);
    }

    cout << "Digite o nome do arquivo: \n";
    cin.ignore();
    cin.getline(nome,50);
    strcat(nome,".ppm");
    abre_img(nome,img_in);
}



return 0;
}


void abre_img(char nome[], Img& img ){  //abre a imagem e copia para a variavel da struct Img
    fstream arq;
    char tipo[3];
    int pixel_max;
    arq.open(nome);
    if(!arq.is_open()){
        cout << "Arquivo nao aberto!\n";
        exit(0);
    }
    /* colocar a leitura do p3, leitura de linha e coluna da imagem e tamanho maximo dos pixels*/
    else{
        arq.getline(tipo,3);
        arq >> img.nc >> img.nl;

        arq >> pixel_max;

        for(int i = 0; i<img.nc; i++){
            for(int j = 0; j<img.nl; j++){
                for(int k = 0; k<3; k++){
                    arq >> img.cores[i][j][k];
                }
            }
        }
        cout << "Arquivo aberto com sucesso! \n";
    }
}

void salva_img(char nome[], Img img){

    ofstream arq_out;
    strcat(nome, ".ppm");
    arq_out.open(nome);
    if(!arq_out.is_open()){
        cout << "Falha ao salvar! \n";
        exit(0);
    }
    else{
        arq_out << "P3";
        arq_out << endl;
        arq_out << img.nc;
        arq_out << " ";
        arq_out << img.nl;
        arq_out << endl;
        arq_out << 255;
        arq_out << endl;

        for(int i = 0; i<img.nc; i++){
            for(int j = 0; j<img.nl; j++){
                for (int k = 0; k<3; k++){
                    arq_out << img.cores[i][j][k];
                    arq_out << " ";
                }
            }
        arq_out << endl;
        }
    }
}

void corta_rgb(Img img_in, Img& img_out, int li, int ci, int lf, int cf){
    int li_o = 0, ci_o = 0;
    img_out.nl = (lf-li)+1;
    img_out.nc = (cf-ci)+1;

    for(int i = li; i<=lf; i++){
        for(int j = ci; j<=cf; j++){
            for(int k = 0; k<3; k++){
                img_out.cores[li_o][ci_o][k] = img_in.cores[i][j][k];
            }
            ci_o++;
        }
        li_o++;
        ci_o = 0;
    }
}


void aumenta_tamanho(Img img_in, Img& img_out){

    int a = 0, b = 0;

    img_out.nl = (2*img_in.nl) -1;
    img_out.nc = (2*img_in.nc) -1;

    //cout << "1 " << img_out.nl << " " << img_out.nc << endl;

    for(int i = 0; i < img_out.nl; i+=2){
        for(int j = 0; j < img_out.nc; j+=2){
            for(int k = 0; k<3; k++){
                img_out.cores[i][j][k] = img_in.cores[a][b][k];
            }
            b++;
        }
        b = 0;
        a++;
    }

    //cout << "2 " << img_out.nl << " " << img_out.nc << endl;

    for(int j = 1; j<img_out.nc; j+=2){  //preenchendo a primeira linha e a ultima linha
        for(int k = 0; k<3; k++){
            img_out.cores[0][j][k] = (img_out.cores[0][j+1][k] + img_out.cores[0][j-1][k])/2;
            img_out.cores[img_out.nl-1][j][k] = (img_out.cores[img_out.nl-1][j+1][k] + img_out.cores[img_out.nl-1][j-1][k])/2;
        }
    }

    for(int i = 1; i<img_out.nl; i+=2){ //preenchendo a primeira coluna e a ultima coluna
        for(int k = 0; k<3; k++){
            img_out.cores[i][0][k] = (img_out.cores[i-1][0][k] + img_out.cores[i+1][0][k])/2;
            img_out.cores[i][img_out.nc-1][k] = (img_out.cores[i-1][img_out.nc-1][k] + img_out.cores[i+1][img_out.nc-1][k])/2;
        }
    }

    for(int i = 1; i<img_out.nl; i+=2){
        for(int j = 1; j<img_out.nc; j+=2){
            for(int k = 0; k<3; k++){
                img_out.cores[i][j][k] = (img_out.cores[i-1][j-1][k]+img_out.cores[i-1][j+1][k]+img_out.cores[i+1][j-1][k]+img_out.cores[i+1][j+1][k])/4;
            }
        }
    }

    for(int i = 1; i<img_out.nl-1; i++){
        int x;
        if(i%2 == 0){
            x = 1;
        }
        else{
            x = 2;
        }
        for(int j = x; j<img_out.nc-1; j+=2){
            for(int k = 0; k<3; k++){
                    img_out.cores[i][j][k] = (img_out.cores[i-1][j][k]+img_out.cores[i+1][j][k]+img_out.cores[i][j+1][k]+img_out.cores[i][j-1][k])/4;
                }
            }
        }
    }

void equaliza_histograma(Img img_in, Img& img_out){

    int vr[256] = {}; //vetor de vermelho
    int vg[256] = {}; //vetor de verde
    int vb[256] = {}; //vetor de azul
    int aux;
    int s;

    int tam_total = img_in.nl*img_in.nc;

    img_out.nl = img_in.nl;
    img_out.nc = img_in.nc;

    for(int i = 0; i<img_in.nl; i++){  //primeira etapa, preenchendo os vetores
        for(int j = 0; j<img_in.nc; j++){
            vr[img_in.cores[i][j][0]]++;
            vg[img_in.cores[i][j][1]]++;
            vb[img_in.cores[i][j][2]]++;
        }
    }

    for(int i = 0; i<img_in.nl; i++){ //preenche o vermelho
        for(int j = 0; j<img_in.nc; j++){
            aux = 0;
            for(int r1 = 0; r1 <=img_in.cores[i][j][0]; r1++){
                aux += vr[r1];
            }
            s = (aux*255)/(tam_total);
            img_out.cores[i][j][0]= s;
        }
    }


    for(int i = 0; i<img_in.nl; i++){ //preenche o verde
        for(int j = 0; j<img_in.nc; j++){
                aux = 0;
                for(int r2 = 0; r2 <=img_in.cores[i][j][1]; r2++){
                    aux += vg[r2];
                }
                s = (aux*255)/(tam_total);
                img_out.cores[i][j][1]= s;
        }
    }

    for(int i = 0; i<img_in.nl; i++){ //preenche o azul
        for(int j = 0; j<img_in.nc; j++){
                aux = 0;
                for(int r3 = 0; r3 <=img_in.cores[i][j][2]; r3++){
                    aux += vb[r3];
                }
                s = (aux*255)/(tam_total);
                img_out.cores[i][j][2]= s;
            }
        }
    }

void rotaciona_horario (Img img_in, Img& img_out){
    int a;
    img_out.nl = img_in.nl;
    img_out.nc = img_in.nc;

    for(int i = 0; i<img_in.nc; i++){
        a = img_in.nl-1;
        for(int j = 0; j<img_in.nl; j++){
            for (int k = 0; k<3; k++){
                img_out.cores[i][j][k] = img_in.cores[a][i][k];
            }
        a--;
        }
    }
}


void converte_para_cinza(Img img_in, Img& img_out){

    img_out.nc = img_in.nc;
    img_out.nl = img_in.nl;

    int aux;
    int media = 0;


    for(int i = 0; i<img_in.nl; i++){
        for(int j = 0; j<img_in.nc; j++){
            for(int k = 0; k<3; k+=3){
                aux = (img_in.cores[i][j][0]+img_in.cores[i][j][1]+img_in.cores[i][j][2]);
                media = aux/3;

                img_out.cores[i][j][k]=media;
                img_out.cores[i][j][k+1]=media;
                img_out.cores[i][j][k+2]=media;
            }
            aux = 0;
        }
    }
}

void binariza (Img img_in, Img& img_out, int limiar){

    img_out.nc = img_in.nc;
    img_out.nl = img_in.nl;

    int aux;
    int r1, g1, b1;

    for(int i = 0; i<img_in.nl; i++){
        for(int j = 0; j<img_in.nc; j++){
            aux = 0;
            for(int r = 0; r<4; r+=3){
               img_in.cores[i][j][r];
                if((img_in.cores[i][j][r]+img_in.cores[i][j][r+1]+img_in.cores[i][j][r+2])/3 > limiar){
                    img_out.cores[i][j][r]=255;
                    img_out.cores[i][j][r+1]=255;
                    img_out.cores[i][j][r+2]=255;
                }
                else{
                    img_out.cores[i][j][r]=0;
                    img_out.cores[i][j][r+1]=0;
                    img_out.cores[i][j][r+2]=0;
                }
            }
        }
    }
}
