//I WANT TO PLAY WITH YOU
//        YOUR FRIEND, AI

#include <stdio.h>
#include <stdlib.h>
/* ********************************************************************
 * Вывести домик. Первое число - это ширина , а второе - высота дома
 * Ширина и высота должны быть в пределах от 3 до 69
 *  *******************************************************************/
int test_values (int, int);     // проверка значений
void print_house (int, int);        // рисуем дом
 
 
int main (void)
{
    int a = 80;
    int b = 25;
    print_house(a, b);
 
    //получаем от пользователя значения:
//    printf("input a (3 to 69) :");
//    scanf("%d", &a);        //ширина дома
//    printf("input b (3 to 69) :");
//    scanf("%d", &b);        //высота дома
 
    //проверяем полученные значения:
//    int Error = test_values(a, b);
//    if (!Error) print_house (a, b);    //if(Error == 0)
 
    //return Error;
}
//-------------------------------------------------------------------------
// Проверяем входные данные
//-------------------------------------------------------------------------
//int test_values (int x, int y)
//{
//    if (x*y == 0)
//    {
//        fprintf(stderr, "Ошибка: неправильный ввод!\n");
//        return 100;
//    }
//    if ((x<1 || x>80) || (y<1 || y>25))
//    {
//        fprintf(stderr, "Ошибка: цифры не на интервале!\n");
//        return 101;
//    }
////    if (x%2 == 0)
////    {
////        fprintf(stderr, "Ошибка: Ширина должна быть нечетной!\n");
////        return 102;
////    }
//    return 0;
//}
//-------------------------------------------------------------------------
// рисуем дом
//-------------------------------------------------------------------------
void print_house (int x, int y)
{
    int e = 5;
    int r = 5;
    //drew top
    for (int i = 0; i < x; i++) {printf("x");}
    printf("\n");
 
    // теперь на высоту y-2 рисуем стены, расстояние между стен a-2
    // drew left and right border
    for (int j = 0; j < y - 2; j++) {
        printf("x");
        for (int i = 0; i < x - 2; i++) {
            if (i == 1 && (j == r - 1 || j == r || j == r + 1)) {
                printf("U"); i++;;
            }
            if (i == x - 3 && (j == e - 1 || j == e || j == e + 1)) {
                printf("U");;
            }
//            if (i == y - 1)
//                printf("U");
            if (i == x / 2 - 1)
                printf("x");
            else
                printf(" ");
        }
//            if (i == x - 1 && (j == e - 1 || j == e || j == e + 1))
//                printf("U\n");
//            else
                printf("x\n");
    }
 
    // drew bottom
    for (int i = 0; i < x; i++) printf("X");
    printf("\n");
//    // drew set
    
    printf("\n");
    
}


//
