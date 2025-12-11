# 🔐 DES (Data Encryption Standard) Implementation

> A complete, production-grade implementation of the Data Encryption Standard algorithm in C

![DES Algorithm](algo.png)

---

## 🎯 Overview

This project provides a **fully functional DES encryption implementation** in C, demonstrating the complete cryptographic workflow from key scheduling to encryption/decryption of 64-bit data blocks.

**DES** is a symmetric-key block cipher that has been a cornerstone of data security for decades. This implementation includes:
- ✅ Complete key schedule generation (16 round keys)
- ✅ Full encryption pipeline with 16 rounds
- ✅ Decryption support using reverse key order
- ✅ All standard DES permutation tables and S-boxes
- ✅ Well-documented, educational code

---

## 🚀 Quick Start

### Compilation
```bash
gcc -o des des_implementation.c
```

### Usage
```bash
./des
```

---

## 📋 Features

| Feature | Status |
|---------|--------|
| **Initial Permutation (IP)** | ✅ Implemented |
| **Key Schedule Generation** | ✅ Implemented |
| **16-Round Feistel Function** | ✅ Implemented |
| **S-Box Substitution** | ✅ All 8 S-boxes |
| **Expansion & Permutation** | ✅ Implemented |
| **Encryption (64-bit blocks)** | ✅ Functional |
| **Decryption** | ✅ Functional |

---

## 🔧 How It Works

### The DES Algorithm Flow
1. **Input Processing**: 64-bit plaintext block
2. **Initial Permutation**: Rearrange bit positions
3. **16 Rounds of Encryption**:
   - Expand right half (32 → 48 bits)
   - XOR with round key
   - S-box substitution (48 → 32 bits)
   - Permutation
   - Swap left and right halves
4. **Final Permutation**: Inverse of initial permutation
5. **Output**: 64-bit ciphertext

---

## 📁 Project Structure

```
des_implementation.c
├── Data Structures & Tables
│   ├── Permutation tables (IP, IP_INV, E, P)
│   ├── PC-1 & PC-2 (Key permutations)
│   ├── Shift counts
│   └── S-boxes (S1-S8)
├── Utility Functions
├── Key Schedule Generation
├── Encryption Logic
└── Main Program
```

---

## 🎓 Educational Value

Perfect for:
- 📚 Cryptography students learning cipher mechanics
- 👨‍💻 Developers understanding symmetric encryption
- 🔍 Security enthusiasts exploring classic algorithms
- 🏫 University coursework and projects

---

## ⚠️ Important Note

**⚡ For Educational Use Only**

DES is **cryptographically broken** for modern applications due to its small 56-bit effective key size and has been superseded by **AES (Advanced Encryption Standard)**.

For production systems, use:
- 🔑 **AES-256** (recommended)
- **ChaCha20**
- Other NIST-approved ciphers

---

## 🔑 Key Parameters

- **Block Size**: 64 bits
- **Key Size**: 56 bits (64 bits with parity)
- **Rounds**: 16
- **Subkey Size**: 48 bits per round
- **Output**: 64-bit ciphertext

---

## 📊 Performance

- **Time Complexity**: O(1) - Fixed 16 rounds
- **Space Complexity**: O(1) - Constant tables
- **Block Processing**: Sequential 64-bit blocks

---

## 🤝 Contributing

Found an issue or want to improve this implementation? Contributions welcome!

---

## 📜 License

This project is open source and available under the MIT License.

---

## 🌟 Show Your Support

If this implementation helped you understand DES better, please ⭐ star the repository!

---

**Made with ❤️ for the cryptography community**
