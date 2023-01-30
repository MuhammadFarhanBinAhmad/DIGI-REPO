#include <stdio.h>

typedef struct Inventory
{
    int health,speed,damage;
}Inventory;

Inventory TeamInventory[3];

int main(void)
{
    TeamInventory[0].damage = 1;
    TeamInventory[0].health = 1;
    TeamInventory[0].speed = 1;

    TeamInventory[1].damage = 5;
    TeamInventory[1].health = 5;
    TeamInventory[1].speed = 5;

    TeamInventory[2].damage = 25;
    TeamInventory[2].health = 25;
    TeamInventory[2].speed = 25;

    Inventory *p_inventory_Current = &TeamInventory[0];
    
    printf("%d\n",p_inventory_Current->damage);

    p_inventory_Current = &TeamInventory[1];

    printf("%d\n",p_inventory_Current->damage);
}