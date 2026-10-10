/*
 * ==============================================================================
 * PROYECTO: Circuito 2 - Simulación de Semáforo Americano
 * AUTOR: Antigravity Assistant & Usuario
 * DESCRIPCIÓN:
 *   Simula el ciclo tradicional de un semáforo vehicular según el estándar
 *   estadounidense (MUTCD - Manual on Uniform Traffic Control Devices).
 * 
 * SECUENCIA DE OPERACIÓN:
 *   1. VERDE (Go): Flujo vehicular activo (Duración: 5.0 s).
 *   2. AMARILLO (Caution): Intervalo de cambio/despeje vehicular (Duración: 2.0 s).
 *   3. TODO ROJO (All-Red Clearance): Intervalo de seguridad entre fases (Duración: 1.0 s).
 *   4. ROJO (Stop): Detención obligatoria de vehículos (Duración: 5.0 s).
 *   5. Regresa a VERDE.
 * 
 * COMPONENTES:
 *   - 1x Arduino Uno
 *   - 1x LED Verde (Pin Digital 2)
 *   - 1x LED Amarillo (Pin Digital 3)
 *   - 1x LED Rojo (Pin Digital 4)
 *   - 3x Resistencias de 220 Ω (1/4 W)
 *   - Protoboard y jumpers
 * 
 * CONEXIONES:
 *   - Pin 2 -> Resistencia 220 Ω -> Ánodo (+) LED Verde -> Cátodo (-) -> GND
 *   - Pin 3 -> Resistencia 220 Ω -> Ánodo (+) LED Amarillo -> Cátodo (-) -> GND
 *   - Pin 4 -> Resistencia 220 Ω -> Ánodo (+) LED Rojo -> Cátodo (-) -> GND
 * ==============================================================================
 */

// Asignación de pines de salida digital
const uint8_t PIN_VERDE    = 2;
const uint8_t PIN_AMARILLO = 3;
const uint8_t PIN_ROJO     = 4;

// Temporizaciones en milisegundos (ajustables)
const unsigned long TIEMPO_VERDE    = 5000; // 5 segundos
const unsigned long TIEMPO_AMARILLO = 2000; // 2 segundos
const unsigned long TIEMPO_ALL_RED  = 1000; // 1 segundo (seguridad de despeje)
const unsigned long TIEMPO_ROJO     = 5000; // 5 segundos

// Prototipo de función auxiliar para control de estados
void establecerLuces(bool verde, bool amarillo, bool rojo);

void setup() {
  Serial.begin(9600);
  Serial.println(F("========================================"));
  Serial.println(F("Circuito 2: Semáforo Americano (Vehicular)"));
  Serial.println(F("Iniciando secuencia de semáforo..."));
  Serial.println(F("========================================"));

  // Configurar los pines de los LEDs como salidas digitales
  pinMode(PIN_VERDE, OUTPUT);
  pinMode(PIN_AMARILLO, OUTPUT);
  pinMode(PIN_ROJO, OUTPUT);

  // Inicializar en estado de seguridad: Todo Apagado
  establecerLuces(false, false, false);
}

void loop() {
  // FASE 1: VERDE - Tráfico en marcha
  Serial.println(F("[FASE 1] Semáforo en VERDE (Avance permitido)"));
  establecerLuces(true, false, false);
  delay(TIEMPO_VERDE);

  // FASE 2: AMARILLO - Precaución / Tiempo de cambio
  Serial.println(F("[FASE 2] Semáforo en AMARILLO (Precaución, frenar si es seguro)"));
  establecerLuces(false, true, false);
  delay(TIEMPO_AMARILLO);

  // FASE 3: ALL-RED - Margen de despeje de intersección
  Serial.println(F("[SEGURIDAD] Intervalo Todo Rojo (Despeje de intersección)"));
  establecerLuces(false, false, true);
  delay(TIEMPO_ALL_RED);

  // FASE 4: ROJO - Detención total
  Serial.println(F("[FASE 3] Semáforo en ROJO (Detención obligatoria)"));
  establecerLuces(false, false, true);
  delay(TIEMPO_ROJO);
}

/**
 * Función auxiliar para fijar el estado de las tres luminarias de forma segura.
 * Garantiza que sólo las luces deseadas estén activas.
 */
void establecerLuces(bool verde, bool amarillo, bool rojo) {
  digitalWrite(PIN_VERDE,    verde    ? HIGH : LOW);
  digitalWrite(PIN_AMARILLO, amarillo ? HIGH : LOW);
  digitalWrite(PIN_ROJO,     rojo     ? HIGH : LOW);
}
