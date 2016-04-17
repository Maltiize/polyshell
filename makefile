



CC=gcc
KERN=Kernel.c Serv.c
FULLSRC=Kernel.c Serv.c MyCd.c MyPwd.c MyDu.c MyRm.c MyEcho.c MyCat.c MyChmod.c MyCp.c MyLs.c MyMkdir.c MyChown.c MyChgrp.c
DEFAULTSRC=MyPwd.c MyDu.c MyRm.c MyEcho.c MyCat.c MyChmod.c MyCp.c MyLs.c MyMkdir.c MyChown.c MyChgrp.c
FLAGC= -Wall
WITHOUTMY=
WITHOUTC=
FILE=
all: bash bashfile

bash:
	rm bash;
	cd BashFullStatic ;\
	$(CC) $(FLAGC) $(FULLSRC) -o ../bash
	
	
	
bashfile:
		-mkdir libb;
		cd BashUsingFile ;\
	    for number in $(DEFAULTSRC) ; do \
	    	$(CC) $(FLAGC) $(number) -o ../libb/$(FILE);\
		done
		$(CC) $(FLAGC) $(FULLSRC) -o ../bashfile


    
