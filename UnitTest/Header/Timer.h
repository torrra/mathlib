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
			double			nanoToSec = 0.000000001, nanoToMilli = 0.000001, nanoToMicro = 0.001;
			long long		secToNano = 1000000000ll, milliToNano = 1000000ll, microToNano = 1000ll;

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




private:
	using hrc = std::chrono::high_resolution_clock;

	// When timer was started
	hrc::time_point		m_beg = hrc::now();

	// Stop point - start point in nanoseconds (timer must be stopped to save elapsed time)
	long long			m_elapsed = 0ll;

};