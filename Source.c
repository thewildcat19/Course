#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<iso646.h>
#include<ctype.h>
#include<string.h>
#include<math.h>

typedef struct {
    int number;
    char name[50];
    int stage1;
    int stage2;
    int stage3;
    int stage4;
    int stage5;
    int penalty;
    int total;
    int place;
} cyclist;

void arr_filling(cyclist*);
void arr_print_data(cyclist*, int);
void arr_print_results(cyclist*, int);
void arr_sorted(cyclist*, int);
void arr_calc(cyclist*, int);
void arr_change(cyclist*, int);
void arr_sort_deprecated(cyclist*, int);
void arr_search(cyclist*, int, int, int);

    
 int main() {
 
    setlocale(LC_ALL, "Russian");
    static int size = 3;
    cyclist* a= (cyclist*)malloc(size * sizeof(cyclist)); 
    arr_filling(a);
    int choice;
    do {
        printf("Программа оценки соревнований по велоспорту\n"
            "Для вывода всей таблицы нажмите - 1\n"
            "Для вывода отсортированного по среднему значению списка нажмите - 2\n"
            "Для вывода результатов и мест нажмите - 3\n"
            "Для заполнения таблицы случайными значениями нажмите - 4\n"
            "Для поиска спортсмена по штрафным очкам в диапазоне нажмите - 5\n"
            "Для изменения значений этапа игрока нажмите - 6\n"
            "Для записи базы данных в файл нажмите - 7\n"
            "Для считывания из файла базы нажмите - 8\n"
            "Для выхода из программы нажмите - 0\n"
        );
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            system("cls");
            arr_print_data(a, size);
            break;
        case 2:
            system("cls");
            arr_sorted(a, size);
            break;
        case 3:
            system("cls");
            arr_calc(a, size);
            arr_print_results(a, size);
            break;
        case 4:
            system("cls");
            printf("Данный функционал еще не реализован");
            break;
        case 5:
            system("cls");
            printf("Введите значения нижнего и верхнего пределов диапазона:");
            int ub=0,lb=0;
            scanf("%d", &lb);
            scanf("%d", &ub);
            arr_search(a,size,lb,ub);
            break;
        case 6:
            system("cls");
            arr_change(a, size);
            break;
        case 7:
            //запись в файл
            system("cls");
            FILE* S1 = fopen("Table.txt", "w");
            // fprintf(S1,"Таблица данных\n");
            // fprintf(S1,"|%2s|%-17s|%5s|%5s|%5s|%5s|%5s|%5s|\n", "Номер", "Имя Фамилия", "Этап1", "Этап2", "Этап3", "Этап4", "Этап5", "Штрафные очки");
            for (int i = 0; i < size; i++) {
                fprintf(S1, "|%5d|%20s|%5d|%5d|%5d|%5d|%5d|%13d|\n", a[i].number, a[i].name, a[i].stage1, a[i].stage2, a[i].stage3, a[i].stage4, a[i].stage5, a[i].penalty);
            };
            fclose(S1);
            printf("Сохранено успешно!\n");
            break;
        case 8:
            //чтение из файла
            system("cls");
            FILE* S2 = fopen("Table.txt", "rt");
            int i = 0;
            int k = 0;
            while (!feof(S2)) {
                cyclist tmp;
                char c[21];
                fscanf(S2, "|%5d|", &tmp.number);
                fgets(c, 21, S2);
                strcpy(&tmp.name, c);
                fscanf(S2, "|%5d|%5d|%5d|%5d|%5d|%13d|\n", &tmp.stage1, &tmp.stage2, &tmp.stage3, &tmp.stage4, &tmp.stage5, &tmp.penalty);
                k++;

            }
            size = k;
            cyclist* a_temp=NULL ;
            a_temp = (cyclist*)malloc(size * sizeof(cyclist));
            a = a_temp;
            fclose(S2);
            S2 = fopen("Table.txt", "rt");
            while (!feof(S2))
            {
               
                fscanf(S2,"|%5d|", &a[i].number);
                char c[21];
                // for(int j=0;j<17;j++){fgetc(S2);}
                // printf("\n%s\n",c);
                fgets(c, 21, S2);
                strcpy(&a[i].name, c);
                //printf("\n%s\n",c);
                //fscanf(S2,"|%5d|%17s|%5d|%5d|%5d|%5d|%5d|%13d|", &a[i].number,&c, &a[i].stage1, &a[i].stage2, &a[i].stage3, &a[i].stage4, &a[i].stage5, &a[i].penalty);
                //fscanf(S2,"|%c[17]", a[i].name);
                fscanf(S2, "|%5d|%5d|%5d|%5d|%5d|%13d|\n", &a[i].stage1, &a[i].stage2, &a[i].stage3, &a[i].stage4, &a[i].stage5, &a[i].penalty);
                i++;
              
            }
            printf("Успешно импортировано %d записей!\n",i);
            fclose(S2);
            break;
        case 0:
            exit(0);
        default:
            system("cls");
            printf("---Неверная операция, повторите еще раз!---\n");
            break;

        }

    } while (choice != 0);
    
    return 0;
}


void arr_filling(cyclist* a) {
    a[0].number = 1;
    strcpy(a[0].name, "Geoffrey BOUCHARD");
    //a[0].name="Geoffrey BOUCHARD";
    a[0].stage1 = 3;
    a[0].stage2 = 0;
    a[0].stage3 = 2;
    a[0].stage4 = 3;
    a[0].stage5 = 0;
    a[0].penalty = 0;
    a[0].total = 5;
    a[0].place = 1;

    a[1].number = 2;
    strcpy(a[1].name, "Phil BAUHAUS");
    //a[1].name="Phil BAUHAUS";
    a[1].stage1 = 5;
    a[1].stage2 = 5;
    a[1].stage3 = 5;
    a[1].stage4 = 5;
    a[1].stage5 = 0;
    a[1].penalty = 1;
    a[1].total = 4;
    a[1].place = 4;

    a[2].number = 3;
    strcpy(a[2].name, "Leonardo BASSO");
    //a[2].name="Leonardo BASSO";
    a[2].stage1 = 3;
    a[2].stage2 = 0;
    a[2].stage3 = 2;
    a[2].stage4 = 3;
    a[2].stage5 = 1;
    a[2].penalty = 2;
    a[2].total = 2;
    a[2].place = 6;


};

void arr_print_data(cyclist* a, int size) {
    printf("\nТаблица данных\n");
    printf("|%2s|%20s|%5s|%5s|%5s|%5s|%5s|%5s|\n", "Номер", "Имя Фамилия", "Этап1", "Этап2", "Этап3", "Этап4", "Этап5", "Штрафные очки");
    for (int i = 0; i < size; i++) {
        printf("|%5d|%20s|%5d|%5d|%5d|%5d|%5d|%13d|\n", a[i].number, a[i].name, a[i].stage1, a[i].stage2, a[i].stage3, a[i].stage4, a[i].stage5, a[i].penalty);
    };
}
void arr_print_results(cyclist* a, int size) {
    printf("\nТаблица результатов\n");
    printf("|%20s|%5s|%5s|\n", "Имя Фамилия", "Общие очки", "Место");
    for (int i = 0; i < size; i++) {
        printf("|%20s|%10d|%5d|\n", a[i].name, a[i].total, a[i].place);
    };
}

void arr_sorted(cyclist* a, int size) {
    cyclist t;
    cyclist* b = (cyclist*)malloc(size * sizeof(cyclist));
    for (int i = 0; i < size; i++)
    {
        b[i] = a[i];

    }
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (((b[i].stage1 + b[i].stage2 + b[i].stage3 + b[i].stage4 + b[i].stage5) / 5.) < ((b[j].stage1 + b[j].stage2 + b[j].stage3 + b[j].stage4 + b[j].stage5) / 5.)) {

                t = b[i];
                b[i] = b[j];
                b[j] = t;
            }
        }
    }
    printf("\nТаблица данных\n");
    printf("|%2s|%20s|%5s|%5s|%5s|%5s|%5s|%7s|%5s|\n", "Номер", "Имя Фамилия", "Этап1", "Этап2", "Этап3", "Этап4", "Этап5", "Среднее", "Штрафные очки");
    for (int i = 0; i < size; i++) {
        printf("|%5d|%20s|%5d|%5d|%5d|%5d|%5d|%7.1f|%13d|\n", b[i].number, b[i].name, b[i].stage1, b[i].stage2, b[i].stage3, b[i].stage4, b[i].stage5, ((b[i].stage1 + b[i].stage2 + b[i].stage3 + b[i].stage4 + b[i].stage5) / 5.), b[i].penalty);
    };
}

void arr_sort_deprecated(cyclist* a, int n)
{
    int i, j;
    cyclist t;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i].total < a[j].total) {


                t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }

}
/*
void arr_competition(cyclist* a, int size) {
    int k = 1;
    for (int i = 0; i < size; i++) {
        if (compare(a[i].total, a[i + 1].total) == 0) { a[i].place = k; a[i + 1].place = k; }
        else if (compare(a[i].total, a[i + 1].total) == 1) { a[i].place = k; k++; a[i + 1].place = k; }
    }
}

int compare(int a, int b) {
    if (a == b)return 0;
    else if (a > b) return 1;
}
*/

void arr_calc(cyclist* a, int size) {
    for (int i = 0; i < size; i++) {
        a[i].total = (a[i].stage1 + a[i].stage2 + a[i].stage3 + a[i].stage4 + a[i].stage5) - a[i].penalty;
    };
    arr_sort_deprecated(a, size);
}

void arr_search(cyclist* a, int size, int lowerbound, int upperbound) {
    printf("\nТаблица данных\n");
    printf("|%2s|%20s|%5s|\n", "Номер", "Имя Фамилия", "Штрафные очки");

    for (int i = 0; i < size; i++)
    {
        if (a[i].penalty >= lowerbound and a[i].penalty <= upperbound) {
            printf("|%5d|%20s|%13d|\n", a[i].number, a[i].name, a[i].penalty);
        }
    }
}

void arr_change(cyclist* a, int size) {
    printf("Напишите номер игрока , этапа(для штрафных очков введите - 6) и новое значение:");
    int pl_numb, pl_st, pl_val;
    scanf("%d %d %d", &pl_numb, &pl_st, &pl_val);
    for (int i = 0; i < size; i++) {
        if (a[i].number == pl_numb) {
            switch (pl_st) {
            case 1:
                a[i].stage1 = pl_val;
                break;
            case 2:
                a[i].stage2 = pl_val;
                break;
            case 3:
                a[i].stage3 = pl_val;
                break;
            case 4:
                a[i].stage4 = pl_val;
                break;
            case 5:
                a[i].stage5 = pl_val;
                break;
            case 6:
                a[i].penalty = pl_val;
                break;
            }
        }
    }
}