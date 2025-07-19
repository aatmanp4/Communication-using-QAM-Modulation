% Parameters
bitrate = 5000; % bits per second
Fs = 1000000;   % Sampling rate (1 MHz)
M = 4;          % 4-QAM
k = log2(M);    % Bits per symbol
N = 1000;       % Number of bits

bits = randi([0 1], 1, N);
symbols = bi2de(reshape(bits, k, []).', 'left-msb');
modulated = qammod(symbols, M);

% Pulse shaping
sps = Fs / bitrate / k;
pulse = ones(1, sps);  % Simple rectangular pulse
upsampled = upsample(modulated, sps);
tx_signal = conv(upsampled, pulse);

% Normalize and plot
plot(real(tx_signal(1:200)));
title('QAM Transmit Signal');

% Save for embedded TX
fid = fopen('qam_tx_signal.txt', 'w');
fprintf(fid, '%f\n', real(tx_signal));
fclose(fid);
