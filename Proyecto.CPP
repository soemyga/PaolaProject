#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;
//utilidades
struct estudiante
{
    string nombre;
    int calificaciones[20];
    int calFin(int numerodecolumnas) {
        int retornar = 0;
        for (int i = 0; i < numerodecolumnas; i++) {
            retornar += calificaciones[i];
        }
        return retornar;
    }
};
void imprimirLEstudiantes(estudiante arregloE[], string nombreColumnas[], int numeroColumnas) {
    cout << "Nombre\t\t";
    for (int i = 0; i < numeroColumnas; i++) {
        cout << nombreColumnas[i] << "\t";
    }
    cout << "Final" << "\n";
    cout << "----------------------------------------------------------------------------\n";

    int i = 0;
    while (arregloE[i].nombre.compare("") != 0)
    {
        cout << arregloE[i].nombre << setw(5) << " \t";
        for (int j = 0; j < numeroColumnas; j++) {
            cout << arregloE[i].calificaciones[j] << "\t";
        }
        cout << arregloE[i].calFin(numeroColumnas) << "\n";
        i++;
    }
}
estudiante* leerArchivo(estudiante arregloE[], string nombreArchivo, int numColumnas) {
    string linea;
    ifstream archivo(nombreArchivo.c_str());
    string space_delimiter = ",";

    int i = 0;
    while (getline(archivo, linea)) {
        //Obtener nombre
        int pos;
        pos = linea.find(space_delimiter);
        arregloE[i].nombre = linea.substr(0, pos);
        linea.erase(0, pos + space_delimiter.length());

        //Obtener calificaciones
        for (int j = 0; j < 20; j++) {
            pos = linea.find(space_delimiter);
            string calificacion = linea.substr(0, pos);
            int cal = stoi(calificacion);
            arregloE[i].calificaciones[j] = cal;
            linea.erase(0, pos + space_delimiter.length());
        }
        i++;
    }
    return arregloE;

}
void ordenarCalificacion(estudiante arreglo[], string nombreColumnas[], int numeroColumnas);
void ordenarNombre(estudiante arreglo[]);
int numeroEstudiantes(estudiante arregloE[]) {
    int i = 0;
    while (arregloE[i].nombre.compare("") != 0)
    {
        i++;
    }
    return i;

}
void aniadirEstudiante(estudiante arregloE[], string nombreColumnas[], int numeroColumnas);
void establecerColumnas(string columnas[], int numeroColumnas);
void guardarArchivo(estudiante arregloE[], string nombreArchivo);
void corregircalif(estudiante arregloE[], string nombreColumnas[], int numeroColumnas);
/*----------------------------------------------------
|                  Funcion central                    |
|                     Inicio                          |
----------------------------------------------------  */

int main() {
    //Nombre columnas
    int numeroColumnas = 1;
    string nombreColumnas[20];
    //Fin

    //Estudiantes
    estudiante base[100];
    estudiante* arregloE;
    //Fin estudiantes;

    string nombreArchivo = "C:/Users/sakuy/Desktop/Proyecto.txt";
    arregloE = leerArchivo(base, nombreArchivo, numeroColumnas);

    int entrar;
    //introduccion
    cout << "Este programa permite llevar un registro de calificaciones y \n"
        << "balance del grupo\n";
    cout << "|No se hace ningun tipo de validacion de datos,tenga cuidado|\n";
    //inicio
    cout << "Entrar? -[1|SI]-  -[Otro|NO]- >";
    cin >> entrar;

    int opcion;
    if (entrar == 1) {
        cout << "Ingresa el numero columnas(parametros de evalucion)y nombralos\n";
        cout << "Numero de columnas > ";
        cin >> numeroColumnas;
        fflush(stdin);
        establecerColumnas(nombreColumnas, numeroColumnas);
        do {
            cout << "<-------Menu------->\n";
            cout << "1) Imprimir tabla de valores y nombres\n";
            cout << "2) Ordenar por calificaciones\n";
            cout << "3) Ordenar por nombres\n";
            cout << "4) Añadir estudiante a la lista\n";
            cout << "5) Corregir calificacion\n";
            cout << "0) Salir\n\n";
            cout << "Opcion > ";
            cin >> opcion;
            fflush(stdin);

            //Selector de opciones
            switch (opcion)
            {
            case 0:
                guardarArchivo(arregloE, nombreArchivo);
                cout << "Gracias por usar el programa!";
                break;
            case 1:
                imprimirLEstudiantes(arregloE, nombreColumnas, numeroColumnas);
                break;
            case 2:
                ordenarCalificacion(arregloE, nombreColumnas, numeroColumnas);
                cout << "<Tabla ordenada en calificaciones de menor a mayor>\n";
                break;
            case 3:
                ordenarNombre(arregloE);
                cout << "<Tabla ordenada en orden alfabetico>\n";
                break;
            case 4:
                aniadirEstudiante(arregloE, nombreColumnas, numeroColumnas);
                cout << "<Estudiante añadido al listado>\n";
                break;
            case 5:
                corregircalif(arregloE, nombreColumnas, numeroColumnas);
                break;
            default:
                cout << "-Opcion invalida-\n"
                    << "-Elige otra opcion-\n";
            }

        } while (opcion != 0);
    }
    cout << "Gracias por usar el programa!";
}
/*----------------------------------------------------
|                  Funcion central                    |
|                     final                           |
----------------------------------------------------  */

void ordenarCalificacion(estudiante arreglo[], string nombreColumnas[], int numeroColumnas) {
    int i, j;
    estudiante aux;
    int length = numeroEstudiantes(arreglo);
    for (i = 1; i < length; i++) {
        for (j = 0; j < length - i; j++) {
            if (arreglo[j].calFin(numeroColumnas) > arreglo[j + 1].calFin(numeroColumnas)) {
                aux = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = aux;
            }
        }
    }
}

void ordenarNombre(estudiante arreglo[]) {
    int i, j;
    estudiante aux;
    int length = numeroEstudiantes(arreglo);
    for (i = 1; i < length; i++) {
        for (j = 0; j < length - i; j++) {
            if (arreglo[j].nombre.compare(arreglo[j + 1].nombre) > 0) {
                aux = arreglo[j];
                arreglo[j] = arreglo[j + 1];
                arreglo[j + 1] = aux;
            }
        }
    }
}

void aniadirEstudiante(estudiante arregloE[], string nombreColumnas[], int numeroColumnas) {
    int a = numeroEstudiantes(arregloE);
    if (a >= 100) {
        cout << "<Lista llena>";
        return;
    }
    else {
        estudiante aux;
        string nombre;
        cout << "Nombre del alumno> ";
        getline(cin, aux.nombre);
        //cin >> aux.nombre;
        fflush(stdin);

        for (int i = 0; i < numeroColumnas; i++)
        {
            cout << nombreColumnas[i] << " > ";
            cin >> aux.calificaciones[i];
            fflush(stdin);
        }
        for (int i = numeroColumnas; i < 20; i++)
        {
            aux.calificaciones[i] = 0;
        }
        arregloE[a] = aux;
    }

}
void corregircalif(estudiante arregloE[], string nombreColumnas[], int numeroColumnas) {
    int a = 0;
    cout << "numero de estudiante > ";
    cin >> a;
    fflush(stdin);
    if (a > numeroEstudiantes(arregloE)) {
        cout << "<Estudiante no existente>\n";
        return;
    }
    else {
        estudiante aux;
        string nombre;
        cout << "Nombre del alumno> ";
        getline(cin, aux.nombre);
        //cin >> aux.nombre;
        fflush(stdin);

        for (int i = 0; i < numeroColumnas; i++)
        {
            cout << nombreColumnas[i] << " > ";
            cin >> aux.calificaciones[i];
            fflush(stdin);
        }
        for (int i = numeroColumnas; i < 20; i++)
        {
            aux.calificaciones[i] = 0;
        }
        arregloE[a - 1] = aux;
    }
    cout << "<Calificacion corregida>\n";
}
void establecerColumnas(string columnas[], int numeroColumnas) {
    for (int i = 0; i < numeroColumnas; i++)
    {
        cout << "Nombre de la Columna " << i + 1 << " > ";
        //cin>>columnas[i];
        getline(cin, columnas[i]);
        fflush(stdin);
    }
}

void guardarArchivo(estudiante arregloE[], string nombreArchivo) {
    ofstream archivo;
    archivo.open(nombreArchivo.c_str(), fstream::out);
    int i = 0;
    while (arregloE[i].nombre.compare("") != 0)
    {
        archivo << arregloE[i].nombre;
        for (int j = 0; j < 20; j++) {
            archivo << "," << arregloE[i].calificaciones[j];
        }
        archivo << endl;
        i++;
    }
    archivo.close();
}
