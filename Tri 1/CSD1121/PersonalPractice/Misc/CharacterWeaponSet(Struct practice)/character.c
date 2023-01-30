#include<stdio.h>
struct weapon{
    char *name;
    int damage;
    float range;
}default_w = {"sword",30,2.5f};

struct shield{
    char *name;
    int defense;
}default_s = {"woodenShield",10};

struct character
{
    char* name;
    float speed;
    int health;
    
    struct weapon c_weapon;
    struct shield c_shield;
};

struct weapon create_w(char* name,int damage, float range)
{
    struct weapon new_w;
    new_w.name = name;
    new_w.damage = damage;
    new_w.range = range;
    
    return new_w;
}
struct shield create_s(char* name,int defense)
{
    struct shield new_s;
    new_s.name = name;
    new_s.defense = defense;

    return new_s;
}
int main() 
{
    printf("%s damage %d range : %.2f",default_w.name,default_w.damage,default_w.range);
    struct weapon w_2 = create_w("spear",20,5.f);
    printf("\n");
    printf("%s damage: %d range : %.2f",w_2.name,w_2.damage,w_2.range);
    
    printf("\n");
    struct weapon greg_w = create_w("Greg sword",500,-1.f);
    printf("%s damage: %d range : %.2f",greg_w.name,greg_w.damage,greg_w.range);

    fprintf(stdout,"\n");
    
    printf("%s defense: %d",default_s.name,default_s.defense);
    struct shield s_2 = create_s("IronShield",20);

    struct shield greg_s = create_s("Greg shield",0);

    printf("\n");
    printf("%s defense: %d",s_2.name,s_2.defense);
    
    fprintf(stdout,"\n");
    fprintf(stdout,"--------------------------------------------\n");

    struct character default_c = {"James",5.5f,100,default_w,default_s};
    printf("character name:%s\nhealth: %d\nspeed: %f\ncurrentweapon:%s\ncurrentshield:%s",default_c.name,default_c.health,default_c.speed,default_c.c_weapon.name,default_c.c_shield.name);

    fprintf(stdout,"\n");
    fprintf(stdout,"--------------------------------------------\n");

    struct character greg_c = {"Greg",2.4f,10,greg_w,greg_s};
    printf("character name:%s\nhealth: %d\nspeed: %f\ncurrentweapon:%s\ncurrentshield:%s",greg_c.name,greg_c.health,greg_c.speed,greg_c.c_weapon.name,greg_c.c_shield.name);
}