#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySerial(D1, D2);  // RX, TX para o DFPlayer
DFRobotDFPlayerMini myDFPlayer;

const int alegria = D5;  // Botão 1 (001-030)
const int tristeza = D6;  // Botão 2 (031-041)
const int raiva = D7;  // Botão 3 (041-051)

void setup() {
  mySerial.begin(9600);
  Serial.begin(115200);

  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("Erro ao inicializar o DFPlayer Mini");
    while (true);
  }
  
  Serial.println("DFPlayer Mini inicializado com sucesso.");
  myDFPlayer.volume(39);  // Define o volume entre 0 e 30

  // Configura os botões como entradas
  pinMode(alegria, INPUT_PULLUP);
  pinMode(tristeza, INPUT_PULLUP);
  pinMode(raiva, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(alegria) == LOW) {
    playRandomTrack(1);  // Reproduz uma música aleatória do conjunto 1 
  }
  if (digitalRead(tristeza) == LOW) {
    playRandomTrack(2);  // Reproduz uma música aleatória do conjunto 2 
  }
  if (digitalRead(raiva) == LOW) {
    playRandomTrack(3);  // Reproduz uma música aleatória do conjunto 3 
  }
  delay(150);  // Debounce simples para evitar múltiplas leituras rápidas
}

void playRandomTrack(int emotion) {
  int track = 0;

  // Escolhe uma faixa aleatória de acordo com o botão pressionado
  if (emotion == 1) {
    track = random(1, 6);  // Alegria: faixas de 001 a 006
    Serial.println("Alegria");
  } else if (emotion == 2) {
    track = random(7, 12);  // Tristeza: faixas de 007 a 012
    Serial.println("Tristeza");
  } else if (emotion == 3) {
    track = random(13, 18);  // Raiva: faixas de 012 a 018
    Serial.println("Raiva");
  }
  // Garante que o número seja formatado corretamente como "001", "002", etc.
  char trackString[4];  // Vetor para armazenar o número formatado como string
  sprintf(trackString, "%03d", track);  // Converte o número para string com 3 dígitos
  // Exibe a faixa escolhida no monitor serial
  Serial.print("Tocando faixa: ");
  Serial.println(trackString);
  int trackNumber = atoi(trackString);  // Converte a string para inteiro
  // Toca a faixa correta no DFPlayer
  myDFPlayer.play(trackNumber);  // O DFPlayer Mini toca a faixa com o número convertido
}
