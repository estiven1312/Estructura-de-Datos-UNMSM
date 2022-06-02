#include <iostream>
#include <string>

enum TipoPaquete{Abarrote, Electro};
std::string tipoNames[] = {"Abarrote", "Electro"};

// Estructura paquete
struct Paquete{
    TipoPaquete tipo_paquete;
    int codigo;
    void createPaquete();
};

// Constructor paquete
 void Paquete::createPaquete() {
    int tipo;
    std::cout<<"Seleccione el tipo de pedido"<<std::endl;
    std::cout<<"1. Abarrote \n2. Electro"<<std::endl;
    std::cout<<"Ingrese el tipo (1 para abarrote y 2 para electro)"<<std::endl;
    std::cout<<"Tipo: ";
    std::cin>>tipo;
    if(tipo == 1){
        tipo_paquete = Abarrote;
    } else {
        tipo_paquete = Electro;
    }
    std::cout<<"Ingrese el codigo del paquete (debe ser un numero de 4 cifras)"<<std::endl;
    std::cout<<"Codigo: ";
    std::cin>>codigo;
}

// Estructura Nodo
struct Node{
    Paquete paquete;
    struct Node *next_node;
    //Constructores
    Node(){
        next_node = NULL;
    };
    Node(Paquete new_paquete){
        paquete = new_paquete;
        next_node = NULL;
    }

};
typedef struct Node *Node_ptr;

// Estructura ColaPedidos
struct ColaPedidos{
    Node_ptr top_node;
    TipoPaquete tipo_cola;
    int cant_paquetes;
    ColaPedidos(TipoPaquete tipo){
        cant_paquetes = 0;
        tipo_cola = tipo;
        top_node = NULL;
    };
    void agregarPaquete(Paquete new_paquete);
    void despacharPaquete();

};

// Estructura PilaPedidos
struct PilaPedidos{
    Node_ptr top_node;
    int pedidos_number;
    PilaPedidos(){
        top_node = NULL;
        pedidos_number = 0;
    };
    void agregarPaquete();
    void reasignarPaquete(ColaPedidos &cola_abarrotes, ColaPedidos &cola_electro);
};



// Declaracion de funciones
void menu(PilaPedidos &pila_pedidos, ColaPedidos &cola_abarrotes, ColaPedidos &cola_electro);
void showList(Node_ptr list_head);
void mostrarPaquetes(Node_ptr top_node, std::string nombre_lista);

// Main
int main() {
    PilaPedidos pila_pedidos = PilaPedidos();
    ColaPedidos cola_abarrotes = ColaPedidos(Abarrote);
    ColaPedidos cola_electro = ColaPedidos(Electro);
    menu(pila_pedidos, cola_abarrotes, cola_electro);
    return 0;
}


// Menu
void menu(PilaPedidos &pila_pedidos, ColaPedidos &cola_abarrotes, ColaPedidos &cola_electro){
    int opc;
    std::cout<<"\nElija una opcion del menu:"<<std::endl;
    std::cout<<"1. Recibir pedido\n";
    std::cout<<"2. Reasignar pedido\n";
    std::cout<<"3. Despachar pedido\n";
    std::cout<<"4. Mostrar estado de las pilas y colas"<<std::endl;
    std::cout<<"5. Salir\n";
    std::cout<<"Opcion: ";
    std::cin>>opc;

    switch (opc) {
        case 1:{
            pila_pedidos.agregarPaquete();
            mostrarPaquetes(pila_pedidos.top_node, "pedidos");
            break;
        }
        case 2:{
            pila_pedidos.reasignarPaquete(cola_abarrotes, cola_electro);
            mostrarPaquetes(pila_pedidos.top_node, "pedidos");
            mostrarPaquetes(cola_electro.top_node, "electro");
            mostrarPaquetes(cola_abarrotes.top_node, "abarrotes");
            break;
        }
        case 3:{
            int cola_despacho;
            std::cout<<"¿De que cola desea despachar?\n";
            std::cout<<"1. Abarrotes \n2.Electro\n";
            std::cout<<"Cola: (1 para abarrotes 2 para electro)";
            std::cin>>cola_despacho;
            if(cola_despacho == 1){
                cola_abarrotes.despacharPaquete();
                mostrarPaquetes(cola_abarrotes.top_node, "abarrotes");
                std::cout<<"\nNumero de paquetes en la cola de abarrotes: "<<cola_abarrotes.cant_paquetes<<std::endl;
            } else {
                cola_electro.despacharPaquete();
                mostrarPaquetes(cola_electro.top_node, "electro");
                std::cout<<"\nNumero de paquetes en la cola de electro: "<<cola_electro.cant_paquetes<<std::endl;


            }
            break;
        }
        case 4:{
            mostrarPaquetes(pila_pedidos.top_node, "pedidos");
            mostrarPaquetes(cola_electro.top_node, "electro");
            mostrarPaquetes(cola_abarrotes.top_node, "abarrotes");
            break;
        }
        default:
            break;
    }
    if(opc != 5){
        menu(pila_pedidos, cola_abarrotes, cola_electro);
    }
}


// Metodos de PilaPedidos

// Agrega pedido a la pila de pedidos
void PilaPedidos::agregarPaquete() {
    if(pedidos_number == 8){
        std::cout<<"Limite de pedidos alcanzado (8 como maximo)."<<std::endl;
        return;
    }
    Node_ptr new_node = new Node();
    new_node->paquete.createPaquete();
    std::cout<<"Agregando a la lista de pedidos el paquete de tipo "<<tipoNames[new_node->paquete.tipo_paquete]<<" con codigo "<<new_node->paquete.codigo<<std::endl;
    pedidos_number++;
    if(!top_node){
        top_node = new_node;
        return;
    }
    new_node->next_node = top_node;
    top_node = new_node;
    
}

// Reasigna un pedido de la lista de pedidos
void PilaPedidos::reasignarPaquete(ColaPedidos &cola_abarrotes, ColaPedidos &cola_electro) {
    if(!top_node){
        std::cout<<"Pila de pedidos vacia. No hay elementos para reasignar."<<std::endl;
        return;
    }
    std::cout<<"Reasignando paquete de tipo "<<tipoNames[top_node->paquete.tipo_paquete]<<" con codigo "<<top_node->paquete.codigo<<std::endl;
    if(top_node->paquete.tipo_paquete == Abarrote){
        cola_abarrotes.agregarPaquete(top_node->paquete);
    } else {
        cola_electro.agregarPaquete(top_node->paquete);
    }
    if(!top_node->next_node){
        top_node = NULL;
        return;
    }
    Node_ptr top_node_copy = top_node;
    top_node = top_node->next_node;
    delete top_node_copy;

}

//Metodos de ColaPedidos

// Agrega un paquete reasignado a la cola
void ColaPedidos::agregarPaquete(Paquete paquete) {
    Node_ptr new_paquete = new Node(paquete);
    cant_paquetes++;
    if(!top_node){
        top_node = new_paquete;
        return;
    }
    Node_ptr top_node_copy = top_node;
    while(top_node_copy->next_node){
        top_node_copy = top_node_copy->next_node;
    }
    top_node_copy->next_node = new_paquete;

};

// Despacha un paquete de la cola
void ColaPedidos::despacharPaquete() {
    if(!top_node){
        std::cout<<"No se encuentran paquetes para despechar en la cola de "<<tipoNames[top_node->paquete.tipo_paquete]<<std::endl;
        return;
    }
    cant_paquetes--;
    if(!top_node->next_node){
        std::cout<<"Despachando el paquete de la lista de "<<tipoNames[tipo_cola]<<" con codigo "<<top_node->paquete.codigo<<std::endl;
        top_node = NULL;
        return;
    }
    Node_ptr top_node_copy = top_node;
    Node_ptr prev_node = NULL;
    std::cout<<"Despachando el paquete de la lista de "<<tipoNames[tipo_cola]<<"con codigo "<<prev_node->next_node->paquete.codigo<<std::endl;
    while(top_node_copy->next_node){
        prev_node = top_node_copy;
        top_node_copy = top_node_copy->next_node;
    }
    prev_node->next_node = NULL;
}


// Muestra los paquetes
void mostrarPaquetes(Node_ptr top_node, std::string nombre_lista) {
    if(!top_node){
        std::cout<<"La lista de "<<nombre_lista<<" se encuentra vacia."<<std::endl;
        return;
    }
    Node_ptr top_node_copy = top_node;
    int count = 1;
    std::cout<<"\nMostrando lista de paquetes de "<<nombre_lista<<std::endl;
    while(top_node_copy){
        std::cout<<"Pedido: "<<count<<std::endl;
        std::cout<<"Tipo: "<<tipoNames[top_node_copy->paquete.tipo_paquete]<<std::endl;
        std::cout<<"Codigo: "<<top_node_copy->paquete.codigo<<std::endl;
        count++;
        top_node_copy = top_node_copy->next_node;
    }

}





