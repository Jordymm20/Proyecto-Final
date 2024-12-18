#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

struct Producto {
    string nombre;
    float precio;
    int cantidad;
};

struct Solicitud {
    string cliente;
    string producto;
    int cantidad;
};

struct Cliente {
    string nombre;
};

class SistemaGestion {
private:
    vector<Producto> inventario;
    vector<Solicitud> solicitudes;
    vector<Cliente> listaEspera;
    stack<string> historialCambios;

    //productos en inventario
    void listarInventario() {
        if (inventario.empty()) {
            cout << "No hay productos en inventario." << endl;
            return;
        }
        sort(inventario.begin(), inventario.end(), [](const Producto& a, const Producto& b) {
            return a.nombre < b.nombre;
        });
        for (const auto& prod : inventario) {
            cout << "Producto: " << prod.nombre << ", Precio: " << prod.precio << ", Cantidad: " << prod.cantidad << endl;
        }
    }

    //cambios en el inventario
    void registrarCambio(const string& cambio) {
        historialCambios.push(cambio);
    }

public:
    //Gestión de Inventario
    void registrarProducto() {
        Producto prod;
        cout << "Ingrese nombre del producto: ";
        cin >> prod.nombre;
        cout << "Ingrese precio del producto: ";
        cin >> prod.precio;
        cout << "Ingrese cantidad del producto: ";
        cin >> prod.cantidad;
        inventario.push_back(prod);
        registrarCambio("Agregado producto: " + prod.nombre);
        cout << "Producto registrado exitosamente." << endl;
    }
    void eliminarProducto() {
        string nombre;
        cout << "Ingrese nombre del producto a eliminar: ";
        cin >> nombre;
        auto it = find_if(inventario.begin(), inventario.end(), [&nombre](const Producto& prod) {
            return prod.nombre == nombre;
        });

        if (it != inventario.end()) {
            inventario.erase(it);
            registrarCambio("Eliminado producto: " + nombre);
            cout << "Producto eliminado exitosamente." << endl;
        } else {
            cout << "Producto no encontrado." << endl;
        }
    }
    void consultarProducto() {
        string nombre;
        cout << "Ingrese nombre del producto a consultar: ";
        cin >> nombre;
        auto it = find_if(inventario.begin(), inventario.end(), [&nombre](const Producto& prod) {
            return prod.nombre == nombre;
        });

        if (it != inventario.end()) {
            cout << "Producto: " << it->nombre << ", Precio: " << it->precio << ", Cantidad: " << it->cantidad << endl;
        } else {
            cout << "Producto no encontrado." << endl;
        }
    }

    //Gestión de Solicitudes de Compra
    void registrarSolicitud() {
        Solicitud sol;
        cout << "Ingrese nombre del cliente: ";
        cin >> sol.cliente;
        cout << "Ingrese nombre del producto: ";
        cin >> sol.producto;
        cout << "Ingrese cantidad del producto: ";
        cin >> sol.cantidad;
        solicitudes.push_back(sol);
        cout << "Solicitud registrada exitosamente." << endl;
    }
    void procesarSolicitud() {
        if (!solicitudes.empty()) {
            Solicitud sol = solicitudes.front();
            solicitudes.erase(solicitudes.begin());
            cout << "Solicitud procesada: Cliente: " << sol.cliente << ", Producto: " << sol.producto << ", Cantidad: " << sol.cantidad << endl;
        } else {
            cout << "No hay solicitudes pendientes." << endl;
        }
    }
    void consultarSolicitud() {
        if (!solicitudes.empty()) {
            cout << "Solicitud en proceso: Cliente: " << solicitudes.front().cliente
                 << ", Producto: " << solicitudes.front().producto << ", Cantidad: " << solicitudes.front().cantidad << endl;
        } else {
            cout << "No hay solicitudes pendientes." << endl;
        }
    }
    void listarSolicitudesPendientes() {
        if (solicitudes.empty()) {
            cout << "No hay solicitudes pendientes." << endl;
            return;
        }
        cout << "Solicitudes pendientes:" << endl;
        for (const auto& sol : solicitudes) {
            cout << "Cliente: " << sol.cliente << ", Producto: " << sol.producto << ", Cantidad: " << sol.cantidad << endl;
        }
    }

    //Gestión de Clientes en Espera

    void registrarCliente() {
        Cliente cli;
        cout << "Ingrese nombre del cliente: ";
        cin >> cli.nombre;
        listaEspera.push_back(cli);
        cout << "Cliente registrado en espera." << endl;
    }
    void atenderCliente() {
        if (!listaEspera.empty()) {
            Cliente cli = listaEspera.front();
            listaEspera.erase(listaEspera.begin());
            cout << "Cliente atendido: " << cli.nombre << endl;
        } else {
            cout << "No hay clientes en espera." << endl;
        }
    }
    void consultarListaEspera() {
        if (listaEspera.empty()) {
            cout << "No hay clientes en espera." << endl;
            return;
        }
        cout << "Clientes en espera:" << endl;
        for (const auto& cli : listaEspera) {
            cout << cli.nombre << endl;
        }
    }

    //Gestión de Registro de Cambios en el Inventario

    void deshacerCambio() {
        if (!historialCambios.empty()) {
            cout << "Deshaciendo accion: " << historialCambios.top() << endl;
            historialCambios.pop();
        } else {
            cout << "No hay cambios para deshacer." << endl;
        }
    }

    void mostrarMenu() {
        int opcion;
        do {
            cout << "\nMenu del Sistema de Gestion:" << endl;
            cout << "1. Gestionar Inventario" << endl;
            cout << "2. Gestionar Solicitudes de Compra" << endl;
            cout << "3. Gestionar Clientes en Espera" << endl;
            cout << "4. Gestionar Registro de Cambios" << endl;
            cout << "0. Salir" << endl;
            cout << "Elija una opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1:
                    gestionarInventario();
                    break;
                case 2:
                    gestionarSolicitudes();
                    break;
                case 3:
                    gestionarClientes();
                    break;
                case 4:
                    gestionarCambios();
                    break;
                case 0:
                    cout << "Saliendo del sistema..." << endl;
                    break;
                default:
                    cout << "Opcion no valida." << endl;
            }
        } while (opcion != 0);
    }

    // Sub-menus
    void gestionarInventario() {
        int opcion;
        do {
            cout << "\nGestionar Inventario:" << endl;
            cout << "1. Registrar producto" << endl;
            cout << "2. Eliminar producto" << endl;
            cout << "3. Consultar producto" << endl;
            cout << "4. Listar productos" << endl;
            cout << "0. Volver al menu principal" << endl;
            cout << "Elija una opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1: registrarProducto(); break;
                case 2: eliminarProducto(); break;
                case 3: consultarProducto(); break;
                case 4: listarInventario(); break;
                case 0: break;
                default: cout << "Opcion no valida." << endl;
            }
        } while (opcion != 0);
    }

    void gestionarSolicitudes() {
        int opcion;
        do {
            cout << "\nGestionar Solicitudes de Compra:" << endl;
            cout << "1. Registrar solicitud" << endl;
            cout << "2. Procesar solicitud" << endl;
            cout << "3. Consultar solicitud en proceso" << endl;
            cout << "4. Listar solicitudes pendientes" << endl;
            cout << "0. Volver al menu principal" << endl;
            cout << "Elija una opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1: registrarSolicitud(); break;
                case 2: procesarSolicitud(); break;
                case 3: consultarSolicitud(); break;
                case 4: listarSolicitudesPendientes(); break;
                case 0: break;
                default: cout << "Opcion no valida." << endl;
            }
        } while (opcion != 0);
    }

    void gestionarClientes() {
        int opcion;
        do {
            cout << "\nGestionar Clientes en Espera:" << endl;
            cout << "1. Registrar cliente" << endl;
            cout << "2. Atender cliente" << endl;
            cout << "3. Consultar lista de espera" << endl;
            cout << "0. Volver al menu principal" << endl;
            cout << "Elija una opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1: registrarCliente(); break;
                case 2: atenderCliente(); break;
                case 3: consultarListaEspera(); break;
                case 0: break;
                default: cout << "Opcion no valida." << endl;
            }
        } while (opcion != 0);
    }

    void gestionarCambios() {
        int opcion;
        do {
            cout << "\nGestionar Registro de Cambios:" << endl;
            cout << "1. Deshacer ultimo cambio" << endl;
            cout << "0. Volver al menu principal" << endl;
            cout << "Elija una opcion: ";
            cin >> opcion;

            switch(opcion) {
                case 1: deshacerCambio(); break;
                case 0: break;
                default: cout << "Opcion no valida." << endl;
            }
        } while (opcion != 0);
    }
};

int main() {
    SistemaGestion sistema;
    sistema.mostrarMenu();
    return 0;
}

