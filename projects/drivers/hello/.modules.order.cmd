cmd_/home/pdsilva/projects/drivers/hello/modules.order := {   echo /home/pdsilva/projects/drivers/hello/hello.ko; :; } | awk '!x[$$0]++' - > /home/pdsilva/projects/drivers/hello/modules.order
