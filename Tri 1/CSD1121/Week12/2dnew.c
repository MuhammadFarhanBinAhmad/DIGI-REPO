#include <stdio.h>
#include <stdlib.h>


int* read_grades(char const *file_name,int *student_count,int *quiz_count)
{
    FILE *ifs = fopen(file_name, "r");
    if (!ifs)
    {
        return NULL;
    }
    
    fscanf(ifs,"%d",student_count);
    fscanf(ifs,"%d",quiz_count);

    //int **grades = (int**)malloc(sizeof(int*) * *student_count);//allocate memory for student(grades[studentcount][])

    int t = *student_count * *quiz_count;

    int *grades = (int*)malloc(sizeof(int) * t);

    for (int i = 0 ; i < *student_count ; i++)
    {
        for (int j = 0;j< *quiz_count;j++)
        {
            fscanf(ifs,"%d",&grades[i * *quiz_count +j]);
        }
    }   
    // for (int i = 0;i < *student_count;++i)
    // {
    //     grades[i] = (int*) malloc(sizeof(int) * *quiz_count);//allocate memory for quizgrade(grades[][quiz_count])
    //     for (int j = 0; j < *quiz_count;++j)
    //     {
    //         fscanf(ifs,"%d",&grades[i][j]);
    //     }
    // }
    fclose(ifs);
    return grades;
}
void printgrades(int *grades,int *total,int quiz_count,int currentstud)
{
    *total = 0;
    for (int i = 0; i < quiz_count;i++)
    {
        printf("%d ",(*grades+i));
        *total += (*grades+i);
    }
    printf("\ntotal :%d",*total);
}
void printavrg(int *avrg,int *total,int currentstud,int quiz_count)
{
    *avrg = 0;

    *avrg = *total/quiz_count;
    printf("\navrg: %d",*avrg);
}
void printhighestval(int *grades,int *highestval,int quiz_count,int currentstud)
{
    *highestval = 0;

    for (int i =0; i < quiz_count;i++)
    {
        if (*highestval < (*grades+i))
        {
            *highestval = (*grades+i);
        }
    }
    printf("\nhighest score: %d",*highestval);
}
void freememoryallocated(int *grades,int *total,int *avrg,int *highestval,int student_count)
{
    //need reset to memory starting address cause code acrement all the memory to the last guy
    avrg -= student_count;
    total -= student_count;
    grades -= student_count;

    //free(dom)
    free(avrg);
    free(total);
    free(highestval);

    // for (int i =0 ; i < student_count;i++)
    // {
    //     free(grades);//clear out quiz memory
    // }
    free(grades);//clear out everyone else
}
int main(int agrv,char* agrc[])
{

    int student_count,quiz_count;
    int *grades = read_grades(agrc[1],&student_count,&quiz_count);
    int *total = (int*)malloc(sizeof(int) * student_count);
    int *avrg = (int*)malloc(sizeof(int) * student_count);
    int *highestval = (int*)malloc(sizeof(int) * student_count);
    //int *lowestval = (int*)malloc(size)
    if (grades == NULL)
    {
        return 0;
    }

    printf("%d | %d\n",student_count,quiz_count);

    for (int i =0; i < student_count;i++)
    {
        printf("Student %d\n",i+1);
        printgrades(grades,total,quiz_count,i);
        printavrg(avrg,total,i,quiz_count);
        printhighestval(grades,highestval,quiz_count,i);
        total++;
        grades++;
        avrg++;
        printf("\n");
    }

    freememoryallocated(grades,total,avrg,highestval,student_count);

    return 0;
}