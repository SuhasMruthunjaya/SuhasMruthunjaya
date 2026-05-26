

close all;
clear all;
clc;

fs = 8000;
Ts = 1/fs;
T  = 2;

f1 = 7000;
f2 = 1000;

N = T/Ts;
n = 0:1:N-1; 

x1 = sin(2*pi*f1*Ts*n) 
x2 = sin(2*pi*f2*Ts*n);


pspectrum(x1,fs);
figure
pspectrum(x2,fs);

