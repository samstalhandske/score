SRC_FILES :=

ifneq ($(filter SCORE_CONSOLE,$(SCORE_DEFINES)),)
    SRC_FILES += $(wildcard console/*.c)
endif

ifneq ($(filter SCORE_HTTP,$(SCORE_DEFINES)),)
    SRC_FILES += $(wildcard http/*.c)
endif

ifneq ($(filter SCORE_JSON,$(SCORE_DEFINES)),)
    SRC_FILES += $(wildcard json/*.c)
endif
ifneq ($(filter SCORE_JSON_CJSON,$(SCORE_DEFINES)),)
    SRC_FILES += json/backends/cjson/json_cjson.c
    SRC_FILES += $(wildcard json/backends/cjson/cJSON/*.c)
endif
ifneq ($(filter SCORE_JSON_JANSSON,$(SCORE_DEFINES)),)
    SRC_FILES += json/backends/jansson/json_jansson.c
endif

ifneq ($(filter SCORE_LINKED_LIST,$(SCORE_DEFINES)),)
    SRC_FILES += $(wildcard linked_list/*.c)
endif

ifneq ($(filter SCORE_STRING,$(SCORE_DEFINES)),)
    SRC_FILES += $(wildcard string/*.c)
endif

ifneq ($(filter SCORE_BUFFER,$(SCORE_DEFINES)),)
    SRC_FILES += $(wildcard buffer/*.c)
    SRC_FILES += $(wildcard buffer/writer/*.c)
    SRC_FILES += $(wildcard buffer/reader/*.c)
endif

ifneq ($(filter SCORE_UTILS,$(SCORE_DEFINES)),)
    SRC_FILES += $(wildcard utils/flag/*.c)
endif

INCLUDE_PATHS := .. .
INCLUDE_FILES := $(wildcard types/types.h)

CFLAGS = -std=c$(C_VERSION) -Wall -Wextra -Werror -Wpedantic $(addprefix -I,$(INCLUDE_PATHS)) $(addprefix -include,$(INCLUDE_FILES))
SCORE_DEFINES_PREFIXED = $(addprefix -D,$(SCORE_DEFINES))

MY_OBJ_DIR = $(OBJ_DIR)/score

OBJS = $(patsubst %,$(MY_OBJ_DIR)/%,$(SRC_FILES))
OBJS := $(OBJS:.c=.o)

all: $(OBJS)
	@echo "Done building score."

$(MY_OBJ_DIR)/%.o: %.c
	@echo "Compiling $< with flags $(CFLAGS) and defines $(SCORE_DEFINES) to $@..."
	@mkdir -p $(dir $@)
	@gcc -c $< $(CFLAGS) -o $@  $(SCORE_DEFINES_PREFIXED)

clean_score:
	@rm -rf $(MY_OBJ_DIR)

.PHONY: all clean_score