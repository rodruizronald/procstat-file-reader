//*****************************************************************************
//
//  Newcastle University
//  EEE8126 - Embedded Systems and Programming
//  Project 1: Real-time parsing using c++ pointers and structures/classes.
//  -------------------------------------------------------------------------
//  File:     cpu.cpp
//  Author:   Ronald Rodriguez Ruiz.
//  Date:     December 6, 2018.
//
//*****************************************************************************
//
//  Header providing fixed width integer types.
//
#include <cstdint>
//
//
//
#include "cpu.h"

namespace procstat
{

  //*****************************************************************************
  //
  //  This method stores on the data array the time spent by the CPU on
  //  different types of processes or in idle mode, and calculates the total
  //  CPU time.
  //  data[0] - user.
  //  data[1] - nice.
  //  data[2] - system.
  //  data[3] - idle.
  //
  //*****************************************************************************
  void Cpu::set_data(uint64_t* data)
  {
    //
    //  Reset the total CPU time at the start of each call.
    //
    this->total_cpu_time = 0;

    for (uint8_t i = 0; i < 4; i++)
    {
      this->data[i] = static_cast<uint32_t>(data[i]);
      this->total_cpu_time += this->data[i];
    }
  }

  //*****************************************************************************
  //
  //  This method returns the percentage of execution time by the processor
  //  in user mode executing normal processes.
  //
  //*****************************************************************************
  float Cpu::get_cpu_busy_pct(void)
  {
    return (static_cast<float>(data[0]) / this->total_cpu_time) * 100;
  }

  //*****************************************************************************
  //
  //  This method returns the percentage of execution time by the processor
  //  in user mode executing niced processes.
  //
  //*****************************************************************************
  float Cpu::get_cpu_nice_pct(void)
  {
    return (static_cast<float>(data[1]) / this->total_cpu_time) * 100;
  }

  //*****************************************************************************
  //
  //  This method returns the percentage of execution time by the processor in
  //  kernel mode executing operating system processes.
  //
  //*****************************************************************************
  float Cpu::get_cpu_system_pct(void)
  {
    return (static_cast<float>(data[2]) / this->total_cpu_time) * 100;
  }

  //*****************************************************************************
  //
  //  This method returns the percentage of idle times in all modes.
  //
  //*****************************************************************************
  float Cpu::get_cpu_idle_pct(void)
  {
    return (static_cast<float>(data[3]) / this->total_cpu_time) * 100;
  }
}
