##### Regression tests #####
#
# Organized as follows
# ./sources/    EMPTY but RESERVED (should contain in the future the original C source code)
# ./calipso/    contains the source processed by calipso
# ./reference/    what the FFX should be
# ./current/    what the FFX is with the current version of oRange
# ./diff/   Potential differences between the reference and the current version
# ./doc/   Elements of documentation of the regression tests

.SECONDARY:

M := Makefile
C := $(wildcard calipso/*.c)
STATUS := $(C:calipso/%.c=%.status)
CMD := ../main/orange --no-control-reduction --print_exp

.PHONY: all
all: $(STATUS)

diff/%.diff: reference/%.extract current/%.extract $(M)
	@mkdir -p $(dir $@)
	diff reference/$*.extract current/$*.extract > $@ ; test $$? -ne 2

%.extract: %.ffx $(M)
	grep total $< > $@ ; test $$? -ne 2

current/%.ffx: calipso/%.c $(M)
	@mkdir -p $(dir $@)
	$(CMD) -o $@ $< main > /dev/null

reference/%.ffx:
	@echo "# No reference FFX for test $*."
	@echo "# If this this test was just introduced, you can run:"
	@echo "$(CMD) -o $@ calipso/$*.c main"
	@false

.PHONY: %.status
%.status: diff/%.diff
	bash status.sh $*

.PHONY: clean
clean:
	rm -rf current diff reference/*.extract
	find -name '*~' -delete
