
# OverlapTool

This tool calculates trigger overlaps (and PD overlaps) for a CMS triggering emulator. 


A comment about the event sizes: The event size \<\<in a given PD\>\> is calculated in two ways. First, for events that fire two (or more) different triggers, it averages the event sizes of the various triggers that fired (this is labeled "estimated average event size").  Alternatively, it simply takes the largest event size of all triggers that fired that event (this is labeled "estimated max evt size").

To run it, you'll need a text file with triggers, prescales, and PDs in it. 
see ExampleInputFile.txt

you can run it by 

```` 
./GenerateOverlapInputs.py <ExampleInputFile.txt> 

--mytag <base_output_name> 

--HltTreePath <path_to_HltTree_file> 


optional:    --rate <full_rate>  --nEvents 100  --customrootpath <path_to_root>  --SetAllEvtSizes <100>  --verbosity <0 or 1>  --debug <0 or 1>

```` 

'--mytag' is simply to give the output a unique name.  ie. the output would be called Overlaps_base_output_name.root

'--HltTreePath' is the path to your root file containing the HltTree. The tree should be in a TDirectory called 'hltbitanalysis'

'--rate' is your desired raw input collision rate by which the HltTree results get scaled. 

'--nEvents' is the number of HltTree events you want to run over. 

'--customrootpath' point to your preferred root installation

'--SetAllEvtSizes' integer that will be used for the average event size of all paths (and you don't need to supply a last column in the input file).

'--debug', if this is *not* set to 0 then the .C(.h) MakeClass files will be generated but *not* run (you can do it by hand).

=======================================================================
******* INSTRUCTIONS FOR THE 2018 RUN *********************
Steps: 

1) https://docs.google.com/spreadsheets/d/1TknFD6DUsvPEDwc6dLzV2sNIyKPDWjONBped5e9RDnE/edit#gid=1586769811

-- download the sheet with rates and prescales, and dump it in a regular excel sheet, then:

a) add a very last column (after the 60kHz column is inserted), with event content (as in the Rates_nov sheet uploaded as examxple)

b) check all the L1 seeds that they are exactly 1 word 
-- eg.: at the moment, the 2nd dilepton path, L1DoubleMuOpen_OS_Centrality40100 ..., has a composite L1 path, L1_seedA AND L1_seedB --> remove everything that is after 'L1_seedA'  
----- it will nto affect the HLT rate calculation, it's jsut a script-reading problem

c) remove all the HLT paths (whole line) that do NOT exist in the menu run with the input file you want to get rates from

d) don't care about Div/0, but care about all the PS colums (both L1 and HLT) to be properly filled (the extra rates in the table do NOT matter). 

e) After you 'doctored' the excel, save the sheet as Tab delimited Text (txt) (from the EXcel menu)
e.g. rates_nov02.txt


2) Break this huge file, in 1 per each collision rate, in a format that is taken as input by the OverlapTool:

"python sorting.py rates_nov02.txt output_file_prefix"

===> if everything is fine, the screen output will be:
````
python sorting.py Rates_nov3.txt test
('outputfilename: ', 'test')
('Number of PS columns:', 11)
('columns in input file and output file:', 71, 6)
('PS column# ....: ', '8kHz')
('PS column# ....: ', '10kHz')
('PS column# ....: ', '13kHz')
('PS column# ....: ', '16kHz')
('PS column# ....: ', '20kHz')
('PS column# ....: ', '23kHz')
('PS column# ....: ', '26kHz')
('PS column# ....: ', '30kHz')
('PS column# ....: ', '40kHz')
('PS column# ....: ', '50kHz')
('PS column# ....: ', '60kHz')
''''

AND, there will be a bunch of text files in the same directory, with the formatted files:

````
ls -lt *.txt
-rw-r--r--  1 cameliamironov  staff   23302 Nov  8 12:11 test_60kHz.txt
-rw-r--r--  1 cameliamironov  staff   23294 Nov  8 12:11 test_50kHz.txt
-rw-r--r--  1 cameliamironov  staff   23288 Nov  8 12:11 test_40kHz.txt
-rw-r--r--  1 cameliamironov  staff   23279 Nov  8 12:11 test_30kHz.txt
-rw-r--r--  1 cameliamironov  staff   23275 Nov  8 12:11 test_26kHz.txt
-rw-r--r--  1 cameliamironov  staff   23271 Nov  8 12:11 test_23kHz.txt
-rw-r--r--  1 cameliamironov  staff   23275 Nov  8 12:11 test_20kHz.txt
-rw-r--r--  1 cameliamironov  staff   23291 Nov  8 12:11 test_16kHz.txt
-rw-r--r--  1 cameliamironov  staff   23287 Nov  8 12:11 test_13kHz.txt
-rw-r--r--  1 cameliamironov  staff   23280 Nov  8 12:11 test_10kHz.txt
-rw-r--r--  1 cameliamironov  staff   23295 Nov  8 12:11 test_8kHz.txt
''''

3) Run the overlap tool. There is a script in which you provide all the info:
-- an input file (data or MC, it doesn't matter), BUT, for 'MB triggered events' (so PS for MB=1, or, each event triggered the MB trigger)
-- the number of events to process (250K set as default)
-- the prefix of the input files ("test" in the above case)
-- the list of columns to process (can also chose start-end of the column, from the list, in case don't want to go through all of them)

-- suggest to direct all the numbers/info the overlap tool is spitting out, into a txt file (see later)

"./makeRateHistos.sh > spitScreen.txt"

-- for the full menu (all trigger paths/pd), takes max 30min for first 8 columns)
-- at the end, there will be 1 root file/collision rate, with histograms containing rate for each trigger and pd, and prescales

4) IF interested in 'SUMMARY' NUMBERS (rate/PD and output_size/PD), run a script on the "spitScreen.txt"

"python readOutput.py spitScreen.txt simpleOut"

---> have 3 txt spit out:
````
ls -lt simpleOut_pd*
-rw-r--r--  1 cameliamironov  staff  831 Nov  6 13:28 simpleOut_pdsizeave.txt
-rw-r--r--@ 1 cameliamironov  staff  798 Nov  6 13:28 simpleOut_pdsize.txt
-rw-r--r--@ 1 cameliamironov  staff  473 Nov  6 13:28 simpleOut_pdrate.txt
''''

The content can be put in an excel sheet, as the one uploaded here, called "summary_2018PDs"

5) IF interested in PD overlap plots (with overlaps plotted as % or as absolute), run the drawing macro (draw.C). There is a script, which, given the output root files from step (3) are in the same directories, provide this.
-- can chose the CR for which you want this made
-- to save time, instead of doing also the trigger overlaps (which takes a LOT of time), the main loop inside the draw starts at 1 (  for(int a=1; a<nHistPlot;a++)
 ). To get trigger overlap change to '0')'

"./makePlots.sh"



=============
If you just want to do a short test, few events, 1 CR, smth simple, to run directly the overlapTool the command line is in run.sh script
