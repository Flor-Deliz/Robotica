/*
 * ==============================================================================
 * PROYECTO: Circuito 3 - Semáforo para Carros y Personas (Sincronizado)
 * AUTOR: Antigravity Assistant & Usuario
 * DESCRIPCIÓN:
 *   Control sincronizado entre un semáforo vehicular de tres luces (Verde, 
 *   Amarillo, Rojo) y un semáforo peatonal de dos luces (Verde "Caminar", 
 *   Rojo "No Caminar").
 * 
 * LÓGICA DE SEGURIDAD VIAL:
 *   - En NINGÚN momento pueden coincidir Verde de autos con Verde de peatones.
 *   - Existe un período de transición (Amarillo vehicular) para despejar vehículos.
 *   - Período "All-Red" (ambos en Rojo) antes de habilitar el paso peatonal.
 *   - Parpadeo del Verde peatonal previo al corte para alertar que el tiempo de cruce finaliza.
 * 
 * PINES ASIGNADOS:
 *   Vehicular:
 *     - Pin 2: LED Verde Vehicular (CAR_VERDE)
 *     - Pin 3: LED Amarillo Vehicular (CAR_AMARILLO)
 *     - Pin 4: LED Rojo Vehicular (CAR_ROJO)
 *   Peatonal:
 *     - Pin 5: LED Verde Peatonal (PEATON_VERDE / WALK)
 *     - Pin 6: LED Rojo Peatonal (PEATON_ROJO / DONT_WALK)
 * 
 * COMPONENTES:
 *   - 1x Arduino Uno
 *   - 5x Resistencias de 220 Ω
 *   - 2x LEDs Verdes, 1x LED Amarillo, 2x LEDs Rojos
 * ==============================================================================
 */

// Definición de Pines - Semáforo Vehicular
const uint8_t PIN_CAR_VERDE    = 2;
const uint8_t PIN_CAR_AMARILLO = 3;
const uint8_t PIN_CAR_ROJO     = 4;

// Definición de Pines - Semáforo Peatonal
const uint8_t PIN_PEAT_VERDE   = 5;
const uint8_t PIN_PEAT_ROJO    = 6;

// Duraciones de tiempo en milisegundos
const unsigned long T_AUTOS_VERDE        = 6000; // Paso vehicular
const unsigned long T_AUTOS_AMARILLO     = 2500; // Transición vehicular
const unsigned long T_DESPEJE_ALL_RED    = 1500; // Seguridad: autos rojo, peatón rojo
const unsigned long T_PEATON_VERDE       = 5000; // Paso peatonal firme
const unsigned long T_PEATON_PARPADEO    = 2500; // Parpadeo peatonal de aviso

// Funciones controladoras
void setSemaforos(bool carV, bool carA, bool carR, bool peatV, bool peatR);
void parpadearVerdePeatonal(unsigned long duracionTotal, unsigned int periodoMs);

void setup() {
  Serial.begin(9600);
  Serial.println(F("=================================================="));
  Serial.println(F("Circuito 3: Semáforo Sincronizado Autos y Peatones"));
  Serial.println(F("Iniciando controlador de tráfico y peatones..."));
  Serial.println(F("=================================================="));

  // Configuración de pines como salidas digitales
  pinMode(PIN_CAR_VERDE,    OUTPUT);
  pinMode(PIN_CAR_AMARILLO, OUTPUT);
  pinMode(PIN_CAR_ROJO,     OUTPUT);
  pinMode(PIN_PEAT_VERDE,   OUTPUT);
  pinMode(PIN_PEAT_ROJO,    OUTPUT);

  // Inicializar en estado seguro (Todos en rojo)
  setSemaforos(false, false, true, false, true);
  delay(1000);
}

void loop() {
  // --------------------------------------------------------------------------
  // FASE 1: TRÁFICO VEHICULAR ACTIVO
  // Autos: VERDE | Peatones: ROJO (Detención)
  // --------------------------------------------------------------------------
  Serial.println(F("[FASE 1] Vehículos: VERDE | Peatones: ROJO (No cruzar)"));
  setSemaforos(true, false, false, false, true);
  delay(T_AUTOS_VERDE);

  // --------------------------------------------------------------------------
  // FASE 2: ADVERTENCIA VEHICULAR
  // Autos: AMARILLO | Peatones: ROJO
  // --------------------------------------------------------------------------
  Serial.println(F("[FASE 2] Vehículos: AMARILLO | Peatones: ROJO (Precaución)"));
  setSemaforos(false, true, false, false, true);
  delay(T_AUTOS_AMARILLO);

  // --------------------------------------------------------------------------
  // FASE 3: INTERVALO DE SEGURIDAD (ALL-RED)
  // Autos: ROJO | Peatones: ROJO
  // --------------------------------------------------------------------------
  Serial.println(F("[FASE 3] Seguridad (ALL-RED): Todos en ROJO"));
  setSemaforos(false, false, true, false, true);
  delay(T_DESPEJE_ALL_RED);

  // --------------------------------------------------------------------------
  // FASE 4: CRUCE PEATONAL HABILITADO
  // Autos: ROJO | Peatones: VERDE (Paso libre)
  // --------------------------------------------------------------------------
  Serial.println(F("[FASE 4] Vehículos: ROJO | Peatones: VERDE (Cruce seguro)"));
  setSemaforos(false, false, true, true, false);
  delay(T_PEATON_VERDE);

  // --------------------------------------------------------------------------
  // FASE 5: AVISO DE FIN DE CRUCE PEATONAL (PARPADEO)
  // Autos: ROJO | Peatones: VERDE PARPADEANTE
  // --------------------------------------------------------------------------
  Serial.println(F("[FASE 5] Peatones: VERDE PARPADEANDO (Apresure el paso)"));
  parpadearVerdePeatonal(T_PEATON_PARPADEO, 500);

  // --------------------------------------------------------------------------
  // FASE 6: CIERRE PEATONAL Y DESPEJE FINAL
  // Autos: ROJO | Peatones: ROJO
  // --------------------------------------------------------------------------
  Serial.println(F("[FASE 6] Cierre Peatonal: Peatón ROJO, Vehículos preparando"));
  setSemaforos(false, false, true, false, true);
  delay(T_DESPEJE_ALL_RED);
}

/**
 * Establece el estado lógico de los 5 indicadores lumínicos de forma coordinada.
 */
void setSemaforos(bool carV, bool carA, bool carR, bool peatV, bool peatR) {
  digitalWrite(PIN_CAR_VERDE,    carV  ? HIGH : LOW);
  digitalWrite(PIN_CAR_AMARILLO, carA  ? HIGH : LOW);
  digitalWrite(PIN_CAR_ROJO,     carR  ? HIGH : LOW);
  digitalWrite(PIN_PEAT_VERDE,   peatV ? HIGH : LOW);
  digitalWrite(PIN_PEAT_ROJO,    peatR ? HIGH : LOW);
}

/**
 * Realiza el parpadeo del LED verde peatonal mientras mantiene el rojo vehicular.
 */
void parpadearVerdePeatonal(unsigned long duracionTotal, unsigned int periodoMs) {
  unsigned long inicio = millis();
  bool estadoLed = true;

  while (millis() - inicio < duracionTotal) {
    digitalWrite(PIN_PEAT_VERDE, estadoLed ? HIGH : LOW);
    estadoLed = !estadoLed;
    delay(periodoMs / 2);
  }
  // Al terminar el parpadeo, apagar el verde
  digitalWrite(PIN_PEAT_VERDE, LOW);
}
