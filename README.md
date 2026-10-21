# 🏧 Cajero Automático (ATM System in C++)

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Console-lightgrey.svg)]()

Consola interactiva que simula el funcionamiento de un Cajero Automático desarrollado en C++. Incluye autenticación por PIN con control de intentos, operaciones bancarias básicas, comisiones por transferencia y validaciones de límites transaccionales y de formato de entrada.

---

## 📋 Características Clave

- **Autenticación Segura:**
  - Límite de **3 intentos** para ingresar el PIN de 4 dígitos antes del bloqueo de la tarjeta.
- **Gestión de Saldos y Transacciones:**
  - Consulta de saldo actual.
  - Depósitos con límite máximo de **$10,000.00** por operación.
  - Retiros limitados a montos **múltiplos de 5** y un tope acumulado diario de **$2,000.00**.
  - Transferencias a cuentas de 8 dígitos con cálculo automático de **comisión del 1%**.
- **Control de Formato y Robustez:**
  - Limpieza del búfer de entrada (`cin.clear()` / `cin.ignore()`) para evitar bucles infinitos ante entradas no numéricas o con caracteres especiales.

---

## 📊 Plan de Pruebas (Casos de Uso)

A continuación se detallan los **10 casos de prueba** diseñados para verificar tanto los flujos normales como el manejo de errores y casos límite:

- **TC01 - Autenticación Exitosa**
  - **Entrada:** PIN correcto (`2026`).
  - **Salida / Comportamiento:** Muestra el mensaje de bienvenida y despliega el menú principal de operaciones en pantalla.

- **TC02 - Bloqueo por PIN Incorrecto**
  - **Entrada:** Tres PINs erróneos consecutivos (`1111`, `2222`, `3333`).
  - **Salida / Comportamiento:** Muestra un mensaje de error por cada intento fallido e imprime la advertencia de tarjeta bloqueada al tercer intento, finalizando la ejecución.

- **TC03 - Depósito Válido**
  - **Entrada:** Opción del menú de depósito (`2`) y monto válido (`250.00`).
  - **Salida / Comportamiento:** Suma el monto al saldo anterior ($500) y muestra "Depósito exitoso. Saldo actual: 750.00".

- **TC04 - Límite Excedido en Depósito**
  - **Entrada:** Opción del menú de depósito (`2`) y monto superior al permitido (`15000`).
  - **Salida / Comportamiento:** Muestra el mensaje de error indicando que el depósito máximo permitido por operación es de 10,000.00, manteniendo el saldo intacto.

- **TC05 - Retiro Válido**
  - **Entrada:** Opción del menú de retiro (`3`) y monto válido múltiplo de 5 (`100`).
  - **Salida / Comportamiento:** Resta el monto al saldo actual ($500) y muestra "Retiro exitoso. Saldo actual: 400.00".

- **TC06 - Monto no Múltiplo de 5**
  - **Entrada:** Opción del menú de retiro (`3`) y monto no divisible por 5 (`12`).
  - **Salida / Comportamiento:** Muestra el mensaje de error indicando que el monto debe ser múltiplo de 5, sin modificar el saldo de la cuenta.

- **TC07 - Límite Diario de Retiro Excedido**
  - **Entrada:** Opción del menú de retiro (`3`) realizada en dos transacciones consecutivas (`1500` y luego `600`).
  - **Salida / Comportamiento:** La primera transacción procede con éxito, pero la segunda muestra un mensaje de error indicando que se supera el límite diario de retiro establecido en 2,000.00.

- **TC08 - Transferencia Exitosa con Comisión**
  - **Entrada:** Opción del menú de transferencia (`4`), número de cuenta destino (`12345678`) y monto a transferir (`200`).
  - **Salida / Comportamiento:** Calcula la comisión del 1% ($2.00), debita el total de $202.00 del saldo, y muestra la confirmación junto con el saldo actualizado ($298.00).

- **TC09 - Saldo Insuficiente en Transferencia**
  - **Entrada:** Opción del menú de transferencia (`4`), número de cuenta destino (`87654321`) y monto a transferir de valor elevado (`500`).
  - **Salida / Comportamiento:** Detecta que el monto más su comisión excede el saldo disponible actual, mostrando un mensaje de error por saldo insuficiente y cancelando la operación.

- **TC10 - Validación de Entradas con Formato Incorrecto**
  - **Entrada:** Caracteres alfabéticos o símbolos (`abc` o espacios vacíos) en campos numéricos como el PIN o la selección de opciones del menú.
  - **Salida / Comportamiento:** Detecta el error de tipo de dato, limpia el búfer de entrada mediante las funciones de control y vuelve a solicitar el ingreso correcto sin romper la ejecución del programa.

---

## 🛠️ Requisitos e Instalación

### Prerrequisitos
Un compilador de C++ compatible con la norma **C++11** o superior (por ejemplo: `g++`, `clang++` o MSVC).

### Compilación y Ejecución (vía Terminal/Consola)

1. **Clona el repositorio:**
   ```bash
   git clone [https://github.com/tu-usuario/cajero-automatico.git](https://github.com/tu-usuario/cajero-automatico.git)
   cd cajero-automatico
