cmd_/home/maximus/os_mini_project/kernel_ws/mem-kernelmod/mem_module.ko := ld -r -m elf_x86_64  -z max-page-size=0x200000  --build-id  -T ./scripts/module-common.lds -o /home/maximus/os_mini_project/kernel_ws/mem-kernelmod/mem_module.ko /home/maximus/os_mini_project/kernel_ws/mem-kernelmod/mem_module.o /home/maximus/os_mini_project/kernel_ws/mem-kernelmod/mem_module.mod.o;  true
