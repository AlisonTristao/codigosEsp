//Autor: Alison de Oliveira
//Email: AlisonTristao@hotmail.com

void setup() {
  Serial.begin(115200);
  //pinMode(13, INPUT);
}

void loop() {

  // le o valor do pino 13
  int valor = analogRead(13);

  // faz um regra de 3
  valor = map(valor, 0, 4095, -7, 7);

  // printa o resultado
  Serial.println(valor);
  delay(500);
  
}
