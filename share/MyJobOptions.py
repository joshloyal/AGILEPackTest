from AthenaCommon.AlgSequence import AlgSequence

job = AlgSequence()

from AGILEPackTest.AGILEPackTestConf import AgileTest
job += AgileTest( "AGILEPackTest" )

job.AGILEPackTest.OutputLevel = INFO
job.AGILEPackTest.data   = "training_ntuple.root"  
job.AGILEPackTest.ntuple = "test_ntup"
job.AGILEPackTest.calib  = "VHbb_tagger.yaml"

theApp.EvtMax = 1
