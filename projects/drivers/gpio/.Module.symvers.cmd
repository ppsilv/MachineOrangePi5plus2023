cmd_/home/orangepi/projects/drivers/gpio/Module.symvers := sed 's/\.ko$$/\.o/' /home/orangepi/projects/drivers/gpio/modules.order | scripts/mod/modpost -m -a   -o /home/orangepi/projects/drivers/gpio/Module.symvers -e -i Module.symvers   -T -