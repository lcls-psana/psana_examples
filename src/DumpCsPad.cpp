//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id$
//
// Description:
//	Class DumpCsPad...
//
// Author List:
//      Andrei Salnikov
//
//------------------------------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "psana_examples/DumpCsPad.h"

//-----------------
// C/C++ Headers --
//-----------------
#include <algorithm>
#include <iomanip>
#include <iterator>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "MsgLogger/MsgLogger.h"
#include "psddl_psana/cspad.ddl.h"

//-----------------------------------------------------------------------
// Local Macros, Typedefs, Structures, Unions and Forward Declarations --
//-----------------------------------------------------------------------

using namespace psana_examples;
PSANA_MODULE_FACTORY(DumpCsPad)

//		----------------------------------------
// 		-- Public Function Member Definitions --
//		----------------------------------------

namespace psana_examples {

//----------------
// Constructors --
//----------------
DumpCsPad::DumpCsPad (const std::string& name)
  : Module(name)
{
  m_src = configStr("source", "DetInfo(:Cspad)");
}

//--------------
// Destructor --
//--------------
DumpCsPad::~DumpCsPad ()
{
}

/// Method which is called at the beginning of the calibration cycle
void 
DumpCsPad::beginCalibCycle(Env& env)
{
  MsgLog(name(), trace, "in beginCalibCycle()");

  shared_ptr<Psana::CsPad::ConfigV1> config1 = env.configStore().get(m_src);
  if (config1.get()) {
    
    WithMsgLog(name(), info, str) {
      str << "CsPad::ConfigV1:";
      str << "\n  concentratorVersion = " << config1->concentratorVersion();
      str << "\n  runDelay = " << config1->runDelay();
      str << "\n  eventCode = " << config1->eventCode();
      str << "\n  inactiveRunMode = " << config1->inactiveRunMode();
      str << "\n  activeRunMode = " << config1->activeRunMode();
      str << "\n  tdi = " << config1->tdi();
      str << "\n  payloadSize = " << config1->payloadSize();
      str << "\n  badAsicMask0 = " << config1->badAsicMask0();
      str << "\n  badAsicMask1 = " << config1->badAsicMask1();
      str << "\n  asicMask = " << config1->asicMask();
      str << "\n  quadMask = " << config1->quadMask();
      str << "\n  numAsicsRead = " << config1->numAsicsRead();
      str << "\n  numQuads = " << config1->numQuads();
      str << "\n  numSect = " << config1->numSect();
    }
    
  }

  shared_ptr<Psana::CsPad::ConfigV2> config2 = env.configStore().get(m_src);
  if (config2.get()) {
    
    WithMsgLog(name(), info, str) {
      str << "CsPad::ConfigV2:";
      str << "\n  concentratorVersion = " << config2->concentratorVersion();
      str << "\n  runDelay = " << config2->runDelay();
      str << "\n  eventCode = " << config2->eventCode();
      str << "\n  inactiveRunMode = " << config2->inactiveRunMode();
      str << "\n  activeRunMode = " << config2->activeRunMode();
      str << "\n  tdi = " << config2->tdi();
      str << "\n  payloadSize = " << config2->payloadSize();
      str << "\n  badAsicMask0 = " << config2->badAsicMask0();
      str << "\n  badAsicMask1 = " << config2->badAsicMask1();
      str << "\n  asicMask = " << config2->asicMask();
      str << "\n  quadMask = " << config2->quadMask();
      str << "\n  numAsicsRead = " << config2->numAsicsRead();
      str << "\n  numQuads = " << config2->numQuads();
      str << "\n  numSect = " << config2->numSect();
      str << "\n  roiMask =";
      for (unsigned i = 0; i < config2->numQuads(); ++ i) {
        str.setf(std::ios::showbase);
        str << ' ' << std::hex << config2->roiMask(i) << std::dec;
      }
      str << "\n  numAsicsStored =";
      for (unsigned i = 0; i < config2->numQuads(); ++ i) {
        str << ' ' << config2->numAsicsStored(i);
      }
    }
    
  }
}

/// Method which is called with event data, this is the only required 
/// method, all other methods are optional
void 
DumpCsPad::event(Event& evt, Env& env)
{

  shared_ptr<Psana::CsPad::DataV1> data1 = evt.get(m_src);
  if (data1.get()) {
    
    WithMsgLog(name(), info, str) {
      str << "CsPad::DataV1:";
      int nQuads = data1->quads_shape()[0];
      for (int q = 0; q < nQuads; ++ q) {
        const Psana::CsPad::ElementV1& el = data1->quads(q);
        str << "\n  Element #" << q ;
        str << "\n    virtual_channel = " << el.virtual_channel() ;
        str << "\n    lane = " << el.lane() ;
        str << "\n    tid = " << el.tid() ;
        str << "\n    acq_count = " << el.acq_count() ;
        str << "\n    op_code = " << el.op_code() ;
        str << "\n    quad = " << el.quad() ;
        str << "\n    seq_count = " << el.seq_count() ;
        str << "\n    ticks = " << el.ticks() ;
        str << "\n    fiducials = " << el.fiducials() ;
        str << "\n    frame_type = " << el.frame_type() ;
        str << "\n    sb_temp = [ ";
        const uint16_t* sb_temp = el.sb_temp();
        std::copy(sb_temp, sb_temp+Psana::CsPad::ElementV1::Nsbtemp, 
            std::ostream_iterator<uint16_t>(str, " "));
        str << "]";
      }

    }
  }


  shared_ptr<Psana::CsPad::DataV2> data2 = evt.get(m_src);
  if (data2.get()) {
    
    WithMsgLog(name(), info, str) {
      str << "CsPad::DataV2:";
      int nQuads = data2->quads_shape()[0];
      for (int q = 0; q < nQuads; ++ q) {
        const Psana::CsPad::ElementV2& el = data2->quads(q);
        str << "\n  Element #" << q ;
        str << "\n    virtual_channel = " << el.virtual_channel() ;
        str << "\n    lane = " << el.lane() ;
        str << "\n    tid = " << el.tid() ;
        str << "\n    acq_count = " << el.acq_count() ;
        str << "\n    op_code = " << el.op_code() ;
        str << "\n    quad = " << el.quad() ;
        str << "\n    seq_count = " << el.seq_count() ;
        str << "\n    ticks = " << el.ticks() ;
        str << "\n    fiducials = " << el.fiducials() ;
        str << "\n    frame_type = " << el.frame_type() ;
        str << "\n    sb_temp = [ ";
        const uint16_t* sb_temp = el.sb_temp();
        std::copy(sb_temp, sb_temp+Psana::CsPad::ElementV2::Nsbtemp, 
            std::ostream_iterator<uint16_t>(str, " "));
        str << "]";
      }

    }
  }

}

} // namespace psana_examples