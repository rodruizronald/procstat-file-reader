//
//  Standard input/output streams library.
//
#include <iostream>
//
//  Input/output stream class to operate on files.
//
#include <fstream>
//
//  Stream class to operate on strings.
//
#include <sstream>
//
//  Standard string class.
//
#include <string>
//
//  Header providing parametric manipulators.
//
#include <iomanip>
//
//  Header providing fixed width integer types.
//
#include <cstdint>
//
//  C standard general utilities library.
//
#include <cstdlib>
//
//  POSIX operating system API for usleep.
//
#include <unistd.h>
//
//  CPU class.
//
#include "classes/cpu.h"
//
//  System class.
//
#include "classes/system.h"
//
//  Parser class.
//
#include "classes/parser.h"

//*****************************************************************************
//
//  Main Function.
//
//*****************************************************************************
int main(int argc, char const *argv[])
{
  std::ifstream fs;
  std::string line;

  //
  //  Parser object to parse a single file
  //  line into a label and data.
  //
  procstat::Parser parser;

  //
  //  Elements contained in a file line.
  //
  procstat::Label label;
  uint64_t* data = nullptr;

  //
  //  Counters for the number of lines
  //  and CPUs in the file.
  //
  uint8_t line_cnt = 0;
  uint8_t cpu_cnt = 0;

  //
  //  Open the file in read mode.
  //
  fs.open("/proc/stat", std::ifstream::in);

  //
  //  If the file is open proceed, if not,
  //  display an error message and exit the program.
  //
  if (fs.is_open())
  {
    //
    //  Ignore the first line.
    //
    getline(fs, line);

    //
    //  Read the file line by line.
    //
    while (getline(fs, line))
    {
      //
      //  Parse each line an get the label.
      //
      parser.parse_string(line);
      label = parser.get_label();

      //
      //  If the previous label was a CPU,
      //  then increase the CPU counter.
      //
      if (label == procstat::Label::Cpu)
      {
        cpu_cnt++;
      }

      line_cnt++;
    }

    fs.close();
  }
  else
  {
    std::cerr << "Error: The file cannot be open." << std::endl;
		exit(EXIT_FAILURE);
  }

  //
  //  New array of Cpu objects based on the number
  //  of CPUs previously counted in the file.
  //
  procstat::Cpu* cpu = new procstat::Cpu[cpu_cnt];

  //
  //  System object to manage general system information
  //  (page, swap, intr, ctxt, btime).
  //
  procstat::System system;

  //
  //  The infinite loop does the following steps until CTL + C is pressed:
  //  Open the file, parse the lines, store data on the corresponding object,
  //  and display the results.
  //
  while(1)
  {
    //
    //  Open the file in read mode.
    //
    fs.open("/proc/stat", std::ifstream::in);

    //
    //  If the file did not open, then display
    //  an error message and exit the program.
    //
    if (!fs.is_open())
    {
      std::cerr << "Error: The file cannot be open." << std::endl;
      exit(EXIT_FAILURE);
    }

    //
    //  Ignore the first line.
    //
    getline(fs, line);

    //
    //  Loop through the remaining lines.
    //
    for (uint8_t i = 0; i < line_cnt; i++)
    {
      //
      //  Read a new line, parse the line,
      //  and get its label and data.
      //
      getline(fs, line);
      parser.parse_string(line);
      label = parser.get_label();
      data = parser.get_data();

      //
      //  Set the data into the corresponding object.
      //
      switch (label)
      {
        //
        //  The CPUs come always first in the file, so the index of the
        //  for loop can be used as index for the array of Cpu objects.
        //
        case procstat::Label::Cpu:
          cpu[i].set_data(data);
          break;

        case procstat::Label::Page:
          system.set_page_data(data);
          break;

        case procstat::Label::Swap:
          system.set_swap_data(data);
          break;

        case procstat::Label::Intr:
          system.set_intr_data(data);
          break;

        case procstat::Label::Ctxt:
          system.set_ctxt_data(data);
          break;

        case procstat::Label::Btime:
          system.set_btime_data(data);
          break;

        default:
          break;
      }
    }

    //
    //  Default values for the output format.
    //
    uint8_t fixed_precision = 6;
    uint8_t fixed_width = 12;

    //
    //  Clean the previous screen and print the new results.
    //
    std::cout << "\e[1;1H\e[2J";
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "CPU Cores: " << unsigned(cpu_cnt) << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << std::left << "CPU ";
    std::cout << std::setw(13) << std::right << "Busy";
    std::cout << std::setw(11) << std::right << "Nice";
    std::cout << std::setw(12) << std::right << "System";
    std::cout << std::setw(12) << std::right << "Idle" << std::endl;
    std::cout << "=======================================================" << std::endl;
    //
    //  Display the CPUs percentage of execution time.
    //
    for (uint8_t i = 0; i < cpu_cnt; i++)
    {
      //
      //  If the number of CPUs is more than 9, then the width of the
      //  second column is reduced to mantain the same distance between columns.
      //
      if (i == 10)
      {
        fixed_width--;
      }
      std::cout << std::left << "CPU" << unsigned(i);
      std::cout << std::setprecision(1) << std::fixed;
      std::cout << std::setw(fixed_width) << std::right << cpu[i].get_cpu_busy_pct() << "%";
      std::cout << std::setw(10) << std::right << cpu[i].get_cpu_nice_pct() << "%";
      std::cout << std::setw(11) << std::right << cpu[i].get_cpu_system_pct() << "%";
      std::cout << std::setw(11) << std::right << cpu[i].get_cpu_idle_pct() << "%" << std::endl;
    }
    std::cout << "-------------------------------------------------------" << std::endl;
    //
    //  Some machines do not provide the information about page and swap within the file,
    //  so the float precision is changed to display only two decimals instead of six.
    //
    if (system.get_page_ratio() == 0)
    {
      fixed_precision = 1;
    }
    //
    //  Display the general system information.
    //
    std::cout << std::setprecision(fixed_precision) << std::fixed;
    std::cout << std::left << "Page in/out ratio: " << system.get_page_ratio() << std::endl;
    std::cout << "Swap in/out ratio: " << system.get_swap_ratio() << std::endl;
    std::cout << "Interrupts serviced: " << system.get_intr_serviced() << std::endl;
    std::cout << "Context switch count: " << system.get_ctxt_switch_count() << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;

    //
    //  Delay the program execution for 0.5 seconds
    //  and then close the file.
    //
    usleep(500000);
    fs.close();
  }

  //
  //  If the file is still open, close it.
  //
  if (fs.is_open())
  {
    fs.close();
  }

  //
  //  Free the memory previously allocated
  //  for the array of Cpu objects.
  //
  delete [] cpu;

  return 0;
}
