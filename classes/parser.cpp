//*****************************************************************************
//
//  Newcastle University
//  EEE8126 - Embedded Systems and Programming
//  Project 1: Real-time parsing using c++ pointers and structures/classes.
//  -------------------------------------------------------------------------
//  File:     parser.cpp
//  Author:   Ronald Rodriguez Ruiz.
//  Date:     December 6, 2018.
//
//*****************************************************************************
//
//  Stream class to operate on strings.
//
#include <sstream>
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
#include "parser.h"

namespace procstat
{

  //*****************************************************************************
  //
  //  Constructor: Initilize the labels array with string constants.
  //
  //*****************************************************************************
  Parser::Parser()
    : labels {"cpu", "pag", "swa", "int", "ctx", "btim"}
  {

  }

  //*****************************************************************************
  //
  //  This method parses a file line into a label and data array.
  //
  //*****************************************************************************
  void Parser::parse_string(const std::string &line)
  {
    uint8_t pos = 0;
    std::string label = "";
    std::string data = "";

    //
    //  Clear data buffer.
    //
    for (uint8_t i = 0; i < 4; i++)
    {
      this->data[i] = 0;
    }

    //
    //  Get the label of the line by looping
    //  until the first empty character.
    //
    while (line[pos] != ' ')
    {
      label += line[pos++];
    }

    //
    //  Move to the start of the data, and
    //  build a sub-string from this position.
    //
    data = line.substr(++pos);

    //
    //  Store the first four values from the
    //  current position in a data array.
    //
    std::istringstream ss(data);
    ss >> this->data[0]
        >> this->data[1]
          >> this->data[2]
            >> this->data[3];

    //
    //  Cut the cpu index number by building a sub-string
    //  from the first to the third character of the label.
    //
    label = label.substr(0, 3);

    //
    //  Loop through the labels array to find the matching
    //  label, then assign the corresponding value to the
    //  enumeration label.
    //
    for (uint8_t i = 0; i < 6; i++)
    {
      if (label.compare(this->labels[i]) == 0)
      {
        this->label = static_cast<Label>(i);
      }
    }
  }

  //*****************************************************************************
  //
  //  This method returns a pointer to the data array of the last file line
  //  parsed.
  //
  //*****************************************************************************
  uint64_t* Parser::get_data()
  {
    return this->data;
  }

  //*****************************************************************************
  //
  //  This method returns an enumeration label of the last file line parsed.
  //
  //*****************************************************************************
  enum Label Parser::get_label()
  {
    return this->label;
  }
}
