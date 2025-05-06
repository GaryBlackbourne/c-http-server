workerpool-test-sources := $(wildcard test/workerpool/*.c)
workerpool-test-objects := $(patsubst test/workerpool/%.c, $(test-obj-dir)/workerpool/%.o, $(workerpool-test-sources))
workerpool-test-deps    := $(patsubst test/workerpool/%.c, $(test-obj-dir)/workerpool/%.d, $(workerpool-test-sources))

test-objects            += $(workerpool-test-objects)

$(test-obj-dir)/workerpool/%.o: test/workerpool/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@
-include $(workerpool-test-deps)
