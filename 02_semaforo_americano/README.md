# Circuito 2: Simulación de Semáforo Americano (MUTCD)

## 1. Análisis del Sistema
El estándar norteamericano (*Manual on Uniform Traffic Control Devices - MUTCD*) rige la señalización vial en EE. UU.
A diferencia de otros estándares internacionales:
1. **Verde:** Permite el flujo continuo del tráfico vehicular.
2. **Amarillo:** Advierte el cambio inminente a rojo y provee tiempo de detención o despeje de la intersección.
3. **All-Red:** Margen de seguridad donde todos los accesos permanecen en rojo.
4. **Rojo:** Alto obligatorio.
*En el estándar americano no existe la combinación Rojo+Amarillo simultánea previa al Verde.*

---

## 2. Diagrama de Estados y Temporización

```
  ┌────────────────┐
  │  VERDE (5.0s)  │ ──► Autos avanzan
  └───────┬────────┘
          ▼
  ┌────────────────┐
  │ AMARILLO (2.0s)│ ──► Precaución / Frenado
  └───────┬────────┘
          ▼
  ┌────────────────┐
  │ ALL-RED (1.0s) │ ──► Despeje de seguridad de la intersección
  └───────┬────────┘
          ▼
  ┌────────────────┐
  │   ROJO (5.0s)  │ ──► Detención obligatoria
  └───────┬────────┘
          │
          └───────────► Vuelve a VERDE
```

---

## 3. Conexiones Físicas

| Componente | Pin Arduino | Resistencia | Color Cable |
| :--- | :--- | :--- | :--- |
| **LED Verde** | Pin Digital 2 | 220 Ω en serie | Verde |
| **LED Amarillo** | Pin Digital 3 | 220 Ω en serie | Naranja / Amarillo |
| **LED Rojo** | Pin Digital 4 | 220 Ω en serie | Rojo |
| **Cátodos de LEDs** | GND | - | Negro (Común) |

---

## 4. Archivos
* Código fuente: [`02_semaforo_americano.ino`](file:///C:/Users/deliz/.gemini/antigravity/scratch/circuitos-semaforos-arduino/02_semaforo_americano/02_semaforo_americano.ino)
* Simulación Wokwi: [`diagram.json`](file:///C:/Users/deliz/.gemini/antigravity/scratch/circuitos-semaforos-arduino/02_semaforo_americano/diagram.json)
