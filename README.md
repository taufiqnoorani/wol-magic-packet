# Wake-on-LAN (WoL) C Program

## Overview
This C program allows you to remotely power on a PC over the internet using the Wake-on-LAN (WoL) protocol. It sends a "magic packet" to a target machine's MAC address via UDP broadcast, instructing the machine to wake up from sleep or powered-off state (if WoL is enabled in BIOS/UEFI settings).

## Prerequisites
Before running this program, ensure that:
- The target PC supports Wake-on-LAN and has it enabled in BIOS/UEFI and the network adapter settings.
- You know the MAC address of the target PC.
- The target PC is connected via Ethernet (WoL may not work reliably over Wi-Fi).

## Compilation
To compile the program, use **GCC**:
```sh
gcc wake_on_lan.c -o wake_on_lan
```

## Usage
Run the compiled program as follows:
```sh
./wake_on_lan
```
By default, it sends the magic packet to the broadcast address `255.255.255.255` on UDP port `9`.

## Configuration
To modify the MAC address of the target machine, edit the following lines in `wake_on_lan.c`:
```c
mac[0] = 0xAB;
mac[1] = 0xCD;
mac[2] = 0xEF;
mac[3] = 0x12;
mac[4] = 0x34;
mac[5] = 0x56;
```
Replace these values with the actual MAC address of the target PC.

To change the broadcast IP, modify:
```c
udpServer.sin_addr.s_addr = inet_addr("xxx.xxx.xxx.xxx");
```

## Troubleshooting
1. **The target PC is not waking up:**
   - Ensure WoL is enabled in BIOS/UEFI and the network adapter settings.
   - The PC must be in a sleep state or soft-off mode (S5) with power still supplied.
   - Use a wired Ethernet connection; WoL often does not work over Wi-Fi.

2. **No broadcast permission error:**
   - Try running the program with elevated privileges using `sudo`:
     ```sh
     sudo ./wake_on_lan
     ```

3. **Firewall blocks the packet:**
   - Some routers or firewalls may block UDP broadcasts. Check your network configuration.

## License
This project is licensed under the MIT License. Feel free to modify and distribute it.


