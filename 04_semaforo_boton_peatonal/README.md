# Circuito 4: Semáforo Inteligente con Botón Peatonal (FSM No Bloqueante)

## 1. Análisis del Problema de Ingeniería
En un cruce con botón de llamada peatonal:
1. **Flujo Prioritario:** El semáforo permanece indefinidamente en verde para vehículos si no hay peatones.
2. **Atención por Demanda:** Cuando una persona pulsa el botón, el microcontrolador no debe ignorar la señal ni congelar el sistema con `delay()`.
3. **Tiempo Mínimo de Verde Vehicular ($T_{min}$):** Si un peatón oprime el botón justo 1 segundo después de que los autos recibieron luz verde, el sistema **no debe** pasar de inmediato a amarillo, pues causaría frenadas de emergencia y colisiones. Se garantiza un mínimo de $6\text{ s}$ de flujo vehicular continuo.
4. **Filtro Anti-rebote (*Debounce*):** Los contactos mecánicos de un pulsador rebotan durante $10\text{ a }30\text{ ms}$, generando múltiples falsos pulsos. Se implementa un filtro temporal de $50\text{ ms}$ por software.

---

## 2. Diagrama de la Máquina de Estados Finitos (FSM)

```
       ┌───────────────────────────────────────────────────────────┐
       │                                                           │
       ▼                                                           │
 [ESTADO_AUTOS_VERDE]                                              │
       │                                                           │
       │ (Pulsador presionado && millis() - tVerde >= 6s)          │
       ▼                                                           │
 [ESTADO_AUTOS_AMARILLO] (3.0s)                                    │
       │                                                           │
       ▼                                                           │
 [ESTADO_ALL_RED_PRE] (1.5s)                                       │
       │                                                           │
       ▼                                                           │
 [ESTADO_PEATON_CRUCE] (5.0s)                                      │
       │                                                           │
       ▼                                                           │
 [ESTADO_PEATON_AVISO] (2.5s con parpadeo)                         │
       │                                                           │
       ▼                                                           │
 [ESTADO_ALL_RED_POST] (1.5s) ─────────────────────────────────────┘
```

---

## 3. Conexiones del Hardware

| Dispositivo | Pin Arduino | Modo Pin | Descripción |
| :--- | :--- | :--- | :--- |
| **Pulsador Peatonal** | **Pin Digital 7** | `INPUT_PULLUP` | Conecta Pin 7 con GND al presionar |
| **LED Auto - Verde** | Pin Digital 2 | `OUTPUT` | Resistencia 220 Ω en serie |
| **LED Auto - Amarillo**| Pin Digital 3 | `OUTPUT` | Resistencia 220 Ω en serie |
| **LED Auto - Rojo** | Pin Digital 4 | `OUTPUT` | Resistencia 220 Ω en serie |
| **LED Peatón - Verde**| Pin Digital 5 | `OUTPUT` | Resistencia 220 Ω en serie |
| **LED Peatón - Rojo** | Pin Digital 6 | `OUTPUT` | Resistencia 220 Ω en serie |

> **Nota de Diseño Eléctrico:** Al usar `pinMode(PIN_BOTON, INPUT_PULLUP)`, Arduino activa su resistencia interna de polarización a 5V ($\approx 20\text{ k}\Omega - 50\text{ k}\Omega$). Esto ahorra una resistencia externa en la protoboard y reduce el ruido eléctrico. Al presionar el botón, el pin lee `LOW` (0V).

---

## 4. Archivos
* Código fuente: [`04_semaforo_boton_peatonal.ino`](file:///C:/Users/deliz/.gemini/antigravity/scratch/circuitos-semaforos-arduino/04_semaforo_boton_peatonal/04_semaforo_boton_peatonal.ino)
* Simulación Wokwi: [`diagram.json`](file:///C:/Users/deliz/.gemini/antigravity/scratch/circuitos-semaforos-arduino/04_semaforo_boton_peatonal/diagram.json)
