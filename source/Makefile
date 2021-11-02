# Executable
NAME = a.out
NAME_DEBUG = debug.out
NAME_FSANITIZE = fsanitize.out
EXECS = $(NAME) $(NAME_DEBUG) $(NAME_FSANITIZE)

# Directories
OTHER_DIR := other
SDIR := src
ODIR := $(OTHER_DIR)/obj
DDIR := $(OTHER_DIR)/dep
IDIR := includes
LDIR := libs

# Naming for different FLAGS
ifdef DEBUG
	NAME = $(NAME_DEBUG)
	SUBDIR = debug/
endif # DEBUG
ifdef FSANITIZE
	NAME = $(NAME_FSANITIZE)
	SUBDIR = fsanitize/
endif # FSANITIZE

# Files
SRC := $(shell find $(SDIR) -name "*.c" -type f)
OBJ := $(patsubst $(SDIR)/%.c,$(ODIR)/$(SUBDIR)%.o,$(SRC))
DEP := $(patsubst $(SDIR)/%.c,$(DDIR)/$(SUBDIR)%.d,$(SRC))

# Compilation
CC = gcc
IFLAGS = -I$(IDIR)
LFLAGS = -ldl -rdynamic
CFLAGS = -Wall -Wextra -Werror
DFLAGS := -O0 -g3

# Unused Flags
UNUSED_FLAGS := -Wno-unused -Wno-unused-parameter
CFLAGS += $(UNUSED_FLAGS)

ifdef FSANITIZE
	DFLAGS += -fsanitize=address
	ifeq ($(shell uname -s),Linux)
		DFLAGS += -fsanitize=leak
	endif # LINUX
endif # FSANITIZE

ifdef DEBUG
	CFLAGS += $(DFLAGS)
	LFLAGS += $(DFLAGS)
endif

RM = /bin/rm -f

# Rules
.PHONY: all
all: $(NAME)

# Compilation
$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LFLAGS)
$(OBJ): $(ODIR)/$(SUBDIR)%.o: $(SDIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)
$(DDIR)/$(SUBDIR)%.d: $(SDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $< -MM -MF $@ -MT $(ODIR)/$(SUBDIR)$*.o $(CFLAGS) $(IFLAGS)

# Cleanup
.PHONY: clean fclean re cleanall
clean:
	$(RM) -r $(OTHER_DIR)
fclean: clean
	$(RM) $(EXECS)
re: fclean
	$(MAKE) all

# Debug
.PHONY: debug
debug:
	$(MAKE) all DEBUG=1
fsanitize:
	$(MAKE) all DEBUG=1 FSANITIZE=1

-include $(DEP)
