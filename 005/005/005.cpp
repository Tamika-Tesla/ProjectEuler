#include <iostream>
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>

std::vector<int> primes;

void fill(int n)
{
	primes.resize(n + 1);
	for (int i = 0; i < primes.size(); ++i)
		primes[i] = i;

	int p = 1;
	while (p < n)
	{
		++p;
		if (primes[p] != 0)
		{
			p = primes[p];
			for (int i = p * p; i <= n; i += p)
				primes[i] = 0;
		}
	}
	primes.erase(std::remove(primes.begin(), primes.end(), 0), primes.end());
}

int solve(int arg)
{
	fill(arg);
	int result = 1;
	int limit = sqrt(arg);
	for (int i = 1; i < primes.size(); ++i)
	{
		int p = primes[i];
		if (p <= limit)
			result *= pow(p, (int)(log(arg) / log(p)));
		else
			result *= p;
	}
	return result;
}

int main()
{
	assert(solve(8) == 840);
	assert(solve(10) == 2520);
	auto  now = std::chrono::high_resolution_clock::now();
	auto answer = solve(20);
	auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - now);
	std::cout << "Answer = " << answer << "\n";
	std::cout << "Time : " << elapsed.count() << "ns.\n";
	return 0;
}
