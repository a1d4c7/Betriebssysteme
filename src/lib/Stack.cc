#include "lib/Stack.h"


// Einfuegen eines Elementes auf den Stack
void Stack::push(Chain* item)
{
    item->next = tos; //alter tos ist elem unter neuem elem
    tos = item;      //neuen tos setzen
}


// Entfernen des obersten Stackelements
Chain* Stack::pop()
{
    Chain* item = 0;

    if (tos != 0)
    {
        tos = item->next; //neuen tos setzen  
        item = tos; //alter tos ist gesuchtes item   
    }
    
    return item;    
}


//gibt das oberste element im stack zurueck ohne es zu entfernen
Chain* Stack::peek()
{
    return tos;
}