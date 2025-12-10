// ELEC2645 Unit 2 Project Template
// Command Line Application – Signal Generation tools
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pbPlots.h"//https://github.com/InductiveComputerScience/pbPlots/blob/master/C/pbPlots.h
#include "supportLib.h"//https://github.com/InductiveComputerScience/pbPlots/blob/master/C/supportLib.h
#include "SignalGenerator.h"

#define Number_of_points 100
/*Main function*/
int Signal_Generator(void) {
    print_SigGen_menu();
    select_SigGen_menu();
    return 0;
}

/*---------MENU PRINT--------*/
void print_SigGen_menu(void){
    printf("\n----- Signal Generator -----\n");
    printf("1. Sinusoidal Wave\n");
    printf("2. Sawtooth Wave\n");
    printf("3. Square Wave\n");
    printf("4. Triangle Wave\n");
}

/*---------MENU SELECT----------*/
void select_SigGen_menu(void){
    int select;
    printf("Select function: ");
    scanf("%d", &select);
  // Switch statement for function selection 
    switch(select){
        case 1:  Sine_plot();     break;
        case 2:  Saw_plot();      break;
        case 3:  Square_plot();   break;
        case 4:  Triangle_plot(); break;
        default:
            printf("Error: Incorrect input detected\n");
            return;
    }
}

/*-------PLOT FUNCTION (FOR ALL WAVE INPUTS)---------*/
void MakePlot(double *Fs, double *Amp, char *filename){
    _Bool success;
    StartArenaAllocator();

    RGBABitmapImageReference *canvas = CreateRGBABitmapImageReference();
    StringReference *errorMessage = CreateStringReference(L"", 0);

    success = DrawScatterPlot(canvas, 600, 400, Fs, Number_of_points, Amp, Number_of_points, errorMessage);

    if (success) {
        ByteArray *pngData = ConvertToPNG(canvas->image);
        WriteToFile(pngData, filename);
        DeleteImage(canvas->image);
        printf("%s saved.\n", filename);
    } else {
        printf("Plot error!\n");
    }// Calls to functions in pbPlots used to print a function

    FreeAllocations();
    //Allows for a new wave to be formed
}

/* ---------------- SINE WAVE ---------------- */
void Sine_plot(void){
    double Fs[Number_of_points], Amp[Number_of_points];
    double frequency, sampling_rate, amplitude;
    /*Parameter selection: same across all functions*/
    printf("Frequency: ");      
    scanf("%lf", &frequency);
    printf("Amplitude: ");     
    scanf("%lf", &amplitude);
    printf("Sampling Rate: ");  
    scanf("%lf", &sampling_rate);
    /*Sine wave equation*/
    for(int i = 0; i < Number_of_points; i++){
        Fs[i] = (double)i / sampling_rate;
        Amp[i] = amplitude * sin(2.0 * M_PI * frequency * Fs[i]);
        //M_PI used as it is a more accurate definition of PI than my own (math.h)
    }

    MakePlot(Fs, Amp, "sine_plot.png");
}

/* ---------------- SAWTOOTH WAVE ---------------- */
void Saw_plot(void){
    double Fs[Number_of_points], Amp[Number_of_points];
    double frequency, sampling_rate, amplitude;

    printf("Frequency: ");      
    scanf("%lf", &frequency);
    printf("Amplitude: ");      
    scanf("%lf", &amplitude);
    printf("Sampling Rate: ");  
    scanf("%lf", &sampling_rate);
    /*Sawtooth equation*/
    double period = 1.0 / frequency;

    for(int i = 0; i < Number_of_points; i++){
        Fs[i] = (double)i / sampling_rate;
        double phase = fmod(Fs[i], period);
        Amp[i] = (2.0 * amplitude / period) * phase - amplitude; 
        /*equations used instead of intergration to help 
        simplify the code rather than having to use methods 
        such as the newton raphson method (this was found online)*/
    }

    MakePlot(Fs, Amp, "sawtooth_plot.png");
}

/* ---------------- SQUARE WAVE ---------------- */
void Square_plot(void){
    double Fs[Number_of_points], Amp[Number_of_points];
    double frequency, sampling_rate, amplitude;

    printf("Frequency: ");      
    scanf("%lf", &frequency);
    printf("Amplitude: ");      
    scanf("%lf", &amplitude);
    printf("Sampling Rate: ");  
    scanf("%lf", &sampling_rate);
    /*Square wave equation*/
    double period = 1.0 / frequency;//setting period

    for(int i = 0; i < Number_of_points; i++){
        Fs[i] = (double)i / sampling_rate;
        double phase = fmod(Fs[i], period);

        Amp[i] = (phase < period/2.0)? amplitude: -amplitude; /*bases on whether the phase is at half of the period
        creating an else if statement outputting a positive or negative amplitude*/
    }

    MakePlot(Fs, Amp, "square_plot.png");
}

/* ---------------- TRIANGLE WAVE ---------------- */
void Triangle_plot(void){
    double Fs[Number_of_points], Amp[Number_of_points];
    double frequency, sampling_rate, amplitude;

    printf("Frequency: ");      scanf("%lf", &frequency);
    printf("Amplitude: ");      scanf("%lf", &amplitude);
    printf("Sampling Rate: ");  scanf("%lf", &sampling_rate);
//function selection as seen previously gives you the input command and uses the input to form the wave
    double period = 1.0 / frequency;
    /*Triangle wave equation*/
    for(int i = 0; i < Number_of_points; i++){
        Fs[i] = (double)i / sampling_rate;
        double phase = fmod(Fs[i], period) / period;//fmod from math.h (module of function)
        double tri = 2.0 * fabs(2.0 * phase - 1.0) - 1.0;
        Amp[i] = amplitude * tri;//Scale the triangle function to amplitude
    }

    MakePlot(Fs, Amp, "triangle_plot.png");//Use the make plot function to write wave onto a file
}
