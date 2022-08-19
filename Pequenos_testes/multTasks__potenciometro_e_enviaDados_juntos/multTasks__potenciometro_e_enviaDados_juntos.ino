//Autor: Alison de Oliveira
//Email: AlisonTristao@hotmail.com

// bluetooth
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it 
#endif 
BluetoothSerial SerialBT;
boolean con = false;

// multtasks
TaskHandle_t observer;

// potenciometro
int valor = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Esp32 dadosTasks");//nome do dispositivo
}

void enviaDados(void * pvParameters){
    for(;;){ // loop infinito
      /*
          Tem que dar o delay antes pq senao ele tenta enviar os dados logo em seguida de conectar 
          e acaba dando algum erro
      */
      delay(150); 
      SerialBT.println("{"+String(valor)+"}");
    }
}

void loop() {
  /*
      Se tentar iniciar a task em segundo plano antes de conectar com o celular não da
    pq o pareamento da esp usa o segundo processador, entao temos q conectar com o celular 
    pra depois começar a segunda task
  */
  if(!con){conecta();}

  // le o valor e ja converte pra nao dar tempo de envair um numero sem ser convertido
  valor = map(analogRead(13), 0, 4095, -7, 7);
}


String texto = "";
void conecta(){
  if(SerialBT.available()){
    char a = SerialBT.read();

    texto += a;

    /*
        Depois de conectar o app com a esp32 é preciso enviar 0 0 0 0 nas constantes
      para iniciar a task q manda os dados para o celular
    */
    if(texto == "{0,0,0,0}"){
      // cria a task
      xTaskCreatePinnedToCore(
                      enviaDados,   // Função da tarefa 
                      "task",       // nome da tarefa 
                      10000,        // Tamanho (bytes) 
                      NULL,         // parâmetro da tarefa 
                      1,            // prioridade da tarefa 
                      &observer,    // observa a tarefa criada
                      0);           // nucleo

        Serial.println("Task iniciada!");

        // define a conexao como true pra n ficar verificando sempre
        con = true;
        texto = "";      
      }else if(a == '}'){

        // se a conexao ser falta e enviar algo limpa a variavel
        texto = "";
      }   
    } 
}
