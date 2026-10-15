/*realice un progarama que permita hacer converciones entre unidades de longitud, masa y tiempo; considere las mas usadas, valide la entrada por ceclado y 
consider las correcciones del otro ejercicio y debe ser capaz de elegir las unidades que desea convertir*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    // Activar color amarillo para toda la consola
    cout << "\033[33m";
    
    char repetir = 's';

    // Bucle principal para repetir el programa si el usuario lo desea
    while (repetir == 's' || repetir == 'S') {
        int categoria = 0;
        
        // 1. Elegir la categoría de conversión
        do {
            cout << "\n\t\t========================================\n";
            cout << "\t\t         CONVERSOR DE UNIDADES          \n";
            cout << "\t\t========================================\n";
            cout << "\t\t1. Longitud (m, km, cm, mm, mi, in)\n";
            cout << "\t\t2. Masa (kg, g, lb, oz)\n";
            cout << "\t\t3. Tiempo (s, min, h, dias)\n";
            cout << "\t\tElija la categoria (1-3): ";
            cin >> categoria;
            
            if (cin.fail() || categoria < 1 || categoria > 3) {
                cin.clear();
                cin.ignore(10000, '\n');
                categoria = 0;
                cout << "\n\t\t[Error] Categoria invalida. Ingrese 1, 2 o 3.\n";
            }
        } while (categoria < 1 || categoria > 3);

        int unidadOrigen = 0, unidadDestino = 0;
        int maxUnidades = (categoria == 1) ? 6 : (categoria == 2) ? 4 : 4;

        // 2. Elegir unidad de origen
        do {
            cout << "\n\t\t--- UNIDAD DE ORIGEN ---\n";
            if (categoria == 1) {
                cout << "\t\t1. Metros (m)\n\t\t2. Kilometros (km)\n\t\t3. Centimetros (cm)\n\t\t4. Milimetros (mm)\n\t\t5. Millas (mi)\n\t\t6. Pulgadas (in)\n";
            } else if (categoria == 2) {
                cout << "\t\t1. Kilogramos (kg)\n\t\t2. Gramos (g)\n\t\t3. Libras (lb)\n\t\t4. Onzas (oz)\n";
            } else {
                cout << "\t\t1. Segundos (s)\n\t\t2. Minutos (min)\n\t\t3. Horas (h)\n\t\t4. Dias (dias)\n";
            }
            cout << "\t\tElija la unidad de origen (1-" << maxUnidades << "): ";
            cin >> unidadOrigen;

            if (cin.fail() || unidadOrigen < 1 || unidadOrigen > maxUnidades) {
                cin.clear();
                cin.ignore(10000, '\n');
                unidadOrigen = 0;
                cout << "\n\t\t[Error] Opcion invalida. Intente de nuevo.\n";
            }
        } while (unidadOrigen < 1 || unidadOrigen > maxUnidades);

        // 3. Elegir unidad de destino
        do {
            cout << "\n\t\t--- UNIDAD DE DESTINO ---\n";
            if (categoria == 1) {
                cout << "\t\t1. Metros (m)\n\t\t2. Kilometros (km)\n\t\t3. Centimetros (cm)\n\t\t4. Milimetros (mm)\n\t\t5. Millas (mi)\n\t\t6. Pulgadas (in)\n";
            } else if (categoria == 2) {
                cout << "\t\t1. Kilogramos (kg)\n\t\t2. Gramos (g)\n\t\t3. Libras (lb)\n\t\t4. Onzas (oz)\n";
            } else {
                cout << "\t\t1. Segundos (s)\n\t\t2. Minutos (min)\n\t\t3. Horas (h)\n\t\t4. Dias (dias)\n";
            }
            cout << "\t\tElija la unidad de destino (1-" << maxUnidades << "): ";
            cin >> unidadDestino;

            if (cin.fail() || unidadDestino < 1 || unidadDestino > maxUnidades) {
                cin.clear();
                cin.ignore(10000, '\n');
                unidadDestino = 0;
                cout << "\n\t\t[Error] Opcion invalida. Intente de nuevo.\n";
            }
        } while (unidadDestino < 1 || unidadDestino > maxUnidades);

        // 4. Ingresar el valor numérico a convertir con validación
        double valor = -1;
        do {
            cout << "\n\t\tIngrese el valor a convertir: ";
            cin >> valor;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                valor = -1;
                cout << "\n\t\t[Error] Entrada invalida. Ingrese un numero valido.\n";
            } else if (valor < 0) {
                cout << "\n\t\t[Error] El valor no puede ser negativo.\n";
            }
        } while (valor < 0);

        // 5. Realizar conversión mediante unidad base
        double valorEnBase = 0;

        // Convertir origen a unidad base (m para longitud, g para masa, s para tiempo)
        if (categoria == 1) {
            switch (unidadOrigen) {
                case 1: valorEnBase = valor; break;          // m
                case 2: valorEnBase = valor * 1000.0; break;   // km
                case 3: valorEnBase = valor * 0.01; break;     // cm
                case 4: valorEnBase = valor * 0.001; break;    // mm
                case 5: valorEnBase = valor * 1609.344; break; // mi
                case 6: valorEnBase = valor * 0.0254; break;   // in
            }
        } else if (categoria == 2) {
            switch (unidadOrigen) {
                case 1: valorEnBase = valor * 1000.0; break;    // kg
                case 2: valorEnBase = valor; break;          // g
                case 3: valorEnBase = valor * 453.59237; break;// lb
                case 4: valorEnBase = valor * 28.349523; break;// oz
            }
        } else {
            switch (unidadOrigen) {
                case 1: valorEnBase = valor; break;          // s
                case 2: valorEnBase = valor * 60.0; break;     // min
                case 3: valorEnBase = valor * 3600.0; break;   // h
                case 4: valorEnBase = valor * 86400.0; break;  // días
            }
        }

        double resultado = 0;

        // Convertir de unidad base a destino
        if (categoria == 1) {
            switch (unidadDestino) {
                case 1: resultado = valorEnBase; break;
                case 2: resultado = valorEnBase / 1000.0; break;
                case 3: resultado = valorEnBase / 0.01; break;
                case 4: resultado = valorEnBase / 0.001; break;
                case 5: resultado = valorEnBase / 1609.344; break;
                case 6: resultado = valorEnBase / 0.0254; break;
            }
        } else if (categoria == 2) {
            switch (unidadDestino) {
                case 1: resultado = valorEnBase / 1000.0; break;
                case 2: resultado = valorEnBase; break;
                case 3: resultado = valorEnBase / 453.59237; break;
                case 4: resultado = valorEnBase / 28.349523; break;
            }
        } else {
            switch (unidadDestino) {
                case 1: resultado = valorEnBase; break;
                case 2: resultado = valorEnBase / 60.0; break;
                case 3: resultado = valorEnBase / 3600.0; break;
                case 4: resultado = valorEnBase / 86400.0; break;
            }
        }

        // Textos descriptivos para mostrar
        string nombresLongitud[6] = {"Metros (m)", "Kilometros (km)", "Centimetros (cm)", "Milimetros (mm)", "Millas (mi)", "Pulgadas (in)"};
        string nombresMasa[4] = {"Kilogramos (kg)", "Gramos (g)", "Libras (lb)", "Onzas (oz)"};
        string nombresTiempo[4] = {"Segundos (s)", "Minutos (min)", "Horas (h)", "Dias (dias)"};

        string nombreOrigen = "", nombreDestino = "";
        if (categoria == 1) {
            nombreOrigen = nombresLongitud[unidadOrigen - 1];
            nombreDestino = nombresLongitud[unidadDestino - 1];
        } else if (categoria == 2) {
            nombreOrigen = nombresMasa[unidadOrigen - 1];
            nombreDestino = nombresMasa[unidadDestino - 1];
        } else {
            nombreOrigen = nombresTiempo[unidadOrigen - 1];
            nombreDestino = nombresTiempo[unidadDestino - 1];
        }

        // 6. Mostrar el resultado centrado
        cout << "\n\t\t========================================\n";
        cout << "\t\t         RESULTADO DE CONVERSION        \n";
        cout << "\t\t========================================\n";
        cout << "\t\t" << valor << " " << nombreOrigen << "\n";
        cout << "\t\tEquivale a:\n";
        cout << "\t\t>> " << fixed << setprecision(4) << resultado << " " << nombreDestino << " <<\n";
        cout << "\t\t========================================\n";

        // 7. Preguntar si desea repetir el proceso
        cout << "\n\t\tDesea realizar otra conversion? (s/n): ";
        cin >> repetir;
        cin.ignore(10000, '\n');
    }

    cout << "\n\t\t¡Gracias por usar el conversor! Hasta luego.\n\n";
    cout << "\033[0m"; // Restaurar color predeterminado al salir

    return 0;
}