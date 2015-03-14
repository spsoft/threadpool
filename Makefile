#--------------------------------------------------------------------

CC = gcc
AR = ar cru
CFLAGS = -Wall -D_REENTRANT -D_GNU_SOURCE -g
SOFLAGS = -shared -fPIC
LDFLAGS = -lpthread

LINKER = $(CC)
LINT = lint -c
RM = /bin/rm -f

ifeq ($(origin version), undefined)
	version = 0.2.1
endif

#--------------------------------------------------------------------

TARGET = testthreadpool

#--------------------------------------------------------------------

all: $(TARGET)

testthreadpool: threadpool.o testthreadpool.o
	$(LINKER) $(LDFLAGS) $^ $(LIBS) -o $@

dist: clean threadpool-$(version).src.tar.gz

threadpool-$(version).src.tar.gz:
	@ls | grep -v CVS | grep -v .so | sed 's:^:threadpool-$(version)/:' > MANIFEST
	@(cd ..; ln -s threadpool threadpool-$(version))
	(cd ..; tar cvf - `cat threadpool/MANIFEST` | gzip > threadpool/threadpool-$(version).src.tar.gz)
	@(cd ..; rm threadpool-$(version))

clean:
	$(RM) *.o core core.* $(TARGET)

#--------------------------------------------------------------------

# make rule
%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

