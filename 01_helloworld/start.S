.global c_entry
.global entry

entry:
  ldr x30, =stack_top
  mov sp, x30
  BL c_entry
  B .