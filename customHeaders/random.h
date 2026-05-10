#include <random>

// dont use, not sure if this works as it should
inline float randomDouble(double min = 0.0, double max = 1.0)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}

// returns a random float between min (inclusive) and max (inclusive)
inline float randomFloat(float min = 0.f, float max = 1.f)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

// returns a random int between min (inclusive) and max (inclusive)
inline int randomInt(int min = 0, int max = 1)
{
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}