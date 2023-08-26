// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here
#include <math.h>
// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
float analog_signal_generator(asignal signal, int t)
{																//printf("%f\n",signal.A * sin((signal.omega * t) + signal.sigma));  //uncomment for testing
	return signal.A * sin((signal.omega * t) + signal.sigma);
}
void sampler(float *samples, int interval, asignal signal)
{
	 for (int t = 0; t <= signal.duration; t=t+interval)
	 	{															// printf("%d   ",t); //Uncomment for testing
        samples[t/interval] =  analog_signal_generator(signal, t); // generate samples and store in samples array
		}
}

extern float amplitude;  //#### This is the amplitude of the signal. its linked and same as the amplitude in lab2.c

void quantizer(float *samples, int *pcmpulses, int levels)
{
	for(int i = 0; i < sizeof(samples)/sizeof(float); i++)
	{
		if (samples[i] == amplitude){
			pcmpulses[i] = levels - 1;
		}
		else{
			pcmpulses[i] = floor(levels*(samples[i] + amplitude) / (2.0*amplitude));
		}
	}
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
	for (int i = 0; i < sizeof(dsignal)/sizeof(int); i++) {
        int num = pcmpulses[i];
        int index = encoderbits - 1; // Start from the rightmost digit
        
        // Convert decimal to binary
        while (num > 0 && index >= 0) {
            dsignal[i * encoderbits + index] = num % 2;
            num /= 2;
            index--;
        }
        
        // Fill remaining digits with 0
        while (index >= 0) {
            dsignal[i * encoderbits + index] = 0;
            index--;
        }
    }
}