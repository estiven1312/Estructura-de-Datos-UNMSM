#include <iostream>
#define CANTIDAD_MAXIMA 8
using namespace std;
struct nodo
{
    char tipo;
    int codigo;
    struct nodo *sgte;
};

typedef struct nodo *TpLista;

TpLista crearNodo()
{
    TpLista nuevo = NULL;
    nuevo = new (struct nodo);
    cout << "****Crear Pedido******" << endl;
    do{
        cout << "Ingresar tipo --> ";
        fflush(stdin);
        cin.get(nuevo->tipo);
    } while(nuevo -> tipo != 'a' && nuevo -> tipo != 'e');
    cout << "Ingresar codigo --->";
    cin >> nuevo->codigo;
    cout << endl;
    nuevo->sgte = NULL;
    return nuevo;
}
// PUSH Permite insertar un nodo al inicio de uan Pila
void push(TpLista &lista, int &cantidad)
{
    if (cantidad < CANTIDAD_MAXIMA)
    {
        TpLista q = crearNodo();
        if (lista != NULL)
            q->sgte = lista;
        lista = q;
        cantidad++;
    }
    else
    {
        cout << "NO SE PUEDE APILAR, PILA DE PEDIDOS LLENA" << endl;
    }
}

void verPila(TpLista lista)
{

    int i = 0;
    cout << " "
         << "L"
         << "  "
         << "TIPO"
         << "\t"
         << "CODIGO" << endl;
    while (lista != NULL)
    {
        cout << " " << i + 1 << ") " << lista->tipo << "\t" << lista->codigo << endl;
        lista = lista->sgte;
        i++;
    }
}

void menu()
{

    system("CLS");
    cout << "\n\t LAB03\n\n";
    cout << "1.- Insertar elementos en Pila Pedidos" << endl;
    cout << "2.- Extraer de Pila Pedidos y Cargar en Cola Correspondiente" << endl;
    cout << "3.- Despachar Paquete" << endl;
    cout << "4.- Mostrar la Pila de Pedidos y las Colas correspondientes" << endl;
    cout << "0.- Salir" << endl
         << endl;

    cout << "Ingresar Opcion---> " << endl;
}
// POP extrae un nodo desde el inicio de una PILA
TpLista pop(TpLista &lista, int &cantidad)
{
    TpLista t = lista;
    if (lista == NULL)
    {
        cout << "ERROR: Lista vacia.. no permite esta opcion" << endl;
        system("pause");
        return t;
    }
    lista = lista->sgte;
    t->sgte = NULL;
    cantidad--;
    system("pause");
    return t;
}

void encolar(TpLista &lista, TpLista nodo, int &cantidad)
{
    
        
    TpLista p = lista;
    cantidad++;
    if (lista == NULL)
    {
        lista = nodo;
        
        return;
    }
    while (p->sgte != NULL)
    {
        p = p->sgte;
    }
    p->sgte = nodo;
}

void verCola(TpLista lista, int cantidad)
{

    int i = 0;
    cout<<"Cantidad de la cola: "<<cantidad<<endl;
    while (lista != NULL)
    {
        cout << " " << i + 1 << ") " << lista->tipo << "\t"<<lista->codigo;
        lista = lista->sgte;
        if (lista != NULL)
            cout << "----->";
        i++;
    }
    cout << endl;
}

void desencolar(TpLista &cola1, TpLista &cola2, char tipo, int &cantidad1, int &cantidad2)
{

    switch (tipo)
    {
    case 'a':
    {
        TpLista t = cola1;
        if (cola1 == NULL)
        {
            cout << "ERROR: COLA vacia.. no permite esta opcion" << endl;
            system("pause");
            return;
        }
        cola1 = cola1->sgte;
        cantidad1--;
        delete (t);
        break;
    }
    case 'e':
    { 
        TpLista t = cola2;
        if (cola2 == NULL)
        {
            cout << "ERROR: COLA vacia.. no permite esta opcion" << endl;
            system("pause");
            return;
        }
        cola2 = cola2->sgte;
        delete (t);
        cantidad2--;
        break;
    }
    }

    system("pause");
}

int main()
{
    TpLista pilaPedidos = NULL, temp = NULL;
    int cantidad = 0;
    TpLista colaAbarrotes = NULL, colaElectro = NULL;
    int opc, numeroAbarrotes=0, numeroElectro=0;
    do
    {
        menu();
        cin >> opc;

        switch (opc)
        {
        case 1:
        {   

            push(pilaPedidos, cantidad);
            system("pause");
            break;
        }
        case 2:
        {

            temp = pop(pilaPedidos, cantidad);
            if(temp == NULL)
            {
                cout<<"NO SE PUEDE, PERDON"<<endl;
                break;
            }
            switch (temp->tipo)
            {
            case 'a':
                encolar(colaAbarrotes, temp, numeroAbarrotes);
                break;
            
            case 'e':
                encolar(colaElectro, temp, numeroElectro);
                break;
            }

            system("pause");
            break;
        }

        case 3:
        {
            fflush(stdin);
            char tipo;
            cout<<"Ingrese el producto a despachar--->";cin.get(tipo);
            desencolar(colaAbarrotes, colaElectro, tipo, numeroAbarrotes, numeroElectro);
            break;
        }
        case 4:
        {
            cout << "*******PILA PEDIDOS **********" << endl
                 << endl;
            verPila(pilaPedidos);
            cout << "*******COLA ABARROTES **********" << endl
                 << endl;
            verCola(colaAbarrotes, numeroAbarrotes);
            cout << "*******COLA ELECTRO **********" << endl
                 << endl;
            verCola(colaElectro, numeroElectro);
            system("pause");
            break;
        }
        }
    } while (opc != 0);
    cout<<"\n\n\t\t\t****************FIN*****************"<<endl;
    return 0;
}


