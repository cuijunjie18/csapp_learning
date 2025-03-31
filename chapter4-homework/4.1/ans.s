.pos
    0x100 : 30 F3 0F 00 00 00 00 00 00 00  irmoveq   $15,%rbx
    0x10A : 20 31                          rrmoveq   %rbx,%rcx
.loop
    0x10C : 40 13 FD FF FF FF FF FF FF FF  rmmoveq   %rcx,-3(%rbx)
    0x116 : 60 31                          addq %rbx,%rcx
    0x118 : 70 0C 01 00 00 00 00 00 00 00  jmp loop
