#include <iostream>
#include <vector>
#include <conio.h>
#include <unordered_map>
#include <map>
#include <fstream>
#include <string>
using namespace std;
 
 
// -----------------------DECLARACION DE LAS CLASES ---------------------
 
// ----------- CLASE MEDICAMENTOS -----------
class Medicamentos {
    private:
    string Denominacion_Generica;
    string Forma_Farmaceutica;
    string Concentracion;
    string Denominacion_Distinta;
    string Registro_Sanitario;
    string Titular;
    int stock; // Se agrega el atributo para llevar el stock
 
public:
    Medicamentos(string _denominacionGenerica, string _formaFarmaceutica,
                 string _concentracion, string _denominacionDistinta,
                 string _registroSanitario, string _titular, int _stock) {
        Denominacion_Generica = _denominacionGenerica;
        Forma_Farmaceutica = _formaFarmaceutica;
        Concentracion = _concentracion;
        Denominacion_Distinta = _denominacionDistinta;
        Registro_Sanitario = _registroSanitario;
        Titular = _titular;
        stock = _stock;
    }
 
    //setter
    void setStock(int _stock) {
        stock = _stock;
    }
 
    int getStock() const {
        return stock;
    }
    void setdenominacionGenerica(string& _denominacionGenerica){
        Denominacion_Generica = _denominacionGenerica;
    }
    void setformaFarmaceutica(string& _formaFarmaceutica){
        Forma_Farmaceutica = _formaFarmaceutica;
    }
    void setconcentracion(string& _concentracion){
        Concentracion = _concentracion;
    }
    void setdenominacionDistinta(string& _denominacionDistinta){
        Denominacion_Distinta = _denominacionDistinta;
    }
    void setregistroSanitario(string& _registroSanitario){
        Registro_Sanitario = _registroSanitario;
    }
    void settitular(string& _titular){
        Titular = _titular;
    }
 
 
//getter
   string getdenominacionGenerica() const{
        return Denominacion_Generica;
    }
    string getformaFarmaceutica(){
        return Forma_Farmaceutica;
    }
    string getconcentracion(){
        return Concentracion;
    }
    string getdenominacionDistinta(){
        return Denominacion_Distinta;
    }
    string getregistroSanitario(){
        return Registro_Sanitario;
    }
    string gettitular(){
        return Titular;
    }
 
};
 
// ----------- FIN CLASE MEDICAMENTOS -----------
 
 
// ----------- CLASE EMPLEADOS -----------
 
class Empleados{
private:
    string Nombre_Empleado;
    int Expediente;
    string RFC;
    vector <string> v;
 
public:
    Empleados(string _nombreEmpleado, int _expediente, string _RFC, vector<string> _v){
        Nombre_Empleado = _nombreEmpleado;
        Expediente = _expediente;
        RFC = _RFC;
        v = _v;
    }
 
//setter
    void setnombreEmpleado(string& _nombreEmpleado){
        Nombre_Empleado = _nombreEmpleado;
    }
    void setexpediente(int& _expediente){
        Expediente = _expediente;
    }
    void setRFC(string& _RFC){
        RFC = _RFC;
    }
    void setRFC(vector<string> _v){
        v = _v;
    }
 
//getter
    string getnombreEmpleado(){
        return Nombre_Empleado;
    }
    int getexpediente(){
        return Expediente;
    }
    string getRFC(){
        return RFC;
    }
   
 
};
 
//------------------------------MAPA GLOBAL-------------------------------------------
multimap<string, Empleados> mapaNombreId;  
multimap<string, Medicamentos> inventario;
vector <string> v;
void menu();
void mostrarEmpleados();
void menuEmpleados();
void gestioninventario(multimap<string, Medicamentos>& inventario);

// -----------------------EMPLEADOS ---------------------
void numEmpleados(multimap<string, Empleados> mapaNombreId, multimap<string, Medicamentos> inventario){
    cout << "Numero de empleados: "<< mapaNombreId.size() << endl;
    cout << "Numero de medicamentos: "<<inventario.size() << endl;

    int x;
    do{
        cout << "  Elige una opcion \n";
        cout << "1.Menu empleados y medicamento\n";
        cout << "2.Menu principal\n";
        cin >> x;
    switch (x)
    {
    case 1:
        mostrarEmpleados();
        break;
    
    case 2:
        menu();
        break;

    default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
    }
    }while( x != 2);
}

void imprimirMedicamentosStock(const std::multimap<std::string, Medicamentos>& medicamentosMultimap, int umbralStock) {
    std::cout << "Medicamentos con stock de " << umbralStock << " o mas:" << std::endl;

    for (const auto& par : medicamentosMultimap) {
        const Medicamentos& medicamento = par.second;
        if (medicamento.getStock() >= umbralStock) {
            std::cout << "Nombre: " << medicamento.getdenominacionGenerica() <<", Stock: " << medicamento.getStock() << std::endl;
        }
    }
    mostrarEmpleados();
}

void mostrarEmpleados(){
    cout << "\n1. Imprimir el numero total de medicamentos y empleados\n";
    cout << "2. Imprimir el numero de medicamentos con stock mayor a una cantidad\n";
    cout << "3. Menu principal\n";
    int op;
    cin >> op;
    if (op==1)
    {
        numEmpleados(mapaNombreId, inventario);
    }
    else if (op==2) {
        cout << "Ingrese el numero de stock:\n";
        int n;
        cin >> n;
        imprimirMedicamentosStock(inventario, n);
        
    } else {
        menu();
    }
}

void vaciar(multimap<string, Empleados> mapaNombreId, multimap<string, Medicamentos> inventario){
    mapaNombreId.clear();
    inventario.clear();
}
 
void eliminar() {
    string nombre;
    cout << "Ingrese el nombre del empleado que desea eliminar:\n";
    cin >> nombre;
 
   
    auto range = mapaNombreId.equal_range(nombre);
    if (range.first != mapaNombreId.end()) {
        cout << "Seleccione el ID del empleado que desea eliminar:\n";
 
       
        int counter = 1;
        for (auto it = range.first; it != range.second; ++it) {
            cout << counter << ". ID: " << it->second.getRFC() << endl;
            counter++;
        }
 
       
        int seleccion;
        cin >> seleccion;
 
        if (seleccion > 0 && seleccion <= counter - 1) {
           
            auto itToDelete = range.first;
            advance(itToDelete, seleccion - 1);
 
           
            mapaNombreId.erase(itToDelete);
 
            cout << "Empleado eliminado con exito.\n";
           
        } else {
            cout << "Selección invalida.\n";
        }
    } else {
        cout << "No se encontro ningún empleado para " << nombre << endl;
    }
    menuEmpleados();
}
 
void busqueda() {
    string nombre;
    cout << "Ingrese el nombre para consultar el ID:\n";
    cin >> nombre;
 
    // Buscar en el multimap global
    auto range = mapaNombreId.equal_range(nombre);
    if (range.first != mapaNombreId.end()) {
        cout << "ID para " << nombre << ":\n";
        for (auto it = range.first; it != range.second; ++it) {
            cout << "Nombre: " << it->second.getnombreEmpleado() << ", Expediente: " << it->second.getRFC() << endl;
        }
    } else {
        cout << "No se encontro un ID para " << nombre << endl;
    }
    cout << "1. Menu\n";
    cout << "2. Buscar otro empleado\n";
    int op = 0;
    cin >> op;
    switch (op)
    {
    case 1:
        menuEmpleados();
        break;
    case 2:
        busqueda();
        break;
   
    default:
        break;
    }
}
 
string crearId(string nm, int fe) {
    static int n = 0;
    string id = nm + to_string(fe) + to_string(n);
    n++;
    return id;  
}
 
void agregar() {
    int op = 0;
    string nm, edo, ho;
    int num;
    
    int fe;
    cout << "--Ingrese los espacios con guion bajo--:\n";
    cout << "Inserte nombre:\n";
    cin >> nm;
    cout << "Inserte Expediente:\n";
    cin >> fe;
    cout << "Cuantos dias trabaja:\n";
    cin >> num;
   
   
    for (int i = 0; i < num; i++)
    {
        cout << "Dias laborales:\n";
        cin >> ho;
        v.push_back(ho);
    }
   
    string id = crearId(nm, fe);
    Empleados nuevoEmpleado(nm, fe, id, v);
    cout << "ID generado: " << id << endl;
    mapaNombreId.insert(make_pair(nm, nuevoEmpleado));  // Cambiado a insert
 
    cout << "\nEmpleado agregado:\n";
    cout << "Nombre: " << nm << ", ID: " << id << endl;
    cout << "Dias laborales: ";
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << endl;
    }
    cout << "1. Agregar otro empleado\n";
    cout << "2. Ir al menu de gestion de empleados\n";
    
   
    cin >> op;
    if(op==1){
        agregar();
    } else {
        menuEmpleados();
    }
}
 
void menuEmpleados(){
    int op = 0;
    cout << "1. Agregar empleado\n";
    cout << "2. Eliminar empleado\n";
    cout << "3. Buscar empleado\n";
    cout << "4. Menu principal\n";
    cin >> op;
    switch (op)
    {
    case 1:
        agregar();
        break;
    case 2:
        eliminar();
        break;
    case 3:
        busqueda();
        break;
    case 4:
        menu();
        break;
    default:
        break;
    }
}

// -----------------------RECETAS ---------------------
void crearReceta() {
    string nombrePaciente, fechaEmision, medicamento, dosis, frecuencia, duracion, nombreMedico, firma;
    char guardar;
 
    cout << "Ingrese el Nombre del paciente: ";
    cin.ignore();  // Para evitar problemas con getline después de cin
    getline(cin, nombrePaciente);
 
    cout << "Ingrese la Fecha de emision: ";
    getline(cin, fechaEmision);
 
    cout << "Ingrese el Medicamento: ";
    getline(cin, medicamento);
 
    cout << "Ingrese la Dosis: ";
    getline(cin, dosis);
 
    cout << "Ingrese la Frecuencia: ";
    getline(cin, frecuencia);
 
    cout << "Ingrese la Duracion de la medicacion: ";
    getline(cin, duracion);
 
    cout << "Ingrese el Nombre del medico: ";
    getline(cin, nombreMedico);
 
    cout << "Ingrese la Firma digital: ";
    getline(cin, firma);
 
    cout << "\nDesea guardar la receta en un documento de texto?\n1.Si\n2.No\n ";
    cin >> guardar;
 
    if (guardar == '1') {
        // Guardar la receta en un archivo de texto
        ofstream archivo("receta.txt");
        archivo << "Nombre del paciente: " << nombrePaciente << endl;
        archivo << "Fecha de emision: " << fechaEmision << endl;
        archivo << "Medicamento: " << medicamento << endl;
        archivo << "Dosis: " << dosis << endl;
        archivo << "Frecuencia: " << frecuencia << endl;
        archivo << "Duracion de la medicacion: " << duracion << endl;
        archivo << "Nombre del medico: " << nombreMedico << endl;
        archivo << "Firma digital: " << firma << endl;
        archivo.close();
 
        cout << "\nReceta guardada con exito en receta.txt" << endl;
    }
 
    char crearOtraReceta;
    cout << "\nQuiere crear otra receta?\n1.Si\n2.No\n";
    cin >> crearOtraReceta;
 
    if (crearOtraReceta == '1' ) {
        // Llamada recursiva para crear otra receta
        crearReceta();
    }
    else {
        menu();
    }
}

void menuReceta(){
    int alternativa;
    do{
        cout << "\nElige una opcion:\n";
        cout << "1.Crear Receta\n";
        cout << "2.Volver al menu principal\n";
        cin >> alternativa;
    switch (alternativa)
    {
    case 1:
        crearReceta();
        break;
    
    case 2:
        menu();
        break;
    default:
        cout << "Opcion invalida. Intente nuevamente.\n";
        break;
    }
    }while (alternativa != 2);
}

string crearId2(string nm, string fe) {
    static int n = 0;
    string id = nm + fe + to_string(n);
    n++;
    return id;  
}

// -----------------------INVENTARIO ---------------------
void busqueda2(){
    string id;
    cout << "\nIngrese el Registro sanitario para consultar el nombre:\n";
    cin >> id;
 
    // Buscar en el multimap global
    auto range = inventario.equal_range(id);
    if (range.first != inventario.end()) {
        cout << "\nRegistro sanitario para " << id << ":\n";
        for (auto it = range.first; it != range.second; ++it) {
            cout << "Medicamento: " << it->second.getdenominacionGenerica() << ", Registro sanitario: " << it->second.getregistroSanitario() << ", Stock: "<< it->second.getStock() << endl;
        }
    } else {
        cout << "No se encontro un medicamento para " << id << endl;
    }
    cout << "\nElija una opcion\n";
    cout << "1. Menu\n";
    cout << "2. Buscar otro medicamento\n";
    int op = 0;
    cin >> op;
    switch (op)
    {
    case 1:
        gestioninventario(inventario);
        break;
    case 2:
        busqueda2();
        break;
   
    default:
        break;
    }
}
 
void crearMedicamento(multimap<string, Medicamentos>& inventario) {
 
    string denominacionGenerica, formaFarmaceutica, concentracion, denominacionDistinta, registroSanitario, titular;
    int stock;
    cout << "\n---Ingrese los espacios con guion bajo--- " << endl;
    cout << "Ingrese la Denominacion Generica: " << endl;
    cin >> denominacionGenerica;
    cout << "Ingrese la Forma Farmaceutica: " << endl;
    cin >> formaFarmaceutica;
    cout << "Ingrese la Concentracion: " << endl;
    cin >> concentracion;
    cout << "Ingrese la Denominacion Distinta: " << endl;
    cin >> denominacionDistinta;
    cout << "Ingrese el Titular: " << endl;
    cin >> titular;
    cout << "Ingrese el stock inicial: " << endl;
    cin >> stock;
    //crear id
    string id = crearId2(denominacionGenerica, concentracion);
    // Crear un nuevo objeto Medicamentos
    Medicamentos nuevoMedicamento(denominacionGenerica, formaFarmaceutica, concentracion, denominacionDistinta, id, titular, stock);
    // Agregar el nuevo medicamento al inventario
    inventario.insert({ id, nuevoMedicamento });
    cout << "\nRegistro sanitario: "<< id << endl;
 
    cout << "\nMedicamento agregado al inventario.\n";
    int op;
    cout << "\nElija una opcion:\n1. Agregar otro\n2. Ir al menu\n";
    cin >> op;
    if (op==1)
    {
        crearMedicamento(inventario);
    } else{
        gestioninventario(inventario);
    }
   
}
 
void eliminarDelStock(multimap<string, Medicamentos>& inventario) {
    string registroSanitario;
    cout << "\n--Ingrese los espacios con guion bajo-- " << endl;
    int cantidad;
    cout << "Ingrese el Registro Sanitario del medicamento: ";
    cin >> registroSanitario;
    cout << "Ingrese la cantidad a eliminar: ";
    cin >> cantidad;
 
    // Verificar si el medicamento está en el inventario
    auto it = inventario.find(registroSanitario);
    if (it != inventario.end()) {
        it->second.setStock(it->second.getStock() - cantidad);
        cout << "\nStock actualizado para el medicamento con Registro Sanitario " << registroSanitario << ".\n";
    } else {
        cout << "\nMedicamento no encontrado en el inventario.\n";
    }
}
 
void actualizarStock(multimap<string, Medicamentos>& inventario) {
    string registroSanitario;
    cout << "--Ingrese los espacios con guion bajo-- " << endl;
    int nuevoStock;
    cout << "Ingrese el Registro Sanitario del medicamento: ";
    cin >> registroSanitario;
    cout << "Ingrese el nuevo stock: ";
    cin >> nuevoStock;
 
    // Verificar si el medicamento está en el inventario
    auto it = inventario.find(registroSanitario);
    if (it != inventario.end()) {
        it->second.setStock(nuevoStock);
        cout << "\nStock actualizado para el medicamento con Registro Sanitario " << registroSanitario << ".\n";
        } else {
        cout << "\nMedicamento no encontrado en el inventario.\n";
    }
}
 
void gestioninventario(multimap<string, Medicamentos>& inventario) {
    int opcion;
    do {
        cout << "\nOpciones:\n";
        cout << "1. Crear medicamento\n";
        cout << "2. Eliminar del stock\n";
        cout << "3. Actualizar stock\n";
        cout << "4. Buscar medicamento\n"; 
        cout << "5. Volver a menu principal\n";
        cout << "\nIngrese su opcion: ";
        cin >> opcion;
 
        switch (opcion) {
            case 1:
                crearMedicamento(inventario);
                break;
            case 2:
                eliminarDelStock(inventario);
                break;
            case 3:
                actualizarStock(inventario);
                break;
            case 4:
                busqueda2();
                break;
            case 5:
                menu();
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
        }
    } while (opcion != 5);
}
 
 // -----------------------MENU PRINCIPAL ---------------------
void menu(){
cout << "      _/_/_/  _/_/_/_/_/    _/_/    _/    _/  _/_/_/_/_/  _/          _/    _/_/    _/_/_/    _/_/_/_/" << endl;
cout << "   _/            _/      _/    _/  _/    _/      _/      _/          _/  _/    _/  _/    _/  _/" << endl;
cout << "    _/_/        _/      _/    _/  _/    _/      _/      _/    _/    _/  _/_/_/_/  _/_/_/    _/_/_/" << endl;
cout << "       _/      _/      _/    _/  _/    _/      _/        _/  _/  _/    _/    _/  _/    _/  _/" << endl;
cout << "_/_/_/        _/        _/_/      _/_/        _/          _/  _/      _/    _/  _/    _/  _/_/_/_/" << endl;
    cout << "                 ..........''''''''',,'',,,,,,',,,'',,,,,,,,,,,,,,,,,,'''''''''........" << endl;
    cout << "                 .........'''''''''''',,,'',,,,,:cllllllc;,,,',,',,,,,,'''''''''......." << endl;
    cout << "                 .......'''''''''','',,,'''''',loodoodooldo,''',,',,,,,''''''''''......" << endl;
    cout << "                 .......''''''''''''''',,;okOOdcokO0OOd,.:Okdoc,''',,,,'''''''''''....." << endl;
    cout << "                 ......'''''''''''',.;x00KNWWNNNNNWNNWO:.'clcoxkxc,',,'',''''''''''...." << endl;
    cout << "                 ......''''''''''',..xNNWNNWWNNXXNNNWNO:.,dkxo:;dOx;'''''''''''''''...." << endl;
    cout << "                 ......''''''''''',,'xNK0KXNWNNKocloooc;...;cx0x;;Ok;',''''''''''''...." << endl;
    cout << "                 ......'''''''''''lo,xXl,;:l0WNk;.''.'',.;::o;;xl.;0x,','''''''''''...." << endl;
    cout << "                 ......'''''''''',kx,xX:.'''dNXl',::;,,,.cd:xO:;cldOx;'''''''''''''...." << endl;
    cout << "                 ......'''''''''';Ok,dXc...'dNXl,,,'''''.:d,;xkddoc:,,'''''''''''''...." << endl;
    cout << "                 .......''''''''',kO,lXd....oNXl','....:oo:'.'''''''''''''''''''''....." << endl;
    cout << "                 ........'''''''''oKc'xKl...,do,.,,'.'';ldxkxo:,'''''''''''''''''......" << endl;
    cout << "                 ..........''''''',x0:'o0k;.......''',,,'',;coxkxc,'''''''''''''......." << endl;
    cout << "                 ...........''''''',d0o';x0kl,.........'',cxo;',cxko;'''''''''........." << endl;
    cout << "                 .............'''''''ckkl;;cdkxo:'........,lOKx;..:kOc''.''''.........." << endl;
    cout << "                 ...............'''''.':dkxl;,:oxxl;,'.......c0Kc..'d0c'.'............." << endl;
    cout << "                 .................'...'..,:oOd''',:clll:'.....;0K:...xO;.'............." << endl;
    cout << "                 ....................',;:,..dx,c:.....,:'....'oXNd.,.:0o..............." << endl;
    cout << "                 .................;ldxdx0x'.dx,c:...'.........lKWd':,;0d..............." << endl;
    cout << "                 .................oKd,'.c0o.ox,::...''........;0K:':.:0l..............." << endl;
    cout << "                 .................;Od.,;'l0o:llc:;,;;,'.....,o00c':''kk,..............." << endl;
    cout << "                 ..................cOo',:,:xkdodollllc::cldk0Oo;,;''xO:................" << endl;
    cout << "                 ...................:kx:',,;codxxxxxkxxxxdol:;;,''ckx;................." << endl;
    cout << "                 ....................'lkxl;,,',,''''''....',,,,:okx:..................." << endl;
    cout << "                 .......................:oxddoc:;'......';clodxdl;....................." << endl;
    cout << "                 ..........................':coddxdl;;cdxdolc;'........................" << endl;
    cout << "                 .................................:dkkd:'.............................." << endl;
    cout << "                 ......................................................................" << endl;
    int choseAnOption;
    cout << "\n";
    cout << "   ELIJA LA ACCION A REALIZAR: \n1. Gestion de Inventario \n2. Recetas Medicas \n3. Gestion de Empleados \n4. Mostrar numero de empleados y medicamentos \n5. Salir del menu" << endl;
    cin >> choseAnOption;
    while(choseAnOption > 6){
    cout << "   Ingrese una opcion valida" << endl;
    cin >> choseAnOption;
    }
    switch (choseAnOption){
        case 1:
        cout << "   ---Gestionando Inventario--" << endl;
        gestioninventario(inventario);
        break;
 
        case 2:
        cout << "   --Recetas Medicas--" << endl;
        menuReceta();
        break;
 
        case 3:
        cout << "   --Gestion de Empleados--" << endl;
        menuEmpleados();
        break;

        case 4:
        cout << "   --Menu empleados y medicamentos--" << endl;
        mostrarEmpleados();
        break;

        case 5:
        cout << "   Saliste del menu" << endl;
        break;
}}
 
int main(){
  menu();
  getch();
  return 0;
}