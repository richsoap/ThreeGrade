APPSOURCES = naiveMNIST.cpp conv_bi.cpp cnpy.cpp
EXECUTABLE = mnist_pc.elf

PLATFORM = zed
SDSFLAGS = -sds-pf ${PLATFORM} \
	-sds-hw conv_bi conv_bi.cpp -sds-end \
	-sds-hw conv_bf conv_bi.cpp -sds-end

#-poll-mode 1 

CC = sds++ ${SDSFLAGS}

CFLAGS = -Wall -O3 -c
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
CFLAGS += -I ~/zlib/zlib-master/build/include -L ~/zlib/zlib-master/build/lib -lz
LFLAGS = -O3

OBJECTS := $(APPSOURCES:.cpp=.o)
DEPS := $(OBJECTS:.o=.d)

.PHONY: all

all: ${EXECUTABLE}

${EXECUTABLE}: ${OBJECTS}
	${CC} ${LFLAGS} ${OBJECTS} -o $@ 

-include ${DEPS}

%.o: %.cpp
	${CC} ${CFLAGS} $< -o $@

clean:
	${RM} ${EXECUTABLE} ${OBJECTS} *.d 

ultraclean: clean
	${RM} ${EXECUTABLE}.bit 
	${RM} -rf _sds sd_card
