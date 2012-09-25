all:matops
matops:matops.c
	gcc $< -o $@
.PHONY:clean
clean:
	@rm -fv core* *~ matops
