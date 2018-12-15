//*****************************************************************************
//
//  Newcastle University
//  EEE8126 - Embedded Systems and Programming
//  Project 1: Real-time parsing using c++ pointers and structures/classes.
//  -------------------------------------------------------------------------
//  File:     parser.h
//  Author:   Ronald Rodriguez Ruiz.
//  Date:     December 6, 2018.
//
//*****************************************************************************

#ifndef __PARSER_H__
#define __PARSER_H__

namespace procstat
{

  //*****************************************************************************
  //
  //  Strong type enumeration for the "/proc/stat" file labels.
  //
  //*****************************************************************************
  enum class Label : uint8_t
  {
    Cpu,
    Page,
    Swap,
    Intr,
    Ctxt,
    Btime
  };

  //*****************************************************************************
  //
  //  Parser class.
  //  This class handles the parsing requests for the "/proc/stat" file lines.
  //  The file lines are parse one at the time, and the label and data can be
  //  accessed through getter methods. IMPORTANT: The get_label and get_data
  //  methods should be called right away after the parse_string, otherwise its
  //  values will be overwritten by sequential calls to the parse_string method.
  //
  //*****************************************************************************
  class Parser
  {
    public:
      //
      //  Constructor.
      //
      Parser();

      //
      //  Getter methods for the file line elements.
      //
      enum Label get_label();
      uint64_t* get_data();

      //
      //  String parser method.
      //
      void parse_string(const std::string &line);
    private:
      Label label;
      uint64_t data[4];
      const std::string labels[6];
  };
}

#endif  // __PARSER_H__
