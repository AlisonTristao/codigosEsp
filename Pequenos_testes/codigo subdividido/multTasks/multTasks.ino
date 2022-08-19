//Autor: Alison de Oliveira
//Email: AlisonTristao@hotmail.com

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it 
#endif 

BluetoothSerial SerialBT;

TaskHandle_t Task1;
TaskHandle_t Task2;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Esp32 MultTask Teste");//nome do dispositivo
  
  xTaskCreatePinnedToCore(
                    Task1code,   /* Função da tarefa */
                    "Lembrete",  /* nome da tarefa */
                    1000,       /* Tamanho (bytes) */
                    NULL,        /* parâmetro da tarefa */
                    1,           /* prioridade da tarefa */
                    &Task1,      /* observa a tarefa criada */
                    0);          /* tarefa alocada ao núcleo 0 */                  

  xTaskCreatePinnedToCore(
                    Task2code,   /* Função da tarefa */
                    "Ventilador",/* nome da tarefa */
                    1000,       /* Tamanho (bytes) */
                    NULL,        /* parâmetro da tarefa */
                    1,           /* prioridade da tarefa */
                    &Task2,      /* observa a tarefa criada */
                    1);          /* tarefa alocada ao núcleo 1 */
}

void Task1code(void * pvParameters){
  for(;;){ // Loop infinito
    SerialBT.println("teste");
  }
}

void Task2code(void * pvParameters){
  for(;;){ // Loop infinito
    Serial.println("dale");
  }
}

void loop() {
  
}
