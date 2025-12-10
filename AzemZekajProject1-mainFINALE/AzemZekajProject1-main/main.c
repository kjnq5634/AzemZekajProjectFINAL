// ELEC2645 Unit 2 Project Template
// Command Line Application Menu Handling Code

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "pbPlots.h"//https://github.com/InductiveComputerScience/pbPlots/blob/master/C/pbPlots.h (reference used for plotting signals)
#include "supportLib.h"//https://github.com/InductiveComputerScience/pbPlots/blob/master/C/supportLib.h
#include "Calculator.h"
#include "SignalGenerator.h"

/*Function declarations*/
void main_menu(void);
void go_back_to_main(void);
int  get_user_input(void);
void select_menu_item(int input);
int main(void){
        while(1) {
        main_menu(); //main menu calls to every function that is required and allows for selection of them
    }
    return 0;
}
/*Menu Creation and selection functions*/
void main_menu(void) {
    print_main_menu();
    int input = get_user_input();
    select_menu_item(input);
}
int get_user_input(void) {
    int input;
    printf("\nSelect item: ");
    scanf("%d", &input); 
     // tells user to give input and then uses input for the switch scenarios
    return input;
}
/* main menu printed  */
void print_main_menu(void) {
    printf("\n-------------------- Main menu ------------------\n");
    printf("|\t1. Scientific Calculator\t\t|\n");
    printf("|\t2. Signal Generator\t\t\t|\n");
    printf("|\t3. Exit\t\t\t\t\t|\n");
    printf("-------------------------------------------------\n");
}// main  menu printed
/*Main menu selections*/
void select_menu_item(int input) {
    switch (input) {
        case 1:
        Calculator();
        go_back_to_main(); 
        break;
        case 2: 
        Signal_Generator();
        go_back_to_main(); 
        break;
        case 3: printf("Exiting program...\n"); 
        exit(0); //exit function
        default: printf("Invalid selection. Exiting...\n"); exit(1);
    } //switch cases used to gather functions
}
void go_back_to_main(void) {
    char input;
    // this do loop ensures user inputs 'b' or 'B' to go back
    // if user inputs other characters, it keeps prompting
    do {
        printf("\nEnter 'b' or 'B' to go back to main menu: ");
        scanf(" %c", &input);
    } while (input != 'b' && input != 'B');
}