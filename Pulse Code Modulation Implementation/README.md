## Lab 2 - Analog Signal Processing and PCM Encoding

In this lab, you will work on creating an analog signal generator, sampler, quantizer, and an encoder for Pulse Code Modulation (PCM) encoding.

### Lab 2.1 - Analog Signal Generator

The `analog_signal_generator` function generates a sinusoidal analog signal using the following formula:
```x(t) = A * sin(omega * t + sigma)```

Where:
- `A` is the peak amplitude.
- `omega` is the angular frequency in radians.
- `sigma` is the phase in radians.
- `t` is time.

### Lab 2.2 - Sampler

The `sampler` function takes analog signal samples and updates an array with sampled values at specified intervals. This step is crucial for converting continuous signals into discrete samples.

### Lab 2.3 - Quantizer

The `quantizer` function takes the sampled analog signal values and quantizes them to produce Pulse Code Modulation (PCM) pulses. The quantization levels are determined by the given number of quantization bits.

### Lab 2.4 - Encoder

The `encoder` function encodes the quantized PCM pulses into binary codes, which represent the quantized values in a binary number stream.

### The `run()` Function

The `run()` function is designed to:
1. Read input parameters from stdin, including `A`, `omega`, `sigma`, `duration`, `interval`, and `encoderbits`.
2. Utilize the provided functions to generate an analog signal, sample it, quantize it, and encode it using PCM.
3. Print the final output as a binary bit stream (0s and 1s) to stdout.

This lab assignment focuses on processing analog signals and converting them into PCM-encoded digital streams. Ensure you understand the function inputs and outputs, and follow the provided formulas for accurate results.

Remember, the primary goal is to develop a streamlined process for signal processing and encoding in the context of data communication and networks.
