#include<stdio.h>   //FILE
#include<stdlib.h>  //rand
#include<string.h>  //memcpy
#include<time.h>
#include<math.h>    //tanh, exp

typedef struct{
    double inputs[8];  //8 características da fruta
    double target;     //espécie
} fruta;

typedef struct{
    double weights[8][4];  //8 inputs -> 4 neurônios da camada oculta
    double bias[4];
} CamadaEntrada;

typedef struct{
    double weights[4][1];  //4 neurônios da camada oculta -> 1 output
    double bias[1];
} CamadaSaida;

typedef struct{
    CamadaEntrada entrada;
    CamadaSaida saida;
} RedeNeural;

//Função de ativação: tanh
double ativacao(double x){
    return tanh(x);
}

//Sigmoid para a saída final
double sigmoid(double x){
    return 1.0 / (1.0 + exp(-x));
}

//Forward pass
void forward(RedeNeural *rede, fruta *dados, double *hidden, double *output){
    //Camada de entrada -> Camada oculta
    for(int j=0; j<4; j++){
        double soma = rede->entrada.bias[j];
        for(int i=0; i<8; i++){
            soma += dados->inputs[i] * rede->entrada.weights[i][j];
        }
        hidden[j] = ativacao(soma);
    }
    
    //Camada oculta -> Saída
    double soma = rede->saida.bias[0];
    for(int j=0; j<4; j++){
        soma += hidden[j] * rede->saida.weights[j][0];
    }
    output[0] = sigmoid(soma);
}

int main(){
    fruta dataset[30];
    RedeNeural rede;
    int laranjacerto=0, laranjaerrado=0, qqrcerto=0, qqrerrado=0; //contabilizando acertos e erros
    srand(time(0));
    
    //Busca os valores no arquivo entradas2.txt
    FILE *fp = fopen("entradas2.txt", "r");
    for(int x=0; x<30; x++){
        double in[8];
        char especie;
        fscanf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %c\n",
               &in[0], &in[1], &in[2], &in[3], &in[4], &in[5], &in[6], &in[7], &especie);
        memcpy(dataset[x].inputs, in, sizeof(double)*8);
        dataset[x].target = (especie == 'l') ? 1.0 : 0.0;
    }
    fclose(fp);
    
    //Carrega os pesos e bias do arquivo bias1.txt
    fp = fopen("bias1.txt", "r");
    
    //Carrega pesos da camada de entrada
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            fscanf(fp, "%lf\n", &rede.entrada.weights[i][j]);
        }
    }
    
    //Carrega bias da camada de entrada
    for(int j=0; j<4; j++){
        fscanf(fp, "%lf\n", &rede.entrada.bias[j]);
    }
    
    //Carrega pesos da camada de saída
    for(int j=0; j<4; j++){
        fscanf(fp, "%lf\n", &rede.saida.weights[j][0]);
    }
    
    //Carrega bias da camada de saída
    fscanf(fp, "%lf\n", &rede.saida.bias[0]);
    fclose(fp);
    
    printf("\n--- RESULTADO ---\nPara as 30 frutas da base de dados\n\n");
    
    //Testa a rede neural com 1000 predições aleatórias
    for(int s=0; s<1000; s++){
        fruta alguma = dataset[rand() % 30];  //escolhe uma fruta qualquer
        double hidden[4];
        double output[1];
        
        forward(&rede, &alguma, hidden, output);
        
        //Classifica como laranja se output > 0.5, senão como outra fruta
        int predicao = (output[0] > 0.5) ? 1 : 0;
        int esperado = (alguma.target > 0.5) ? 1 : 0;
        
        if(esperado == 1){  //fruta esperada é laranja
            if(predicao == 1)
                laranjacerto++;
            else
                laranjaerrado++;
        }
        else{  //fruta esperada é outra (qqr)
            if(predicao == 0)
                qqrcerto++;
            else
                qqrerrado++;
        }
    }
    
    printf("Esperado laranja dado laranja (acertos): %d\n", laranjacerto);
    printf("Esperado laranja dado qqr (erros): %d\n", laranjaerrado);
    printf("Esperado qqr dado qqr (acertos): %d\n", qqrcerto);
    printf("Esperado qqr dado laranja (erros): %d\n\n", qqrerrado);
    
    return 0;
}