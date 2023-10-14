cmd_/home/orangepi/projects/drivers/gpio/modules.order := {   echo /home/orangepi/projects/drivers/gpio/gpio_driver.ko; :; } | awk '!x[$$0]++' - > /home/orangepi/projects/drivers/gpio/modules.order
