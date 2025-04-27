#include <iostream>

using namespace std;

struct Estudiante {
    int id;
    string nombres;
    string apellidos;
    float notas[4];
};

void ingresarDatos(Estudiante* estudiantes, int n) {
    for (int i = 0; i < n; i++) {
        cout << "\nEstudiante " << i + 1 << endl;
        cout << "ID: ";
        cin >> estudiantes[i].id;
        cin.ignore();  

        cout << "Nombres: ";
        getline(cin, estudiantes[i].nombres);

        cout << "Apellidos: ";
        getline(cin, estudiantes[i].apellidos);

        for (int j = 0; j < 4; j++) {
            cout << "Nota " << j + 1 << ": ";
            cin >> estudiantes[i].notas[j];
        }
    }
}

void calcularPromedio(Estudiante* estudiantes, int n) {
    cout << "\nResultados:\n";
    for (int i = 0; i < n; i++) {
        float suma = 0;
        for (int j = 0; j < 4; j++) {
            suma += estudiantes[i].notas[j];
        }
        float promedio = suma / 4;

        cout << "\nEstudiante " << i + 1 << " (" << estudiantes[i].nombres << " " << estudiantes[i].apellidos << ")" << endl;
        cout << "Promedio: " << promedio << endl;
        cout << (promedio >= 60 ? "APROBADO" : "REPROBADO") << endl;
    }
}

int main() {
    int n;
    cout << "Ingrese la cantidad de estudiantes: ";
    cin >> n;

    Estudiante* estudiantes = new Estudiante[n];  

    ingresarDatos(estudiantes, n);
    calcularPromedio(estudiantes, n);

    delete[] estudiantes; 

    return 0;
}
