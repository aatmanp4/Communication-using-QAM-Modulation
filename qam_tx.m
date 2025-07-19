% Parameters
bitrate = 5000;              % bits per second
Fs = 1000000;                % Sampling rate (1 MHz)
M = 4;                       % 4-QAM
k = log2(M);                 % Bits per symbol
N = 10000;                   % Total bits
sps = Fs / (bitrate / k);   % Samples per symbol

% Generate bitstream and QAM modulate
bits = randi([0 1], 1, N);
symbols = bi2de(reshape(bits, k, []).', 'left-msb');
modulated = qammod(symbols, M, 'UnitAveragePower', true);

% Upsample and pulse shape (raised cosine)
rolloff = 0.25;
span = 8;
pulse = rcosdesign(rolloff, span, sps);
upsampled = upsample(modulated, sps);
tx_signal = conv(pulse, upsampled);

% Normalize
tx_signal = real(tx_signal / max(abs(tx_signal)));

% Save signal and bitstream for MCU and BER calc
writematrix(tx_signal.', 'qam_tx_signal.txt');
writematrix(bits, 'tx_bits.txt');

% Plot waveform and spectrum
subplot(2,1,1); plot(tx_signal(1:1000)); title('QAM Waveform');
subplot(2,1,2); pwelch(tx_signal, [], [], [], Fs); title('Power Spectrum');
