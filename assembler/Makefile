NAME := bynan

SRC := $(wildcard *.c)
HDR := $(wildcard *.h)

riscv-assembler: $(SRC) $(HDR)
	gcc $(SRC) -o $@ -Wall -Wextra -O0 -g

test: test.py riscv-assembler
	@ python3  $<

clean:
	@ rm -f riscv-assembler
	@ rm -rf __pycache__ .pytest_cache .hypothesis ._* *~
	@ find tests \( -name '*.o' -o -name '*.bin' -o -name '*.hex' -o -name '*.state' \) -delete
	@ find ../exos -type f -executable -delete

tar: clean
	@ rm -f ../*.tgz
	@ (cd ..; tar -cvzf "$(NAME).tgz" *)
	@ echo "==="; echo "Created: ../$(NAME).tgz"

.PHONY: test clean tar
