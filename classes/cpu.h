//*****************************************************************************
//
//  Newcastle University
//  EEE8126 - Embedded Systems and Programming
//  Project 1: Real-time parsing using c++ pointers and structures/classes.
//  -------------------------------------------------------------------------
//  File:     cpu.h
//  Author:   Ronald Rodriguez Ruiz.
//  Date:     December 6, 2018.
//
//*****************************************************************************

#ifndef __CPU_H__
#define __CPU_H__

namespace procstat
{
  //*****************************************************************************
  //
  //  Cpu class.
  //  This class manages the cpu information contained in the "/proc/stat" file.
  //
  //*****************************************************************************
  class Cpu
  {
    public:
      //
      //  Setter method for the CPU data.
      //
      void set_data(uint64_t* data);

      //
      //  Getter methods for the percentage of execution time.
      //  user (busy) - normal processes executing in user mode.
      //  nice - niced processes executing in user mode.
      //  system - processes executing in kernel mode.
      //  idle - idle times in all modes.
      //
      float get_cpu_busy_pct(void);
      float get_cpu_nice_pct(void);
      float get_cpu_system_pct(void);
      float get_cpu_idle_pct(void);
    private:
      uint32_t total_cpu_time;
      uint32_t data[4];
  };
}

#endif  // __CPU_H__
