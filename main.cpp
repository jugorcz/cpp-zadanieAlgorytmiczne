#include <iostream>
#include <math.h>
using namespace std;

struct node
{
    node* next;
    int val;
    bool primeNumber;
};

node* arrayToList(int array[], int length)
{
    node* first = new node;
    first -> val = array[0];
    first -> primeNumber = false;

    node* tmp = first;
    for(int i=1; i<length; i++)
    {
        node* newNode = new node;
        newNode -> val = array[i];
        newNode -> primeNumber = false;
        tmp -> next = newNode;
        tmp = tmp -> next;
    }
    tmp -> next = NULL;
    return first;
}

bool isPrimeNumber(int number)
{
    if(number == 0 or number == 1) return false;
    for(int i = 2; i<=sqrt(number); i++)
        if(number%i == 0)
            return false;
    return true;
}

int main() {
    int arrayA[] = {2,3,9,2,5,1,3,7,10};
    int arrayB[] = {2,1,3,4,3,10,6,6,1,7,10,10,10};

    int a = sizeof(arrayA) / sizeof(int);  //liczba elementow tablicy A
    int b = sizeof(arrayB) / sizeof(int);  //liczba elementow tablicy B

    node* firstB = arrayToList(arrayB,b);   //tablica B przepisania do listy
    node* firstA = NULL; //tablica A bedzie zamieniana na liste w trakcie dzialania programu

    for(int i=0; i<a; i++) //petla glowna, szuka elementow tabA w tabB
    {
        bool found = false; //flaga okreslajaca czy dana liczba juz jest w liscie wynikowej A
        int quantity = 0; //ilosc powtorzen elementow w tablicy B

        node* toAdd = new node;  //wezel do dodania na koniec do listy A
        toAdd -> val = arrayA[i];
        toAdd -> next =NULL;

//----------------------sprawdzam czy dany numer juz zostal znaleziony i dodany do listy A--------------------
        node* tmp = firstA; //zmienna potrzebna do przebiegania po liscie
        node* lastNode = NULL; //bedzie wskazywala na ostatni element listy wynikowej
        if(tmp)
        {
            while(tmp)
            {
                if (!found and tmp -> val == toAdd -> val)
                {
                    found = true;
                    toAdd -> primeNumber = tmp -> primeNumber;
                }
                lastNode = tmp;
                tmp = tmp -> next;
            }
            if(found) //jesli znaleziono dany element w liscie wynikowej to dodajemy jeszcze jeden na jej koniec
            {
                lastNode -> next = toAdd;
                continue; //przechodzimy do kolejnego elementu
            }
        }

//------------------------gdy w liscie wynikowej A nie znaleziono tego numeru to szukamy w liscie B----------
        tmp = firstB;
        node* beforeTmp = firstB;
        while(tmp)
        {
            if(tmp -> val == toAdd -> val)
            {
                quantity++; //zwiekszam liczbe wystapien danego elementu
                node* toDelete = tmp; // i kasuje ten numer z listy B
                if(firstB == tmp) //jesli to pierwszy el do skasowania
                {
                    firstB = firstB -> next;
                    tmp = tmp -> next;
                    beforeTmp = beforeTmp -> next;
                    toDelete -> next = NULL;
                    delete toDelete;
                }
                else //jesli element do skasowania jest na koncu lub w środku
                {
                    beforeTmp -> next = tmp -> next;
                    tmp = tmp -> next;
                    toDelete -> next = NULL;
                    delete toDelete;
                }
            }
            else //jeśli nie znaleziono przechodze dalej
            {
                beforeTmp = tmp;
                tmp = tmp->next;
            }
        }
//------------------------wstawiam do listy wynikowej------------------------------------
        toAdd -> primeNumber = isPrimeNumber(quantity); //sprawdzam czy quantity jest liczba pierwsza
        if(lastNode) lastNode -> next = toAdd; //wstawiam na koniec listy wynikowej
        else firstA = toAdd; //jesli jeszcze lista nie powstala to teraz ustawiam perwszy element
    }

//------------------------/wyswietlam liste-----------------------------------------------
    while(firstA)
    {
        if(!firstA -> primeNumber)
            cout<<firstA -> val << " ";
        firstA = firstA -> next;
    }
    return 0;
}
