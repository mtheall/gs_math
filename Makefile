TARGET  := $(notdir $(CURDIR))

CFILES   := $(wildcard *.c)
CXXFILES := $(wildcard *.cpp)
OFILES   := $(CXXFILES:.cpp=.o) $(CFILES:.c=.o)

#ARCH     := -march=armv6k -mtune=mpcore

CFLAGS   := -Wall -g $(ARCH) -pipe
CXXFLAGS := $(CFLAGS) -std=gnu++11 -DGLM_FORCE_RADIANS
LDFLAGS  := $(ARCH) -pipe -lm

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OFILES)
	@echo "Linking $@"
	@$(CXX) -o $@ $^ $(LDFLAGS)

%.o : %.cpp $(wildcard *.h)
	@echo "Compiling $@"
	@$(CXX) -o $@ -c $< $(CXXFLAGS)

%.o : %.c $(wildcard *.h)
	@echo "Compiling $@"
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@$(RM) *.o $(TARGET)
