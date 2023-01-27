// Definir baud rate
void setup() {
  Serial.begin(9600);
}

// Comandos de loop no Arduino
void loop() {
  // Ler informação enviada pelo Raspberry Pi se estiver disponível
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');  
    // Se o comando recebido for "1", enviar valor da porta analógica 5 para o Raspberry Pi
    if (data.toInt() == 1){
      Serial.println(analogRead(5));
    }
    // Caso contrário, enviar para o Raspberry Pi a string "e" a simbolizar erro
    else{
      Serial.println("e");
    }
  }
}