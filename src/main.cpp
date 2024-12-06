#include <Arduino.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

Servo servoGarra;
Servo servoAltura;
Servo servoLejania;
Servo servoEje;

// Pines de los servos
int pinServoGarra = 27;
int pinServoAltura = 12;
int pinServoLejania = 13;
int pinServoEje = 14;

int pasosAngulos = 2;

int anguloServoGarra = 0;
int anguloServoAltura = 10;
int anguloServoLejania = 0;
int anguloServoEje = 0;

bool autonomo = false;

void moverServoAltura(int anguloActual, int anguloObjetivo) {

    if (anguloObjetivo < 10) anguloObjetivo = 10; 
    if (anguloObjetivo > 90) anguloObjetivo = 90;

    Serial.println(anguloObjetivo);

    if (anguloActual < anguloObjetivo) {
        for (; anguloActual < anguloObjetivo; anguloActual += pasosAngulos) {
            servoAltura.write(anguloActual);
            delay(10);
        }
    } else {
        for (; anguloActual > anguloObjetivo; anguloActual -= pasosAngulos) {
            servoAltura.write(anguloActual);
            delay(10);
        }
    }
    anguloServoAltura = anguloObjetivo;
}

void moverServoGarra(int anguloActual, int anguloObjetivo) {

    if (anguloObjetivo < 0) anguloObjetivo = 0; 
    if (anguloObjetivo > 30) anguloObjetivo = 30;

    Serial.println(anguloObjetivo);

    if (anguloActual < anguloObjetivo) {
        for (; anguloActual < anguloObjetivo; anguloActual += pasosAngulos) {
            servoGarra.write(anguloActual);
            delay(10);
        }
    } else {
        for (; anguloActual > anguloObjetivo; anguloActual -= pasosAngulos) {
            servoGarra.write(anguloActual);
            delay(10);
        }
    }
    anguloServoGarra = anguloObjetivo;
}

void moverServoLejania(int anguloActual, int anguloObjetivo) {

    if (anguloObjetivo < 0) anguloObjetivo = 0; 
    if (anguloObjetivo > 110) anguloObjetivo = 110;

    Serial.println(anguloObjetivo);

    if (anguloActual < anguloObjetivo) {
        for (; anguloActual < anguloObjetivo; anguloActual += pasosAngulos) {
            servoLejania.write(anguloActual);
            delay(10);
        }
    } else {
        for (; anguloActual > anguloObjetivo; anguloActual -= pasosAngulos) {
            servoLejania.write(anguloActual);
            delay(10);
        }
    }
    anguloServoLejania = anguloObjetivo;
}

void moverServoEje(int anguloActual, int anguloObjetivo) {

    if (anguloObjetivo < 0) anguloObjetivo = 0; 
    if (anguloObjetivo > 180) anguloObjetivo = 180;

    Serial.println(anguloObjetivo);

    if (anguloActual < anguloObjetivo) {
        for (; anguloActual < anguloObjetivo; anguloActual += pasosAngulos) {
            servoEje.write(anguloActual);
            delay(10);
        }
    } else {
        for (; anguloActual > anguloObjetivo; anguloActual -= pasosAngulos) {
            servoEje.write(anguloActual);
            delay(10);
        }
    }
    anguloServoEje = anguloObjetivo;
}

void reiniciarServos() {
    moverServoAltura(anguloServoAltura, 100);
    moverServoEje(anguloServoEje, 60);
    moverServoGarra(anguloServoGarra, 30);
    moverServoLejania(anguloServoLejania, 0);
}

void setup() {
    servoGarra.attach(pinServoGarra);
    servoAltura.attach(pinServoAltura);
    servoLejania.attach(pinServoLejania);
    servoEje.attach(pinServoEje);

    Serial.begin(115200);

    Dabble.begin("GarraDabble");
}

void loop() {
    Dabble.processInput();

    // Comandos para los servos
    if (autonomo == false)
    {
        if (GamePad.isUpPressed()) {
            moverServoAltura(anguloServoAltura, anguloServoAltura + 10);
            Serial.println("subiendo");
        }
        if (GamePad.isDownPressed()) {
            moverServoAltura(anguloServoAltura, anguloServoAltura - 10);
            Serial.println("bajando");
        }
        if (GamePad.isRightPressed()) {
            moverServoEje(anguloServoEje, anguloServoEje - 10);
            Serial.println("derecha");
        }
        if (GamePad.isLeftPressed()) {
            moverServoEje(anguloServoEje, anguloServoEje + 10);
            Serial.println("izquierda");
        }
        if (GamePad.isCirclePressed()) {
            moverServoGarra(anguloServoGarra, anguloServoGarra + 10);
            Serial.println("cerrando");
        }
        if (GamePad.isCrossPressed()) {
            moverServoGarra(anguloServoGarra, anguloServoGarra - 10);
            Serial.println("abriendo");
        }
        if (GamePad.isSquarePressed()) {
            moverServoLejania(anguloServoLejania, anguloServoLejania + 10);
            Serial.println("delante");
        }
        if (GamePad.isTrianglePressed()) {
            moverServoLejania(anguloServoLejania, anguloServoLejania - 10);
            Serial.println("atras");
        }
        if (GamePad.isStartPressed())
        {
            reiniciarServos();
        }
    } else {
        if (GamePad.isCirclePressed()) {
            // Banda
            moverServoEje(anguloServoEje, 180);
            moverServoAltura(anguloServoAltura, 10);
            moverServoGarra(anguloServoGarra, 15);
            moverServoLejania(anguloServoLejania, 100);
            delay(1000);
            moverServoGarra(anguloServoGarra, 30);
            moverServoLejania(anguloServoLejania, 20);
            moverServoAltura(anguloServoAltura, 180);
            moverServoEje(anguloServoEje, 0);
            moverServoAltura(anguloServoAltura, 10);
            moverServoGarra(anguloServoGarra, 15);
            moverServoLejania(anguloServoLejania, 100);
            moverServoLejania(anguloServoLejania, 0);
            moverServoAltura(anguloServoAltura, 100);
            reiniciarServos();
            Serial.println("secuencia circulo");
        }
        if (GamePad.isCrossPressed()) {
            // Se la jala
            moverServoEje(anguloServoEje, 0);
            moverServoGarra(anguloServoGarra, 30);
            for (size_t i = 0; i < 5; i++)
            {
                moverServoAltura(anguloServoAltura, 180);
                moverServoAltura(anguloServoAltura, 0);
            }
            

            Serial.println("secuencia cruz");
        }
    }
    
    if (GamePad.isSelectPressed())
    {
        autonomo = !autonomo;
        Serial.println("autonomo: " + String(autonomo));
    }
    
    

    delay(50); 
}
