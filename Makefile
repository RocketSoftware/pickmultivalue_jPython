#ifndef pythonMaj
pythonMaj = 3
#endif

#ifndef pythonMin
pythonMin = .6m
#endif

libtarget = lib/libjpython.so
bin_src = callpython_test.jabba
binobject = jabba]MOBJECT/$(patsubst %.jabba,%.o,$(bin_src))
bintarget = bin/$(patsubst %.jabba,%,$(bin_src))

jabba_src = python_class.jabba
jabba_object=$(patsubst %.jabba,%.o,$(jabba_src))
libobject = classes/$(jabba_object)
headers = include/jbcpython_common.h
linklib = python$(pythonMaj)$(pythonMin)

targets: $(bintarget) $(libtarget)

all: targets

$(libobject): classes/$(jabba_src) $(headers)
	BASIC -I.. -I/usr/include/python$(pythonMaj)$(pythonMin) classes $(jabba_src)

$(libtarget): $(libobject)
	cd classes && jcompile -o../$(libtarget) $(jabba_object) -l$(linklib)

$(binobject): jabba/$(bin_src) $(headers)
	BASIC jabba $(bin_src)

$(bintarget): $(binobject)
	CATALOG -o./bin jabba $(bin_src)

clean:
	-rm -f $(bintarget)* $(binobject) $(libtarget)* $(libobject)
