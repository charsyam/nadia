# nadia Makefile
# Copyright (C) 2013 CharSyam <charsyam at gmail dot com>
# This file is released under the BSD license, see the COPYING file
#

uname_S := $(shell sh -c 'uname -s 2>/dev/null || echo not')

CC=g++
FINAL_CFLAGS=-g
FINAL_LDFLAGS=
NADIA_CC=$(QUIET_CC)$(CC) $(FINAL_CFLAGS)
NADIA_LD=$(QUIET_LINK)$(CC) $(FINAL_LDFLAGS)

CCCOLOR="\033[34m"
LINKCOLOR="\033[34;1m"
SRCCOLOR="\033[33m"
BINCOLOR="\033[37;1m"
MAKECOLOR="\033[32;1m"
ENDCOLOR="\033[0m"

ifndef V
QUIET_CC = @printf '    %b %b\n' $(CCCOLOR)CC$(ENDCOLOR) $(SRCCOLOR)$@$(ENDCOLOR) 1>&2;
QUIET_LINK = @printf '    %b %b\n' $(LINKCOLOR)LINK$(ENDCOLOR) $(BINCOLOR)$@$(ENDCOLOR) 1>&2;
QUIET_INSTALL = @printf '    %b %b\n' $(LINKCOLOR)INSTALL$(ENDCOLOR) $(BINCOLOR)$@$(ENDCOLOR) 1>&2;
endif

TARGET= nadia
NADIA_OBJ=nadia.o nadia_stream.o

all: $(TARGET) 
	@echo ""
	@echo "Hint: To run 'make test' is a good idea ;)"
	@echo ""

.PHONY: all

# Deps (use make dep to generate this)
dep:
	$(REDIS_CC) -MM *.c > Makefile.dep

.PHONY: dep

$(TARGET): $(NADIA_OBJ)
	$(NADIA_LD) -o $@ $^ $(LIBS)

clean:
	rm -rf $(TARGET) *.o *.gcda *.gcno *.gcov lcov-html

.PHONY: clean
