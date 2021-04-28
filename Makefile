UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CXX = g++
	CXXFLAGS = --std=c++11 -I~/benchmark/include -L~/benchmark/build/src -lpthread -lbenchmark 
	EX_NAME = mybenchmark
else
	CXX = clang++
	CXXFLAGS = -I/usr/local/Cellar/google-benchmark/1.5.3/include/ -L/usr/local/Cellar/google-benchmark/1.5.3/lib -lbenchmark -std=c++11 -O3
	EX_NAME = mybenchmark
endif

$(EX_NAME) : $(EX_NAME).cpp
	$(CXX) $< $(CXXFLAGS) -o $@

clean :
	rm -f $(EX_NAME)
