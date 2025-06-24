COMPILER = g++
CPPFLAGS = -Wall -std=c++17 -Wextra -Werror
RES_DIR = resourses
COV_DIR = coverage_report

# CPP_LIBS
ifeq ($(OS),Windows_NT) # MinGW
	CPP_LIBS = -lcheck -lm -lpthread -lrpc_containers -L.
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux) # Linux
		CPP_LIBS = -lgtest -lm -lpthread -L.
	endif
	ifeq ($(UNAME_S),Darwin) # Apple
 		CPP_LIBS = -lgtest
	endif
endif

all: clean test

res:
	mkdir -p resourses

cov:
	$(eval CPPFLAGS+=--coverage)
	$(eval CPP_LIBS+=-lgcov)

gcov_report: clean cov test
#	lcov --ignore-errors inconsistent -c --directory . --output-file rpc_containers_all.info
#	lcov -r rpc_containers_all.info "gtest*" "c++*" "tests*" -o  rpc_containers.info
#	genhtml rpc_containers.info --output-directory $(COV_DIR)
	-lcov --rc lcov_coverage=1 -t "rpc_containers_report" -o rpc_containers_all.info -c -d .
	-lcov --rc lcov_coverage=1 -r rpc_containers_all.info "*/usr/*" "*src/tests*" -o rpc_containers.info
	-genhtml --rc lcov_coverage=1 -o $(COV_DIR) rpc_containers.info
	-mv *.gcda *.gcno *.info $(RES_DIR)/

test: res 
	$(COMPILER) $(CPPFLAGS) -c tests/*.cc
	mv *.o $(RES_DIR)/
	$(COMPILER) $(CPPFLAGS) $(RES_DIR)/*.o -o test -lgtest_main $(CPP_LIBS)
	./test

test_stack: res
	$(COMPILER) $(CPPFLAGS) -c tests/rpc_stack_test.cc
	mv *.o $(RES_DIR)/
	$(COMPILER) $(CPPFLAGS) $(RES_DIR)/*.o -o stack_test -lgtest_main $(CPP_LIBS)

test_queue: res
	$(COMPILER) $(CPPFLAGS) -c tests/rpc_queue_test.cc
	mv *.o $(RES_DIR)/
	$(COMPILER) $(CPPFLAGS) $(RES_DIR)/*.o -o queue_test -lgtest_main $(CPP_LIBS)

test_vector: res
	$(COMPILER) $(CPPFLAGS) -c tests/rpc_vector_test.cc
	mv *.o $(RES_DIR)/
	$(COMPILER) $(CPPFLAGS) $(RES_DIR)/*.o -o vector_test -lgtest_main $(CPP_LIBS)

test_list: res
	$(COMPILER) $(CPPFLAGS) -c tests/rpc_list_test.cc
	mv *.o $(RES_DIR)/
	$(COMPILER) $(CPPFLAGS) $(RES_DIR)/*.o -o list_test -lgtest_main $(CPP_LIBS)

test_set: res
	$(COMPILER) $(CPPFLAGS) -c tests/rpc_set_test.cc
	mv *.o $(RES_DIR)/
	$(COMPILER) $(CPPFLAGS) $(RES_DIR)/*.o -o set_test -lgtest_main $(CPP_LIBS)

test_map: res
	$(COMPILER) $(CPPFLAGS) -c tests/rpc_map_test.cc
	mv *.o $(RES_DIR)/
	$(COMPILER) $(CPPFLAGS) $(RES_DIR)/*.o -o map_test -lgtest_main $(CPP_LIBS)

vg: clean test
	valgrind  --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test

clean:
	rm -rf *.o *.a *.out test *_test
	rm -rf gcov_report *.gcno *.gcda
	rm -rf $(RES_DIR) $(COV_DIR)
