#--------------------------------------------------------------------------
# File and Version Information:
#  $Id: dump_acqiris.py 2622 2011-11-11 14:35:00Z salnikov@SLAC.STANFORD.EDU $
#
# Description:
#  Pyana user analysis module dump_princeton...
#
#------------------------------------------------------------------------

"""Example module for accessing SharedIpimb data.

This software was developed for the LCLS project.  If you use all or 
part of it, please give an appropriate acknowledgment.

@version $Id: dump_acqiris.py 2622 2011-11-11 14:35:00Z salnikov@SLAC.STANFORD.EDU $

@author Andy Salnikov
"""
from __future__ import print_function

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
from psana import *

#----------------------------------
# Local non-exported definitions --
#----------------------------------

# local definitions usually start with _

#---------------------
#  Class definition --
#---------------------
class dump_acqiris (object) :
    """Class whose instance will be used as a user analysis module. """

    #----------------
    #  Constructor --
    #----------------
    def __init__ ( self ) :
        
        self.m_src = self.configSrc('source', "")

    #-------------------
    #  Public methods --
    #-------------------
    def beginjob( self, evt, env ) :
        
        config = env.configStore().get(Acqiris.Config, self.m_src)
        if config:
        
            print("%s: %s" % (config.__class__.__name__, self.m_src))
            
            print("  nbrBanks =", config.nbrBanks(), end=' ')
            print("channelMask =", config.channelMask(), end=' ')
            print("nbrChannels =", config.nbrChannels(), end=' ')
            print("nbrConvertersPerChannel =", config.nbrConvertersPerChannel())
     
            h = config.horiz()
            print("  horiz: sampInterval =", h.sampInterval(), end=' ')
            print("delayTime =", h.delayTime(), end=' ')
            print("nbrSegments =", h.nbrSegments(), end=' ')
            print("nbrSamples =", h.nbrSamples())

            nch = config.nbrChannels()
            vert = config.vert()
            for ch in range(nch):
                v = vert[ch]
                print("  vert(%d):" % ch, end=' ')
                print("fullScale =", v.fullScale(), end=' ')
                print("slope =", v.slope(), end=' ')
                print("offset =", v.offset(), end=' ')
                print("coupling =", v.coupling(), end=' ')
                print("bandwidth=", v.bandwidth())

    def event( self, evt, env ) :
        """This method is called for every L1Accept transition.

        @param evt    event data object
        @param env    environment object
        """

        acqData = evt.get(Acqiris.DataDesc, self.m_src)
        if not acqData:
            return

        # find matching config object
        config = env.configStore().get(Acqiris.Config, self.m_src)

        # loop over channels
        nchan = acqData.data_shape()[0];
        for chan in range(nchan):
            
            elem = acqData.data(chan);
            v = config.vert()[chan]
            slope = v.slope()
            offset = v.offset()

            print("Acqiris::DataDescV1: channel=%d" % chan) ### XXX should print real class name instead
            print("  nbrSegments=%d" % elem.nbrSegments())
            print("  nbrSamplesInSeg=%d" % elem.nbrSamplesInSeg())
            print("  indexFirstPoint=%d" % elem.indexFirstPoint())

            timestamps = elem.timestamp()
            raw = elem.waveforms()
            wf = raw*slope + offset

            # loop over segments
            for seg in range(elem.nbrSegments()):
                print("  Segment #%d" % seg)
                print("    timestamp =", timestamps[seg].pos())
                print("    raw =", raw[seg])
                print("    wf =", wf[seg])
