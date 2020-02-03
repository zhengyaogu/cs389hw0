### Part 1
a. Explain in your README.md file how many iterations you picked at different sizes and why. There is no single correct answer here, I just want to see your reasoning.

From 2^8(256) to 2^24(16777216) coordinates, here is a table of number iterations I choose to run the benchmark on in python:
|size  |  iters  | 
|256  |   10000 |
|512  |   10000 |
|1024  |  1000|
|2048 |   1000|
|4096  |  1000|
|8192   | 100|
|16384  | 100|
|32768  | 100|
|65536  | 50 |
|131072 | 25 |
|262144 | 12 |
|524288 | 6  |
|1048576 |3 |
|2097152 |1 |
|4194304 |1  |
|8388608 |1   |
|16777216 |1  |
I choose the largest number of iterations such that the benchmark runs under 62097152 30
0 seconds to maximize stability of the benchmark, while saving time.

b. Explain how you picked a single number from repeated measurements and justify it. There is no single correct answer here either.

I ran each size-iters combination 5 times and chose the smallest time per coordinate. I observed that the smallest time is usually very close to the median and average of the 5 times, while the largest deviates away from the mean and median. Thus I suspect that the largest time might reflect some erratic behavior of the execution.

c. Plot a line graph of mean update time per coordinate as a function of total no. of objects (first parameter).

See tpcplot.pdf.

### Part 2
From 2^8(256) to 2^24(16777216) coordinates, here is a table of number iterations I choose to run the benchmark on in C++; since the program runs much faster in C++, we are able to increase the number of iterations across all sizes of objects by about 10 times:
|size  |  iters  | 
|256  |   100000 |
|512  |   100000 |
|1024  |  50000|
|2048 |   20000|
|4096  |  10000|
|8192   | 10000|
|16384  | 4000|
|32768  | 2000|
|65536  | 500 |
|131072 | 500 |
|262144 | 200 |
|524288 | 100  |
|1048576 |100 |
|2097152 |30 |
|4194304 |10  |
|8388608 |5   |
|16777216 |5  |

All the updates are conducted in double type.

### Part 2
To compare C++'s performance across different data types, we fix the size of coordinates to be 4096, and number of iterations to be 10000. We run the each data type for five trials and take the minimum runtime as its performance score. The following table demonstrates the results.
|data type | time ()