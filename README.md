# skinny
C++ Implementation of Skinny cipher

This repository contains simple C++ implementations of the following ciphers:
- [Skinny-64-128](https://github.com/hadipourh/skinny/blob/master/skinny-64-128.cpp)
- [Skinny-64-192](https://github.com/hadipourh/skinny/blob/master/skinny-64-192.cpp)
- [Skinny-128-256](https://github.com/hadipourh/skinny/blob/master/skinny-128-256.cpp)
- [Skinny-128-384](https://github.com/hadipourh/skinny/blob/master/skinny-128-384.cpp)

## Building
In order to build this project, just type the following command:
```
make
```
## Usage
Open the terminal inside the skinny folder, and then call the object file corresponding to the target cipher. For example, in order 
to doing encryption via the `skinny-64-128`, type the following command:
```
./skinny-64-128
```
## Test-Vectors

It is supposed that the state array is filled according to the following order:
Skinny-64:
```
d70fd8c5735f8264 :

d 7 0 f
d 8 c 5
7 3 5 f
8 2 6 4
```
Skinny-128:
```
c683dc9e0ad25edf7d6300367d4b8665 :
c6 83 dc 9e
0a d2 5e df 
7d 63 00 36
7d 4b 86 65
```
```
cipher           | tk1                              | tk2                              | tk3                              | plaintext                        | ciphertext 
Skinny-64-128  : | d70fd8c5735f8264                 | c2c7a48ccb456a3c                 | none                             | 14ca5472ebae80c7                 | 01398221bd577c31
Skinny-64-192  : | bebea20a052cc18b                 | b23b936a8045a680                 | 399816adb6c979cc                 | 16bb1e8a3477e654                 | 9033c0d31432637d
Skinny-128-256 : | c683dc9e0ad25edf7d6300367d4b8665 | 7926f29ea97cf5d67a08d6446cb7ce32 | none                             | e82da08d25828a562dfd13ffca64e18a | 8a7fa5c2f46472123f28c639cfa00824
Skinny-128-384 : | b372cdd48ca7d309d10f2fb2e6f5fe2a | 365b015aac7bfd8f4b06b919864c3839 | be050e4bade1547ef08330d6792e01af | 44405dd624507aa3e3d0092ace7f931f | 4b25c67cf6f5d9dca8d718120fe3903c
```
Note that, `convert_hexstr_to_statearray(string hex_str, uint8_t int_array[16], bool reversed = false)` function is
used to pass the parameters to the encryption, and decryption, and tweakey-schedule functions in reverse order. 
For example `convert_hexstr_to_statearray("4628f5375c8df07d", tweakey1, true)`, and `convert_hexstr_to_statearray("d70fd8c5735f8264", tweakey1, false)` are equivalent. 
