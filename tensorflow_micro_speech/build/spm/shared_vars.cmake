set(spm_KERNEL_HEX_NAME zephyr.hex)
set(spm_ZEPHYR_BINARY_DIR /home/jolu/ncs/tensorflow_micro_speech/build/spm/zephyr)
set(spm_KERNEL_ELF_NAME zephyr.elf)
list(APPEND spm_BUILD_BYPRODUCTS /home/jolu/ncs/tensorflow_micro_speech/build/spm/zephyr/zephyr.hex)
list(APPEND spm_BUILD_BYPRODUCTS /home/jolu/ncs/tensorflow_micro_speech/build/spm/zephyr/zephyr.elf)
list(APPEND spm_BUILD_BYPRODUCTS
    /home/jolu/ncs/tensorflow_micro_speech/build/spm/libspmsecureentries.a)
