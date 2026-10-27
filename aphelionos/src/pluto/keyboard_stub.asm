global keyboard_isr_stub
extern keyboard_handler_main

keyboard_isr_stub:
    pushad

    call keyboard_handler_main

    popad
    iret
    