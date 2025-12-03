#include<stdio.h> //FILE
#include<stdlib.h> //rand
#include<string.h> //memcpy
#include<time.h>
#include<math.h>    //tanh

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

//Derivada da tanh
double derivada_ativacao(double x){
    return 1.0 - (x * x);
}

//Sigmoid para a saída final
double sigmoid(double x){
    return 1.0 / (1.0 + exp(-x));
}

//Derivada da sigmoid
double derivada_sigmoid(double x){
    return x * (1.0 - x);
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

//Backward pass (Backpropagation)
void backward(RedeNeural *rede, fruta *dados, double *hidden, double *output, double taxa_aprendizado){
    //Erro na camada de saída
    double erro_saida = dados->target - output[0];
    double delta_saida = erro_saida * derivada_sigmoid(output[0]);
    
    //Atualiza pesos da camada oculta -> saída
    for(int j=0; j<4; j++){
        rede->saida.weights[j][0] += taxa_aprendizado * delta_saida * hidden[j];
    }
    rede->saida.bias[0] += taxa_aprendizado * delta_saida;
    
    //Erro na camada oculta
    double delta_hidden[4];
    for(int j=0; j<4; j++){
        delta_hidden[j] = delta_saida * rede->saida.weights[j][0] * derivada_ativacao(hidden[j]);
    }
    
    //Atualiza pesos da entrada -> camada oculta
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            rede->entrada.weights[i][j] += taxa_aprendizado * delta_hidden[j] * dados->inputs[i];
        }
    }
    for(int j=0; j<4; j++){
        rede->entrada.bias[j] += taxa_aprendizado * delta_hidden[j];
    }
}

int main(){
    fruta dataset[30];
    RedeNeural rede;
    srand(time(0));
    
    //Busca os valores no arquivo entradas2.txt
    FILE *fp = fopen("entradas2.txt", "r");
    for(int x=0; x<30; x++){
        double in[8];
        char especie;
        fscanf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %c\n",
               &in[0], &in[1], &in[2], &in[3], &in[4], &in[5], &in[6], &in[7], &especie);
        for(int i=0; i<8; i++) dataset[x].inputs[i] = in[i];
        dataset[x].target = (especie == 'l') ? 1.0 : 0.0;
    }
    fclose(fp);
    
    //Inicializa os pesos com valores aleatórios (Xavier initialization)
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            rede.entrada.weights[i][j] = ((double)rand() / (double)RAND_MAX) - 0.5;
        }
    }
    for(int j=0; j<4; j++) rede.entrada.bias[j] = 0.0;
    
    for(int j=0; j<4; j++){
        rede.saida.weights[j][0] = ((double)rand() / (double)RAND_MAX) - 0.5;
    }
    rede.saida.bias[0] = 0.0;
    
    //Treinamento
    double taxa_aprendizado = 0.5;
    for(int epoch=0; epoch<10000; epoch++){
        double erro_total = 0.0;
        
        for(int i=0; i<30; i++){
            double hidden[4];
            double output[1];
            
            forward(&rede, &dataset[i], hidden, output);
            backward(&rede, &dataset[i], hidden, output, taxa_aprendizado);
            
            erro_total += (dataset[i].target - output[0]) * (dataset[i].target - output[0]);
        }
        
        if(epoch % 500 == 0){
            printf("Epoch %d - Erro total: %.6lf\n", epoch, erro_total / 30.0);
        }
    }
    
    //Salva os pesos e bias
    fp = fopen("bias1.txt", "w");
    for(int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            fprintf(fp, "%lf\n", rede.entrada.weights[i][j]);
        }
    }
    for(int j=0; j<4; j++){
        fprintf(fp, "%lf\n", rede.entrada.bias[j]);
    }
    for(int j=0; j<4; j++){
        fprintf(fp, "%lf\n", rede.saida.weights[j][0]);
    }
    fprintf(fp, "%lf\n", rede.saida.bias[0]);
    fclose(fp);
    
    printf("\nTreinamento finalizado. Pesos salvos em 'bias1.txt'\n");
    return 0;
}