/*! 
 * @ file to analysis application node 
 * @ sample cpu usage \ memory usage 
 * @
 *
 */

#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <thread>

#include <iostream>
#include <string>
#include <vector>
#include "glog/logging.h"

namespace common {

const char Kpscommand[] = "ps axu|grep ";
const char Kawkcommand[] =  "  |grep -v \"grep\"| awk -F\" \"  '{print $3,$4,$6}' ";
const int KCpupos = 0;
const int KMempos = 1;
const int KRsspos = 2;
const int KUsagelen = 3;

class LoadAnalysis {
 public:
  /*
   * @brief construct function
   * @date JAN/16/2022
   * @
   */
  LoadAnalysis() {
    proccess_pid_ = getpid();
  }

  /*
   * @brief deconstruct function
   * @date JAN/16/2022
   * @
   */
  virtual ~LoadAnalysis() {
     analysis_flag_ = false; //  stop analysis
  }

  /*
   * @brief init sample rate 
   * @param[in] sleeptime ,  sample rate
   * @parma[in] flag ,  to start run analysis
   * @param[return] void 
   * @
   * @
   */
  void Init(int sleeptime, bool flag) {
    resttime_ = sleeptime;
    analysis_flag_ = flag;
  }

  /*   
   * @brief start rate proccess cpu \mem \rss 
   * @param[out] void 
   * @date Jan/16/2022
   * @author dc_neo(yan.zhang)
   */
void StartAnalysis() { 
  char resultdata[128] = {}; 
  std::string execcmd = std::string(Kpscommand) + std::to_string(proccess_pid_) +
     std::string(Kawkcommand);
  LOG(INFO) << "To popen --" << execcmd << "\n";
  std::string valcmd;
  while (analysis_flag_) {
    FILE* fp = nullptr;
    fp = popen(execcmd.c_str(), "r");
    if (fp == nullptr) {
        LOG(FATAL) << "find have proccess id ,no reason to come here\n";
    } else {
      if (fgets(resultdata, sizeof(resultdata), fp) != nullptr) {
        valcmd = resultdata;
        valcmd = valcmd.replace(valcmd.find("\n"), 1, "");
        std::vector<std::string> vusage;
        StringSplit(&valcmd, vusage);
        if (vusage.size() == KUsagelen) {
          LOG(INFO) << "pid:" << proccess_pid_ << ":CPU usage:" 
              << vusage[KCpupos] << ":MEM usage:" << vusage[KMempos]
              << ":Rss:" << vusage[KRsspos];
        }
      } else {
          LOG(ERROR) << "-----ps command execute failed--------fatata error \n";
      }
    }
    pclose(fp);
    std::this_thread::sleep_for(std::chrono::seconds(resttime_));
    }
  }

  /*   
   * @brief stop run analysis
   * @param[out] void 
   * @date Jan/16/2022
   *
 */ 
  void StopAnalysis() {
     analysis_flag_ = false;
  }

 private:
  /*
   * @brief init sample rate 
   * @param[in] str ,  string to be split by " " 
   * @param[out] vdest , cpu \mem\rss 
   * @param[return] void 
   */
   void StringSplit(std::string* pstr, std::vector<std::string>& vdest) {
     size_t pos = 0;
     size_t strlen = pstr->length();
     if (strlen != 0) {
        while (pos < strlen) {
          int find_pos = pstr->find(" ", pos);
          if (find_pos < 0) {
            vdest.push_back(pstr->substr(pos, strlen - pos));
            break;
         } 
         vdest.push_back(pstr->substr(pos, find_pos - pos));
         pos = find_pos + 1; 
        }    
    }  
  }

 private:
  bool analysis_flag_; 
  int proccess_pid_;
  int resttime_;
};

}  //  namespace common
