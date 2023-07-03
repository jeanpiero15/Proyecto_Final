#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int validarTelefono(int telefono) {
    string telefonoStr = to_string(telefono);
    while (telefonoStr.length() != 9) {
        cout << "El número de teléfono debe tener 9 dígitos. Inténtelo nuevamente: ";
        cin >> telefono;
        telefonoStr = to_string(telefono);
    }
    return telefono;
}

string validarCod(string dni) {
    while (dni.length() != 4) {
        cout << "El número de teléfono debe tener 9 dígitos. Inténtelo nuevamente: ";
        cin >> dni;
    }
    return dni;
}

template <typename T>
T validarPositivo(T valor){
    while (valor < 0){
        cout << "Valor incorrecto, vuelva a ingresar: ";
        cin >> valor;
    }
    return valor;
}

class Persona {
private:
    string clave;
protected:
    string correoelec;

public:
    string codigo;
    string nombre;
    int telefono;
    float desc;
    Persona(string nombre, string codigo) : nombre(nombre), codigo(codigo) {}
    Persona(string nombre, string codigo, int telefono, string clave, string correoelec) : nombre(nombre), codigo(codigo), telefono(telefono), clave(clave), correoelec(correoelec) {}

    friend ostream& operator<<(ostream& os, Persona& per) {
        os << "Nombre: " << per.nombre << endl;
        os << "Codigo: " << per.codigo << endl;
        os << "Telefono: " << per.telefono << endl;
        os << "Correo: " << per.correoelec << endl;
        return os;
    }

    virtual void agregarEnVector(vector<Persona*> vectorPersonas) = 0;
    float getDescuento();
};

class ClienteIndividual : public Persona {
private:
    string nivel;

public:
    float desc;

    ClienteIndividual(string nombre, string codigo, int telefono, string clave, string correoelec) : Persona(nombre, codigo, telefono, clave, correoelec) {
        nivel = "C";
        desc = 3.0 / 100.0;
    }

    void nivelA() {
        if (nivel == "A") {
            cout << "Ya se encuentra en la categoria A" << endl;
        }
        else {
            nivel = "A";
        }
    }

    void nivelB() {
        if (nivel == "B") {
            cout << "Ya se encuentra en la categoria B" << endl;
        }
        else {
            nivel = "B";
        }
    }

    void nivelC() {
        if (nivel == "C") {
            cout << "Ya se encuentra en la categoria C" << endl;
        }
        else {
            nivel = "C";
        }
    }

    void nivelD() {
        if (nivel == "D") {
            cout << "Ya se encuentra en la categoria D" << endl;
        }
        else {
            nivel = "D";
        }
    }

    void agregarEnVector(vector<Persona*> vectorPersonas) {
        vectorPersonas.push_back(this);
        cout << "El cliente individual se ha agregado correctamente al vector." << endl;
    }

    float getDescuento() {
        return desc;
    }
};

class ClienteCorporativo : public Persona {
private:
    string nivel;

public:
    float desc;
    ClienteCorporativo(string nombre, string codigo, int telefono, string clave, string correoelec) : Persona(nombre, codigo, telefono, clave, correoelec) {
        nivel = "C";
        desc = 10.0 / 100.0;
    }
    
    void nivelA() {
        if (nivel == "A") {
            cout << "Ya se encuentra en la categoria A" << endl;
        }
        else {
            nivel = "A";
        }
    }

    void nivelB() {
        if (nivel == "B") {
            cout << "Ya se encuentra en la categoria B" << endl;
        }
        else {
            nivel = "B";
        }
    }

    void nivelC() {
        if (nivel == "C") {
            cout << "Ya se encuentra en la categoria C" << endl;
        }
        else {
            nivel = "C";
        }
    }

    void nivelD() {
        if (nivel == "D") {
            cout << "Ya se encuentra en la categoria D" << endl;
        }
        else {
            nivel = "D";
        }
    }
    void agregarEnVector(vector<Persona*> vectorPersonas) {
        vectorPersonas.push_back(this);
        cout << "El cliente corporativo se ha agregado correctamente al vector." << endl;
    }

    float getDescuento() {
        return desc;
    }
};

class Vendedor : public Persona {
public:
    float salario;
    static int contvendedores;
    Vendedor(string nombre, string codigo, float salario) : Persona(nombre, codigo), salario(salario) {}
    static void aumentarVendedor(){contvendedores++;}
    void agregarEnVector(vector<Persona*> vectorPersonas) {
        vectorPersonas.push_back(this);
        cout << "El vendedor se ha agregado correctamente al vector." << endl;
    }
};

class Producto {
private:
    string nombre;
    float precio;
    int stock;
public:
    static int cantidadventas;
    Producto(string nombre, float precio, int stock) : nombre(nombre), precio(precio), stock(stock) {}
    string getnom(){return nombre;}
    float getprecio(){return precio;}
    int getstock(){return stock;}
    void agregarStock(int cantidad) {
        stock += cantidad;
    }

    void modificarPrecio(float nuevoPrecio) {
        precio = nuevoPrecio;
    }
    static void ventaRealizada(){cantidadventas++;}
    friend float calcularTotal(const Producto& producto, int cantidad, float descuento);
    friend ostream& operator<<(ostream& os, const Producto& producto){
        os << "Nombre: " << producto.nombre << endl;
        os << "Precio: S/" << producto.precio << endl;
        os << "Stock: " << producto.stock << endl;
        return os;
    }
};

float calcularTotal(const Producto& producto, int cantidad, float descuento) {
    while (cantidad > producto.stock){
        cout << "Cantidad superior a stock, vuelva a ingresar: " << endl;
        cin >> cantidad;
    }
    float total = (producto.precio * cantidad) * descuento;
    producto.ventaRealizada();
    return total;
}

void mostrarClientes(const vector<Persona*> vectorPersonas) {
    cout << "Lista de Clientes:" << endl;
    for (const auto persona : vectorPersonas) {
        if (dynamic_cast<ClienteIndividual*>(persona)) {
            cout << "Cliente Individual:" << endl;
        }
        else if (dynamic_cast<ClienteCorporativo*>(persona)) {
            cout << "Cliente Corporativo:" << endl;
        }
        cout << *persona << endl;
    }
}

void mostrarVendedores(const vector<Persona*> vectorPersonas) {
    cout << "Lista de Vendedores:" << endl;
    for (const auto persona : vectorPersonas) {
        if (dynamic_cast<Vendedor*>(persona)) {
            cout << "Vendedor:" << endl;
            cout << *persona << endl;
        }
    }
}
bool compararPorCodigo(const Persona* persona1, const Persona* persona2) {
    return persona1->codigo < persona2->codigo;
}

void ordenarPorNombre(vector<Persona*> vectorPersonas) {                                    
    sort(vectorPersonas.begin(), vectorPersonas.end(), compararPorCodigo);
}
//int Vendedor::contvendedor = 0;
int Producto::cantidadventas = 0;
int main() {
    vector<Persona*> vectorPersonas;
    vector<Producto> vectorProductos;
    vector<Persona*> vectorVendedores;
    ClienteIndividual cliente1("Cliente1", "C001", 123456789, "clave1", "cliente1@example.com");
    cliente1.nivelA();
    vectorPersonas.push_back(&cliente1);

    ClienteIndividual cliente2("Cliente2", "C002", 987654321, "clave2", "cliente2@example.com");
    cliente2.nivelB();
    vectorPersonas.push_back(&cliente2);

    ClienteCorporativo cliente3("Cliente3", "C003", 456789123, "clave3", "cliente3@example.com");
    cliente3.nivelC();
    vectorPersonas.push_back(&cliente3);

    // Crear vendedores por defecto
    Vendedor vendedor1("Vendedor1", "V001", 1000.0);
    vectorVendedores.push_back(&vendedor1);

    Vendedor vendedor2("Vendedor2", "V002", 1500.0);
    vectorVendedores.push_back(&vendedor2);

    Vendedor vendedor3("Vendedor3", "V003", 1200.0);
    vectorVendedores.push_back(&vendedor3);

    Vendedor vendedor4("Vendedor4", "V004", 1100.0);
    vectorVendedores.push_back(&vendedor4);

    Vendedor vendedor5("Vendedor5", "V005", 1300.0);
    vectorVendedores.push_back(&vendedor5);

    Vendedor vendedor6("Vendedor6", "V006", 1400.0);
    vectorVendedores.push_back(&vendedor6);

    Vendedor vendedor7("Vendedor7", "V007", 1700.0);
    vectorVendedores.push_back(&vendedor7);

    Vendedor vendedor8("Vendedor8", "V008", 1600.0);
    vectorVendedores.push_back(&vendedor8);

    Vendedor vendedor9("Vendedor9", "V009", 1800.0);
    vectorVendedores.push_back(&vendedor9);

    Vendedor vendedor10("Vendedor10", "V010", 2000.0);
    vectorVendedores.push_back(&vendedor10);

    // Crear productos por defecto
    Producto producto1("Producto1", 10.0, 50);
    vectorProductos.push_back(producto1);

    Producto producto2("Producto2", 20.0, 100);
    vectorProductos.push_back(producto2);

    Producto producto3("Producto3", 15.0, 30);
    vectorProductos.push_back(producto3);

    Producto producto4("Producto4", 25.0, 70);
    vectorProductos.push_back(producto4);

    Producto producto5("Producto5", 12.0, 80);
    vectorProductos.push_back(producto5);
    int opcion;
    bool salir = false;
    string eleccion, codcli;
    float desc;

    while (!salir) {
        cout << "SISTEMA COMERCIAL" << endl;
        cout << "1. NUEVOS CLIENTES" << endl;
        cout << "2. BUSCAR CLIENTES" << endl;
        cout << "3. NUEVO VENDEDOR" << endl;
        cout << "4. NUEVO PRODUCTO" << endl;
        cout << "5. VENTAS" << endl;
        cout << "6. LISTA DE CLIENTES" << endl;
        cout << "7. LISTA DE VENDEDORES" << endl;
        cout << "8. SALIR" << endl;
        cout << "Ingrese la opcion a realizar: ";
        cin >> opcion;

        try {
            if(opcion > 0){
                throw(1);
            }
            else{
                throw("a");
            }
        }
        catch (const int e) {
            try{
                if(opcion > 9){
                    throw(1);
                }
                switch (opcion) {
                case 1: {
                    cout << "Ingrese el nombre del cliente: ";
                    string nombre;
                    cin >> nombre;

                    cout << "Ingrese el codigo del cliente: ";
                    string codigo;
                    cin >> codigo;

                    cout << "Ingrese el telefono del cliente: ";
                    int telefono;
                    cin >> telefono;
                    telefono = validarTelefono(telefono);

                    cout << "Ingrese la clave del cliente: ";
                    string clave;
                    cin >> clave;

                    cout << "Ingrese el correo electronico del cliente: ";
                    string correoelec;
                    cin >> correoelec;

                    cout << "¿Es cliente individual o corporativo? (I/C): ";
                    char tipoCliente;
                    cin >> tipoCliente;

                    if (tipoCliente == 'I') {
                        Persona* clienteIndividual = new ClienteIndividual(nombre, codigo, telefono, clave, correoelec);
                        clienteIndividual->agregarEnVector(vectorPersonas);
                    }
                    else if (tipoCliente == 'C') {
                        Persona* clienteCorporativo = new ClienteCorporativo(nombre, codigo, telefono, clave, correoelec);
                        clienteCorporativo->agregarEnVector(vectorPersonas);
                    }
                    else {
                        throw runtime_error("Opcion invalida");
                    }

                    break;
                }

                case 2: {
                    string codcli;
                
                    cout << "Codigo de cliente: " ; 
                    cin >> codcli;
                    for (const auto persona : vectorPersonas) {
                        if (dynamic_cast<ClienteIndividual*>(persona)) {
                            if(codcli == persona->codigo){
                                cout << "Cliente encontrado, pertenece a 'Cliente Individual\n";
                            }
                        }
                        else if (dynamic_cast<ClienteCorporativo*>(persona)) {
                            if(codcli == persona->codigo){
                                cout << "Cliente encontrado, pertenece a 'Cliente Corporativo\n";

                            }
                        }
                        else{}
                    }
                    break;
                }

                case 3: {
                    cout << "Ingrese el nombre del vendedor: ";
                    string nombre;
                    cin.ignore();
                    getline(cin, nombre);

                    cout << "Ingrese el codigo del vendedor: ";
                    string codigo;
                    cin >> codigo;

                    cout << "Ingrese el salario del vendedor: ";
                    float salario;
                    cin >> salario;

                    Persona* vendedor = new Vendedor(nombre, codigo, salario);
                    vendedor->agregarEnVector(vectorVendedores);

                    break;
                }

                case 4: {
                    cout << "Ingrese el nombre del producto: ";
                    string nombre;
                    cin >> nombre;

                    cout << "Ingrese el precio del producto: ";
                    float precio;
                    cin >> precio;
                    precio = validarPositivo<float>(precio);

                    cout << "Ingrese el stock del producto: ";
                    int stock;
                    cin >> stock;
                    stock = validarPositivo<int>(stock);

                    Producto producto(nombre, precio, stock);
                    vectorProductos.push_back(producto);

                    break;
                }

                case 5: {
                    int cant;
                    string nom;
                    cout << "Codigo de cliente: " ;
                    cin >> codcli;
                    for (const auto persona : vectorPersonas) {
                        if (dynamic_cast<ClienteIndividual*>(persona)) {
                            if(codcli == persona->codigo){
                                desc = persona->desc;
                                nom = persona->nombre;

                            }
                        }
                        else if (dynamic_cast<ClienteCorporativo*>(persona)) {
                            if(codcli == persona->codigo){
                                desc = persona->desc;
                                nom = persona->nombre;

                            }
                        }
                    }
                    cout << "Ingrese nombre del producto a adquirir: ";
                    cin >> eleccion;
                    cout << "Ingrese cantidad a comprar: \n";
                    cin >> cant;
                    cant = validarPositivo<int>(cant);
                    
                    for(Producto p : vectorProductos){
                        if (p.getnom() == eleccion){
                            float total;
                            cout<<"producto encontrado\n";
                            total = calcularTotal(p,cant,desc);
                            cout << "Venta " << producto1.cantidadventas << endl;
                            cout << "Cliente: " << nom << endl;
                            cout << " - PRODUCTO - " << " - CANTIDAD - " << " - PRECIO UNI - " << " - TOTAL - " << endl;
                            cout << "   " << p.getnom() << "        " << cant << "              " << p.getprecio() << "            " << total << endl;
                        }
                    }
                    
                    break;
                }

                case 6: {
                    ordenarPorNombre(vectorPersonas);
                    mostrarClientes(vectorPersonas);
                    break;
                }

                case 7: {
                    ordenarPorNombre(vectorVendedores);
                    mostrarVendedores(vectorVendedores);
                    break;
                }

                case 8: {
                    cout << "Hasta pronto!" << endl;
                    salir = true;
                    break;
                }

                default:
                    throw runtime_error("Opcion invalida");
            }
            }
            catch(const int e){
                cout << "Error: Opcion no disponible\n" << endl;
                break;
            }
        }
        catch (char e){
            cout << "Error: Opcion invalida\n";
            break;
        }
    }    

    return 0;
}
