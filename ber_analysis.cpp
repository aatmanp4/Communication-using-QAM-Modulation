import numpy as np

# Load TX and RX bitstreams
tx = np.fromfile('tx_bits.txt', dtype=np.uint8)
rx = np.fromfile('rx_bits.txt', dtype=np.uint8)

# Make sure length matches
length = min(len(tx), len(rx))
tx = tx[:length]
rx = rx[:length]

# Compute bit errors
errors = np.sum(tx != rx)
ber = errors / length

print(f"Bit Error Rate (BER): {ber:.4e} over {length} bits")
