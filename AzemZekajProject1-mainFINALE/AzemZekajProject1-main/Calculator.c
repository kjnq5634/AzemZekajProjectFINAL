// ELEC2645 Unit 2 Project Template 
// Command Line Application Menu Handling Code 
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <string.h> 
#include "Calculator.h" 
// include all key repositories

double *ANS = NULL;
//declare and optimise ANS
/*----------------- Read Number or ANS -----------------*/
double read_number_or_ANS() {
    char buf[32];

    scanf("%31s", buf);
    //scans up to 31 characters

    if (strcmp(buf, "ANS") == 0 || strcmp(buf, "ans") == 0) {
        if (ANS == NULL) {
            printf("No stored ANS value yet, using 0.\n");
            return 0.0;
        }
        return *ANS;
    }
    //If user typed in ANS/ans , then the value will be equivalant to the last result given.
    return atof(buf);
    // ascii to float used to show number input if ANS/ans wasnt the value input
}

/*----------------- Print Calculator Menu -----------------*/
void print_Calculator_menu(void){
    printf("\t1.Arithemtic\t"); 
    printf("\t2.Non Linear\t"); 
    printf("\t3.Matrix\t"); 
} // calculator menu printed
/*----------------- Arithmetic Function -----------------*/
void C1(void) {
    char arop;
    double n1 = 0.0;
    double result = 0.0;

    printf("Enter first number (or ANS): ");
    result = read_number_or_ANS();
    
    if (ANS == NULL) {
        ANS = malloc(sizeof(double));
        // malloc used to get value of result after "="
        if (ANS == NULL) {
            printf("Memory allocation failed!\n");
            return;
        }
    } //error is there is no value stored in ANS

    while (1) {
        printf("Enter an arithmetic operator (+ - * / =): ");
        if (scanf(" %c", &arop) != 1) return;
        //input menu , printed and scanned
        if (arop == '=') {
            *ANS = result;
            printf("Final result: %.2f\n", result);
            printf("Stored in ANS = %.2f\n", *ANS);
            break;
        } // equals used to break function but also store final result in ANS

        printf("Enter number (or ANS): ");
        n1 = read_number_or_ANS();
        //switch scenarios used to do any function which you have done
        switch (arop) {
            case '+': result += n1; break;
            case '-': result -= n1; break;
            case '*': result *= n1; break;
            case '/':
                if (n1 == 0) {
                    printf("Error: division by zero!\n");
                    continue;
                }
                result /= n1;
                break;
            default:
                printf("%c is not valid\n", arop);
                return; //error output incase a random character i.e "a" is typed in. 
        }

        printf("Result: %.3f\n", result);
    }
}

/*----------------- Non Linear Function -----------------*/
void C2(void) {
    char op[16]; //operator string
    double n2;
    double result1;

    printf("Enter number (or ANS): ");
    n2 = read_number_or_ANS();
    // calls to function to read both numbers input and ans
    if (ANS == NULL) {
        ANS = malloc(sizeof(double));
        if (ANS == NULL) {
            printf("Memory allocation failed!\n");
            return;
        } // error code if ANS is used without it having a value stored (i.e using ans before having pressed "=")
    }

    printf("Enter a nonlinear operator (sin cos tan sec cosec cot ln exp): ");
    scanf("%15s", op);
    // this is the non lineaar selection function, I have used else if statements along with strcmp to create a
    //switch statement which reads strings rather than just characters.
    if (strcmp(op, "sin") == 0)       result1 = sin(n2);
    else if (strcmp(op, "cos") == 0)  result1 = cos(n2);
    else if (strcmp(op, "tan") == 0)  result1 = tan(n2);
    else if (strcmp(op, "sec") == 0)  result1 = 1.0 / cos(n2);
    else if (strcmp(op, "cosec") == 0)result1 = 1.0 / sin(n2);
    else if (strcmp(op, "cot") == 0)  result1 = 1.0 / tan(n2);
    else if (strcmp(op, "ln") == 0)  result1 = log(n2);
    else if (strcmp(op, "exp") == 0)  result1 = exp(n2);
    else {
        printf("%s is not a valid nonlinear operator.\n", op);
        return;
    }

    *ANS = result1; // store result (after "=" is pressed) in  ANS for future use

    printf("Result: %.5f\n", result1);
    printf("Stored in ANS = %.5f\n", *ANS);/* print to 5 dp for accuracy as non linear functions tend to have 
    lower values and so higher degrees of accuracy are required*/
}

/*----------------- Matrix Function -----------------*/
void C3(void){get_matrix_function();} 
// Main matrix function , calls to the get_matrix_function , which calls to all other matrix function
/*----------------- Matrix Operation Menu -----------------*/
void get_matrix_function(void){
    printf("Select matrix operation to perform:\n");
    printf("+. Addition\n");
    printf("-. Subtraction\n");
    printf("*. Multiplication\n");
    printf("/. Division\n");
    printf("2d. Determinant (2x2) \n");
    printf("3d. Determinant (3x3) \n");
    printf("t. Transposition\n");
    printf("2i. Inversion\n");
    printf("3i. Inversion\n");
    printf("Enter your choice: ");
    char choice[16];
    scanf("%15s", choice);
   // this it the output of the matrix menu
    if (strcmp(choice , "+")==0){
        Matrix matrix1, matrix2, sum;
        get_matrix(&matrix1, "first");
        get_matrix(&matrix2, "second");
        add_matrices(&matrix1, &matrix2, &sum);
    }
    else if(strcmp(choice , "-")==0){
        Matrix matrix1, matrix2, sum;
        get_matrix(&matrix1, "first");
        get_matrix(&matrix2, "second");
        subtract_matrices(&matrix1, &matrix2, &sum); 
        /*get_matrix allows the user to get a matrix and rather than making the function 
        work on a limited amount of matrices in its won code it is instead made to be used 
        as many times as it is called to and allows users to name the matrix applied*/
    }
    else if(strcmp(choice , "*")==0){
        Matrix matrix1, matrix2, sum;
        get_matrix(&matrix1, "first");
        get_matrix(&matrix2, "second");
        multiply_matrices(&matrix1, &matrix2, &sum);
    }
    else if(strcmp(choice , "2d")==0){
        Matrix matrix1;
        int *det = malloc(sizeof(int));
        get_matrix(&matrix1, "A");
        determinant_2x2(&matrix1,*det);
    }
    else if(strcmp(choice , "3d")==0){
        Matrix matrix1;
        int *det = malloc(sizeof(int));
        get_matrix(&matrix1, "A");
        determinant_3x3(&matrix1,*det);
        /*due to deteminants, transposition and inversion only working based on 1 matrix this allows for 
        just one matrix to be used rather than a set 2 matrices*/
    }
    else if(strcmp(choice , "t")==0){
        Matrix matrix1,result;
        get_matrix(&matrix1, "A");
        transposition(&matrix1,&result);
    }
    else if(strcmp(choice , "2i")==0){
        Matrix matrix1,result;
        get_matrix(&matrix1, "A");
        inversion2x2(&matrix1,&result);
    }
    else if(strcmp(choice , "3i")==0){
        Matrix matrix1,result;
        get_matrix(&matrix1, "A");
        inversion3x3(&matrix1,&result);
    } 
    else if(strcmp(choice, "/")==0) {
        Matrix matrix1,matrix2,result;
        get_matrix(&matrix1,"first");
        get_matrix(&matrix2,"second");
        divide_matrices(&matrix1,&matrix2,&result);
    }  
/*displays menu , allows different scenarios based on the string input and 
allows for the function to work on the 1 or 2 matrices gathered*/
}

/*----------------- Get Matrix Elements -----------------*/
void get_matrix(Matrix *m, char name[]){
    printf("Enter number of row for %s: ", name);
    scanf("%d", &m->r);
    printf("Enter number of column for %s: ", name);        
    scanf("%d", &m->c);
    printf("Enter elements of the rows for %s:\n", name);
    for (int i = 0; i < m->r; i++){
        for (int j = 0; j < m->c; j++){
            printf("Element [%d][%d]: ", i + 1, j + 1);
            scanf("%f", &m->data[i][j]);
        }
    } //for loop used throughout all the matrix functions to retreive the matrix dimensions and elements
    printf("\nMatrix %s:\n", name);
    for (int i = 0; i < m->r; i++){
        for (int j = 0; j < m->c; j++){
            printf("%f ", m->data[i][j]); 
        }
        printf("\n"); //outputs original matrix
    }
}

/*----------------- Matrix Addition -----------------*/
void add_matrices(Matrix *m1, Matrix *m2, Matrix *result){
    if (m1->r != m2->r || m1->c != m2->c){
        printf("Error: Matrices must have the same dimensions for addition.\n");
        return;
    } //error message returns user back ot the start
    result->r = m1->r;
    result->c = m1->c; //sets the result 
    for (int i = 0; i < m1->r; i++){
        for (int j = 0; j < m1->c; j++){
            result->data[i][j] = m1->data[i][j] + m2->data[i][j];
        } //element wise addition using for loop.
    }
    printf("Resultant Matrix after Addition:\n");
    for (int i = 0; i < result->r; i++){
        for (int j = 0; j < result->c; j++){
            printf("%.2f ", result->data[i][j]);
        }
        printf("\n");//prints off the result of the 2 matrices which have been operated on this 
        //is used in each of the matrices below
    }
}

/*----------------- Matrix Subtraction -----------------*/
void subtract_matrices(Matrix *m1, Matrix *m2, Matrix *result){
    if (m1->r != m2->r || m1->c != m2->c){
        printf("Error: Matrices must have the same dimensions for subtraction.\n");
        return;
    }
    result->r = m1->r;
    result->c = m1->c; //points dimensions of m1 and result to r and c
    for (int i = 0; i < m1->r; i++){
        for (int j = 0; j < m1->c; j++){
            result->data[i][j] = m1->data[i][j] - m2->data[i][j];
        } //element wise subtraction
    }
    printf("Resultant Matrix after subtraction:\n");
    for (int i = 0; i < result->r; i++){
        for (int j = 0; j < result->c; j++){
            printf("%.2f ", result->data[i][j]);
        }
        printf("\n"); //element wise printing
    }
}
/*----------------- Matrix Multiplication -----------------*/
void multiply_matrices(Matrix *m1, Matrix *m2, Matrix *result){
    if (m1->c != m2->r){
        printf("Error: Rows of Matrix1 must equal the columns of Matrix2.\n");
        return;
    } // cannot multiply matrices when the colums of A arent equal to the rows of B
    result->r = m1->r;
    result->c = m2->c; 
    // corrected to proper matrix multiplication size

    for (int i = 0; i < m1->r; i++){
        for (int j = 0; j < m2->c; j++){
            result->data[i][j] = 0;
            for (int k = 0; k < m1->c; k++){
                result->data[i][j] += m1->data[i][k] * m2->data[k][j];
            } //elemntwise  multiplication , points dimensions to input c and r, and results display on result matrix
        }
    }

    printf("Resultant Matrix after Multiplication:\n");
    for (int i = 0; i < result->r; i++){
        for (int j = 0; j < result->c; j++){
            printf("%.2f ", result->data[i][j]);
        }
        printf("\n");
    }
}

/*----------------- Determinant 2x2 -----------------*/
void determinant_2x2(Matrix *m1, Matrix *result){
    if (m1->r != 2 || m1->c != 2){
        printf("Error: Determinant function only supports 2x2 matrices.\n");
        return;
    } // holds matrix to 2x2 dimensions
    result->det = (int)(m1->data[0][0] * m1->data[1][1] - m1->data[0][1] * m1->data[1][0]);
    //determinant function for a 2x2 (ab-dc)
    printf("Determinant of the matrix is: %d\n", result->det);
    //determinant printing function
}

/*----------------- Determinant 3x3 -----------------*/
void determinant_3x3(Matrix *m1, Matrix *result){
    if (m1->r != 3 || m1->c != 3){
        printf("Error: Determinant function only supports 3x3 matrices.\n");
        return;
    } // holds the function to only 3 by 3 dimensions

    result->det =
          m1->data[0][0] * (m1->data[1][1] * m1->data[2][2] - m1->data[1][2] * m1->data[2][1])
        - m1->data[0][1] * (m1->data[1][0] * m1->data[2][2] - m1->data[1][2] * m1->data[2][0])
        + m1->data[0][2] * (m1->data[1][0] * m1->data[2][1] - m1->data[1][1] * m1->data[2][0]);
    
    printf("Determinant of the matrix is: %d\n", result->det);
     /*does the minor multiplication 
    (could potentially be made more efficient by implementing the 2x2 det
     function but it was too far out of my current scope)*/  
}

/*----------------- Matrix Transposition -----------------*/
void transposition(Matrix *m1, Matrix *result){
    result->r = m1->c;
    result->c = m1->r;
    //sets the rows of results to the input matrix colums and vive versa for the colums of the result

    for (int i = 0; i < m1->r; i++){
        for (int j = 0; j < m1->c; j++){
            result->data[j][i] = m1->data[i][j];
        }
    }

    printf("Resultant Matrix after Transposition:\n");
    for (int i = 0; i < result->r; i++){
        for (int j = 0; j < result->c; j++){
            printf("%.2f ", result->data[i][j]);
        }
        printf("\n");//element wise printing of matrix
    }
}

/*----------------- 2x2 Matrix Inversion -----------------*/
void inversion2x2(Matrix *m1, Matrix *result){
    Matrix det_holder;
    determinant_2x2(m1, &det_holder); //calls to 2by2 matrix function and holds it in det_holder
 
    if (det_holder.det == 0){
        printf("Error: Matrix is not invertible.\n");
        return;
    } // det = 0 meaning non invertible

    float det = det_holder.det; 
    // holds the determinant for use later in the code
    /*Points reult to given matrix element*/
    result->data[0][0] =  m1->data[1][1] / det;
    result->data[0][1] = -m1->data[0][1] / det;
    result->data[1][0] = -m1->data[1][0] / det;
    result->data[1][1] =  m1->data[0][0] / det;
   
    result->r = 2;
    result->c = 2; //result is set and held to a 2x2 dimension

    printf("Resultant Matrix after Inversion:\n");
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            printf("%.2f ", result->data[i][j]);
        } /*this is a for loop to allow the matrix to be printed element by element 
        i.e when i = 0 and j = 0 it will print elements at [0,0]*/
        printf("\n");
    }
}

/*----------------- 3x3 Matrix Inversion -----------------*/
void inversion3x3(Matrix *m1, Matrix *result){
    Matrix det_holder;
    determinant_3x3(m1, &det_holder);//calls to 3 by 3 matrix determinant and holds it onto det_holder

    if (det_holder.det == 0){
        printf("Error: Matrix is not invertible.\n");
        return;
    } // det = 0 , meaning non invertible

    float det = det_holder.det;
    //holds the determinant value (pointer)
    float cof[3][3];
    cof[0][0] =  (m1->data[1][1]*m1->data[2][2] - m1->data[1][2]*m1->data[2][1]);
    cof[0][1] = -(m1->data[1][0]*m1->data[2][2] - m1->data[1][2]*m1->data[2][0]);
    cof[0][2] =  (m1->data[1][0]*m1->data[2][1] - m1->data[1][1]*m1->data[2][0]);
    cof[1][0] = -(m1->data[0][1]*m1->data[2][2] - m1->data[0][2]*m1->data[2][1]);
    cof[1][1] =  (m1->data[0][0]*m1->data[2][2] - m1->data[0][2]*m1->data[2][0]);
    cof[1][2] = -(m1->data[0][0]*m1->data[2][1] - m1->data[0][1]*m1->data[2][0]);
    cof[2][0] =  (m1->data[0][1]*m1->data[1][2] - m1->data[0][2]*m1->data[1][1]);
    cof[2][1] = -(m1->data[0][0]*m1->data[1][2] - m1->data[0][2]*m1->data[1][0]);
    cof[2][2] =  (m1->data[0][0]*m1->data[1][1] - m1->data[0][1]*m1->data[1][0]);
    //cofactor matrix (could potentially have created a more efficient version)

    result->r = 3;
    result->c = 3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            result->data[i][j] = cof[j][i] / det;
            //scalarn matrix division
        }
    }

    printf("Resultant Matrix after 3x3 Inversion:\n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%.2f ", result->data[i][j]);
        }
        printf("\n");
    }//print off final inversion of matrix
}

/*----------------- Matrix Division -----------------*/
void divide_matrices(Matrix *m1,Matrix *m2,Matrix *result){
    if (m1->r != m2->r || m1->c != m2->c){
        printf("Error: Matrices must have the same dimensions for division.\n");
        return;
    } // allows only for same dimension matrices to divide as it is simply a multiplication of A*A^-1

    result->r = m1->r;
    result->c = m1->c; 
    //sets dimension to be equal to m1
    if (m1->r == 2 && m1->c == 2) // if statement allows for only 2x2 matrices to be used
    {
        Matrix inverse_matrix2;
        inversion2x2(m2,&inverse_matrix2); // call to inversion of 2 by 2 funtion

        multiply_matrices(m1,&inverse_matrix2,result); // call to multiplication function
    
        printf("Resultant Matrix after division:\n");
        for(int i = 0; i < 2; i++){
            for(int j = 0; j < 2; j++){
                printf("%.2f ", result->data[i][j]);
            } 
            printf("\n");
        } }
        if (m1->r == 3 && m1->c == 3) /*if statement used to decide wether the division will be 
        of 2 3x3 matrices or whether it will be used for 2 2x2 matrices */
        {
        Matrix inverse_matrix3;
        inversion3x3(m2,&inverse_matrix3); //inverts a 3x3 and saves it so it can be used as B^-1

        multiply_matrices(m1,&inverse_matrix3,result); //multiplication function called to again
    
        printf("Resultant Matrix after division:\n");
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                printf("%.2f ", result->data[i][j]);
            }
            printf("\n"); //prints element wise
    }
}}

/*----------------- Calculator Main Loop -----------------*/
void Calculator(void) { 
    int function;
    while (1) {
        print_Calculator_menu();
        printf("Select Function: ");
        if (scanf("%d", &function) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n'); // clear input buffer
            return;
        }
        //switch function to allow for the main C functions to be selected and used
        switch (function) {
            case 1:
                C1();  // call arithmetic function
                printf("Arithmetic function selected.\n");
                break;
            case 2:
                C2(); // call non linear function
                printf("Non linear function selected.\n");
                break;
            case 3:
                C3(); // call Matrix function
                printf("Matrix function selected.\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
