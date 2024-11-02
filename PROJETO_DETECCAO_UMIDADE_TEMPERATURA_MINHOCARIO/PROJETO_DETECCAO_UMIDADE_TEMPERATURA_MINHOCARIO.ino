//No total, meu código utiliza cinco bibliotecas
#include <SoftwareSerial.h> //aqui é para comunicação serial com o módulo Bluetooth
#include <Wire.h> // aqui é para comunicação I2C, necessária para o RTC (relógio)
#include <RTClib.h> // aqui é para controlar o módulo RTC DS3231
#include <OneWire.h> //esse é necessária para o sensor de temperatura DS18B20
#include <DallasTemperature.h> //aqui é  para controle do sensor de temperatura DS18B20

// aqui eu to pedindo para defini os pinos RX e TX para o Bluetooth
SoftwareSerial BTSerial(10, 11); 

// já aqui eu to criando o objeto para o RTC (relógio)
RTC_DS3231 rtc;

// nesse momento eu to definindo as portas dos pinos do sensor de umidade, LEDs, sensor de temperatura e buzzer
const int pinUmidade = A0; //aqui é  Pino do sensor de umidade
const int pinVermelho = 5;    
const int pinVerde = 6;   
const int pinAzul = 7;     
const int pinBuzzer = 8;   // essa porta aqui é do pino do buzzer
const int pinTemp = 9;     // já essa aqui é do pino do sensor de temperatura (DS18B20)

// aqui eu fazendo definição  da biblioteca OneWire e DallasTemperature (DS18B20)
OneWire oneWire(pinTemp);
DallasTemperature sensor(&oneWire);
DeviceAddress endereco_temp;

void setup() {
  // aqui eu pedindo para inicia a comunicação serial com o módulo Bluetooth
  BTSerial.begin(9600);
  
  // já aqui eu pedindo para inicia a comunicação serial com o monitor serial
  Serial.begin(9600);

  //aqui eu pedindo para inicia a  RTC (relógio)
  if (!rtc.begin()) {
    Serial.println("RTC não encontrado!");
    while (1);
  }

  // essa parte é se o RTC estiver sem a hora definida,eu peço para configura na hora atual 
  if (rtc.lostPower()) {
    Serial.println("RTC perdeu a energia! Configurando a hora...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // aqui eu to pedindo para sincroniza com o horario 
    // do computador que estamos utilizando 
  }

  // nessa parte  eu to pedindo para inicia a  o sensor de temperatura (DS18B20)
  sensor.begin();

  // já essa parte eu to definindo os pinos dos LEDs e do buzzer como saída
  pinMode(pinVermelho, OUTPUT);
  pinMode(pinVerde, OUTPUT);
  pinMode(pinAzul, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  // já aqui eu quero mostra uma Mensagem que o programa ta iniciando e ta tudo ok
  Serial.println("Sistema iniciado com sucesso!");
  BTSerial.println("Sistema iniciado com sucesso!");
}

void loop() {
  // esse é parte é hora atual do RTC que eu to pedindo 
  DateTime now = rtc.now();

  // aqui eu quero que mostre o horário como string (hh:mm)
  String timeString = String(now.hour()) + ":" + String(now.minute());

  // nessa parte eu quero Leia os valores da umidade
  int umidadeValor = analogRead(pinUmidade);
  umidadeValor = map(umidadeValor, 0, 1023, 100, 0); // eu quero que ele faça o mapeamento da umidade de 0 a 100% 

  // to fazendo o controle dos LEDs de acordo a umidade a cada valor tem uma cor diferente 
  if (umidadeValor < 60) {
    analogWrite(pinVermelho, 255); //aqui o solo estar  muito seco ai vai acende um leds da cor vermelha 
    analogWrite(pinVerde, 0);
    analogWrite(pinAzul, 0);
    Serial.println("Solo do minhocário seco!");
    BTSerial.println("Solo do minhocário seco!");
  } else if (umidadeValor >= 60 && umidadeValor <= 70) {
    analogWrite(pinVermelho, 0);
    analogWrite(pinVerde, 255); // já aqui o solo estar ideal ai vai acende um leds da  cor verde 
    analogWrite(pinAzul, 0);
    Serial.println("Solo do minhocário ideal!");
    BTSerial.println("Solo do minhocário ideal!");
  } else {
    analogWrite(pinVermelho, 0);
    analogWrite(pinVerde, 0);
    analogWrite(pinAzul, 255); // já nesse daqui o solo estar muito umido ai vai acende um leds da  cor azul 
    Serial.println("Solo do minhocário muito úmido!");
    BTSerial.println("Solo do minhocário muito úmido!");
  }

  // essa parte eu  quero mostre a  umidade e hora atual juntos
  Serial.println("Umidade: " + String(umidadeValor) + "%");
  BTSerial.println("Umidade: " + String(umidadeValor) + "%");
  Serial.println("Hora atual: " + timeString);
  BTSerial.println("Hora atual: " + timeString);

  // eu quero que  ele me informe ser sensor o de temperatura DS18B20 estar conectado
  sensor.requestTemperatures();
  if (!sensor.getAddress(endereco_temp, 0)) {
    Serial.println("SENSOR DE TEMPERATURA NÃO CONECTADO");
  } else {
    //aqui eu to chamando um método getTempC do objeto sensor de temperatura e
    //o método recebe um parâmetro chamado endereco_temp, que é um identificador como endereço do sensor.
    float temperatura = sensor.getTempC(endereco_temp);
    Serial.print("Temperatura = ");
    Serial.println(temperatura, 1);
    BTSerial.print("Temperatura = ");
    BTSerial.println(temperatura, 1);

    // nessa parte to pedindo para controlar a temperatura e o buzzer junto
 //   esta linha enviará a mensagem "Temperatura ideal" 
    if (temperatura >= 20.0 && temperatura <= 25.0) {
      Serial.println("Temperatura ideal");
      BTSerial.println("Temperatura ideal");
      noTone(pinBuzzer); //nessa parte eu peço para desligar o buzzer se a temperatura estiver ideal
    } else if (temperatura < 20.0) {
      Serial.println("Temperatura muito fria");
      BTSerial.println("Temperatura muito fria");
      tone(pinBuzzer, 1000); // aqui to pedindo pra aciona o buzzer se a temperatura estiver fria 
      //ele vai emita um som com uma frequência de 1000 Hz.
      delay(500);// aqui to pedindo aguarda meio segundo
      noTone(pinBuzzer);
    } else if (temperatura > 25.0) {
      Serial.println("Temperatura muito quente");
      BTSerial.println("Temperatura muito quente");
      tone(pinBuzzer, 2000); //aqui to pedindo pra aciona o buzzer se a temperatura estiver quente 
      //ele vai emita um som com uma frequência de 2000 Hz.
      delay(500);
      noTone(pinBuzzer);
    }
  }

  //aqui to separando com uma linha  para deixar mais organizado
  Serial.println("___________________________________");
  BTSerial.println("___________________________________");

  // aqui to pedindo para aguardar 3 segundos
  delay(3000);
}
