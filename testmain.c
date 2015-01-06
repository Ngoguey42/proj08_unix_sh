
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int	 main(void)
{

  //  return (0);
  //  int fde = open("/dev/stderr", O_APPEND);
  //int fdo = open("/dev/stdout", O_APPEND);


  //  dprintf(fdo, "/dev/stdout...\n");
  dprintf(1, "stdout\n");



  //  dprintf(fde, "/dev/stderr...\n");
  dprintf(2, "stderr\n");


  
  //  close(fdo);	close(fde);
  
  return(0);
}
