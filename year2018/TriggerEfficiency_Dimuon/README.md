This code creates trigger efficiency plots.
to run this code follow these instructions:
root -l
.L makeTrigEff.C+
oniaTree t ("Gbv35LowPtJpsi") //this label corresponds to a certain tree. The name represents the sample and the HLT menu. You can find the different possibilities in makeTrigEff.h
t.AllEffCalc()  //This function produces root files for all the efficiecny histograms corresponding to all the triggers in the HLT menus. To choose one specific trigger use TrigEffCalc("HLT_HIL1DoubleMuOpen")

//////// To nicely plot different combinations of turn-on curves together you have to first make adirectiory called "InputFiles" which has .txt files with the names of the triggers you want to plot (see the example here). The first line needs to include the tree label (you can see the different possibilities in makeTrigEff.h) then each line has the name of the trigger. after this you continues in root:
t.Plot("input_LowPtJpsi_L3MuX_L2MuY_HLTv28") //don't put "InputFiles/" or ".txt"
///you can also use t.plotAll()
