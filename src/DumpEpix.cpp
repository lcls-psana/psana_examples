//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id$
//
// Description:
//	Class DumpEpix...
//
// Author List:
//      Andy Salnikov
//
//------------------------------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "psana_examples/DumpEpix.h"

//-----------------
// C/C++ Headers --
//-----------------

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "MsgLogger/MsgLogger.h"
#include "psddl_psana/epix.ddl.h"

//-----------------------------------------------------------------------
// Local Macros, Typedefs, Structures, Unions and Forward Declarations --
//-----------------------------------------------------------------------

// This declares this class as psana module
using namespace psana_examples;
PSANA_MODULE_FACTORY(DumpEpix)

//		----------------------------------------
// 		-- Public Function Member Definitions --
//		----------------------------------------

namespace psana_examples {

//----------------
// Constructors --
//----------------
DumpEpix::DumpEpix (const std::string& name)
  : Module(name)
  , m_src()
{
  m_src = configSrc("source", "DetInfo(:Epix)");
}

//--------------
// Destructor --
//--------------
DumpEpix::~DumpEpix ()
{
}

/// Method which is called at the beginning of the run
void
DumpEpix::beginRun(Event& evt, Env& env)
{
  shared_ptr<Psana::Epix::ConfigV1> config1 = env.configStore().get(m_src);
  if (config1) {
    WithMsgLog(name(), info, str) {
      str << "Psana::Epix::ConfigV1:";
      str << "\n  version = " << config1->version();
      str << "\n  runTrigDelay = " << config1->runTrigDelay();
      str << "\n  daqTrigDelay = " << config1->daqTrigDelay();
      str << "\n  dacSetting = " << config1->dacSetting();
      str << "\n  asicGR = " << int(config1->asicGR());
      str << "\n  asicAcq = " << int(config1->asicAcq());
      str << "\n  asicR0 = " << int(config1->asicR0());
      str << "\n  asicPpmat = " << int(config1->asicPpmat());
      str << "\n  asicPpbe = " << int(config1->asicPpbe());
      str << "\n  asicRoClk = " << int(config1->asicRoClk());
      str << "\n  asicGRControl = " << int(config1->asicGRControl());
      str << "\n  asicAcqControl = " << int(config1->asicAcqControl());
      str << "\n  asicR0Control = " << int(config1->asicR0Control());
      str << "\n  asicPpmatControl = " << int(config1->asicPpmatControl());
      str << "\n  asicPpbeControl = " << int(config1->asicPpbeControl());
      str << "\n  asicR0ClkControl = " << int(config1->asicR0ClkControl());
      str << "\n  prepulseR0En = " << int(config1->prepulseR0En());
      str << "\n  adcStreamMode = " << config1->adcStreamMode();
      str << "\n  testPatternEnable = " << int(config1->testPatternEnable());
      str << "\n  acqToAsicR0Delay = " << config1->acqToAsicR0Delay();
      str << "\n  asicR0ToAsicAcq = " << config1->asicR0ToAsicAcq();
      str << "\n  asicAcqWidth = " << config1->asicAcqWidth();
      str << "\n  asicAcqLToPPmatL = " << config1->asicAcqLToPPmatL();
      str << "\n  asicRoClkHalfT = " << config1->asicRoClkHalfT();
      str << "\n  adcReadsPerPixel = " << config1->adcReadsPerPixel();
      str << "\n  adcClkHalfT = " << config1->adcClkHalfT();
      str << "\n  asicR0Width = " << config1->asicR0Width();
      str << "\n  adcPipelineDelay = " << config1->adcPipelineDelay();
      str << "\n  prepulseR0Width = " << config1->prepulseR0Width();
      str << "\n  prepulseR0Delay = " << config1->prepulseR0Delay();
      str << "\n  digitalCardId0 = " << config1->digitalCardId0();
      str << "\n  digitalCardId1 = " << config1->digitalCardId1();
      str << "\n  analogCardId0 = " << config1->analogCardId0();
      str << "\n  analogCardId1 = " << config1->analogCardId1();
      str << "\n  lastRowExclusions = " << config1->lastRowExclusions();
      str << "\n  numberOfAsicsPerRow = " << config1->numberOfAsicsPerRow();
      str << "\n  numberOfAsicsPerColumn = " << config1->numberOfAsicsPerColumn();
      str << "\n  numberOfRowsPerAsic = " << config1->numberOfRowsPerAsic();
      str << "\n  numberOfPixelsPerAsicRow = " << config1->numberOfPixelsPerAsicRow();
      str << "\n  baseClockFrequency = " << config1->baseClockFrequency();
      str << "\n  asicMask = " << config1->asicMask();
      str << "\n  numberOfRows = " << config1->numberOfRows();
      str << "\n  numberOfColumns = " << config1->numberOfColumns();
      str << "\n  numberOfAsics = " << config1->numberOfAsics();
      str << "\n  asicPixelTestArray = " << config1->asicPixelTestArray();
      str << "\n  asicPixelMaskArray = " << config1->asicPixelMaskArray();

      const int nasics = config1->numberOfAsics();
      for (int i = 0; i != nasics; ++ i) {
        const Psana::Epix::AsicConfigV1& aconfig = config1->asics(i);
        str << "\n    Psana::Epix::AsicConfigV1 #" << i << ":";
        str << "\n      monostPulser = " << int(aconfig.monostPulser());
        str << "\n      dummyTest = " << int(aconfig.dummyTest());
        str << "\n      dummyMask = " << int(aconfig.dummyMask());
        str << "\n      pulser = " << int(aconfig.pulser());
        str << "\n      pbit = " << int(aconfig.pbit());
        str << "\n      atest = " << int(aconfig.atest());
        str << "\n      test = " << int(aconfig.test());
        str << "\n      sabTest = " << int(aconfig.sabTest());
        str << "\n      hrTest = " << int(aconfig.hrTest());
        str << "\n      digMon1 = " << int(aconfig.digMon1());
        str << "\n      digMon2 = " << int(aconfig.digMon2());
        str << "\n      pulserDac = " << int(aconfig.pulserDac());
        str << "\n      Dm1En = " << int(aconfig.Dm1En());
        str << "\n      Dm2En = " << int(aconfig.Dm2En());
        str << "\n      slvdSBit = " << int(aconfig.slvdSBit());
        str << "\n      VRefDac = " << int(aconfig.VRefDac());
        str << "\n      TpsTComp = " << int(aconfig.TpsTComp());
        str << "\n      TpsMux = " << int(aconfig.TpsMux());
        str << "\n      RoMonost = " << int(aconfig.RoMonost());
        str << "\n      TpsGr = " << int(aconfig.TpsGr());
        str << "\n      S2dGr = " << int(aconfig.S2dGr());
        str << "\n      PpOcbS2d = " << int(aconfig.PpOcbS2d());
        str << "\n      Ocb = " << int(aconfig.Ocb());
        str << "\n      Monost = " << int(aconfig.Monost());
        str << "\n      FastppEnable = " << int(aconfig.FastppEnable());
        str << "\n      Preamp = " << int(aconfig.Preamp());
        str << "\n      PixelCb = " << int(aconfig.PixelCb());
        str << "\n      S2dTComp = " << int(aconfig.S2dTComp());
        str << "\n      FilterDac = " << int(aconfig.FilterDac());
        str << "\n      TC = " << int(aconfig.TC());
        str << "\n      S2d = " << int(aconfig.S2d());
        str << "\n      S2dDacBias = " << int(aconfig.S2dDacBias());
        str << "\n      TpsTcDac = " << int(aconfig.TpsTcDac());
        str << "\n      TpsDac = " << int(aconfig.TpsDac());
        str << "\n      S2dTcDac = " << int(aconfig.S2dTcDac());
        str << "\n      S2dDac = " << int(aconfig.S2dDac());
        str << "\n      TestBe = " << int(aconfig.TestBe());
        str << "\n      IsEn = " << int(aconfig.IsEn());
        str << "\n      DelExec = " << int(aconfig.DelExec());
        str << "\n      DelCckReg = " << int(aconfig.DelCckReg());
        str << "\n      RowStartAddr = " << int(aconfig.RowStartAddr());
        str << "\n      RowStopAddr = " << int(aconfig.RowStopAddr());
        str << "\n      ColStartAddr = " << int(aconfig.ColStartAddr());
        str << "\n      ColStopAddr = " << int(aconfig.ColStopAddr());
        str << "\n      chipID = " << int(aconfig.chipID());
      }
    }
  }
}

/// Method which is called with event data, this is the only required 
/// method, all other methods are optional
void 
DumpEpix::event(Event& evt, Env& env)
{
  Pds::Src actualSrc;
  shared_ptr<Psana::Epix::ElementV1> data1 = evt.get(m_src, "", &actualSrc);
  if (data1) {

    WithMsgLog(name(), info, str) {
      str << "Epix::ElementV1 at " << actualSrc;
      str << "\n  vc = " << int(data1->vc());
      str << "\n  lane = " << int(data1->lane());
      str << "\n  acqCount = " << data1->acqCount();
      str << "\n  frameNumber = " << data1->frameNumber();
      str << "\n  ticks = " << data1->ticks();
      str << "\n  fiducials = " << data1->fiducials();
      str << "\n  frame = " << data1->frame();
      str << "\n  excludedRows = " << data1->excludedRows();
      str << "\n  temperatures = " << data1->temperatures();
      str << "\n  lastWord = " << data1->lastWord();
    }
  }
}

} // namespace psana_examples