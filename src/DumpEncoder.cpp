//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id$
//
// Description:
//	Class DumpEncoder...
//
// Author List:
//      Andrei Salnikov
//
//------------------------------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "psana_examples/DumpEncoder.h"

//-----------------
// C/C++ Headers --
//-----------------
#include <iomanip>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "MsgLogger/MsgLogger.h"
#include "psddl_psana/encoder.ddl.h"

//-----------------------------------------------------------------------
// Local Macros, Typedefs, Structures, Unions and Forward Declarations --
//-----------------------------------------------------------------------

using namespace psana_examples;
PSANA_MODULE_FACTORY(DumpEncoder)

//		----------------------------------------
// 		-- Public Function Member Definitions --
//		----------------------------------------

namespace psana_examples {

//----------------
// Constructors --
//----------------
DumpEncoder::DumpEncoder (const std::string& name)
  : Module(name)
{
  m_src = configSrc("source", "DetInfo(:Encoder)");
}

//--------------
// Destructor --
//--------------
DumpEncoder::~DumpEncoder ()
{
}

// Method which is called at the beginning of the calibration cycle
void 
DumpEncoder::beginCalibCycle(Event& evt, Env& env)
{
  MsgLog(name(), trace, "in beginCalibCycle()");

  shared_ptr<Psana::Encoder::ConfigV1> config1 = env.configStore().get(m_src);
  if (config1) {
    
    WithMsgLog(name(), info, str) {
      str << "Encoder::ConfigV1:";
      str << "\n  chan_num = " << config1->chan_num();
      str << "\n  count_mode = " << config1->count_mode();
      str << "\n  quadrature_mode = " << config1->quadrature_mode();
      str << "\n  input_num = " << config1->input_num();
      str << "\n  input_rising = " << config1->input_rising();
      str << "\n  ticks_per_sec = " << config1->ticks_per_sec();
    }
    
  }

  shared_ptr<Psana::Encoder::ConfigV2> config2 = env.configStore().get(m_src);
  if (config2) {
    
    WithMsgLog(name(), info, str) {
      str << "Encoder::ConfigV1:";
      str << "\n  chan_mask = " << std::hex << std::showbase << config2->chan_mask() << std::dec;
      str << "\n  count_mode = " << config2->count_mode();
      str << "\n  quadrature_mode = " << config2->quadrature_mode();
      str << "\n  input_num = " << config2->input_num();
      str << "\n  input_rising = " << config2->input_rising();
      str << "\n  ticks_per_sec = " << config2->ticks_per_sec();
    }
    
  }
}

// Method which is called with event data
void 
DumpEncoder::event(Event& evt, Env& env)
{
  shared_ptr<Psana::Encoder::DataV1> data1 = evt.get(m_src);
  if (data1) {
    
    WithMsgLog(name(), info, str) {
      str << "Encoder::DataV1:"
          << " timestamp = " << data1->timestamp()
          << " encoder_count = " << data1->encoder_count();
    }
  }

  shared_ptr<Psana::Encoder::DataV2> data2 = evt.get(m_src);
  if (data2) {
    
    WithMsgLog(name(), info, str) {
      str << "Encoder::DataV2:"
          << " timestamp = " << data2->timestamp()
          << " encoder_count = " << data2->encoder_count();
    }
  }

}
  
} // namespace psana_examples
