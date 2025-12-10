#ifndef FUNCS_H
#define FUNCS_H//define header functionm
#define PI 3.14159f // pi definition
void Calculator(void);//main calculator function
//void Signal_Generator(void); // main generator function
void print_main_menu(void);
void print_Calculator_menu(void);
void print_SigGen_menu(void);
void C1(void); // arithmetic calculator
void C2(void); // trigonometric calculator
void C3(void); // logarithmic calculator
typedef struct {
   int r;
   int c;
   float data[100][100];
   int det;
} Matrix;
void get_matrix(Matrix *m, char name[]);
void add_matrices(Matrix *m1, Matrix *m2, Matrix *result);
void get_matrix_function(void);
void subtract_matrices(Matrix *m1, Matrix *m2, Matrix *result);
void multiply_matrices(Matrix *m1, Matrix *m2, Matrix *result);
void divide_matrices(Matrix *m1, Matrix *m2, Matrix *result);
void determinant_2x2(Matrix *m1,Matrix *result);
void determinant_3x3(Matrix *m1,Matrix *result);
void transposition(Matrix *m1,Matrix *result);
void inversion2x2(Matrix *m1,Matrix *result);
void inversion3x3(Matrix *m1,Matrix *result);
#endif
