from pathlib import Path

M = 0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f

def long_to_bytes(val):
    return val.to_bytes(max(1, (val.bit_length() + 7) // 8), "big")


def ripple(val, key):
    amp = val
    p = M

    prev = 1
    current = amp

    for _ in range(key):
        new_val = (2 * amp * current - prev) % p
        prev = current
        current = new_val

    return current


encrypted = Path(r"C:\Users\ASUS\Downloads\flag.enc").read_bytes()

base_val = 0x1337C0DE

# brute small range around expected key
for k in range(99900, 100100):

    secret = ripple(base_val, k)
    key = long_to_bytes(secret)

    flag = bytes(
        c ^ key[i % len(key)] for i, c in enumerate(encrypted)
    )

    if b"flag" in flag.lower() or b"ctf" in flag.lower():
        print("[+] FOUND KEY:", k)
        print(flag)
        break