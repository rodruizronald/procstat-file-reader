//*****************************************************************************
//
//  Newcastle University
//  EEE8126 - Embedded Systems and Programming
//  Project 1: Real-time parsing using c++ pointers and structures/classes.
//  -------------------------------------------------------------------------
//  File:     system.cpp
//  Author:   Ronald Rodriguez Ruiz.
//  Date:     December 6, 2018.
//
//*****************************************************************************
//
//  Standard string class.
//
#include <string>
//
//  Header providing fixed width integer types.
//
#include <cstdint>
//
//
//
#include "system.h"

namespace procstat
{
  //*****************************************************************************
  //
  //  Constructor: Initilize the page and swap data arrays values. Since some
  //  machines do not provide this data in the "/proc/stat" file, they must be
  //  initilize to avoid future calls returning values different than zero.
  //
  //*****************************************************************************
  System::System() : page_data {0, 1}, swap_data {0, 1}
  {

  }

  //*****************************************************************************
  //
  //  This method sets the number of pages written in and out to the disk.
  //  data[0] - written in.
  //  data[1] - written out.
  //
  //*****************************************************************************
  void System::set_page_data(uint64_t* data)
  {
    for (uint8_t i = 0; i < 2; i++)
    {
      this->page_data[i] = static_cast<uint32_t>(data[i]);
    }
  }

  //*****************************************************************************
  //
  //  This method sets the number of swap pages written in and out to the disk.
  //  data[0] - written in.
  //  data[1] - written out.
  //
  //*****************************************************************************
  void System::set_swap_data(uint64_t* data)
  {
    for (uint8_t i = 0; i < 2; i++)
    {
      this->swap_data[i] = static_cast<uint32_t>(data[i]);
    }
  }

  //*****************************************************************************
  //
  //  This method sets the number of interrupts serviced since boot time.
  //
  //*****************************************************************************
  void System::set_intr_data(uint64_t* data)
  {
    this->intr_data = std::to_string(*data);
  }

  //*****************************************************************************
  //
  //  This method sets the total number of context switches across all CPUs.
  //
  //*****************************************************************************
  void System::set_ctxt_data(uint64_t* data)
  {
    this->ctxt_data = std::to_string(*data);
  }

  //*****************************************************************************
  //
  //  This method sets the time at which the system booted.
  //
  //*****************************************************************************
  void System::set_btime_data(uint64_t* data)
  {
    this->btime_data = static_cast<uint32_t>(*data);
  }

  //*****************************************************************************
  //
  //  This method returns the ratio of pages written in and out to the disk.
  //  page_data[0] - written in.
  //  page_data[1] - written out.
  //
  //*****************************************************************************
  float System::get_page_ratio(void)
  {
    return (static_cast<float>(page_data[0]) / page_data[1]);
  }

  //*****************************************************************************
  //
  //  This method returns the ratio of swap pages written in and out to the disk.
  //  swap_data[0] - written in.
  //  swap_data[1] - written out.
  //
  //*****************************************************************************
  float System::get_swap_ratio(void)
  {
    return (static_cast<float>(swap_data[0]) / swap_data[1]);
  }

  //*****************************************************************************
  //
  //  This method returns a formatted string that indicates the number of
  //  interrupts serviced since boot time (e.g. "16.47 millions since booting").
  //
  //*****************************************************************************
  std::string System::get_intr_serviced(void)
  {
    return string_formatting(intr_data);
  }

  //*****************************************************************************
  //
  //  This method returns a formatted string that indicates the total number
  //  of context switches across all CPUs (e.g. "1.54 billions since booting").
  //
  //*****************************************************************************
  std::string System::get_ctxt_switch_count(void)
  {
    return string_formatting(ctxt_data);
  }

  //*****************************************************************************
  //
  //  This private method formats an string holding a large number in terms of
  //  millions or billions. The output format goes accordingly to the context
  //  switches and interrupts serviced since boot time.
  //
  //*****************************************************************************
  std::string System::string_formatting(std::string str)
  {
    uint8_t i;
    uint8_t magnitud;
    std::string description;
    uint8_t length = static_cast<uint8_t>(str.length());

    //
    //  The string legth determines the magnitud of the number.
    //  If the legth is higher or equal than 10, then the
    //  number in the string is fromatted as "billions".
    //
    if (length >= 10)
    {
      magnitud = 10;
      description = " billions since booting";
    }
    //
    //  If the legth less than 10, but higher or equal than 7,
    //  then the number in the string is fromatted as "millions".
    //
    else if (length >= 7)
    {
      magnitud = 7;
      description = " millions since booting";
    }

    //
    //  Insert a '.' character at the string sixth position
    //  for millions and ninth position for billions.
    //
    for (i = 0; i < 3; i++)
    {
      //
      //  Find the string length by increasing the magnitud up two times.
      //  millions from 7 to 9.
      //  billions from 10 to 12.
      //
      if (length == (magnitud + i))
      {
        //
        //  Use the loop index (i) to determine how many positions
        //  to move forward before inserting the '.' character.
        //
        str.insert((1 + i), ".");
        break;
      }
    }

    //
    //  Build a sub-string to leave only two number after
    //  the '.' character. Then concatenate the description.
    //
    str = str.substr (0, (4 + i));
    str += description;

    return str;
  }
}
