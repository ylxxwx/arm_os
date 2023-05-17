.global c_entry

entry:
  LDR sp, =stack_top
  BL c_entry
  B .