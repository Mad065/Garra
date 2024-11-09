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
int anguloServoAltura = 0;
int anguloServoLejania = 0;
int anguloServoEje = 0;

void moverServo(Servo *servo, int anguloActual, int anguloObjetivo) {
    if (servo == &servoGarra)
    {
        if (anguloObjetivo < 0) anguloObjetivo = 0; 
        if (anguloObjetivo > 30) anguloObjetivo = 30;
    }

    if (servo == &servoAltura)
    {
        if (anguloObjetivo < 0) anguloObjetivo = 10; 
        if (anguloObjetivo > 180) anguloObjetivo = 100;
    }

    if (servo == &servoLejania)
    {
        if (anguloObjetivo < 0) anguloObjetivo = 0; 
        if (anguloObjetivo > 180) anguloObjetivo = 110;
    }

    if (servo == &servoEje)
    {
        if (anguloObjetivo < 0) anguloObjetivo = 0; 
        if (anguloObjetivo > 180) anguloObjetivo = 180;
    }
    
    Serial.println(anguloObjetivo);

    if (anguloActual < anguloObjetivo) {
        for (; anguloActual < anguloObjetivo; anguloActual += pasosAngulos) {
            servo->write(anguloActual);
            delay(10);
        }
    } else {
        for (; anguloActual > anguloObjetivo; anguloActual -= pasosAngulos) {
            servo->write(anguloActual);
            delay(10);
        }
    }
}

void reiniciarServos() {
    moverServo(&servoAltura, anguloServoAltura, 100);
    moverServo(&servoEje, anguloServoEje, 60);
    moverServo(&servoGarra, anguloServoGarra, 30);
    moverServo(&servoLejania, anguloServoLejania, 0);
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
    if (GamePad.isUpPressed()) {
        moverServo(&servoAltura, anguloServoAltura, anguloServoAltura + 10);
        Serial.println("subiendo");
    }
    if (GamePad.isDownPressed()) {
        moverServo(&servoAltura, anguloServoAltura, anguloServoAltura - 10);
        Serial.println("bajando");
    }
    if (GamePad.isRightPressed()) {
        moverServo(&servoEje, anguloServoEje, anguloServoEje + 10);
        Serial.println("derecha");
    }
    if (GamePad.isLeftPressed()) {
        moverServo(&servoEje, anguloServoEje, anguloServoEje - 10);
        Serial.println("izquierda");
    }
    if (GamePad.isCirclePressed()) {
        moverServo(&servoGarra, anguloServoGarra, anguloServoGarra + 10);
        Serial.println("abriendo");
    }
    if (GamePad.isCrossPressed()) {
        moverServo(&servoGarra, anguloServoGarra, anguloServoGarra - 10);
        Serial.println("cerrando");
    }
    if (GamePad.isSquarePressed()) {
        moverServo(&servoLejania, anguloServoLejania, anguloServoLejania + 10);
        Serial.println("delante");
    }
    if (GamePad.isTrianglePressed()) {
        moverServo(&servoLejania, anguloServoLejania, anguloServoLejania - 10);
        Serial.println("atras");
    }
    if (GamePad.isStartPressed())
    {
        reiniciarServos();
    }
    

    delay(50); 
}
