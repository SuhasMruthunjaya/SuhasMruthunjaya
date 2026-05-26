% CA CFAR Algorhytmus
clear all;
close all;
clc;

% CA CFAR Parameters
N  = 512;   %Sample Size
NG = 1;     %Guard Cells
NR = 10;    %Reference Cells
PFA = 10^-6; %Probability of False Alarm


%%%
% Test Data Generation
%%%

% sine Parameters
A0 = 1;
fs = 256;
ks1 = 20.0;
phase1 = -pi/4;

f1 = fs/N*ks1;

% abgetatstet und "kontinuierlich"
n = 0:(N-1);
x = A0*cos(2*pi*f1/fs*n + phase1); %- 0.5*sin(2*pi*f2/fs*n + phase2);

% noise
A0eff = A0/sqrt(2);
sinePower = A0eff^2;
noise = A0eff*randn(N,1);

% signal and noise
xnoise = x+noise';

% Plot sinus mit noise
figure(1)
plot(n,xnoise,'b');
hold on
plot(n,x,'r','LineWidth',1.5);
xlabel 'n'
ylabel 'x_{noise}(n)'
title('sampled sinewave with AWGN');
legend('sine and noise','sine')


% Spectral computation

figure(2) %plot the spectra



%%%
% CFAR
%%%

% Implement here your CA-CFAR Algorithmn

figure(2) %Plot the resulting threshold in the spectra plot


% give back the number of targets
