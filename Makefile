VPATH	=	src
BINDIR 	=	bin
LOGDIR	=	logs
FIGDIR	=	figs
HERE	=	$(shell pwd)
AT	=	@
DOLLAR  = 	$$


CD	=	$(AT)cd
CP	=	$(AT)cp
ECHO	=	@echo
CAT	=	$(AT)cat
IF	=	$(AT)if
LN	=	$(AT)ln
MKDIR	=	$(AT)mkdir
MV	=	$(AT)mv
SED	=	$(AT)sed
RM	=	$(AT)rm
TOUCH	=	$(AT)touch
CHMOD	=	$(AT)chmod
DATE    =       $(AT)date
PERL	=	$(AT)perl
MEX	=	$(AT)$(MATLAB)/bin/mex
THRIFT	=	/usr/local/bin/thrift
AR	=	$(AT)ar
ARFLAGS	=	rcs

#CC             =       $(AT) gcc
#CXX             =      $(AT) g++
FPIC		=	-fPIC
INCLUDES	=	-I$(HERE) -I. -I$(SRCDIR)
CFLAGS	 	= 	-c -g -Wall $(INCLUDES)
LDFLAGS		= 	-lnsl 

CWARN			=	-Wall -Wno-sign-compare -Wno-unused-variable
CXXWARN			=	$(CWARN) $(FPIC) -Wno-deprecated -Woverloaded-virtual

COMMON_CFLAGS		=	-c -g -std=gnu99 -D_GNU_SOURCE=1 \
					-D_REENTRANT  $(CWARN) $(FPIC)\

COMMON_CXXFLAGS         =       -c -g $(CXXWARN) 


DBG_CFLAGS		=	$(COMMON_CFLAGS) -DDEBUG_MODE=1
DBG_CXXFLAGS		=	$(COMMON_CXXFLAGS) -DDEBUG_MODE=1
OPTIMIZATION_FLAGS	=	-O3
OPT_CFLAGS		=	$(COMMON_CFLAGS) -DNDEBUG \
				$(OPTIMIZATION_FLAGS) -fno-omit-frame-pointer
OPT_CXXFLAGS		=	$(COMMON_CXXFLAGS) -DNDEBUG \
				$(OPTIMIZATION_FLAGS) -fno-omit-frame-pointer

COMMON_LDFLAGS		=	-g $(FPIC) -Wl -lm -lpthread
DBG_LDFLAGS		=	$(COMMON_LDFLAGS) --eh-frame-hdr
OPT_LDFLAGS		=	$(COMMON_LDFLAGS) -O3 -fno-omit-frame-pointer

OPT	=	1
ifneq ($(strip $(OPT)),)
	CFLAGS		=	$(OPT_CFLAGS)
	CXXFLAGS	=	$(OPT_CXXFLAGS)
	LDFLAGS		=	$(OPT_LDFLAGS)
else
	CFLAGS		=	$(DBG_CFLAGS)
	CXXFLAGS	=	$(DBG_CXXFLAGS)
	LDFLAGS		=	$(DBG_LDFLAGS)
endif


# We start our mode with "mode" so we avoud the leading whitespace from the +=.
NEWMODE := mode

# This is the usual DEBUG mode trick. Add DEBUG=1 to the make command line to
# build without optimizations and with assertions ON.
ifeq ($(DEBUG),1)
	CFLAGS  += -O0 -DDEBUG
	NEWMODE += debug
else
	CFLAGS  += -DNDEBUG
	NEWMODE += nodebug
endif

ifeq ($(PROF),1)
	CFLAGS  += -pg
	LDFLAGS += -pg
	NEWMODE += profile
endif

# Rule for compiling c files.
$(BINDIR)/%.o : %.c .buildmode Makefile
	$(ECHO) "compiling $<"
	$(MKDIR) -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<

# Rule for compiling c++ files.
$(BINDIR)/%.o: %.cpp
	$(ECHO) "compiling $<"
	$(MKDIR) -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $<

# If the new mode does'n match the old mode, write the new mode to .buildmode.
# This forces a rebuild of all the objects files, because they depend on .buildmode.
OLDMODE := $(shell cat .buildmode 2> /dev/null)
ifneq ($(OLDMODE),$(NEWMODE))
  $(shell echo "$(NEWMODE)" > .buildmode)
endif

.PHONY: all
all: mpctcp_proxy

.PHONY: clean
clean:
	$(ECHO) Cleaning...
	$(RM) -rf $(BINDIR)
	$(RM) -rf mpctcp_srv mpctcp_cli
	$(RM) -rf mpctcp_proxy

.PHONY: distclean
distclean: clean

.PHONY: remake
remake: clean proxy

mpctcp_cli: $(BINDIR)/mpctcp_cli.o $(BINDIR)/libUtil.a .buildmode Makefile
	$(ECHO) "linking $@"
	$(MKDIR) -p $(dir $@)
	$(CC) -o $@ $(BINDIR)/mpctcp_cli.o $(BINDIR)/libUtil.a $(LDFLAGS)

mpctcp_srv: $(BINDIR)/mpctcp_srv.o $(BINDIR)/libUtil.a .buildmode Makefile
	$(ECHO) "linking $@"
	$(MKDIR) -p $(dir $@)
	$(CC) -o $@ $(BINDIR)/mpctcp_srv.o $(BINDIR)/libUtil.a $(LDFLAGS) 

# Rule to make the libUtil library
$(BINDIR)/libUtil.a: $(BINDIR)/net_util.o $(BINDIR)/socks.o
	$(ECHO) "building  $@"
	$(MKDIR) -p $(dir $@)
	$(AR) $(ARFLAGS) $@ $(BINDIR)/net_util.o $(BINDIR)/socks.o

mpctcp_proxy: $(BINDIR)/mpctcp_proxy.o $(BINDIR)/mpctcp_srv.o $(BINDIR)/mpctcp_cli.o $(BINDIR)/libUtil.a .buildmode Makefile
	$(ECHO) "linking $@"
	$(MKDIR) -p $(dir $@)
	$(CC) -o $@ $(BINDIR)/mpctcp_proxy.o $(BINDIR)/mpctcp_srv.o $(BINDIR)/mpctcp_cli.o $(BINDIR)/libUtil.a $(LDFLAGS)

.PHONY: proxy
proxy: mpctcp_proxy

.PHONY: install
install: all
	install -d $(DESTDIR)/usr/bin
	install mpctcp_proxy $(DESTDIR)/usr/bin 
	install -d $(DESTDIR)/etc/mpctcp/
	install -c -m 644 config/mpctcp_proxy.conf $(DESTDIR)/etc/mpctcp/

# Uncomment to debug the Makefile
# OLD_SHELL := $(SHELL)
# SHELL = $(warning [$@ ($^) ($?)]) $(OLD_SHELL)
