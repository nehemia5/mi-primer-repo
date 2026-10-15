/*realice un programa que permita simular una ruleta de opciones y que el usuario pueda elegir entre dos opciones, tres opciones, cuatro o diez.
 Todas las opciones tienen que ser validadas por teclado, las opciones pueden ser palabras, numeros o palabras especiales.
  No puede usar funciones, arresglos bidimencionales o listas. Una vez listo subir al repositorio con una pequeña descripcion*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main() {
    // Activar color amarillo para toda la ejecución (se inicia al principio)
    cout << "\033[33m";

    // Inicializar la semilla aleatoria una sola vez
    srand(static_cast<unsigned int>(time(0)));
    
    char repetir = 's';

    // Bucle principal para repetir el programa si el usuario lo desea
    while (repetir == 's' || repetir == 'S') {
        int numOpciones = 0;
        
        // Validación para que el usuario elija 2, 3, 4 o 10 opciones (Centrado visual)
        do {
            cout << "\n\t\t========================================\n";
            cout << "\t\t           RULETA DE OPCIONES           \n";
            cout << "\t\t========================================\n";
            cout << "\t\tElija la cantidad de opciones (2, 3, 4 o 10): ";
            cin >> numOpciones;
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                numOpciones = 0;
                cout << "\n\t\t[Error] Entrada invalida. Ingrese un numero.\n";
            } else if (numOpciones != 2 && numOpciones != 3 && numOpciones != 4 && numOpciones != 10) {
                cout << "\n\t\t[Error] Cantidad no permitida. Solo 2, 3, 4 o 10.\n";
            }
        } while (numOpciones != 2 && numOpciones != 3 && numOpciones != 4 && numOpciones != 10);

        // Limpiar el búfer del teclado
        cin.ignore(10000, '\n');

        // Arreglo unidimensional de tamaño fijo (máximo 10)
        string opciones[10];

        cout << "\n\t\t--- INGRESO DE OPCIONES ---\n";
        cout << "\t\t(Palabras, numeros o simbolos especiales)\n\n";

        // Llenar el arreglo con validación de que no estén vacías
        for (int i = 0; i < numOpciones; i++) {
            do {
                cout << "\t\tIngrese la opcion " << (i + 1) << ": ";
                getline(cin, opciones[i]);
                
                if (opciones[i].empty()) {
                    cout << "\t\t[Error] La opcion no puede estar vacia.\n";
                }
            } while (opciones[i].empty());
        }

        // Simulación del giro de la ruleta
        int indiceGanador = rand() % numOpciones;

        cout << "\n\t\t========================================\n";
        cout << "\t\t         ¡GIRANDO LA RULETA!            \n";
        cout << "\t\t========================================\n";
        cout << "\t\tEl resultado ganador es: ** " << opciones[indiceGanador] << " **\n";
        cout << "\t\t========================================\n";

        // Preguntar si desea continuar jugando
        cout << "\n\t\t¿Desea jugar otra vez? (s/n): ";
        cin >> repetir;
        cin.ignore(10000, '\n'); // Limpiar búfer después de leer el caracter
    }

    cout << "\n\t\t¡Gracias por usar la ruleta! Hasta luego.\n\n";

    // Restablecer el color original de la consola antes de salir (opcional)
    cout << "\033[0m";

    return 0;
}