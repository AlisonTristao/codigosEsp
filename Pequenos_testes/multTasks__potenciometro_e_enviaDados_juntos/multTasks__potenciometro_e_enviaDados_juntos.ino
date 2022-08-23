//Autor: Alison de Oliveira
//Email: AlisonTristao@hotmail.com

// bluetooth
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it 
#endif 
BluetoothSerial SerialBT;

// multtasks
TaskHandle_t observer;

// potenciometro
int valor = 0;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Esp32 dadosTasks");//nome do dispositivo

// inicia a task
  xTaskCreatePinnedToCore(
                      enviaDados,   // Função da tarefa 
                      "task",       // nome da tarefa 
                      10000,        // Tamanho (bytes) 
                      NULL,         // parâmetro da tarefa 
                      2,            // prioridade da tarefa (tem q ser 2 pra n dar conflito) 
                      &observer,    // observa a tarefa criada
                      0);           // nucleo
}

void enviaDados(void * pvParameters){
    for(;;){ // loop infinito
      if(SerialBT.available()){
        recebeDados();
      }else{
      delay(150);
      SerialBT.println("{"+String(valor)+"}");
      }
    }
}

void loop() {
  // le o valor e ja converte pra nao dar tempo de envair um numero sem ser convertido
  valor = map(analogRead(13), 0, 4095, -7, 7);
}

String texto = "";
void recebeDados(){
  char a = SerialBT.read();
  texto += a;
  if(a == '}'){
      Serial.println(texto); 
      texto = "";
  }
}
 
