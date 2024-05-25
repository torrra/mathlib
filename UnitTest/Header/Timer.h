#pragma once

#include <iostream>
#include <chrono>
#include <functional>

using hrc = std::chrono::high_resolution_clock;

// Timer class to act as a stopwatch
class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	// Start timer
	void start(void)
	{
		m_beg = hrc::now();
	}

	// Stop timer and save time between start and stop
	void stop(void)
	{
		m_elapsed += std::chrono::duration_cast<std::chrono::nanoseconds>(hrc::now() - m_beg).count();
	}

	// Reset elapsed time
	void clear(void) { m_elapsed = 0ll; }


	//  Display saved elapsed
	void display(bool verbose = false) const
	{
		// Display time in nanoseconds only
		if (!verbose)
			std::cout << "Elapsed time: " << m_elapsed << " nanoseconds.\n";

		// Longer display
		else
		{
			long long		nanoseconds = m_elapsed;

			// Conversion factors between each time unit
			double			nanoToSec = 1e-9, nanoToMilli = 1e-6, nanoToMicro = 1e-3;
			long long		secToNano = (__int64) 1e9, milliToNano = (__int64) 1e6, microToNano = (__int64) 1e3;

			// Divide into microseconds, milliseconds, etc
			long long		seconds = static_cast<long long>(nanoseconds * nanoToSec);

			// Keep remainder
			nanoseconds -= seconds * secToNano;

			long long		milliseconds = static_cast<long long>(nanoseconds * nanoToMilli);

			nanoseconds -= milliseconds * milliToNano;


			long long		microseconds = static_cast<long long>(nanoseconds * nanoToMicro);

			nanoseconds -= microseconds * microToNano;


			std::cout << "Elapsed time: " << seconds << " s, " << milliseconds << " ms, " << microseconds << " us, " << nanoseconds << " ns." << '\n';
		}
	}

	// Get elapsed time in nanoseconds (must be previously saved with start() and stop() or getRuntime())
	long long getElapsed(void) const { return m_elapsed; }



	template <typename T>
	T recordFunction(std::function<T()> func, bool shouldDisplay = true)
	{
		clear();
		start();

		T res = func();

		stop();

		if (shouldDisplay)
			display();

		return res;
	}

	template<>
	void recordFunction<void>(std::function<void()> func, bool shouldDisplay)
	{
		clear();
		start();

		func();

		stop();

		if (shouldDisplay)
			display();

	}




private:
	using hrc = std::chrono::high_resolution_clock;

	// When timer was started
	hrc::time_point		m_beg = hrc::now();

	// Stop point - start point in nanoseconds (timer must be stopped to save elapsed time)
	long long			m_elapsed = 0ll;

};