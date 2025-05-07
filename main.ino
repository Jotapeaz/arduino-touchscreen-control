#include <Mouse.h>
#include <MouseTo.h>

// Mapeamento dos pinos
#define SIGY  A0   // pino analógico
#define S0Y   5
#define S1Y   4
#define S2Y   3
#define S3Y   2
//Y
#define SIGX  A5   // pino analógico
#define S0X   12
#define S1X   11
#define S2X   10
#define S3X   9
// o pino EN do mux vai no GND
#define botaoreset 13 // botão de segurança para o ponteiro do mouse
#define led16 A3 // o led que faltou;

#define valor_multiploX 67.5 //valores da equação de x
#define valor_multiploY 86.66;  //valores da equação de y

int mixX[4]={S3X,S2X,S1X,S0X}; // criação de 2 arrays do mux, que servirão para a transmissão de dados dos mux para o arduino leonardo
int mixY[4]={S3Y,S2Y,S1Y,S0Y};

int valores_analogicosX[16]; // criação da dos arrays das portas analogicas do mux
int valores_analogicosY[16];
int valorled16; // váriavel para guardar o valor lido na porta analógica 
int b, i, x, y;
float mouseZ, mouseX, mouseY;


 // criando valores binarios para salvar a informações separadamente em cada porta
// Valores em binario x
byte ciX[16][4]={              
  {0,0,0,0},   // 0  em decimal
  {0,0,0,1},   // 1  em decimal
  {0,0,1,0},   // 2  em decimal
  {0,0,1,1},   // 3  em decimal
  {0,1,0,0},   // 4  em decimal
  {0,1,0,1},   // 5  em decimal
  {0,1,1,0},   // 6  em decimal
  {0,1,1,1},   // 7  em decimal
  {1,0,0,0},   // 8  em decimal
  {1,0,0,1},   // 9  em decimal
  {1,0,1,0},   // 10 em decimal
  {1,0,1,1},   // 11 em decimal  
  {1,1,0,0},   // 12 em decimal
  {1,1,0,1},   // 13 em decimal
  {1,1,1,0},   // 14 em decimal
  {1,1,1,1},   // 15 em decimal
};//y
byte ciY[10][4]={
  {0,0,0,0},   // 0  em decimal
  {0,0,0,1},   // 1  em decimal
  {0,0,1,0},   // 2  em decimal
  {0,0,1,1},   // 3  em decimal
  {0,1,0,0},   // 4  em decimal
  {0,1,0,1},   // 5  em decimal
  {0,1,1,0},   // 6  em decimal
  {0,1,1,1},   // 7  em decimal
  {1,0,0,0},   // 8  em decimal
  {1,0,0,1},   // 9  em decimal
};

void setup(){
  Serial.begin(57600); //iniciando a comunicação da serial
  Mouse.begin(); // iniciando a comunicação do mouse
  MouseTo.setCorrectionFactor(0.59075); 
  pinMode(botaoreset, INPUT_PULLUP); // configuração pino do botão
  pinMode(led16, INPUT); // configuração do led restante

  for(i = 0; i < 4; i++){ // iniciação das portas das digitais com OUTPUT, para a saida do dados
  pinMode(mixX[i],OUTPUT);
  pinMode(mixY[i],OUTPUT);

  }

}

void loop(){
 
 multiplex(); // vai para a rotina de leitura do mux  
 interseccao(); // vai para a função intersecção
 /*
 for(int a =0; a<=15;a++){
  Serial.print(a);
  Serial.print(" = ");
 Serial.println(valores_analogicosX[a]);
Serial.print(" ");
 }*/
  if(!digitalRead(botaoreset)){ // lógica para indeficar se o botao foi clicado; 
  Mouse.end(); // encerramento do mouse durante 1 minuto;
  Serial.print("fim mouse");
  delay(60*1000);
}

delay(10);
}// fim do loop


//Função de leitura dos valores
void multiplex(){

    for (x = 0; x <= 15; x++) { //laços de repetição para leitura contínua 
    for (y = 0; y <= 3; y++) {
      digitalWrite(mixX[y], ciX[x][y]); // y
      digitalWrite(mixY[y], ciY[x][y]); // x
    }
    valores_analogicosX[x] = analogRead(SIGX);  //guardando  valores nas variaveis 
    valores_analogicosY[x] = analogRead(SIGY);
  }
  valorled16 = analogRead(led16);  //guardando a leitura da porta do led16 na variavel valorled16;
}
// fim do multiplex

void interseccao (){ //função que indica se a houve o cruzamento dos dados
  for (int i = 0; i<=15; i++){
    for(int a = 0; a<=9; a++){
      if(((valores_analogicosX[i]> 965) || (valorled16 > 960)) && valores_analogicosY[a] > 975){
     /*//x
     Serial.print("Pino X");
     Serial.print(i); // a porta
     Serial.print(" = ");
     Serial.println(valores_analogicosX[i]); // resultado, imprime o valor acima de 1000
     Serial.print("Pino X16 = ");
     Serial.println(valorled16);
     Serial.println("");
     //y
     Serial.print("Pino Y");
     Serial.print(a); // a porta
     Serial.print(" = ");
     Serial.println(valores_analogicosY[a]); // resultado, imprime o valor acima de 1000
     */
    if(valorled16 > 960){
   valorled16 = 16; // atribuindo o valor da variavel para 16, assim quando enviada a outra função, o cálculo será feito de maneira da correta;
  
    
    }else{
    valorled16 = 0;
     
     // valores lidos enviados para a função posicaoDaTela
      }//fim da intersecção  
      //b = valorled16;
      posicaoDaTela(i,a,valorled16); 
          }
        }
        
        }
      }
void posicaoDaTela(int x, int y, int z){
      
       if(z == 16){
       mouseZ = z*valor_multiploX; // valor da porta 16 * 123,75;
       mouseY = y*valor_multiploY;
       }else{
       mouseX = x*valor_multiploX; // valor da porta x * 123,75;
       mouseY = y*valor_multiploY; // valor da porta y * 120;
      mouseZ = z*valor_multiploX;
       }
      
        moverMouseParaInterseccao(mouseX, mouseY, mouseZ); // resultados enviados para a função moverMouseParaInterseccao
      //fim posicaoDaTela
      }

void moverMouseParaInterseccao(float x, float y, int z){
  /*Serial.print("valor x =");
  Serial.println(x);
  Serial.print("valor y =");
  Serial.println(y);
  Serial.print("valor z =");
  Serial.println(z);
  Serial.println(" ");
*/


  if(z == 1980){ // se o cálculo de z for correto, efetuar o código abaixo
 MouseTo.setTarget(z, y);  // Mova o ponteiro do mouse para as coordenadas absolutas da tela.
 
 //Mouse.click(); 
    }else{
   MouseTo.setTarget(x, y); //Mova o ponteiro do mouse para as coordenadas absolutas da tela. 
    
    //Mouse.click();
    }
  while (!MouseTo.move()) {}
  static bool clicado = false; 
  if (!clicado) {
    Mouse.click(); 
    clicado = true; 
  } else {
    clicado = false; 
  }
  delay(100);
  
  // fim de moverMouseParaInterseccao
}
 
 // fim de moverMouseParaInterseccao

