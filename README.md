# Artifact evaluation for PageORAM

This repository contains the source code to reproduce the experiments from the 2022 MICRO paper titled "PageORAM : An Efficient DRAM Page Aware ORAM Strategy". 

# Hardware requirements

Systems from the family of Intel(R) Xeon(R) Gold 5220R or Ryzen 9 5950X recommended as the results were obtained on systems with these two CPUs. 

64GB or more RAM is also recommended. 

# Software requirements

Code was tested on Linux (Ubuntu version 20.04) OS with GNU C++ compiler. 

# Setup

The repo can be clone as follows:
```
$ git clone https://github.com/Kintoki74/PageORAM.git
```

One benchmark (16GB deepsjeng) is provided and it can be downloaded from https://drive.google.com/drive/folders/1N6hulk_GYN1xWlmSG8QrYefOYkTnkc0Y?usp=sharing. Other benchmarks would be provided on request.

# Execution and results PageORAM.cpp
This code can be used to reproduce data from figures 4, 6 and 7. Note that we do not expect the absolute results to match but it is expected that the results should follow a similar pattern depending on your microarchitecture. The reason for exact results to not match is due to the inherent randomness of ORAM. As the paths given to each data block is completely random for each execution, the stash growth will be different for each execution and hence the overall performance would vary as well. 

The code can be compiled as follows:
```
$ g++ PageORAM.cpp
```
To run the code use:
```
./a.out
```

During runtime the code will ask for a few user inputs. The first thing user needs to input is the total number of real data blocks. For ORAM with 16GB of real data this value would be 268435456. As each data block is 64B total size of real data is 64*268435456 = 16GB. This is to make sure that none of the values in the trace file (benchmark) is more than this value.

 The second input which the user needs to provide is the file name which contains the memory addresses for a particular benchmark. If the file is in the same folder just enter the file name otherwise enter the path to the file. Note that the addresses in the trace file are in integer and not in hexadecimal. 

 The third thing the user needs to input is the configuration which needs to be run. If PageORAM needs to be run enter 0, for baseline-1 enter 1, for baseline-2 enter 2, for baseline-3 enter 3. 

 After this the code will initialize the ORAM tree. This can take 10-15 minutes. After that the user should see the stash size and the wall time after every 100000 accesses. 

 At the end, the total time is printed. To get the results for figure 4, 6 and 7 run the code for a baseline and then PageORAM and compare the timing. 

# Execution and results stash.cpp
This code can be used to reproduce data from figure 5. As explained before the stash growth can vary because of the random nature of path assignment. 

The code can be compiled as follows:
```
$ g++ stash.cpp
```
To run the code use:
```
./a.out
```

During runtime the code will ask for a few user inputs. The first thing user needs to input is the total number of real data blocks (same as before).

 The second input which the user needs to provide is the file path which contains the memory addresses for a particular benchmark (same as before). 

 The third thing the user needs to input is the configuration which needs to be run. If PageORAM needs to be run enter 0 for PathORAM with bucket size 3 enter 1. 

 After this the code will initialize the ORAM tree. This can take 10-15 minutes. 
 
 The last thing the user need to input is the granularity at which the user wants to see the data i.e. stash growth. That is if the user enters an integer value X, user will see the stash size after every X memory accesses. We recommend using the value 10000. 

 As for this code the total stash size is kept in tens of thousands, it is recommended that user kill this program after a while (we recommend to kill this program after around 50 million accesses). The user should be able to see the stash growth pattern from figure 5 where PathORAM's stash growth keeps increasing, while stash growth for PageORAM is basically 0. 

 # Execution and results stashBucket2.cpp
This code can be used to reproduce data from figure 8. As explained before the stash growth can vary because of the random nature of path assignment. 

The code can be compiled as follows:
```
$ g++ stashBucket2.cpp
```
To run the code use:
```
./a.out
```

During runtime the code will ask for a few user inputs. The first thing user needs to input is the total number of real data blocks (same as before).

 The second input which the user needs to provide is the file path which contains the memory addresses for a particular benchmark (same as before). 

 The third thing the user needs to input is the configuration which needs to be run. If PageORAM needs to be run enter 0 for PathORAM with bucket size 2 enter 1 and for PageORAM with search depth of 4 (figure 9) enter 2. 

 After this the code will initialize the ORAM tree. This can take 10-15 minutes. 
 
 The last thing the user need to input is the granularity at which the user wants to see the data i.e. stash growth. We recommend using 1000 or less for this. We recommend such a low value because for bucket size of 2 PathORAM has a explosive stash growth. So even for around a million memory accesses, the stash can grow to over ten thousand so user would not see the stash growth properly if they provide a very large number.

 As for this code the total stash size is kept in tens of thousands, it is recommended that user kill this program after a while (we recommend to kill this program after around 1-2 million accesses). The user should be able to see the stash growth pattern from figure 8 where PathORAM's stash growth keeps increasing, while stash growth for PageORAM is basically 0. 