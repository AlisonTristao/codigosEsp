//Autor: Alison de Oliveira
//Email: AlisonTristao@hotmail.com

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it 
#endif 

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Esp32 Dados Teste");//nome do dispositivo
}

String texto = "";
void loop() {


  // loop que fica mandando numeros 
  for(int i = -7; i < 8; i++){

    /*
    envia os dados assim {dados} para as chaves indetificarem o começo e o final
    */
    SerialBT.print("{"+String(i)+"}");

    // verifica se rebeu dados
    // (acho q talvez seja melhor de outro jeito)
    verifica();

    // consegui atualizar ate 75 milesimos - 60 milis ja travou
    delay(100);
  }
}

void verifica(){
  if(SerialBT.available()){
      char a = SerialBT.read();

      texto += a;

      if(a == '}'){
          Serial.print(texto);
          texto = "";
      }
  }
}
