# Calc
Calc is small Matlab language interpreter. The applications supports only basic Matlab operations.
I'm currently creating new interpeter from scratch with improved stability and performance.

## To compile requires:
- Boost 1.57
- Qt5
- Visual Studio 2013
- Qt Vs Addin
- DISLIN

# Syntax

## IF instructions

if (a==1)
    c=2
elseif (3)
    d=2
else
    2
end

## Loops
A=[];
for i=1:0.1:10
  A(1,i)=i*i;
end

while i<10
  i=i-1;
end

## Functions
Function must be declered in seperate ".m" file. The file name must be the same as a function name. File has to start with function declaration like in fallowing example:

 function [out1,out2] = method(in1,in2,in3) 
    out1=in1*in2;
    out2=in1+in3;
 end
