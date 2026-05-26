clear all; clc; close all;

set(groot, 'DefaultAxesTickLabelInterpreter', 'LaTeX');

T   = 2; 
f0  = 800;
fs1 = 20000;
fs2 = 1000;

t1 = 0:1/fs1:T;
x1 = sin(2*pi*f0*t1);
t2 = 0:1/fs2:T;
x2 = sin(2*pi*f0*t2);

fig = figure;
set(fig,'color','w');
plot(t1,x1); 
hold on;
plot(t2,x2); 
grid on
grid minor
axis([0, 0.01, -1.1, 1.1])
xlabel('$t/s$','Interpreter','latex');
ylabel('$x(t)$','Interpreter','latex');
box off;

l = legend('$x(t) = \cos(2\pi f t), f = 800Hz, f_s = 20000Hz$','$x(t) = \cos(2\pi f t), f = 800Hz, f_s = 1000Hz$','Location','northoutside');
set(l,'Interpreter','latex');
legend boxoff

fig = figure;
set(fig,'color','w');
X1     = fft(x1);
X_tmp1 = abs(X1/length(t1));
Xf1    = X_tmp1(1:floor(length(t1)/2)+1);
Xf1(2:end) = 2*Xf1(2:end);
f = fs1*(0:length(t1)/2)/length(t1);
plot(f,Xf1);
grid on
grid minor
box off;
axis tight
xlim([0 1000])
xlabel('f/Hz','Interpreter','latex');
ylabel('$\left| X(f) \right|$','Interpreter','latex');
dummy = line(nan, nan, 'Linestyle', 'none', 'Marker', 'none', 'Color', 'none');
l = legend(dummy,'$x(t) = \cos(2\pi f t), f = 800Hz, f_s = 20000Hz$','Location','northoutside');
set(l,'Interpreter','latex');
legend boxoff

soundsc(zeros(1,length(x1)),fs1);
soundsc(x1,fs1)

pause(2);

fig = figure;
set(fig,'color','w');
X2     = fft(x2);
X_tmp2 = abs(X2/length(t2));
Xf2    = X_tmp2(1:floor(length(t2)/2)+1);
Xf2(2:end) = 2*Xf2(2:end);
f = fs2*(0:length(t2)/2)/length(t2);
plot(f,Xf2);
grid on
grid minor
box off;
axis tight
xlim([0 1000])
xlabel('f/Hz','Interpreter','latex');
ylabel('$\left| X(f) \right|$','Interpreter','latex');
dummy = line(nan, nan, 'Linestyle', 'none', 'Marker', 'none', 'Color', 'none');
l = legend(dummy,'$x(t) = \cos(2\pi f t), f = 800Hz, f_s = 1000Hz$','Location','northoutside');
set(l,'Interpreter','latex');
legend boxoff
soundsc(zeros(1,length(x2)),fs2);
soundsc(x2,fs2)