int pino2 = 2;      //Cria uma variável para o pino 2
bool estado_sensor; //Cria uma variável para armazenar o estado do sensor

#include <UIPEthernet.h>
#include <utility/logging.h>
#include <PubSubClient.h>

#include <SPI.h>
boolean mensagem;

//Define o endereço MAC que será utilizado
byte mac[] = {0X1E, 0X97, 0XC3, 0X49, 0XD5, 0XF2};

//Inicia o cliente Ethernet
EthernetClient client;

PubSubClient mqqtClient(client); // Inicia o cliente PubSubClient

void setup()
{
    //Inicia o controlador Ethernet e solicita um IP para o servidor de DHCP
    Ethernet.begin(mac);

    //Inicia o monitor Serial
    Serial.begin(9600);

    pinMode(pino2, INPUT_PULLUP);

    mqqtClient.setServer("3.87.59.89", 1883);

    //Exibe no Monitor Serial as informações sobre o IP do Arduino
    Serial.print("O IP do Arduino e: ");
    Serial.println(Ethernet.localIP());

    //Exibe no Monitor Serial as informações sobre a Máscara de Rede do Arduino
    Serial.print("A Mascara de Rede do Arduino e: ");
    Serial.println(Ethernet.subnetMask());

    //Exibe no Monitor Serial as informações sobre o Gateway do Arduino
    Serial.print("O Gateway do Arduino e: ");
    Serial.println(Ethernet.gatewayIP());

    //Exibe uma linha em branco
    Serial.println("");
}

void loop()
{
    mqqtClient.connect("alexsander"); //Define o nome do cliente MQTT

    estado_sensor = digitalRead(pino2);

    if (estado_sensor == 1)
    {
        mensagem = mqqtClient.publish("alexsander-t", " RACK ABERTO ! ");
    }
    else
    {
        mensagem = mqqtClient.publish("alexsander-t", " RACK FECHADO ! ");
    }
    mqqtClient.loop();

    Serial.println(mensagem);

    delay(500);
}