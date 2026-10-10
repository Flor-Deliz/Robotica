/*
 * ==============================================================================
 * PROYECTO: Circuito 1 - Prender y Apagar un LED (Blink)
 * AUTOR: Antigravity Assistant & Usuario
 * DESCRIPCIÓN: 
 *   Control digital básico mediante Arduino para encender y apagar un LED
 *   con un intervalo temporizado de 1000 ms (1 Hz).
 * 
 * COMPONENTES:
 *   - 1x Arduino Uno (o Nano / Mega)
 *   - 1x Diodo LED (Color Rojo / Verde / Azul, Vf ≈ 2.0V)
 *   - 1x Resistencia limitadora de 220 Ω (1/4 W)
 *   - 1x Protoboard y cables jumpers
 * 
 * CÁLCULO ELÉCTRICO (Ley de Ohm):
 *   Vcc = 5.0 V (Salida digital en nivel HIGH)
 *   V_led ≈ 2.0 V (Caída de tensión directa del LED)
 *   I_deseada = 15 mA = 0.015 A
 *   R = (Vcc - V_led) / I_deseada = (5.0 - 2.0) / 0.015 = 200 Ω -> Usamos 220 Ω estándar.
 *   Potencia disipada: P = I^2 * R = (0.015)^2 * 220 ≈ 0.05 W (Soporta 1/4W sin problemas).
 * 
 * CONEXIONES:
 *   - Pin Digital 8 de Arduino -> Resistencia 220 Ω -> Ánodo (+) del LED
 *   - Cátodo (-) del LED -> GND (Tierra) de Arduino
 * ==============================================================================
 */

// Definición de pines y constantes
const uint8_t PIN_LED = 8;          // Pin digital conectado al LED
const unsigned long TIEMPO_ON = 1000;   // Duración de encendido en milisegundos (1 segundo)
const unsigned long TIEMPO_OFF = 1000;  // Duración de apagado en milisegundos (1 segundo)

void setup() {
  // Configuración del puerto serie para telemetría y depuración
  Serial.begin(9600);
  Serial.println(F("========================================"));
  Serial.println(F("Circuito 1: Prender y Apagar un LED"));
  Serial.println(F("Sistema inicializado correctamente."));
  Serial.println(F("========================================"));

  // Configuración del pin del LED como salida digital (OUTPUT)
  pinMode(PIN_LED, OUTPUT);

  // Estado inicial seguro: LED apagado
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  // 1. Encender el LED
  digitalWrite(PIN_LED, HIGH);
  Serial.println(F("[ESTADO] LED ENCENDIDO (HIGH - 5V)"));
  delay(TIEMPO_ON); // Espera de 1 segundo

  // 2. Apagar el LED
  digitalWrite(PIN_LED, LOW);
  Serial.println(F("[ESTADO] LED APAGADO (LOW - 0V)"));
  delay(TIEMPO_OFF); // Espera de 1 segundo
}
