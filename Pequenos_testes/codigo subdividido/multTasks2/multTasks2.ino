TaskHandle_t Task2;

void setup() {
  Serial.begin(115200);

}

void Task2code(void * pvParameters){
    delay(500);
    
    Serial.print("Tarefa 2 - Nucleo numero: ");
    Serial.print(xPortGetCoreID());
    Serial.println("");

    // nao pode esquecer de fechar a task
    vTaskDelete(Task2);
}

void loop() {
    Serial.print("Tarefa 1 - Nucleo numero: ");
    Serial.print(xPortGetCoreID()); // void loop é automatico no nucleo 1
    Serial.println("");

    // cria a task
    xTaskCreatePinnedToCore(
                    Task2code,    // Função da tarefa 
                    "Ventilador", // nome da tarefa 
                    1000,         // Tamanho (bytes) 
                    NULL,         // parâmetro da tarefa 
                    1,            // prioridade da tarefa 
                    &Task2,       // observa a tarefa criada
                    0);           // nucleo

    delay(1000);
}
