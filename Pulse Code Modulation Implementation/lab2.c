// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <math.h>
// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);

float amplitude; /*#### This is the amplitude of the signal. 
                 This is delcared as a separate global variable because there is no way to access amplitude inside the Quantizer() function.*/

int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here
    amplitude = inputsignal->A; //#### Assigning value to amplitude to access it inside quantizer() function.
    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal) 
{
    float interval;  // interval is the sampling interval
    int encoderbits ;  // encoderbits is the number of bits used for encoding

    // read input from stdin and assign to inputsignal, interval, and encoderbits.
	scanf("%f %f %f %d %f %d", &inputsignal->A, &inputsignal->omega, &inputsignal->sigma, &inputsignal->duration, &interval, &encoderbits);

    float * samples = (float *) malloc(sizeof(float) * (inputsignal->duration / interval)); // samples is the array of samples
    sampler(samples, interval, *inputsignal); // generate samples and store in samples array.

    int * pcmpulses = (int *) malloc(sizeof(int) * (inputsignal->duration / interval)); // pcmpulses is the array of quantized samples
    quantizer(samples, pcmpulses, (int)pow(2,encoderbits)); // quantize samples and store in pcmpulses array.
    free(samples); // free samples array

    int * dsignal = (int *) malloc(sizeof(int) * (inputsignal->duration / interval) * encoderbits); // dsignal is the array of encoded samples. elements are bits.
    encoder(pcmpulses, dsignal, encoderbits); // encode pcmpulses and store in dsignal array.
    free(pcmpulses); // free pcmpulses array
   
    for (int i = 0; i < (inputsignal->duration / interval)* encoderbits; i++) {
        // printf("%d", dsignal[i]); // print encoded samples
    }
    printf("\n");
    free(dsignal); // free dsignal array becuase the only instruction is to output the array of bits.
}


