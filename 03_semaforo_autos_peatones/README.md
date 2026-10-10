# Circuito 3: Semáforo Sincronizado para Autos y Peatones

## 1. Análisis de Seguridad Vial
Un sistema de semáforos integrado vehicular-peatonal debe garantizar condiciones estrictas de **exclusión mutua**:
* Jamás pueden coexistir luz verde para autos y luz verde para personas.
* Todo cambio entre fases debe respetar tiempos de despeje de calzada (*Clearance Intervals*).
* Antes de finalizar el paso peatonal, se incluye una alerta mediante **parpadeo de luz**, otorgando a los peatones en la senda tiempo suficiente para completar el cruce.

---

## 2. Matriz de Estados de la Secuencia

| Fase | Duración | Autos: Rojo (D4) | Autos: Amarillo (D3) | Autos: Verde (D2) | Peatón: Rojo (D6) | Peatón: Verde (D5) | Acción |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :--- |
| **1** | 6.0 s | OFF | OFF | **ON** | **ON** | OFF | Tráfico vehicular activo |
| **2** | 2.5 s | OFF | **ON** | OFF | **ON** | OFF | Advertencia vehicular |
| **3** | 1.5 s | **ON** | OFF | OFF | **ON** | OFF | Margen de seguridad Todo Rojo |
| **4** | 5.0 s | **ON** | OFF | OFF | OFF | **ON** | Cruce peatonal habilitado |
| **5** | 2.5 s | **ON** | OFF | OFF | OFF | **PARPADEO** | Advertencia de fin de tiempo |
| **6** | 1.0 s | **ON** | OFF | OFF | **ON** | OFF | Despeje final Todo Rojo |

---

## 3. Conexiones en Arduino

| Luz / Módulo | Pin Arduino | Resistencia |
| :--- | :--- | :--- |
| **Auto - Verde** | Pin 2 | 220 Ω |
| **Auto - Amarillo** | Pin 3 | 220 Ω |
| **Auto - Rojo** | Pin 4 | 220 Ω |
| **Peatón - Verde** | Pin 5 | 220 Ω |
| **Peatón - Rojo** | Pin 6 | 220 Ω |
| **GND Común** | GND | Tierra de retorno |

---

## 4. Archivos
* Código fuente: [`03_semaforo_autos_peatones.ino`](file:///C:/Users/deliz/.gemini/antigravity/scratch/circuitos-semaforos-arduino/03_semaforo_autos_peatones/03_semaforo_autos_peatones.ino)
* Simulación Wokwi: [`diagram.json`](file:///C:/Users/deliz/.gemini/antigravity/scratch/circuitos-semaforos-arduino/03_semaforo_autos_peatones/diagram.json)
