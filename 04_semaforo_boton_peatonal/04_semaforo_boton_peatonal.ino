/*
 * ==============================================================================
 * PROYECTO: Circuito 4 - Semáforo Interactivo con Botón Peatonal (FSM no bloqueante)
 * AUTOR: Antigravity Assistant & Usuario
 * DESCRIPCIÓN:
 *   Sistema semafórico inteligente basado en una Máquina de Estados Finitos (FSM)
 *   no bloqueante mediante millis(). Da prioridad constante al flujo vehicular
 *   hasta que un peatón oprime el pulsador de demanda de cruce.
 * 
 * LÓGICA DE CONTROL E INGENIERÍA VIAL:
 *   1. Estado en Reposo (Flujo Vehicular Normal):
 *      - Autos: VERDE, Peatones: ROJO.
 *   2. Registro de Solicitud Peatonal:
 *      - El peatón oprime el botón conectado al Pin 7 (con INPUT_PULLUP interno).
 *      - Se aplica algoritmo anti-rebote (debounce).
 *      - Se registra la solicitud (solicitudCruce = true).
 *   3. Tiempo Mínimo de Verde Vehicular:
 *      - Para evitar paradas bruscas y accidentes en cadena, se asegura que los
 *        vehículos tengan un tiempo mínimo de luz verde (ej. 6 segundos) antes
 *        de iniciar el cambio de luces.
 *   4. Secuencia Segura de Cruce:
 *      - Autos pasan a AMARILLO (3 segundos).
 *      - Despeje total ALL-RED (1.5 segundos): Ambos en rojo para despejar la vía.
 *      - Peatones pasan a VERDE (5 segundos): Cruce habilitado.
 *      - Peatones en PARPADEO (2.5 segundos): Aviso preventivo de fin de tiempo.
 *      - Despeje final ALL-RED (1 segundo).
 *      - Retorno al verde vehicular y restablecimiento de bandera.
 * 
 * ASIGNACIÓN DE PINES:
 *   - Pin 2: LED Verde Vehicular (CAR_VERDE)
 *   - Pin 3: LED Amarillo Vehicular (CAR_AMARILLO)
 *   - Pin 4: LED Rojo Vehicular (CAR_ROJO)
 *   - Pin 5: LED Verde Peatonal (PEAT_VERDE)
 *   - Pin 6: LED Rojo Peatonal (PEAT_ROJO)
 *   - Pin 7: Pulsador Peatonal (BOTON_PEATON, activo en nivel LOW con INPUT_PULLUP)
 * ==============================================================================
 */

// Pines de salida - Semáforo Vehicular
const uint8_t PIN_CAR_VERDE    = 2;
const uint8_t PIN_CAR_AMARILLO = 3;
const uint8_t PIN_CAR_ROJO     = 4;

// Pines de salida - Semáforo Peatonal
const uint8_t PIN_PEAT_VERDE   = 5;
const uint8_t PIN_PEAT_ROJO    = 6;

// Pin de entrada - Botón de llamada peatonal
const uint8_t PIN_BOTON        = 7;

// Constantes de Temporización (en milisegundos)
const unsigned long T_MINIMO_VERDE_AUTO = 6000; // Mínimo tiempo de verde garantizado
const unsigned long T_AUTOS_AMARILLO    = 3000; // Precaución autos
const unsigned long T_SEGURIDAD_ALL_RED = 1500; // Ambos en rojo
const unsigned long T_PEATON_VERDE      = 5000; // Paso peatonal
const unsigned long T_PEATON_PARPADEO   = 2500; // Advertencia fin de cruce
const unsigned long T_DEBOUNCE_MS       = 50;   // Filtro de rebotes del pulsador
const unsigned long T_PARPADEO_HZ       = 250;  // Período de conmutación del parpadeo

// Definición de Estados de la Máquina de Estados Finitos (FSM)
enum EstadoSemaforo {
  ESTADO_AUTOS_VERDE,        // Vehículos circulando, esperando petición
  ESTADO_AUTOS_AMARILLO,     // Vehículos frenando
  ESTADO_ALL_RED_PRE,        // Despeje de vía (ambos en rojo)
  ESTADO_PEATON_CRUCE,       // Peatón cruzando (peatón verde, auto rojo)
  ESTADO_PEATON_AVISO,       // Peatón parpadeando (aviso de terminación)
  ESTADO_ALL_RED_POST        // Despeje previo a reactivar tránsito vehicular
};

// Variables de estado y tiempo
EstadoSemaforo estadoActual = ESTADO_AUTOS_VERDE;
unsigned long tiempoInicioEstado = 0;
unsigned long tiempoUltimoCambioVerdeAuto = 0;
bool peticionPeatonal = false;

// Variables para Debounce de Botón
int ultimoEstadoBotonLeido = HIGH;
int estadoBotonEstable = HIGH;
unsigned long tiempoUltimoRebote = 0;

// Variables para parpadeo no bloqueante
unsigned long tiempoUltimoToggleParpadeo = 0;
bool estadoLedParpadeo = false;

// Prototipos de funciones
void actualizarLecturaBoton();
void aplicarLuces(bool cV, bool cA, bool cR, bool pV, bool pR);
void transicionarA(EstadoSemaforo nuevoEstado);

void setup() {
  Serial.begin(9600);
  Serial.println(F("=========================================================="));
  Serial.println(F("Circuito 4: Semáforo con Botón Peatonal (FSM No Bloqueante)"));
  Serial.println(F("Iniciando sistema de control vial inteligente..."));
  Serial.println(F("=========================================================="));

  // Configuración de Pines
  pinMode(PIN_CAR_VERDE,    OUTPUT);
  pinMode(PIN_CAR_AMARILLO, OUTPUT);
  pinMode(PIN_CAR_ROJO,     OUTPUT);
  pinMode(PIN_PEAT_VERDE,   OUTPUT);
  pinMode(PIN_PEAT_ROJO,    OUTPUT);

  // Usamos la resistencia interna PULL-UP de Arduino:
  // El botón conecta el pin 7 a GND cuando se presiona (Lectura = LOW)
  pinMode(PIN_BOTON, INPUT_PULLUP);

  // Iniciar en estado normal de tránsito
  transicionarA(ESTADO_AUTOS_VERDE);
  tiempoUltimoCambioVerdeAuto = millis();
}

void loop() {
  unsigned long tiempoActual = millis();

  // 1. Lectura continua y no bloqueante del botón con anti-rebote
  actualizarLecturaBoton();

  // 2. Ejecución de la Máquina de Estados Finitos (FSM)
  switch (estadoActual) {

    case ESTADO_AUTOS_VERDE:
      // Mantener autos en Verde, peatones en Rojo
      aplicarLuces(true, false, false, false, true);

      // Si existe petición registrada y ya se cumplió el tiempo mínimo de verde
      if (peticionPeatonal && (tiempoActual - tiempoUltimoCambioVerdeAuto >= T_MINIMO_VERDE_AUTO)) {
        Serial.println(F("-> Procesando solicitud de peatón: iniciando cambio a Amarillo..."));
        transicionarA(ESTADO_AUTOS_AMARILLO);
      }
      break;

    case ESTADO_AUTOS_AMARILLO:
      aplicarLuces(false, true, false, false, true);
      if (tiempoActual - tiempoInicioEstado >= T_AUTOS_AMARILLO) {
        transicionarA(ESTADO_ALL_RED_PRE);
      }
      break;

    case ESTADO_ALL_RED_PRE:
      aplicarLuces(false, false, true, false, true);
      if (tiempoActual - tiempoInicioEstado >= T_SEGURIDAD_ALL_RED) {
        transicionarA(ESTADO_PEATON_CRUCE);
      }
      break;

    case ESTADO_PEATON_CRUCE:
      // Autos en Rojo, Peatones en Verde
      aplicarLuces(false, false, true, true, false);
      if (tiempoActual - tiempoInicioEstado >= T_PEATON_VERDE) {
        transicionarA(ESTADO_PEATON_AVISO);
      }
      break;

    case ESTADO_PEATON_AVISO:
      // Autos en Rojo, Peatón en parpadeo no bloqueante
      if (tiempoActual - tiempoUltimoToggleParpadeo >= T_PARPADEO_HZ) {
        tiempoUltimoToggleParpadeo = tiempoActual;
        estadoLedParpadeo = !estadoLedParpadeo;
        digitalWrite(PIN_PEAT_VERDE, estadoLedParpadeo ? HIGH : LOW);
      }
      digitalWrite(PIN_CAR_ROJO, HIGH);
      digitalWrite(PIN_PEAT_ROJO, LOW);

      if (tiempoActual - tiempoInicioEstado >= T_PEATON_PARPADEO) {
        digitalWrite(PIN_PEAT_VERDE, LOW);
        transicionarA(ESTADO_ALL_RED_POST);
      }
      break;

    case ESTADO_ALL_RED_POST:
      aplicarLuces(false, false, true, false, true);
      if (tiempoActual - tiempoInicioEstado >= T_SEGURIDAD_ALL_RED) {
        // Restablecer bandera de petición y volver a verde vehicular
        peticionPeatonal = false;
        tiempoUltimoCambioVerdeAuto = millis();
        transicionarA(ESTADO_AUTOS_VERDE);
        Serial.println(F("-> Ciclo peatonal finalizado. Tránsito vehicular reactivado."));
      }
      break;
  }
}

/**
 * Función que implementa debounce por software para detectar pulsación limpia.
 */
void actualizarLecturaBoton() {
  int lectura = digitalRead(PIN_BOTON);

  if (lectura != ultimoEstadoBotonLeido) {
    tiempoUltimoRebote = millis();
  }

  if ((millis() - tiempoUltimoRebote) > T_DEBOUNCE_MS) {
    if (lectura != estadoBotonEstable) {
      estadoBotonEstable = lectura;

      // Al detectar flanco de bajada (LOW = botón presionado con INPUT_PULLUP)
      if (estadoBotonEstable == LOW) {
        if (!peticionPeatonal) {
          peticionPeatonal = true;
          Serial.println(F("[BOTÓN] ¡Pulsador Peatonal Presionado! Petición registrada en memoria."));
        } else {
          Serial.println(F("[BOTÓN] Petición ya registrada, esperando ventana segura de cambio."));
        }
      }
    }
  }

  ultimoEstadoBotonLeido = lectura;
}

/**
 * Cambia el estado actual y reinicia la referencia de tiempo.
 */
void transicionarA(EstadoSemaforo nuevoEstado) {
  estadoActual = nuevoEstado;
  tiempoInicioEstado = millis();

  switch (nuevoEstado) {
    case ESTADO_AUTOS_VERDE:
      Serial.println(F("[ESTADO] Tráfico Vehicular Libre (Verde Autos / Rojo Peatones)"));
      break;
    case ESTADO_AUTOS_AMARILLO:
      Serial.println(F("[ESTADO] Transición Vehicular (Amarillo Autos / Rojo Peatones)"));
      break;
    case ESTADO_ALL_RED_PRE:
      Serial.println(F("[ESTADO] Despeje de Seguridad Pre-Cruce (All-Red: Ambos Rojo)"));
      break;
    case ESTADO_PEATON_CRUCE:
      Serial.println(F("[ESTADO] Cruce Peatonal Habilitado (Rojo Autos / Verde Peatones)"));
      break;
    case ESTADO_PEATON_AVISO:
      Serial.println(F("[ESTADO] Advertencia de Cierre Peatonal (Verde Peatón Parpadeando)"));
      break;
    case ESTADO_ALL_RED_POST:
      Serial.println(F("[ESTADO] Despeje de Seguridad Post-Cruce (All-Red: Ambos Rojo)"));
      break;
  }
}

/**
 * Control directo de salidas de los semáforos.
 */
void aplicarLuces(bool cV, bool cA, bool cR, bool pV, bool pR) {
  digitalWrite(PIN_CAR_VERDE,    cV ? HIGH : LOW);
  digitalWrite(PIN_CAR_AMARILLO, cA ? HIGH : LOW);
  digitalWrite(PIN_CAR_ROJO,     cR ? HIGH : LOW);
  digitalWrite(PIN_PEAT_VERDE,   pV ? HIGH : LOW);
  digitalWrite(PIN_PEAT_ROJO,    pR ? HIGH : LOW);
}
