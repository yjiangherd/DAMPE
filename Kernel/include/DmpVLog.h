/*
 *  $Id: DmpVLog.h, 2014-04-15 20:53:59 chi $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 08/04/2014
*/

#ifndef DmpVLog_H
#define DmpVLog_H

class DmpVLog{
/*
 *  DmpVLog
 *
 *  all log class derived from here
 *
 */
public:
  DmpVLog():fLevel(0){}
  virtual ~DmpVLog(){}
  virtual void Type(const short&) const=0;      // log type

protected:
  short fLevel;

};

#endif

