#include <benchmark/benchmark.h>
#include <vector>
#include <deque> 
#include <unordered_set>
#include <set>

std::vector<int> constructRandomVector(int size){
	std::vector<int> v;
	v.reserve(size);
	for(int i = 0; i < size; i++){
		v.push_back(static_cast<int>(std::rand() % size));
	}
	return v;	
}

std::deque<int> constructRandomDeque(int size){
	std::deque<int> d;
	for(int i = 0; i<size; i++){
		d.push_front(std::rand() % size);
	}
	return d;
}

std::set<int, std::less<int>> constructRandomSet(int size){
    std::set<int, std::less<int>> s;
    for(int i = 0; i < size; i++){
        s.insert(std::rand() % size);
    }
    return s;
}

std::unordered_set<int> constructRandomUnorderedSet(int size){
    std::unordered_set<int> us;
    for(int i = 0; i < size; i++){
        us.insert(std::rand() % size);
    }
    return us;
}

// Vector insertion is amortized constant
void BM_Complexity_Vector_Insert(benchmark::State& state){
    int n = state.range(0);
    std::vector<int> v;
	for (auto _ : state) {
	    v.clear();   
		for(int i = 0; i < n; i++){
			v.push_back(i);
		}
		benchmark::ClobberMemory();
	}
	state.SetComplexityN(state.range(0));
}

// Vector find is linear
void BM_Complexity_Vector_Find(benchmark::State& state) {
	auto v = constructRandomVector(state.range(0));
	int n = state.range(0);

	std::vector<int> k;
	for(int i = 0; i < n; i++){
		k.push_back(std::rand());
	}

	for (auto _ : state){
		for (int i = 0; i < n; i++){
			benchmark::DoNotOptimize(std::find(v.begin(), v.end(), k[i]));
		}
		benchmark::ClobberMemory();
	}

	state.SetComplexityN(state.range(0));
}

// Deque insertion is amortized constant
void BM_Complexity_Deque_Insert(benchmark::State& state){
	int n = state.range(0);
    std::deque<int> d;

	for (auto _ : state) {
        d.clear();
		for(int i = 0; i < n; i++){
            d.push_back(i);		
        }
		benchmark::ClobberMemory();
	}
	state.SetComplexityN(state.range(0));
}

// Deque find is linear
void BM_Complexity_Deque_Find(benchmark::State& state){
	auto d = constructRandomDeque(state.range(0));
	int n = state.range(0);

	std::deque<int> k;
	for(int i = 0; i < n; i++){
		k.push_back(std::rand());
	}

	for (auto _ : state){
		for (int i = 0; i < n; i++){
			benchmark::DoNotOptimize(std::find(d.begin(), d.end(), k[i]));
		}
		benchmark::ClobberMemory();
	}

	state.SetComplexityN(state.range(0));
}

// Ordered Set insertion is logarithmic
void BM_Complexity_Set_Insert(benchmark::State& state){
	int n = state.range(0);
    std::set<int, std::less<int>> s;
	for (auto _ : state) {
        s.clear();		
		for(int i = 0; i < n; i++){
			benchmark::DoNotOptimize(s.insert(i));
		}
		benchmark::ClobberMemory();
	}
	state.SetComplexityN(state.range(0));

}

// Ordered Set Find is logarithmic
void BM_Complexity_Set_Find(benchmark::State& state){
    auto s = constructRandomSet(state.range(0));
	int n = state.range(0);

	std::vector<int> k;
	for(int i = 0; i < n; i++){
		k.push_back(std::rand());
	}

	for (auto _ : state){
		for (int i = 0; i < n; i++){
			benchmark::DoNotOptimize(s.find(k[i]));
		}
		benchmark::ClobberMemory();
	}

	state.SetComplexityN(state.range(0));

}

// Unordered Set insertion is constant
void BM_Complexity_Unordered_Set_Insert(benchmark::State& state){
    int n = state.range(0);
    std::unordered_set<int> s;
	for (auto _ : state) {
        s.clear();		
		for(int i = 0; i < n; i++){
			benchmark::DoNotOptimize(s.insert(i));
		}
		benchmark::ClobberMemory();
	}
	state.SetComplexityN(state.range(0));
}

// Unordered Set search is constant
void BM_Complexity_Unordered_Set_Find(benchmark::State& state){
    auto us = constructRandomUnorderedSet(state.range(0));
	int n = state.range(0);

	std::vector<int> k;
	for(int i = 0; i < n; i++){
		k.push_back(std::rand());
	}

	for (auto _ : state){
		for (int i = 0; i < n; i++){
			benchmark::DoNotOptimize(us.find(k[i]));
		}
		benchmark::ClobberMemory();
	}

	state.SetComplexityN(state.range(0));

}

BENCHMARK(BM_Complexity_Vector_Insert) 
	->RangeMultiplier(2) 
	->Range(1 << 10, 1 << 16) 
	->Complexity();

BENCHMARK(BM_Complexity_Vector_Find) 
	->RangeMultiplier(2) 
	->Range(1 << 10, 1 << 16) 
	->Complexity();

BENCHMARK(BM_Complexity_Deque_Insert) 
	->RangeMultiplier(2) 
	->Range(1 << 10, 1 << 16) 
	->Complexity();

BENCHMARK(BM_Complexity_Deque_Find) 
	->RangeMultiplier(2) 
	->Range(1 << 10, 1 << 16) 
	->Complexity();

BENCHMARK(BM_Complexity_Set_Insert) 
	->RangeMultiplier(2) 
	->Range(1 << 10, 1 << 16) 
	->Complexity();

BENCHMARK(BM_Complexity_Set_Find) 
	->RangeMultiplier(2) 
	->Range(1 << 10, 1 << 16) 
	->Complexity();

BENCHMARK(BM_Complexity_Unordered_Set_Insert) 
	->RangeMultiplier(2) 
	->Range(1 << 10, 1 << 16) 
	->Complexity();

BENCHMARK(BM_Complexity_Unordered_Set_Find) 
	->RangeMultiplier(2) 
	->Range(1 << 10, 1 << 16) 
	->Complexity(benchmark::oN);

BENCHMARK_MAIN();
