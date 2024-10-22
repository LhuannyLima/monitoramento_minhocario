#include <SoftwareSerial.h>
#include <Wire.h>
#include <RTClib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// aqui eu tô definindo os pinos RX e TX para o Bluetooth
SoftwareSerial BTSerial(10, 11); 

// aqui eu tô criando o objeto para o RTC(relógio)
RTC_DS3231 rtc;

// nessa parte eu tô definindo as porta  dos pinos do sensor de umidade, LEDs, sensor de temperatura e buzzer
const int pinUmidade = A0; // aqui é do pino do sensor de umidade
const int pinVermelho = 5;    
const int pinVerde = 6;    
const int pinAzul = 7;     
const int pinBuzzer = 8;  // aui é do pino do buzzer
const int pinTemp = 9;   //aui é do pino do sensor de temperatura (DS18B20)

// aqui eu to definindo a biblioteca OneWire e DallasTemperature (DS18B20)
OneWire oneWire(pinTemp);
DallasTemperature sensor(&oneWire);
DeviceAddress endereco_temp;

void setup() {
  // aqui eu dando inicio  a comunicação serial com o módulo Bluetooth
  BTSerial.begin(9600);

  // aqui eu to dando inicio a comunicação serial com o monitor serial
  Serial.begin(9600);

  //aqui eu to pedindo para dar inicio a RTC(relógio)
  if (!rtc.begin()) {
    Serial.println("RTC não encontrado!");
    while (1);
  }

  // aqui eu to ajustando a hora manualmente
  rtc.adjust(DateTime(2024, 10, 22, 15, 41, 0)); 
  //aqui to pedindo para dar início ao sensor de temperatura (DS18B20)
  sensor.begin();

  // aqui eu to definindo os pinos dos LEDs e do buzzer como saída
  pinMode(pinVermelho, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  // Mensagem inicial
  Serial.println("Sistema iniciado");
  BTSerial.println("Sistema iniciado");
}

void loop() {
  // aqui eu quero que ele comece com  horário atual do RTC(relógio)
  DateTime now = rtc.now();
  
  // aqui eu to definino  o horário como string (hh:mm:ss)
  String timeString = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

  //aqui eu tô pedido para a leitura dos valores de umidade
  int umidadeValor = analogRead(pinUmidade);
  umidadeValor = map(umidadeValor, 0, 1023, 100, 0); // aqui eu to fazendo o mapeamento da umidade para ficar entre 0 a 100% 

  // aqui eu to pedindo para controlar os LEDS da umidade 
  if (umidadeValor < 60) {
    analogWrite(pinVermelho, 255); // esse Leds é para informa que o solo estar muito seco
    analogWrite(pinVerde, 0);
    analogWrite(pinAzul, 0);
    Serial.println("Solo do minhocário seco!");
    BTSerial.println("Solo do minhocário seco!");
  } else if (umidadeValor >= 60 && umidadeValor <= 70) {
    analogWrite(pinVermelho, 0);
    analogWrite(pinVerde, 255); // esse Leds é para informa que o solo está ideal
    analogWrite(pinAzul, 0);
    Serial.println("Solo do minhocário ideal!");
    BTSerial.println("Solo do minhocário ideal!");
  } else {
    analogWrite(pinVermelho, 0);
    analogWrite(pinVerde, 0);
    analogWrite(pinAzul, 255); // esse Leds é para informa que o solo está muito úmido
    Serial.println("Solo do minhocário muito úmido!");
    BTSerial.println("Solo do minhocário muito úmido!");
  }

  // Aqui eu to pedindo pra mostrar tudo  juntos quanto a umidade e hora atual
  Serial.println("Umidade: " + String(umidadeValor) + "%");
  BTSerial.println("Umidade: " + String(umidadeValor) + "%");
  Serial.println("Hora atual: " + timeString);
  BTSerial.println("Hora atual: " + timeString);

  // aqui eu quero que faça a leitura do sensor de temperatura DS18B20
  sensor.requestTemperatures();
  if (!sensor.getAddress(endereco_temp, 0)) {
    Serial.println("SENSOR DE TEMPERATURA NÃO CONECTADO");
  } else {
    float temperatura = sensor.getTempC(endereco_temp);
    Serial.print("Temperatura = ");
    Serial.println(temperatura, 1);
    BTSerial.print("Temperatura = ");
    BTSerial.println(temperatura, 1);

    // nesse comando eu to pedindo que controle a temperatura e buzzer juntos 
    if (temperatura >= 20.0 && temperatura <= 25.0) {
      Serial.println("Temperatura ideal");
      BTSerial.println("Temperatura ideal");
      noTone(pinBuzzer); // nessa função eu to pedindo para desligar o buzzer se a temperatura estiver ideal
    } else if (temperatura < 20.0) {
      Serial.println("Temperatura muito fria");
      BTSerial.println("Temperatura muito fria");
      tone(pinBuzzer, 1000); // nessa função eu to pedindo para acionar buzzer se a temperatura estiver fria (1000 Hz)
      delay(500);
      noTone(pinBuzzer);
    } else if (temperatura > 25.0) {
      Serial.println("Temperatura muito quente");
      BTSerial.println("Temperatura muito quente");
      tone(pinBuzzer, 2000); //nessa função eu to pedindo para acionar buzzer se a  temperatura  estiver quente (2000 Hz)
      delay(500);
      noTone(pinBuzzer);
    }
  }

  // aqui ele vai separar a próxima leitura para ficar organizado 
  Serial.println("___________________________________");
  BTSerial.println("___________________________________");

  // aqui to pedindo para aguardar 3 segundos
  delay(3000);
}
