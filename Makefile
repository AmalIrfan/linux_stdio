#DEBUG=1
CFLAGS=-nostdlib -ffreestanding -no-pie \
       -pedantic -Wall -Wextra -Werror -std=c89 \
       -march=native -mtune=native -O3
# maybe a bad idea to optimize, remove the
# previous line if so

ifdef DEBUG
  CFLAGS+=-g
else
  CFLAGS+=-s
endif

define cc
#	make depend files to include
	@$(CC) $(CFLAGS) -MM -MF $@.d -MT $@ $<
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "CC  " $@ " <-" $<
endef

define link
	@$(CC) $(CFLAGS) -o $@ $^
	@echo LINK $@ " <-" $^
endef

.PHONY=clean help

tok: src/tok.c.o src/mylib.S.o src/mylib.c.o
	@$(call link)

echo: src/echo.c.o src/mylib.S.o src/mylib.c.o
	@$(call link)

src/%.S.o: src/%.S
	@$(call cc)

src/%.c.o: src/%.c
	@$(call cc)

clean:
	rm src/*.o  # object files
	rm src/*.d  # depend files

help:
	@echo "Usage: make <target>"
	@echo "Targets:"
	@echo "  tok    Build the tokenizer"
	@echo "  echo   Build the echo program"
	@echo "  help   Show this message"
	@echo "  clean  Delete build files"
	@echo "For more info try: make --help"

# include depend files we made
# (it will be a mess XD)
-include $(wildcard src/*.d)
