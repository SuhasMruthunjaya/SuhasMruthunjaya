
clear; close all; clc;
set(groot,'DefaultAxesTickLabelInterpreter', 'LaTeX');
set(groot,'defaultTextInterpreter','LateX'); 
format long;

fs = 8000;
Ts = 1/fs;
T  = 2;

t = 0:Ts:T-Ts;
y = chirp(t,100,2,8000);

figure;
set(gcf,'color','w');
% only plot the first 10ms ... 
plot(t(1:T/(20*Ts)),y(1:T/(20*Ts)));
box off;
grid on; grid minor; 
xlabel('Frequency (Hz)','Interpreter','latex');
ylabel('$s(t)$','Interpreter','latex');
box off;
axis tight

figure;
set(gcf,'color','w');
pspectrum(y,fs,'spectrogram', 'FrequencyLimits',[100 4000])

obj = audioplayer(y,fs);
pause(1);
play(obj);


