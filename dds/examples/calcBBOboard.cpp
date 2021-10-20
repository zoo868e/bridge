/*
   DDS, a bridge double dummy solver.

   Copyright (C) 2006-2014 by Bo Haglund /
   2014-2016 by Bo Haglund & Soren Hein.

   See LICENSE and README.
*/


// Test program for the CalcAllTablesPBN function.
// Uses the hands pre-set in hands.cpp.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/dll.h"
#include "hands.h"
#include <fstream>
#include <iostream>


int main(int argc, char *argv[])
{
  ddTableDealsPBN DDdealsPBN;
  ddTablesRes tableRes;
  allParResults pres;
  std::ifstream readPBN(argv[1]);
  char buffer[80] = {0};
  readPBN.getline(buffer, sizeof(buffer));

  int mode = 0; // No par calculation
  int trumpFilter[DDS_STRAINS] = {0, 0, 0, 0, 0}; // All
  int res;
  char line[80];
  bool match;

#if defined(__linux) || defined(__APPLE__)
  SetMaxThreads(0);
#endif

  DDdealsPBN.noOfTables = 1;
  while(readPBN.getline(buffer, sizeof(buffer))){
      if(buffer[0] == 'P' || (buffer[0] >= '0' && buffer[0] <= '9')){
        std::cout << buffer << std::endl;
        continue;
      }
      else
        strcpy(DDdealsPBN.deals[0].cards, buffer);
      res = CalcAllTablesPBN(&DDdealsPBN, mode, trumpFilter, &tableRes, &pres);
      if (res != RETURN_NO_FAULT){
          ErrorMessage(res, line);
          printf("DDS error: %s\n", line);
      }
    // PrintPBNHand(line, DDdealsPBN.deals[0].cards);
    std::cout << buffer << "|";
    // cout the result order = 
//           North East  South West 
//    NT     40     41    42    43
//     S     00     01    02    03
//     H     10     11    12    13
//     D     20     21    22    23
//     C     30     31    32    33
    int iflag = 0;
    for(int i = 0;i < 5;i++){
        if(iflag > 0){
            std::cout << "@";
        }
        int jflag = 0;
        for(int j = 0;j < 4;j++){
            if(jflag > 0){
                std::cout << ",";
            }
            std::cout << tableRes.results[0].resTable[i][j];
            jflag++;
        }
        iflag++;
    }
    std::cout << std::endl;
    // PrintTable(&tableRes.results[0]);
  }
  readPBN.close();
}

