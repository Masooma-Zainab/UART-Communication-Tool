# UART-Communication-Tool
Linux C implementation of a UART communication interface for RISC-V hardware verification, featuring non-blocking I/O and 115200 8N1 configuration.

Overview
This project provides a robust, Linux-based C implementation of a UART (Universal Asynchronous Receiver-Transmitter) communication tool. It is designed to interface between a host machine and hardware targets, specifically optimized for RISC-V superscalar processor verification and firmware debugging.

The tool handles the low-level system calls required to open, configure, and manage serial data flow, ensuring reliable communication even in non-blocking environments.

Technical Specifications
Protocol: UART (Asynchronous Serial)

Baud Rate: 115200 bps (standard for RISC-V console output)

Data Format: 8N1

Data Bits: 8

Parity: None

Stop Bits: 1

I/O Model: Non-blocking reception with a 5-second timeout (VTIME/VMIN configuration)

Data Integrity: Utilizes tcdrain() to guarantee physical bit transmission before process completion.

Features
Automated Configuration: Dynamically configures termios structures for industry-standard serial communication.

Robust Error Handling: Real-time monitoring of errno for common hardware interface issues (e.g., EACCES for permission denials).

Hardware Simulation Support: Fully compatible with socat for virtualized testing without physical FPGA or ASIC hardware.

Getting Started
1. Prerequisites
You will need a Linux environment (e.g., Ubuntu/Debian) and the following tools:

Bash
sudo apt update && sudo apt install gcc socat
2. Environment Setup (Simulation Mode)
To simulate the hardware "bridge," open a separate terminal and run:

Bash
socat -d -d pty,raw,echo=0 pty,raw,echo=0
Note the output paths, for example: /dev/pts/2 and /dev/pts/3.

3. Compilation
Compile the source code using gcc:

Bash
gcc uart_test.c -o uart_test
4. Running the Test
Execute the program and send a manual reply through the virtual bridge to verify the receiver logic:

Bash
# Run the program in the background
./uart_test &

# Send a reply from the "hardware" side (use the second path from socat)
echo "REPLY RECEIVED" > /dev/pts/3
Future Scope
This tool is part of a broader effort to develop verification environments for RISC-V based superscalar processors. Future iterations will include:

Integration with Verilator for RTL simulation.

Support for custom baud rates and flow control (Hardware/Software).

Logging mechanisms for long-term hardware stress testing.

Author
Masooma Zainab
