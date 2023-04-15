# c-cl
Compile and Run C\C++ Programs with One Command! <br>
Written in Pure C++, No Batch Scripting :wink: <br>

# Example Usage

## Run The Demo
Make sure you have the MSVC compiler installed. <br>
Run the following commands in your terminal: 
```
git clone https://github.com/jglatts/c-cl
cd c-cl
nmake
c_cl demo-code\test.c demo-code\source.c 
```
<br>





## Compile\Run Single Source File
```
c_cl test.c 
```
<br>




## Compile\Run Multiple Source Files
```
c_cl source1.cpp source2.cpp source2.cpp 
```

<br>


## Works with compiler flagas too
```
c_cl /w /O2 tt.c
```