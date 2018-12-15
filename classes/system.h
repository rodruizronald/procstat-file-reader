//*****************************************************************************
//
//  Newcastle University
//  EEE8126 - Embedded Systems and Programming
//  Project 1: Real-time parsing using c++ pointers and structures/classes.
//  -------------------------------------------------------------------------
//  File:     system.h
//  Author:   Ronald Rodriguez Ruiz.
//  Date:     December 6, 2018.
//
//*****************************************************************************

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

namespace procstat
{
  //*****************************************************************************
  //
  //  System class.
  //  This class manages the general system information contained in the in the
  //  "/proc/stat" file.
  //
  //*****************************************************************************
  class System
  {
    public:
      //
      //  Constructor.
      //
      System();

      //
      //  Setter methods for the system information.
      //  page - number of pages written in and out to the disk.
      //  swap - number of swap pages written in and out to the disk.
      //  intr - number of interrupts serviced since boot time.
      //  ctxt - number of context switches since boot time.
      //  btime - time at which system booted.
      //
      void set_page_data(uint64_t* data);
      void set_swap_data(uint64_t* data);
      void set_intr_data(uint64_t* data);
      void set_ctxt_data(uint64_t* data);
      void set_btime_data(uint64_t* data);

      //
      //  Getter methods for the pages and swap pages in/out ratio.
      //
      float get_page_ratio(void);
      float get_swap_ratio(void);

      //
      //  Getter methods for the number of interrupts serviced and context switches
      //  since booting in an string format (e.g. "1.54 billions since booting").
      //
      std::string get_intr_serviced(void);
      std::string get_ctxt_switch_count(void);
    private:
      uint32_t page_data[2];
      uint32_t swap_data[2];
      std::string intr_data;
      std::string ctxt_data;
      uint32_t btime_data;
      std::string string_formatting(std::string str);
  };
}

#endif  // __SYSTEM_H__
