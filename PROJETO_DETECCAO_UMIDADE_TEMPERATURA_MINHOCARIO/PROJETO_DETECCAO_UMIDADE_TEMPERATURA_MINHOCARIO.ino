#include <SoftwareSerial.h>
#include <Wire.h>
#include <RTClib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// aqui eu estou definindo  os pinos RX e TX para a comunicação Bluetooth
SoftwareSerial BTSerial(10, 11); // RX, TX

// nessa função eu to criando  o objeto para o RTC
RTC_DS3231 rtc;

// aqui eu definindo os pinos do sensor de umidade e LEDs eo  sensor de temperatura e buzzer
const int pinUmidade = A0; // aqui é o Pino do sensor de umidade
const int pinVermelho = 5;    
const int pinVerde = 6;    
const int pinAzul = 7;     
const int pinBuzzer = 8;  // aqui é Pino do buzzer
const int pinTemp = 9;   // aqui é Pino do sensor de temperatura (DS18B20)


// aqui é a biblioteca OneWire e DallasTemperature para o sensor (DS18B20)
OneWire oneWire(pinTemp);
DallasTemperature sensor(&oneWire);
DeviceAddress endereco_temp;

void setup() {
  // aqui eu to pedindo pra inicia a comunicação serial com o módulo Bluetooth
  BTSerial.begin(9600);

  // aqui eu to pedindo pra inicia a comunicação serial com o monitor serial
  Serial.begin(9600);

  // aqui eu tô iniciando RTC
  if (!rtc.begin()) {
    Serial.println("RTC não encontrado!");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC perdeu a hora, configurando para o horário padrão.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // aqui eu tô iniciando o sensor de temperatura(DS18B20)
  sensor.begin();

  //aqui eu to fazendo as definição dos pinos dos LEDs e do buzzer como saída
  pinMode(pinVermelho, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  //aqui eu quero ele transmita uma mensagem inicial
  Serial.println("Sistema iniciado");
}

void loop() {
  // aqui to pedindo para que obtenha o horário atual do RTC
  DateTime now = rtc.now();
  
  // aqui eu tô pedindo pra formarta o  horario como string (hh:mm:ss)
  String timeString = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

  // aqui eu tô fazendo a leitura do valores da umidade
  int umidadeValor = analogRead(pinUmidade);
  umidadeValor = map(umidadeValor, 0, 1023, 100, 0); // aqui eu tô fazendo o mapeiamento da umidadede de 0 a 100%

  // aqui vou controla a umidade e vou ter controle dos LEDs
  if (umidadeValor < 60) {
    analogWrite(pinVermelho, 255); // o pin vermelho vai acender quando o solo estiver  muito seco
    analogWrite(pinVerde, 0);
    analogWrite(pinAzul, 0);
    Serial.println("Solo do minhocário seco!");
    BTSerial.println("Solo do minhocário seco!");
  } else if (umidadeValor >= 60 && umidadeValor <= 70) {
    analogWrite(pinVermelho, 0);
    analogWrite(pinVerde, 255); // o pin verde vai acernder quando o solo estiver  ideal
    analogWrite(pinAzul, 0);
    Serial.println("Solo do minhocário ideal!");
    BTSerial.println("Solo do minhocário ideal!");
  } else {
    analogWrite(pinVermelho, 0);
    analogWrite(pinVerde, 0);
    analogWrite(pinAzul, 255); // o pin azul vai acender quando o solo estiver  muito úmido
    Serial.println("Solo do minhocário muito úmido!");
    BTSerial.println("Solo do minhocário muito úmido!");
  }

  // aqui eu tô pedindo pra mostra uma mensagem da umidade e hora
  Serial.println("Umidade: " + String(umidadeValor) + "%");
  BTSerial.println("Umidade: " + String(umidadeValor) + "%");
  Serial.println("Hora atual: " + timeString);
  BTSerial.println("Hora atual: " + timeString);

  //aqui já estou fazendo a leitura do sensor de temperatura DS18B20
  sensor.requestTemperatures();
  if (!sensor.getAddress(endereco_temp, 0)) {
    Serial.println("SENSOR DE TEMPERATURA NÃO CONECTADO");
  } else {
    float temperatura = sensor.getTempC(endereco_temp);
    Serial.print("Temperatura = ");
    Serial.println(temperatura, 1);
    BTSerial.print("Temperatura = ");
    BTSerial.println(temperatura, 1);

    // aqui é uma codiçao  para mostra uma  mensagem e com buzzer vai fazer um som com base na temperatura
    if (temperatura >= 20.0 && temperatura <= 25.0) {
      Serial.println("Temperatura ideal");
      BTSerial.println("Temperatura ideal");
      noTone(pinBuzzer); // aqui eu tô pedindo pra desliga o buzzer se a temperatura estiver ideal
    } else if (temperatura < 20.0) {
      Serial.println("Temperatura muito fria");
      BTSerial.println("Temperatura muito fria");
      // aqui eu quero que o buzzer acione quando a temperatura muito fria
      tone(pinBuzzer, 1000); //aqui estou especificado a  Frequência do buzzer de 1000Hz 
      delay(500);
      noTone(pinBuzzer);
    } else if (temperatura > 25.0) {
      Serial.println("Temperatura muito quente");
      BTSerial.println("Temperatura muito quente");
      // aqui eu quero que o buzzer acione quando a  temperatura muito quente
      tone(pinBuzzer, 2000); // aqui estou especificando a Frequência do buzzer que é 2000Hz
      delay(500);
      noTone(pinBuzzer);
    }
  }

    Serial.println("___________________________________");
    BTSerial.println("___________________________________");
  //aqui eu vou aguarda 3 segundos
  delay(3000);
}
