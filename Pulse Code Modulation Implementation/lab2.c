// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <math.h>
// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);
    
    //call any other function here
    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal) 
{
    int interval;  // interval is the sampling interval
    int encoderbits ;  // encoderbits is the number of bits used for encoding
    int arraylength; //will change the value during execution since some arrays are different in length.
    
    // read input from stdin and assign to inputsignal, interval, and encoderbits.
	scanf("%f %f %f %d %d %d", &inputsignal->A, &inputsignal->omega, &inputsignal->sigma, &inputsignal->duration, &interval, &encoderbits);

    arraylength = (1+ inputsignal->duration / interval); // arraylength is the size of the array of samples without additional 2 elements which may specify some parameters in arrays except in the dsignal and pcmpulses. +1 is since there is a sampling point at the intial starting point.
    
    float * samples = (float *) malloc(sizeof(float) * (2 +arraylength)); // samples is the array of samples. It contains two addtional elements in the start. 
    sampler(samples, interval, *inputsignal); // generate samples and store in samples array.

    samples[0] = 2+arraylength; // first element is for passing the  samples array size including the two additional parameters.
    samples[1] = inputsignal->A; // second element is for passing the amplitude.

    int * pcmpulses = (int *) malloc(sizeof(int) * (arraylength+1)); // pcmpulses is the array of quantized samples. It has a one additional element at start to pass the size of it.
    quantizer(samples, pcmpulses, (int)pow(2,encoderbits)); // quantize samples and store in pcmpulses array.
    free(samples); // free samples array

    pcmpulses[0] = arraylength+1; // first element is for passing the  pcmpulses array size including the one additional parameter.

    int * dsignal = (int *) malloc(sizeof(int) * arraylength * encoderbits); // dsignal is the array of encoded samples. elements are bits.
    encoder(pcmpulses, dsignal, encoderbits); // encode pcmpulses and store in dsignal array.
    free(pcmpulses); // free pcmpulses array
   
    for (int i = 0; i < arraylength* encoderbits; i++) {
         printf("%d", dsignal[i]); // print encoded samples
    }
    printf("\n");
    free(dsignal); // free dsignal array becuase the only instruction is to output the array of bits.
}


