/* Author: Ozlem Kutluel
** Version: 2.0
** Date: 03/26/22
** Copyright 2022 Ozlem Kutluel
*/

/*
** This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
** as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
** of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with this program. 
** If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct Food *ptr;
int tracker = 0;
int numOfPeople;

struct Food{
    char name[10];
    int weight;
};

int promptOne(){
    int temp;
    printf("**********************************************************\n");
    printf("Welcome to What2Eat!\n");
    printf("I will be helping you decide what to order.\n\n");
    printf("First, enter how many people there are: ");
    scanf("%d", &temp);
    return temp;
} // intro

void capitalizeWord(char word[]){
    for(int j=0;j<strlen(word);j++){
        word[j] = toupper(word[j]);
    }
} // capitalize

void foodWeightOne(char food[], int f){
    int temp = 0;
    for(int i = 0; i <= tracker; ++i){
        if (strcmp(food, (ptr+i)->name) == 0){
            (ptr+i)->weight = (ptr+i)->weight + (6-f);
            temp = 1;
        }
    }
    if (temp == 0){
        strcpy((ptr+tracker)->name, food);
        (ptr+tracker)->weight = (6-f);
        tracker++;
    }
}

void scanInFood(int f, int i){
    char food[10];
    printf("%d: ", f);
    scanf("%s", food);
    capitalizeWord(food);
    foodWeightOne(food, f);
} // assignAndCapFood

void arraySort(){
    for (int i = 0; i <= tracker; ++i){

        for (int j = i + 1; j <= tracker; ++j){

            if ((ptr+i)->weight < (ptr+j)->weight){
                char temp[10];
                int a = (ptr+i)->weight;
                strcpy(temp, (ptr+i)->name);
                (ptr+i)->weight = (ptr+j)->weight;
                strcpy((ptr+i)->name, (ptr+j)->name);
                (ptr+j)->weight = a;
                strcpy((ptr+j)->name, temp);

            }
        }
    }
}

void cutAtThreshold(){
    int threshold = (numOfPeople*2);

    for (int i = 0; i <= tracker; i++){
        if ((ptr+i)->weight < threshold){
            tracker = i;
            break;
        }
    }
    if (tracker == 0){
        printf("None of you want the same thing! Just eat at home...\n");
        exit(0);
    }

}

void promptTwo(){
    arraySort();
    cutAtThreshold();
    printf("**********************************************************\n");
    printf("The following are your top choices,\nPlease rank these from best to worst!\n");
    for(int i = 0; i < tracker; ++i){
       printf("%s\t", (ptr+i)->name);
    }
    printf("\n");
}

void foodWeightTwo(char food[], int f){
    for(int i = 0; i <= tracker; ++i){
        if (strcmp(food, (ptr+i)->name) == 0){
            (ptr+i)->weight = (ptr+i)->weight + ((tracker+1)-f);
        }
    }
}

void zeroWeight(){
    for(int i = 0; i <= tracker; ++i){
        (ptr+i)->weight = 0;
    }
}

void scanInFoodTwo(int f){
    char food[10];
    printf("%d: ", f);
    scanf("%s", food);
    capitalizeWord(food);
    foodWeightTwo(food, f);
    arraySort();
}

int main(){

    numOfPeople = promptOne();

    ptr = (struct Food*) malloc((numOfPeople*5) * sizeof(struct Food));

    for (int i = 1; i <= numOfPeople; i++){
       printf("**********************************************************\n");
       printf("Player %d please enter your choices, 1 through 5\n", i);
       printf("One being the best, 5 being the worst.\n");

       for (int f = 1; f <= 5; f++){
           scanInFood(f, i);
        }
    }

    promptTwo();

    zeroWeight();


    for (int i = 1; i <= numOfPeople; i++){
        printf("Player %d please enter your choices, 1 through %d\n", i, tracker);
        printf("One being the best, %d being the worst.\n", tracker);

        for (int f = 1; f <= tracker; f++){
           scanInFoodTwo(f);
        }

    }

    printf("**********************************************************\n");
    printf("You have ranked the choices as follows;\n\n");

    for(int i = 0; i < tracker; ++i){
       printf("%d: %s\n", i+1, (ptr+i)->name);
    }

    printf("\nI think you should order %s!\nEnjoy your meal!\n", (ptr)->name);

    return 0;

}
