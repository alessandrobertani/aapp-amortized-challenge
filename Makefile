CXXFLAGS = -I/usr/local/Cellar/google-benchmark/1.5.3/include/ -L/usr/local/Cellar/google-benchmark/1.5.3/lib -lbenchmark -std=c++11 -O3
EX_NAME = mybenchmark

$(EX_NAME) : $(EX_NAME).cpp
	clang++ $< $(CXXFLAGS) -o $@

clean :
	rm -f $(EX_NAME)
