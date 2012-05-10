#--------------------------------------------------------------------------
# File and Version Information:
#  $Id: dump_simple.py 2622 2011-11-11 14:35:00Z salnikov@SLAC.STANFORD.EDU $
#
# Description:
#  Class DumpAcqiris...
#
# Author List:
#  Joseph S. Barrera III
#------------------------------------------------------------------------

"""Example module for accessing SharedIpimb data.

This software was developed for the LCLS project.  If you use all or 
part of it, please give an appropriate acknowledgment.

@version $Id: dump_simple.py 2622 2011-11-11 14:35:00Z salnikov@SLAC.STANFORD.EDU $

@author Joseph S. Barrera III
"""

#------------------------------
#  Module's version from SVN --
#------------------------------
__version__ = "$Revision: 2622 $"
# $Source$

#--------------------------------
#  Imports of standard modules --
#--------------------------------
import sys
import logging

#-----------------------------
# Imports for other modules --
#-----------------------------
from pypdsdata import xtc

#----------------------------------
# Local non-exported definitions --
#----------------------------------

# local definitions usually start with _

#---------------------
#  Class definition --
#---------------------
class DumpAcqiris (object) :
    """Class whose instance will be used as a user analysis module. """

    #----------------
    #  Constructor --
    #----------------
    def __init__ ( self, source="" ) :
        self.m_src = source

    #-------------------
    #  Public methods --
    #-------------------
    def beginCalibCycle( self, evt, env ) :

        print "in beginCalibCycle()"

        print "jobName=", env.jobName()
        print "instrument=", env.instrument()
        print "experiment=", env.experiment()
        print "expNum=", env.expNum()
        print "calibDir=", env.calibDir()

        print "self.m_src = %s" % (self.m_src)

        self.source = env.configStr("source", "DetInfo(:Acqiris)")
        config = env.getConfig("Psana::Acqiris::ConfigV1", self.source)

        if config:
        
            print "%s: %s" % (config.__class__.__name__, self.m_src)
            
            print "  nbrBanks =", config.nbrBanks(),
            print "channelMask =", config.channelMask(),
            print "nbrChannels =", config.nbrChannels(),
            print "nbrConvertersPerChannel =", config.nbrConvertersPerChannel()
     
            h = config.horiz()
            print "  horiz: sampInterval =", h.sampInterval(),
            print "delayTime =", h.delayTime(),
            print "nbrSegments =", h.nbrSegments(),
            print "nbrSamples =", h.nbrSamples()

            nch = config.nbrChannels()
            """
            for ch in range(nch):
                v = config.vert2(ch)
                print "  vert(%d):" % ch,
                print "fullScale =", v.fullScale(),
                print "slope =", v.slope(),
                print "offset =", v.offset(),
                print "coupling =", v.coupling(),
                print "bandwidth=", v.bandwidth()
            """

    def event(self, evt, env):
        acqData = evt.getData("Psana::Acqiris::DataDescV1", self.source)
        if acqData:

            # find matching config object
            acqConfig = env.getConfig("Psana::Acqiris::ConfigV1", self.source)

            # loop over channels
            nchan = acqData.data_shape()[0];
            for chan in range(nchan):
                print "chan=", chan

                elem = acqData.data(chan);
                print "elem=", elem

                v_array = acqConfig.vert();
                """
                v = v_array.at(chan);
                print "v=", v
                slope = v.slope();
                print "slope=", slope
                offset = v.offset();
                print "offset=", offset
                """

                # WithMsgLog(name(), info, str ) {
                if True:

                    s = "Acqiris::DataDescV1: channel=" + str(chan)
                    s = s + "\n  nbrSegments=" + str(elem.nbrSegments())
                    s = s + "\n  nbrSamplesInSeg=" + str(elem.nbrSamplesInSeg())
                    s = s + "\n  indexFirstPoint=" + str(elem.indexFirstPoint())
                    print s

        pass

    def endJob( self, evt, env ) :
        pass