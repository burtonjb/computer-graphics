#I have not added header tracking,                                             \
    so just clean and remake when a header file changes

EXE = graphics

SRC_DIR = src
TST_DIR = tst
OBJ_DIR = bin/obj
OUTPUT_DIR = bin
IMAGES_DIR = images

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
HEADERS = $(wildcard $(SRC_DIR)/*.h)

CPPFLAGS += -Iinclude
CFLAGS += -Wall -std=c11 -g
LDFLAGS += -Llib
LDLIBS += -lm

.PHONY: all clean format fresh images run

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $(OUTPUT_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(OUTPUT_DIR)/$(EXE)
	$(RM) $(IMAGES_DIR)/*.pam
	$(RM) $(IMAGES_DIR)/*.png

format:
	clang-format -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h
	clang-format -i $(TST_DIR)/*.c

fresh: clean format all test

# does a clean build, makes the executable, runs it and then generates the png files
release: clean format all run images

## FIXME: This should use the capabilities of make to track if the file has been modified
images:
	for pam in images/*.pam ; do \
		pamtopng "$$pam" > "$$pam.png" ; \
	done

run: 
	./bin/graphics

# TODO: clean up this target eventually
test:
	echo "TODO"