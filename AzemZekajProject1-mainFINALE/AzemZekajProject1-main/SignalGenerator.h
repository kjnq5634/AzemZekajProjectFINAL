#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H//define header function
#define PI 3.14159f
int Signal_Generator(void);
void print_SigGen_menu(void);
void select_SigGen_menu(void);
int get_SGinput(void);
void Sine_plot(void); // Sinusoidal wave
void Saw_plot(void); // Sawtoothwave 
void Square_plot(void); // Squarewave
void Triangle_plot(void); // Triangle wave
#endif