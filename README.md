# ToyOS
Toy Operating System for OS design concept learning

## Implemented
- Serial port driver
- VGA display driver
- ATA Drive IO Driver
- Readonly USTAR "filesystem" driver
- Paging
- GDT setting
- Interrupts
## TODO
- Keyboard IO Driver
- Process scheduling
- Memory management

## How to build
For successful build of this project, you have to install GCC Cross Compiler, you can find installation tutorial [here](https://wiki.osdev.org/GCC_Cross-Compiler)
When GCC is successfully installed, execute
```
./compile.sh
```
## How to run
Run script installs compiled image of ToyOS into QEMU virtual machine.
```
./run.sh
```
