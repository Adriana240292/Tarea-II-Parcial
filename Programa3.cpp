#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Estudiante {
    int id;
    char nombres[50];
    char apellidos[50];
    float notas[4];
    float promedio;
    char resultado[10];
};

void calcularPromedio(Estudiante* est) {
    float suma = 0;
    for (int i = 0; i < 4; i++) {
        suma += est->notas[i];
    }
    est->promedio = suma / 4.0;
    strcpy(est->resultado, est->promedio >= 60 ? "Aprobo" : "Reprobo");
}

void crear() {
    int n;
    cout << "¿Cuantos estudiantes desea ingresar?: ";
    cin >> n;

    Estudiante* estudiantes = new Estudiante[n];

    for (int i = 0; i < n; i++) {
        cout << "\nEstudiante #" << (i + 1) << endl;
        cout << "ID: ";
        cin >> estudiantes[i].id;
        cin.ignore();
        cout << "Nombres: ";
        cin.getline(estudiantes[i].nombres, 50);
        cout << "Apellidos: ";
        cin.getline(estudiantes[i].apellidos, 50);

        for (int j = 0; j < 4; j++) {
            cout << "Nota " << j + 1 << ": ";
            cin >> estudiantes[i].notas[j];
        }

        calcularPromedio(&estudiantes[i]);
    }

    ofstream archivo("notas.dat", ios::binary | ios::app);
    archivo.write(reinterpret_cast<char*>(estudiantes), sizeof(Estudiante) * n);
    archivo.close();
    delete[] estudiantes;

    cout << "\nEstudiantes guardados correctamente.\n";
}

void leer() {
    Estudiante est;
    ifstream archivo("notas.dat", ios::binary);
    if (!archivo) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    while (archivo.read(reinterpret_cast<char*>(&est), sizeof(Estudiante))) {
        cout << "\nID: " << est.id
             << "\nNombre: " << est.nombres
             << "\nApellidos: " << est.apellidos
             << "\nNotas: " << est.notas[0] << ", " << est.notas[1] << ", " << est.notas[2] << ", " << est.notas[3]
             << "\nPromedio: " << est.promedio
             << "\nResultado: " << est.resultado << endl;
    }

    archivo.close();
}

void actualizar() {
    fstream archivo("notas.dat", ios::in | ios::out | ios::binary);
    if (!archivo) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    int buscarId;
    cout << "Ingrese el ID del estudiante a actualizar: ";
    cin >> buscarId;

    Estudiante est;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&est), sizeof(Estudiante))) {
        if (est.id == buscarId) {
            encontrado = true;
            cout << "Ingrese nuevos datos para el estudiante:\n";
            cin.ignore();
            cout << "Nombres: ";
            cin.getline(est.nombres, 50);
            cout << "Apellidos: ";
            cin.getline(est.apellidos, 50);
            for (int j = 0; j < 4; j++) {
                cout << "Nota " << j + 1 << ": ";
                cin >> est.notas[j];
            }

            calcularPromedio(&est);

            archivo.seekp(-sizeof(Estudiante), ios::cur);
            archivo.write(reinterpret_cast<char*>(&est), sizeof(Estudiante));
            cout << "Estudiante actualizado correctamente.\n";
            break;
        }
    }

    if (!encontrado) {
        cout << "Estudiante con ID " << buscarId << " no encontrado.\n";
    }

    archivo.close();
}

void eliminar() {
    ifstream archivoIn("notas.dat", ios::binary);
    ofstream archivoOut("temp.dat", ios::binary);

    if (!archivoIn || !archivoOut) {
        cout << "Error al abrir los archivos.\n";
        return;
    }

    int buscarId;
    cout << "Ingrese el ID del estudiante a eliminar: ";
    cin >> buscarId;

    Estudiante est;
    bool eliminado = false;

    while (archivoIn.read(reinterpret_cast<char*>(&est), sizeof(Estudiante))) {
        if (est.id != buscarId) {
            archivoOut.write(reinterpret_cast<char*>(&est), sizeof(Estudiante));
        } else {
            eliminado = true;
        }
    }

    archivoIn.close();
    archivoOut.close();

    remove("notas.dat");
    rename("temp.dat", "notas.dat");

    if (eliminado)
        cout << "Estudiante eliminado correctamente.\n";
    else
        cout << "Estudiante no encontrado.\n";
}

int main() {
    int opcion;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Crear estudiante(s)\n";
        cout << "2. Mostrar estudiantes\n";
        cout << "3. Actualizar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: crear(); break;
            case 2: leer(); break;
            case 3: actualizar(); break;
            case 4: eliminar(); break;
            case 5: cout << "Saliendo del programa.\n"; break;
            default: cout << "Opcion invalida.\n"; break;
        }

    } while (opcion != 5);

    return 0;
}

