#include "kernel/kernel.h"
#include "kernel/debug.h"

static mukernel_t mukernel={
     .state = MUKERNEL_NOT_INITIALISED,
     .f_init         = NULL
};

static void mukernel_panic(void) 
{
  mukernel.state =  MUKERNEL_STOPPED;
  DEBUG_ERR("!!! mukernel panic  !!!\n");
  while(1);
}

mukernel_err_status_t mukernel_init(void)
{
   if (mukernel.state != MUKERNEL_NOT_INITIALISED)
	   return MUKERNEL_ERR_INVALID_STATE;

   //ici il y aura sans doute a terme init de la MMU
   //enum PCIe
   //...
   DEBUG_INFO("ukernel fw initialized!\n");

   mukernel.state = MUKERNEL_INITIALISED;
   return MUKERNEL_OK;
}

mukernel_err_status_t mukernel_start(void)
{
  errno_t errno;

   DEBUG_INFO("ukernel fw starting!\n");

   if ( mukernel.state != MUKERNEL_INTERFACE_REGISTERED)
     return MUKERNEL_ERR_INVALID_STATE;


   //call initialisation function of upper layer
   if (!mukernel.f_init()){
     DEBUG_ERR("no init function have registered\n");
     mukernel_panic();
   }

   errno = mukernel.f_init();//voir s'il ne faut lui passer du contexte, typ des pointeurs vers mukernel_get_time
		      // problematique, car typi le bootloader sentinel n'a pas besoin des meme informatiosn que le shim
		      // suppose des lors que le kernel sait ce qu'il initialise. alors qu'il devrait etre agnostique...
     
   //TODO : gestion errno


   mukernel.state =  MUKERNEL_STARTED;
   DEBUG_INFO("ukernel fw finished!\n");


   mukernel.state =  MUKERNEL_STOPPED;
   while(1); //ajouter un assert ?
}

errno_t mukernel_register_interface(f_init_t *f_init)
{

   if (mukernel.state == MUKERNEL_INTERFACE_REGISTERED)
     return EALREADY;
   if (f_init == NULL)
     return EINVAL; 
     
   if (mukernel.state != MUKERNEL_INITIALISED){
	DEBUG_ERR("try to register an init function while mukernel have not been registered");
	mukernel_panic();
   }

   mukernel.f_init = f_init;

   mukernel.state = MUKERNEL_INTERFACE_REGISTERED;
   return 0;
}
