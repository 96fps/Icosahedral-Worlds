# call on xxxx.c with 'make xxxx' to compile to xxxx
# sudo apt install libxmu-dev libxmu-headers

CC = gcc

LDLIBS = -lglut	-lGL	-lGLU	-lXmu 	-lX11 	-L/usr/X11R6/lib 	-lm

.c:
	$(CC)	$@.c	$(LDLIBS)	-o $@