import numpy as np

# Load TX bits and RX-decoded QAM symbols
tx_bits = np.loadtxt("tx_bits.txt", dtype=int)
rx_symbols = np.loadtxt("rx_symbols.txt", dtype=int)

# Convert symbols to bits (4-QAM)
rx_bits = []
for s in rx_symbols:
    rx_bits.extend([(s >> 1) & 1, s & 1])
rx_bits = np.array(rx_bits)

# Truncate and compare
min_len = min(len(tx_bits), len(rx_bits))
bit_errors = np.sum(tx_bits[:min_len] != rx_bits[:min_len])
ber = bit_errors / min_len
print(f"BER: {ber:.4e} over {min_len} bits")
