// Performance Optimization Module
#pragma once

namespace performance_optimization
{
    // Memory optimization flags
    #define USE_MEMORY_POOLING 1
    #define USE_OBJECT_CACHE 1
    #define USE_SIMD_OPERATIONS 1

    // CPU optimization flags
    #define USE_VECTORIZATION 1
    #define USE_CACHE_OPTIMIZATION 1
    #define USE_BRANCH_PREDICTION 1

    // GPU optimization flags
    #define USE_BATCH_RENDERING 1
    #define USE_INSTANCING 1
    #define USE_COMPUTE_SHADERS 1

    // Threading optimization
    #define USE_THREAD_POOL 1
    #define WORKER_THREAD_COUNT 4

    // Profiling helper class
    class PerformanceProfiler
    {
    public:
        static void StartTimer(const char* name);
        static void EndTimer(const char* name);
        static void PrintResults();
        static void ClearResults();

    private:
        struct TimingData
        {
            float total_time;
            int call_count;
            float average_time;
        };

        static std::map<std::string, TimingData> timings;
    };

    // Memory pool allocator
    template<typename T, size_t PoolSize = 1024>
    class MemoryPool
    {
    public:
        T* Allocate();
        void Deallocate(T* ptr);
        void Clear();
        size_t GetAllocatedCount() const;

    private:
        std::vector<T> pool;
        std::queue<T*> free_list;
        std::set<T*> allocated;
    };

    // Cache optimization utilities
    class CacheOptimizer
    {
    public:
        static void PrefetchMemory(void* ptr, size_t size);
        static void FlushCache();
        static void OptimizeMemoryLayout(void* data, size_t size);
    };

    // SIMD operations helper
    class SIMDHelper
    {
    public:
        // Vector operations
        static void AddVectors(float* a, float* b, float* result, size_t count);
        static void MultiplyVectors(float* a, float* b, float* result, size_t count);
        static void DotProduct(float* a, float* b, float* result, size_t count);
    };
}
