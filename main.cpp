//
// Created by alice on 06.02.2026.
//
/////////////////////////////////////////////////////////////////////////////////

// chapter : Number Processing

/////////////////////////////////////////////////////////////////////////////////

// section : Chrono Management

/////////////////////////////////////////////////////////////////////////////////

// content : Time Measurements

/////////////////////////////////////////////////////////////////////////////////

#include <cassert>
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <iomanip>

/////////////////////////////////////////////////////////////////////////////////

template < typename D = std::chrono::duration < double > >
class Timer
{
public:
    explicit Timer(std::string  scope) :
            m_scope(std::move(scope)),
            m_is_running(false)
    {}

    ~Timer()
    {
        if (!m_measurements.empty())
        {
            std::cout << m_scope << " : среднее время = "
                      << std::fixed << std::setprecision(6)
                      << average() << " с (измерений: "
                      << m_measurements.size() << ")\n";
        }
    }

//  -----------------------------------------------------------------------------

    void start()
    {
        if (m_is_running)
        {
            std::cout << "Ошибка: таймер '" << m_scope << "' уже запущен!\n";
            return;
        }

        m_begin = clock_t::now();
        m_is_running = true;
    }

//  -----------------------------------------------------------------------------

    void stop()
    {
        if (!m_is_running)
        {
            std::cout << "Ошибка: таймер '" << m_scope << "' не был запущен!\n";
            return;
        }

        auto end = clock_t::now();
        auto duration = std::chrono::duration_cast<D>(end - m_begin);

        m_measurements.push_back(duration);

        m_is_running = false;

        std::cout << m_scope << " : измерение " << m_measurements.size()
                  << " = " << std::fixed << std::setprecision(6)
                  << duration.count() << " с\n";
    }

//  -----------------------------------------------------------------------------

    [[nodiscard]] double average() const
    {
        if (m_measurements.empty())
        {
            std::cout << "нет измерений для усреднения\n";
            return 0.0;
        }

        double sum = 0.0;
        for (const auto& measurement : m_measurements)
        {
            sum += measurement.count();
        }

        return sum / m_measurements.size();
    }

//  -----------------------------------------------------------------------------

    [[nodiscard]] std::size_t count() const
    {
        return m_measurements.size();
    }

    [[nodiscard]] double last() const
    {
        if (m_measurements.empty())
            return 0.0;
        return m_measurements.back().count();
    }

private:
    using clock_t = std::chrono::steady_clock;

//  -----------------------------------------------------------------------------

    std::string m_scope;

    clock_t::time_point m_begin;

    bool m_is_running;

    std::vector<D> m_measurements;
};

/////////////////////////////////////////////////////////////////////////////////

auto calculate(std::size_t size)
{
    auto x = 0.0;

    for (auto i = 0uz; i < size; ++i)
    {
        x += std::pow(std::sin(i), 2) + std::pow(std::cos(i), 2);
    }

    return x;
}

/////////////////////////////////////////////////////////////////////////////////

auto equal(double x, double y, double epsilon = 1e-6)
{
    return std::abs(x - y) < epsilon;
}

/////////////////////////////////////////////////////////////////////////////////

int main()
{
    std::cout << std::fixed << std::setprecision(6);

    {
        Timer timer("одиночное измерение");
        timer.start();
        assert(equal(calculate(1'000'000), 1'000'000));
        timer.stop();
    }

    std::cout << "\n" << std::string(50, '-') << "\n";

    {
        Timer timer("много измерений");

        for (int i = 0; i < 5; ++i)
        {
            timer.start();
            assert(equal(calculate(100'000 * (i + 1)), 100'000 * (i + 1)));
            timer.stop();
        }

        std::cout << "Количество измерений: " << timer.count() << "\n";
        std::cout << "Среднее время: " << timer.average() << " с\n";
        std::cout << "Последнее измерение: " << timer.last() << " с\n";
    }

    std::cout << "\n" << std::string(50, '-') << "\n";

    {
        Timer timer("проверка отлова ошибок");

        timer.stop();
    }

    return 0;
}