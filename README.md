# Control Digital y Simulación de Semáforos con Arduino

Repositorio completo de análisis, diseño, esquemáticos, código fuente comentado y simulaciones para 4 circuitos digitales progresivos desarrollados sobre plataforma **Arduino Uno**.

---

## 📋 Contenido del Repositorio

1. [Circuito 1: Prender y apagar un LED (Blink con Ley de Ohm)](./01_led_blink/)
2. [Circuito 2: Simulación de Semáforo Americano (Estándar MUTCD)](./02_semaforo_americano/)
3. [Circuito 3: Semáforo para Carros y Personas Sincronizado](./03_semaforo_autos_peatones/)
4. [Circuito 4: Semáforo Inteligente con Botón Peatonal (FSM no bloqueante)](./04_semaforo_boton_peatonal/)
5. [Simulador Visual Interactivo (Navegador Web)](./simulador_interactivo/)

---

## ⚡ 1. Resumen Teórico y Cálculos Eléctricos

Para conectar diodos emisores de luz (LED) a las salidas digitales de un microcontrolador Arduino ($5\text{ V}$), se calcula la resistencia de protección mediante la **Ley de Ohm**:

$$R = \frac{V_{CC} - V_f}{I_d}$$

* **Voltaje de salida del microcontrolador ($V_{CC}$):** $5.0\text{ V}$
* **Tensión directa típica del LED ($V_f$):** $\approx 2.0\text{ V}$ (Rojo/Amarillo/Verde estándar)
* **Corriente de operación recomendada ($I_d$):** $15\text{ mA} = 0.015\text{ A}$
* **Cálculo:** 
  $$R = \frac{5.0\text{ V} - 2.0\text{ V}}{0.015\text{ A}} = 200\,\Omega \implies \mathbf{220\,\Omega\ (Valor\ comercial\ estándar)}$$
* **Potencia disipada en la resistencia:**
  $$P = I_d^2 \cdot R = (0.015\text{ A})^2 \cdot 220\,\Omega \approx 0.0495\text{ W} = 49.5\text{ mW} \ll \frac{1}{4}\text{ W} (250\text{ mW})$$

---

## 🚦 2. Descripción de los Circuitos

### Circuito 1: Blink de LED
* **Objetivo:** Encendido y apagado periódico a $1\text{ Hz}$ ($1000\text{ ms}$ ON, $1000\text{ ms}$ OFF).
* **Pin:** Pin Digital 8 &rarr; Resistencia 220 Ω &rarr; Ánodo (+) LED &rarr; GND.
* **Archivos:** [`01_led_blink.ino`](./01_led_blink/01_led_blink.ino) | [`diagram.json`](./01_led_blink/diagram.json).

### Circuito 2: Semáforo Americano
* **Objetivo:** Reproducir el estándar de control de tráfico de EE.UU. (MUTCD).
* **Secuencia:** Verde ($5\text{ s}$) &rarr; Amarillo ($2\text{ s}$) &rarr; Todo Rojo / All-Red ($1\text{ s}$) &rarr; Rojo ($5\text{ s}$).
* **Pines:** Pin 2 (Verde), Pin 3 (Amarillo), Pin 4 (Rojo).
* **Archivos:** [`02_semaforo_americano.ino`](./02_semaforo_americano/02_semaforo_americano.ino) | [`diagram.json`](./02_semaforo_americano/diagram.json).

### Circuito 3: Semáforo para Autos y Personas
* **Objetivo:** Coordinación simultánea de semáforo vehicular de 3 luces y semáforo peatonal de 2 luces bajo criterios de seguridad vial estricta.
* **Secuencia de seguridad:**
  1. Autos en **Verde** / Peatones en **Rojo** ($6\text{ s}$).
  2. Autos en **Amarillo** / Peatones en **Rojo** ($2.5\text{ s}$).
  3. Despeje All-Red de seguridad ($1.5\text{ s}$).
  4. Autos en **Rojo** / Peatones en **Verde** ($5\text{ s}$).
  5. Autos en **Rojo** / Peatones en **Parpadeo de Advertencia** ($2.5\text{ s}$).
  6. Despeje All-Red final ($1\text{ s}$).
* **Pines:** Autos (Pines 2, 3, 4), Peatones (Pines 5, 6).
* **Archivos:** [`03_semaforo_autos_peatones.ino`](./03_semaforo_autos_peatones/03_semaforo_autos_peatones.ino) | [`diagram.json`](./03_semaforo_autos_peatones/diagram.json).

### Circuito 4: Semáforo con Botón Peatonal (FSM no bloqueante)
* **Objetivo:** Control reactivo por demanda peatonal mediante máquina de estados finitos (`millis()`).
* **Características avanzadas:**
  - **No bloqueante:** No utiliza la función `delay()` para no perder la pulsación del botón.
  - **Debounce:** Filtro anti-rebotes por software de $50\text{ ms}$.
  - **Tiempo mínimo de verde vehicular ($6\text{ s}$):** Previene frenadas bruscas si el botón es presionado de forma inmediata.
  - **Pull-up interno:** Utiliza `INPUT_PULLUP` en el Pin 7 (el botón conmuta a GND).
* **Pines:** Botón (Pin 7), Autos (Pines 2, 3, 4), Peatones (Pines 5, 6).
* **Archivos:** [`04_semaforo_boton_peatonal.ino`](./04_semaforo_boton_peatonal/04_semaforo_boton_peatonal.ino) | [`diagram.json`](./04_semaforo_boton_peatonal/diagram.json).

---

## 💻 3. Simulador Visual en Navegador Web

Este proyecto incluye una interfaz gráfica interactiva lista para ejecutarse directamente en cualquier navegador web:
* Ubicación del archivo: [`simulador_interactivo/index.html`](./simulador_interactivo/index.html)
* **Funcionalidades:**
  - Pestañas independientes para cada uno de los 4 circuitos.
  - Representación fotorrealista de cabezales de semáforo con viseras y resplandor lumínico LED.
  - Voltímetro virtual con telemetría de Ley de Ohm en tiempo real.
  - Botón interactivo de demanda peatonal que alimenta la máquina de estados FSM.
  - Monitor serie virtual integrado.

---

## 🛠️ 4. Guía para Subir este Proyecto a GitHub

Sigue los siguientes comandos desde una terminal de PowerShell o Bash dentro de esta carpeta:

```bash
# 1. Posicionarse en la carpeta del proyecto
cd "C:\Users\deliz\.gemini\antigravity\scratch\circuitos-semaforos-arduino"

# 2. Inicializar el repositorio Git local
git init

# 3. Configurar usuario local (si no lo has configurado antes)
git config user.name "TuNombre"
git config user.email "tu-correo@ejemplo.com"

# 4. Agregar todos los archivos al área de preparación (stage)
git add .

# 5. Crear el primer commit descriptivo
git commit -m "feat: implementacion y simulacion de 4 circuitos de semaforos y led con arduino"

# 6. Renombrar la rama principal a main
git branch -M main

# 7. Vincular con tu repositorio remoto creado en GitHub
# (Crea un nuevo repositorio vacío en github.com y copia su URL)
git remote add origin https://github.com/TU_USUARIO/circuitos-semaforos-arduino.git

# 8. Subir el código a GitHub
git push -u origin main
```

---

## 🌐 5. Simulación Online en Wokwi

Cada circuito cuenta con su respectivo archivo `diagram.json`. Para simularlo en Wokwi:
1. Ingresa a [Wokwi Arduino Uno Simulator](https://wokwi.com/projects/new/arduino-uno).
2. Pega el código `.ino` en la pestaña `sketch.ino`.
3. Pega el contenido de `diagram.json` en la pestaña `diagram.json`.
4. Presiona el botón verde **Start Simulation**.

---

## 📑 6. Registro y Enlaces del Asistente

* **ID de Conversación:** `c8a3b820-2404-4671-9eb5-61fc140e2090`
* **Enlace de la conversación:** [Abrir Conversación](conversation://c8a3b820-2404-4671-9eb5-61fc140e2090)
* **Registro de transcripción:** [transcript.jsonl](file:///C:/Users/deliz/.gemini/antigravity/brain/c8a3b820-2404-4671-9eb5-61fc140e2090/.system_generated/logs/transcript.jsonl)
