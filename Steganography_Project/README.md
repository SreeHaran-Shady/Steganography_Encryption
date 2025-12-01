# 🧠 StegoC — Image Steganography Encryption in C

## 📌 Description
**StegoC** is a low-level implementation of **Image Steganography** written entirely in **C language**.  
This project focuses on understanding how **digital data can be hidden inside images** using **Least Significant Bit (LSB)** manipulation — the simplest yet most powerful steganographic technique.
to understand **how digital hiding works**, how **data leaks can occur through images**, and how such techniques can be **detected or prevented** in real-world scenarios.

## 🎯 Objectives
- Understand the **BMP file format** (header, pixel data, and metadata).
- Learn **bitwise operations** in C and how to modify binary data.
- Implement **encoding** (hiding secret text) and **decoding** (retrieving hidden message).
- Develop awareness about how **data exfiltration or scams** can happen through seemingly innocent images (e.g., via social media or messaging apps).
- Strengthen my understanding of **C programming, file handling**, and **data security fundamentals**.

## 🪶 Features
- **Encode**: Hide a secret message from a text file into a BMP image.
- **Decode**: Extract the hidden message from a steganographic BMP image.
- **LSB Technique**: Modifies the least significant bits of image pixels to embed data without noticeable visual changes.
- **BMP Support**: Works with standard BMP image files.

## 📚 Prerequisites
- GCC compiler (or any C compiler)
- Standard C libraries (stdio, stdlib, string)

## 📲 Building the Project
1. Navigate to the project directory:
   ```
   cd Steganography_Project
   ```
2. Run the Makefile to compile:
   ```
   make
   ```
   This will generate the executable `stego` in the `build/` directory.

3. To clean up object files and executable:
   ```
   make clean
   ```

##  Usage
Run the compiled executable:
```
./build/stego
```

### 🔐 Encoding a Message
1. Place your secret message in `assets/secret.txt`.
2. Place the input BMP image in `assets/input.bmp`.
3. Run the program and choose option 1 (Encode).
4. The output will be saved as `assets/output.bmp` with the hidden message.

### 🔓 Decoding a Message
1. Place the steganographic BMP image in `assets/input.bmp`.
2. Run the program and choose option 2 (Decode).
3. The extracted message will be saved to `assets/extracted.txt`.

## 🗄️ Project Structure
- `src/` - Source code files
  - `main.c` - Main program entry point
  - `encode.c` - Encoding functionality
  - `decode.c` - Decoding functionality
  - `bmp_utils.c` - BMP file handling utilities
  - `encrypt.c` - XOR encryption (currently unused)
- `include/` - Header files
- `assets/` - Sample files for testing
- `build/` - Compiled executable
- `Makefile` - Build configuration

## 🧩 How It Works
1. The user provides a **24-bit uncompressed BMP image** (`input.bmp`) and a **text file** (`secret.txt`).
2. The program reads the image’s pixel data and replaces the **Least Significant Bit** of each byte with the bits from the secret text.
3. The modified image is saved as `output.bmp` inside the `assets/` folder.
4. During decoding, the tool reads the LSBs back and reconstructs the original hidden text.



## 📃🖇️ License
This project is licensed under the MIT License.

## "Understanding how information hides... is the first step in making the digital world safer."
## —> SreeHaran-Shady
