workerpool-test-sources := $(wildcard test/workerpool/*.c)
workerpool-test-objects := $(patsubst test/workerpool/%.c, $(test_obj_dir)/workerpool/%.o, $(workerpool-test-sources))
workerpool-test-deps    := $(patsubst test/workerpool/%.c, $(test_obj_dir)/workerpool/%.d, $(workerpool-test-sources))
workerpool-test-objects += $(obj_dir)/unity.o

workerpool-test         += $(test_dir)/workerpool-test
tests                   += $(workerpool-test)

$(test_obj_dir)/workerpool/%.o: test/workerpool/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(test-CFLAGS) -c $< -o $@
-include $(workerpool-test-deps)

$(workerpool-test): $(workerpool-test-objects) $(objects)
	@mkdir -p $(@D)
	$(CC) $^ -o $@ $(LDFLAGS)
