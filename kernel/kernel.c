#include "kernel/kernel.h"
#include "drivers/uart.h"

static mukernel_t *mukernel=NULL;

void mukernel_init(void)
{
    uart_puts("ukernel fw initialized!\n");
}

void mukernel_start(void)
{
   uart_puts("ukernel fw starting!\n");

   mukernel->f_init();//voir s'il ne faut lui passer du contexte, typ des pointeurs vers mukernel_get_time
		      // problematique, car typi le bootloader sentinel n'a pas besoin des meme informatiosn que le shim
		      // suppose des lors que le kernel sait ce qu'il initialise. alors qu'il devrait etre agonostique...
		      //
		      //

   uart_puts("ukernel fw finished!\n");
   while(1); //ajouter un assert ?
}

errno_t mukernel_register_interface(f_init_t *f_init)
{
	mukernel->f_init = f_init;
	return 0;
}
