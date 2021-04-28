#include <benchmark/benchmark.h>
#include <vector>
#include <deque> 
#include <random>

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

void BM_Complexity_Vector_Insert(benchmark::State& state){
	std::vector<int> k;
	for(int i = 0; i < state.range(0); i++){
		k.push_back(std::rand());
	}

	for (auto _ : state) {
		int n = state.range(0);
		std::vector<int> v;
		for(int i = 0; i < n; i++){
			benchmark::DoNotOptimize(v.insert(v.end(), k[i]));
		}
		benchmark::ClobberMemory();
	}
	state.SetComplexityN(state.range(0));
}

void BM_Complexity_Deque_Insert(benchmark::State& state){
	std::deque<int> k;
	for(int i = 0; i < state.range(0); i++){
		k.push_back(std::rand());
	}
	
	int n = state.range(0);

	for (auto _ : state) {
		std::deque<int> d;
		for(int i = 0; i < n; i++){
			benchmark::DoNotOptimize(d.insert(d.end(), k[i]));
		}
		benchmark::ClobberMemory();
	}
	state.SetComplexityN(state.range(0));
}

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

void BM_Complexity_Set_Insert(benchmark::State& state){
	std::vector<int> k;
	for(int i = 0; i < state.range(0); i++){
		k.push_back(std::rand());
	}
	
	int n = state.range(0);

	for (auto _ : state) {
		std::set<int, std::less<int>> s;
		for(int i = 0; i < n; i++){
			benchmark::DoNotOptimize(s.insert(k[i]));
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
	->Complexity(benchmark::oNLogN);


BENCHMARK_MAIN();
