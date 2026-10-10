# Circuito 1: Prender y Apagar un LED (Blink)

## 1. Análisis Teórico y Eléctrico
Un diodo emisor de luz (LED) es un dispositivo semiconductor de unión p-n que emite fotones al polarizarse directamente.
Para proteger tanto el LED como el microcontrolador Arduino Uno, se debe calcular la resistencia limitadora de corriente según la **Ley de Ohm**:

$$V_{R} = V_{CC} - V_f$$
$$R = \frac{V_{CC} - V_f}{I_d}$$

### Parámetros:
* Voltaje de salida digital de Arduino ($V_{CC}$): $5.0\text{ V}$ (HIGH)
* Tensión directa del LED rojo ($V_f$): $\approx 2.0\text{ V}$
* Corriente deseada de polarización ($I_d$): $15\text{ mA} = 0.015\text{ A}$
* Cálculo:
  $$R = \frac{5.0\text{ V} - 2.0\text{ V}}{0.015\text{ A}} = \frac{3.0\text{ V}}{0.015\text{ A}} = 200\,\Omega$$

Se selecciona el valor comercial estándar más cercano por encima: **$220\,\Omega$**.

### Disipación de Potencia:
$$P_R = I^2 \cdot R = (0.015\text{ A})^2 \cdot 220\,\Omega \approx 0.0495\text{ W} = 49.5\text{ mW}$$
Una resistencia estándar de $1/4\text{ W}$ ($250\text{ mW}$) opera holgadamente dentro de su rango térmico de seguridad.

---

## 2. Diagrama de Conexiones

| Componente | Terminal | Conexión Arduino | Notas |
| :--- | :--- | :--- | :--- |
| **Resistencia 220 Ω** | Terminal 1 | **Pin Digital 8** | Salida digital |
| **Resistencia 220 Ω** | Terminal 2 | Ánodo (+) del LED | Polarización directa |
| **LED Rojo** | Cátodo (-) | **GND** | Tierra común de Arduino |

---

## 3. Simulación
* **Wokwi:** Abre el archivo [`diagram.json`](file:///C:/Users/deliz/.gemini/antigravity/scratch/circuitos-semaforos-arduino/01_led_blink/diagram.json) directamente en Wokwi o en la extensión Wokwi de VS Code.
* **Código fuente:** [`01_led_blink.ino`](file:///C:/Users/deliz/.gemini/antigravity/scratch/circuitos-semaforos-arduino/01_led_blink/01_led_blink.ino).
