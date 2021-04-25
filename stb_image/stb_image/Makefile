BUILD=bin
DEST_TEST_EXEC=${BUILD}/dft_test
TEST_LOG="${BUILD}/test.log"

all: build test clean
build:
	mkdir -p ${BUILD}
	gcc -Wall -c arrayOperations.c -o ${BUILD}/arrayOperations.o
	gcc -Wall -c imageOperations.c -o ${BUILD}/imageOperations.o
	gcc -Wall -c dft2D.c -o ${BUILD}/dft2D.o
	ar rcs ${BUILD}/libdft.a ${BUILD}/dft2D.o ${BUILD}/imageOperations.o ${BUILD}/arrayOperations.o
test:
	gcc -Wall -c test.c -o ${BUILD}/test.o
	gcc -Wall -o ${DEST_TEST_EXEC} test.c -lm -ldft -L${BUILD}/
	./${DEST_TEST_EXEC} > ${TEST_LOG}
clean:
	rm ${BUILD}/*.o -f
	rm ${DEST_TEST_EXEC} -f
	rm ${TEST_LOG}