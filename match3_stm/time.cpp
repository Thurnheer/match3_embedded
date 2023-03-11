#include <FreeRTOS.h>
#include <task.h>
#include <chrono>

namespace std::chrono
{

time_point<system_clock> system_clock::now() noexcept
{
    return time_point(milliseconds(xTaskGetTickCount()));
}

time_point<steady_clock> steady_clock::now() noexcept
{
    return time_point(milliseconds(xTaskGetTickCount()));
}

}
