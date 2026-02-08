#include <NewPing.h>

#define PINO_TRIGGER  25
#define PINO_ECHO     26
#define PINO_BUZZER   21
#define PINO_LED 22
#define DISTANCIA_MAX 500


NewPing sonar(PINO_TRIGGER, PINO_ECHO, DISTANCIA_MAX);

unsigned long tempoAnterior = 0; // Armazena o tempo do último bipe
bool estadoBuzzer = false;       // Estado atual do buzzer (ligado/desligado)

void setup() {
  Serial.begin(115200);
  pinMode(PINO_BUZZER, OUTPUT);
  pinMode(PINO_LED, OUTPUT);

  digitalWrite(PINO_LED, HIGH);
  delay(100);
  digitalWrite(PINO_LED, LOW);
  delay(100);
  digitalWrite(PINO_LED, HIGH);
  delay(100);
  digitalWrite(PINO_LED, LOW);
  delay(100);
  digitalWrite(PINO_LED, HIGH);
}


void loop() {
  delay(50); // Mantém o sensor estável
  int distancia = sonar.ping_cm();

  Print(distancia)

  // FAIXA 1: PERIGO (0 a 10cm) - Som contínuo
  if (distancia > 0 && distancia <= 10) {
    digitalWrite(PINO_BUZZER, HIGH);     
  }

  // FAIXA 2: ATENÇÃO (11 a 40cm) - Bipe rápido
  else if (distancia > 10 && distancia <= 40) {    
    // Usando millis para não travar a leitura do sensor
    if ((millis() / 100) % 2 == 0) {
      digitalWrite(PINO_BUZZER, HIGH);          
    } else {
      digitalWrite(PINO_BUZZER, LOW);
    
    }
  }

  // FAIXA 3: ALERTA LONGE (41 a 80cm) - Bipe lento
  else if (distancia > 40 && distancia <= 80) {
    if ((millis() / 500) % 2 == 0) {
      digitalWrite(PINO_BUZZER, HIGH);
    } else {      
      digitalWrite(PINO_BUZZER, LOW);
    }
  }

  // FORA DE ALCANCE
  else {
    digitalWrite(PINO_BUZZER, LOW);    
  }
}