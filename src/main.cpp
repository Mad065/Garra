#include <Arduino.h>
#include <ESP32Servo.h>
#include <BluetoothSerial.h>


BluetoothSerial SerialBT;

Servo servoGarra;
Servo servoAltura;
Servo servoLejania;
Servo servoEje;

int pinServoGarra = 27;
int pinServoAltura = 12;
int pinServoLejania = 13;
int pinServoEje = 14;

int pasosAngulos = 2;

int anguloServoGarra = 0;
int anguloServoAltura = 0;
int anguloServoLejania = 0;
int anguloServoEje = 0;

void limpiarBuffer() {
    while (SerialBT.available()) {
        SerialBT.read();  // Descartar todo lo que esté en el búfer
    }
}

void moverServo(Servo &servo, int &anguloActual, int anguloObjetivo) {
    if (anguloObjetivo < 0) anguloObjetivo = 0; // Limite inferior
    if (anguloObjetivo > 180) anguloObjetivo = 180; // Limite superior

    if (anguloActual < anguloObjetivo) {
        for (; anguloActual < anguloObjetivo; anguloActual += pasosAngulos) {
            servo.write(anguloActual);
            delay(10);
        }
    } else {
        for (; anguloActual > anguloObjetivo; anguloActual -= pasosAngulos) {
            servo.write(anguloActual);
            delay(10);
        }
    }
}

void setup() {
    servoGarra.attach(pinServoGarra);
    servoAltura.attach(pinServoAltura);
    servoLejania.attach(pinServoLejania);
    servoEje.attach(pinServoEje);

    Serial.begin(9600);
    SerialBT.begin(57600);

    if (!SerialBT.begin("ESP32_Garra", true)) {
        Serial.println("Error al iniciar el Bluetooth");
        return;
    }
    Serial.println("Cliente Bluetooth iniciado. Conectando al servidor...");
}

void loop() {
    if (SerialBT.available()) {
        char command = SerialBT.read();
        Serial.println(command);

        switch (command) {
            case 'U':
                moverServo(servoAltura, anguloServoAltura, anguloServoAltura + 10);
                break;
            case 'D':
                moverServo(servoAltura, anguloServoAltura, anguloServoAltura - 10);
                break;
            case 'R':
                moverServo(servoEje, anguloServoEje, anguloServoEje + 10);
                break;
            case 'L':
                moverServo(servoEje, anguloServoEje, anguloServoEje - 10);
                break;
            case 'O':
                moverServo(servoGarra, anguloServoGarra, anguloServoGarra + 10);
                break;
            case 'C':
                moverServo(servoGarra, anguloServoGarra, anguloServoGarra - 10);
                break;
            case 'F':
                moverServo(servoLejania, anguloServoLejania, anguloServoLejania + 10);
                break;
            case 'B':
                moverServo(servoLejania, anguloServoLejania, anguloServoLejania - 10);
                break;
            default:
                limpiarBuffer();
                break;
        }
    }
    
    if (SerialBT.available() > 100) {
        limpiarBuffer();  // Limpiar el búfer
        Serial.println("Búfer lleno, limpiado.");
    }
    delay(100);
}