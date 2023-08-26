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
{															//	printf("%f\n",signal.A * sin((signal.omega * t) + signal.sigma));  //uncomment for testing
	return signal.A * sin((signal.omega * t) + signal.sigma);
}
void sampler(float *samples, int interval, asignal signal)
{
	 for (int t = 0; t <= signal.duration; t=t+interval)
	 	{															// printf("%d   ",t); //Uncomment for testing
        samples[t/interval+2] =  analog_signal_generator(signal, t); // generate samples and store in samples array. start from 2 because the first two elements are for passing the true array size and amplitude.
		                                                             //  printf("%f\n",samples[t/interval+2] ); // Uncomment for testing
        }
}


void quantizer(float *samples, int *pcmpulses, int levels)
{   
    float amplitude = samples[1]; // second element is for passing the amplitude.
    /*start from 2 because the first two elements are for passing the true array size and amplitude.
     sample[0] is the true array size and sample[1] is the amplitude.*/ 
	for(int i = 2; i < samples[0]; i++) 
	{   
		if (samples[i] == amplitude){
			pcmpulses[i-1] = levels - 1; //note that pcmpulses arrays first element is a special element for passing the size of the array. it contain pulses starting from second element.
		}
		else{
			pcmpulses[i-1] = (int)floor(levels*(samples[i] + amplitude) / (2.0*amplitude));
		}
        // printf("%f  - ",samples[i] ); // Uncomment for testing
        // printf("%d\n",pcmpulses[i-1] ); // Uncomment for testing
	}
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits) {
    for (int i = 1; i < pcmpulses[0]; i++) {
        int num = pcmpulses[i];  // Get the decimal pulse value
        int index = (i - 1) * encoderbits + encoderbits - 1; // Calculate the starting index for binary storage
        
        // Convert decimal to binary
        while (num > 0 && index >= (i - 1) * encoderbits) {
            dsignal[index] = num % 2;  // Store the binary digit
            num /= 2;  // Divide the decimal number by 2 to get the next binary digit
            index--;   // Move to the next position to the left
        }
        
        // Fill remaining digits with 0 if any
        while (index >= (i - 1) * encoderbits) {
            dsignal[index] = 0;  // Fill with 0
            index--;
        }
    }
}
