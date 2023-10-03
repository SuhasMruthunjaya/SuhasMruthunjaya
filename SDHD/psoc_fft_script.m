%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Testbench Communication from FreeSoc2 to Matlab
% Version 1.0, Bannwarth, 30.05.2020
%
% Behaviour: 
% - Everytime Maltlab writes �s�on the UART, the PSoC sends new measurement 
%    results and Matalab writes 'o' if these data is received.
% - The Script terminates after 10 data transfers.
%
% Using:
% 1. Connect FreeSoc2 to USB (i.e. Power Up)
% 2. Check the correct serial Port Settings
% 3. Start this Matlab Script
% 4. Run this Script
% 5. Press the external Push Button to start measuring
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

close all;
clear all;
clc;

priorPorts=instrfind;
delete(priorPorts);
PSoC=serial('COM6', 'BaudRate', 9600, 'InputBufferSize', 14000);
fopen(PSoC);

f1 = figure;
count = 1;

flg_data_avai = 0;
fwrite(PSoC,'s','uchar') % means send, I am ready to receive
while(flg_data_avai == 0)
   %fprintf('%u\n', PSoC.BytesAvailable); 
       if PSoC.BytesAvailable == (2048 + 8192) 
          % fprintf('%u\n', PSoC.BytesAvailable);
             fwrite(PSoC,'o','uchar') % means I received all expected data
             rx_data_adc = fread(PSoC,1024,'uint16');
             fprintf(" Transfer %i DONE \n",count);

             rx_data_fft = fread(PSoC,2048,'int32');

          % Split the FFT data into real and imaginary parts
             rx_data_fft_real = rx_data_fft(1:2:end);
             rx_data_fft_imag = rx_data_fft(2:2:end);
        
          % Combine real and imaginary parts to form complex numbers
             rx_data_fft_combined = complex(rx_data_fft_real, rx_data_fft_imag);
             
             % Plotting the received data
                
             figure(f1)
             subplot(3,1,1)
             plot([0:(length(rx_data_adc)-1)],rx_data_adc(1:(length(rx_data_adc))));
             title(['Received Time Domain Data No.:',num2str(count)]);
             subplot(3,1,2)
             plot([0:1023],1/length(rx_data_adc)*20*log10(abs(fft(rx_data_adc))));
             title('FFT -  Matlab');

             subplot(3,1,3)
             plot([0:(length(rx_data_fft_combined)-1)],2/length(rx_data_fft_combined)*20*log10(abs(rx_data_fft_combined(1:(length(rx_data_fft_combined))))));
             title('FFT - PSOC');

             % Save the received data
             %save(strcat('CW_rx_data_adc_',int2str(count),'.mat'),'rx_data_adc');
             count=count+1;
       end

       if count == 11
           break;
       end

       fwrite(PSoC,'s','uchar') % means send, I am ready to receive
end

fclose(PSoC);

fprintf(" Scipt End \n");