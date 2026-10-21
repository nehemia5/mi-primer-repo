/**
 * Proyecto: Cajero automatico «Banco PSM»
 * Modelo: Modelo A
 * Asignatura: Lenguaje de Programacion II (C++)
 * Integrantes: Nehemias Hernandez, Alanis Martinez
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

// --- Prototipos de funciones ---
bool validarPIN(int pinIngresado, int pinCorrecto);
int leerEnteroEnRango(int min, int max);
double leerMontoPositivo();
long long leerCuentaDestino();
double depositar(double saldo, double monto);
bool puedeRetirar(double saldo, double monto, double retiradoHoy);
double calcularComision(double monto);
void mostrarResumen(int numDepositos, int numRetiros, int numTransferencias, double totalDepositado, double totalRetirado, double totalComisiones, double saldoFinal);

int main() {
    const int PIN_CORRECTO = 2026;
    double saldo = 500.00;
    int intentos = 0;
    bool accesoConcedido = false;

    // Validacion de PIN: maximo 3 intentos
    while (intentos < 3) {
        cout << "Ingrese su PIN: ";
        int pinIngresado;
        if (!(cin >> pinIngresado)) {
            cout << "PIN incorrecto. Letras o caracteres no validos." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            intentos++;
        } else if (pinIngresado < 1000 || pinIngresado > 9999) {
            cout << "PIN incorrecto. Debe ser un numero de 4 digitos." << endl;
            intentos++;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (validarPIN(pinIngresado, PIN_CORRECTO)) {
                accesoConcedido = true;
                break;
            } else {
                intentos++;
                cout << "PIN incorrecto. Le quedan " << (3 - intentos) << " intentos." << endl;
            }
        }
    }

    if (!accesoConcedido) {
        cout << "Tarjeta bloqueada" << endl;
        return 0;
    }

    cout << "Bienvenido..." << endl;

    // Variables de control y acumuladores para el resumen de la sesion
    int numDepositos = 0;
    int numRetiros = 0;
    int numTransferencias = 0;
    double totalDepositado = 0.0;
    double totalRetirado = 0.0;
    double totalComisiones = 0.0;

    int opcion = 0;
    do {
        cout << "\n=== BANCO PSM ===" << endl;
        cout << "1. Consultar saldo" << endl;
        cout << "2. Depositar" << endl;
        cout << "3. Retirar" << endl;
        cout << "4. Transferir" << endl;
        cout << "5. Resumen" << endl;
        cout << "6. Salir" << endl;
        cout << "Opcion: ";

        opcion = leerEnteroEnRango(1, 6);

        switch (opcion) {
            case 1:
                cout << fixed << setprecision(2);
                cout << "Saldo actual: " << saldo << " Bs" << endl;
                break;
            case 2: {
                cout << "Monto a depositar (maximo 10,000.00 Bs): ";
                double montoDep = leerMontoPositivo();
                if (montoDep > 10000.0) {
                    cout << "Error: El deposito maximo permitido por operacion es de 10,000.00 Bs." << endl;
                } else {
                    saldo = depositar(saldo, montoDep);
                    numDepositos++;
                    totalDepositado += montoDep;
                    cout << fixed << setprecision(2);
                    cout << "Deposito exitoso. Saldo actual: " << saldo << " Bs" << endl;
                }
                break;
            }
            case 3: {
                cout << "Monto a retirar: ";
                double montoRet = leerMontoPositivo();
                if (puedeRetirar(saldo, montoRet, totalRetirado)) {
                    saldo -= montoRet;
                    numRetiros++;
                    totalRetirado += montoRet;
                    cout << fixed << setprecision(2);
                    cout << "Retiro exitoso. Saldo actual: " << saldo << " Bs" << endl;
                }
                break;
            }
            case 4: {
                cout << "Ingrese la cuenta destino (8 digitos): ";
                long long cuentaDest = leerCuentaDestino();
                cout << "Monto a transferir: ";
                double montoTrans = leerMontoPositivo();
                double comision = calcularComision(montoTrans);
                double totalNecesario = montoTrans + comision;

                if (totalNecesario > saldo) {
                    cout << fixed << setprecision(2);
                    cout << "Error: saldo insuficiente para cubrir el monto y la comision del 1% (" << comision << " Bs)." << endl;
                } else {
                    saldo -= totalNecesario;
                    numTransferencias++;
                    totalComisiones += comision;
                    cout << fixed << setprecision(2);
                    cout << "Transferencia exitosa a la cuenta " << cuentaDest << "." << endl;
                    cout << "Comision cobrada: " << comision << " Bs. Saldo actual: " << saldo << " Bs" << endl;
                }
                break;
            }
            case 5:
                mostrarResumen(numDepositos, numRetiros, numTransferencias, totalDepositado, totalRetirado, totalComisiones, saldo);
                break;
            case 6:
                mostrarResumen(numDepositos, numRetiros, numTransferencias, totalDepositado, totalRetirado, totalComisiones, saldo);
                cout << "Gracias por usar el cajero Banco PSM." << endl;
                break;
        }
    } while (opcion != 6);

    return 0;
}

// --- Definicion de funciones ---

/**
 * Compara el PIN escrito con el PIN correcto.
 * Parametros: pinIngresado (int), pinCorrecto (int).
 * Retorna: true si coincide, false en caso contrario.
 */
bool validarPIN(int pinIngresado, int pinCorrecto) {
    return pinIngresado == pinCorrecto;
}

/**
 * Lee y valida un entero dentro de un rango especifico.
 * Parametros: min (int), max (int).
 * Retorna: El numero entero validado.
 */
int leerEnteroEnRango(int min, int max) {
    int valor;
    while (true) {
        if (!(cin >> valor)) {
            cout << "Error: Entrada invalida. Ingrese un numero entero: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (valor < min || valor > max) {
            cout << "Error: El valor debe estar entre " << min << " y " << max << ". Intente de nuevo: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        }
    }
}

/**
 * Lee y valida un monto mayor que 0.
 * Parametros: Ninguno.
 * Retorna: El monto positivo ingresado como double.
 */
double leerMontoPositivo() {
    double monto;
    while (true) {
        if (!(cin >> monto)) {
            cout << "Error: Entrada invalida. Ingrese un monto numerico: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (monto <= 0) {
            cout << "Error: El monto debe ser mayor que 0. Intente de nuevo: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return monto;
        }
    }
}

/**
 * Lee y valida una cuenta destino de 8 digitos.
 * Parametros: Ninguno.
 * Retorna: El numero de cuenta validado como long long.
 */
long long leerCuentaDestino() {
    long long cuenta;
    while (true) {
        if (!(cin >> cuenta)) {
            cout << "Error: Entrada invalida. Ingrese un numero de cuenta: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else if (cuenta < 10000000 || cuenta > 99999999) {
            cout << "Error: La cuenta destino debe ser de exactamente 8 digitos (10000000 a 99999999). Intente de nuevo: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return cuenta;
        }
    }
}

/**
 * Retorna el nuevo saldo despues del deposito.
 * Parametros: saldo (double), monto (double).
 * Retorna: Nuevo saldo.
 */
double depositar(double saldo, double monto) {
    return saldo + monto;
}

/**
 * Indica si el retiro cumple todas las reglas (multiplo de 5, saldo disponible y limite diario de 2000 Bs).
 * Parametros: saldo (double), monto (double), retiradoHoy (double).
 * Retorna: true si es valido, false si no.
 */
bool puedeRetirar(double saldo, double monto, double retiradoHoy) {
    if (fmod(monto, 5.0) != 0.0) {
        cout << "Error: el monto debe ser multiplo de 5." << endl;
        return false;
    }
    if (monto > saldo) {
        cout << "Error: saldo insuficiente." << endl;
        return false;
    }
    if ((retiradoHoy + monto) > 2000.0) {
        cout << "Error: supera el limite diario de retiro (2,000.00 Bs)." << endl;
        return false;
    }
    return true;
}

/**
 * Retorna el 1% del monto de la transferencia como comision.
 * Parametros: monto (double).
 * Retorna: Comision calculada.
 */
double calcularComision(double monto) {
    return monto * 0.01;
}

/**
 * Imprime el resumen de la sesion con los contadores y acumuladores.
 * Parametros: numDepositos, numRetiros, numTransferencias, totalDepositado, totalRetirado, totalComisiones, saldoFinal.
 * Retorna: void.
 */
void mostrarResumen(int numDepositos, int numRetiros, int numTransferencias, double totalDepositado, double totalRetirado, double totalComisiones, double saldoFinal) {
    cout << "\n=== RESUMEN DE LA SESION ===" << endl;
    cout << "Cantidad de depositos: " << numDepositos << endl;
    cout << "Total depositado: " << fixed << setprecision(2) << totalDepositado << " Bs" << endl;
    cout << "Cantidad de retiros: " << numRetiros << endl;
    cout << "Total retirado: " << fixed << setprecision(2) << totalRetirado << " Bs" << endl;
    cout << "Cantidad de transferencias: " << numTransferencias << endl;
    cout << "Total de comisiones cobradas: " << fixed << setprecision(2) << totalComisiones << " Bs" << endl;
    cout << "Saldo final: " << fixed << setprecision(2) << saldoFinal << " Bs" << endl;
}