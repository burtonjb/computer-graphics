#I have not added header tracking,                                             \
    so just clean and remake when a header file changes

EXE = graphics
BINDINGS = image_lib.so

SRC_DIR = src
BINDINGS_DIR = bindings
TST_DIR = tst
SWIG_GEN_OUTPUT_DIR = bin/swig_output
OBJ_DIR = bin/obj
OUTPUT_DIR = bin
IMAGES_DIR = images
LUA_DIR = lua

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_BINDINGS = $(SRC:$(SOURCE_BINDINGS)/%.c=$(OBJ_DIR)/%.o)
HEADERS = $(wildcard $(SRC_DIR)/*.h)

CPPFLAGS += -Iinclude -fPIC
CFLAGS += -Wall -Wextra -std=c11 -g  # note that the g flag means that it compiles with debug symbols
LDFLAGS += -Llib -fPIC
LDLIBS += -lm -ljpeg -lz -lpng

.PHONY: all clean format fresh images run everything bindings

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $(OUTPUT_DIR)/$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

bindings: all
	# eventually fix this, move it to a dependency above'
	# I'm using swig 4.0.2
	swig -lua -o bin/swig_output/lua_bindings.c bindings/swig.i  
	$(CC) -I /usr/include/lua5.2 $(CPPFLAGS) $(CFLAGS) -c bin/swig_output/lua_bindings.c -llua5.2 -o $(OBJ_DIR)/lua_bindings.o
	$(CC) $(LDFLAGS) $(OBJ) bin/obj/lua_bindings.o $(LDLIBS) -shared -o $(OUTPUT_DIR)/$(BINDINGS)

clean:
	$(RM) $(OBJ)
	$(RM) $(OBJ_DIR)/*
	$(RM) $(SWIG_GEN_OUTPUT_DIR)/*.c
	$(RM) $(OUTPUT_DIR)/$(EXE)
	$(RM) $(IMAGES_DIR)/*.pam
	$(RM) $(IMAGES_DIR)/*.png
	$(RM) $(OUTPUT_DIR)/$(BINDINGS)

format:
	clang-format -i $(SRC_DIR)/*.c $(SRC_DIR)/*.h
	clang-format -i $(TST_DIR)/*.c

lint:
	clang-tidy src/* -checks=-*,clang-analyzer-* --	

fresh: clean format all test

# does a clean build, runs the tests, makes the executable, runs it and then generates the png files
everything: clean format all test run bindings images

## FIXME: This should use the capabilities of make to track if the file has been modified
## FIXME: this is broken unless the user install pamtopng (which is somewhat annoying to build). Eventually replace it with the lua script that I have
images:
	for pam in images/*.pam ; do \
		pamtopng "$$pam" > "$$pam.png" ; \
	done

run: 
	./bin/graphics

# TODO: clean up this target eventually
test:
	gcc -w -g -std=c11 tst/test_math.c src/custom_math.c -o bin/tst/custom_math -lm && ./bin/tst/custom_math
	gcc -w -g -std=c11 tst/test_linear_algebra.c src/custom_math.c src/linear_algebra.c -o bin/tst/linear_algebra -lm && ./bin/tst/linear_algebra
	gcc -w -g -std=c11 tst/test_image.c src/custom_math.c src/image.c src/linear_algebra.c src/pixel.c -o bin/tst/image -lm && ./bin/tst/image
	gcc -w -g -std=c11 tst/test_pixel.c src/custom_math.c src/image.c src/linear_algebra.c src/pixel.c -o bin/tst/pixel -lm && ./bin/tst/pixel
	gcc -w -g -std=c11 tst/test_shape.c src/file_pam.c src/custom_math.c src/image.c src/linear_algebra.c src/pixel.c src/shape.c -o bin/tst/shape -lm && ./bin/tst/shape
	gcc -w -g -std=c11 -g tst/test_jpeg.c src/file_jpeg.c src/custom_math.c src/image.c src/linear_algebra.c src/pixel.c src/shape.c -o bin/tst/jpg -lm -ljpeg && valgrind --error-exitcode=1 ./bin/tst/jpg
	gcc -w -g -std=c11 -g tst/test_png.c src/file_png.c src/custom_math.c src/image.c src/linear_algebra.c src/pixel.c src/shape.c -o bin/tst/png -lm -lpng && valgrind --error-exitcode=1 ./bin/tst/png
