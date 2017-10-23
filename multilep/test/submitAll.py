#!/usr/bin/env python
import os, glob, sys

datasetsFile    = sys.argv[1]                                                                             # Input file with datasets
productionLabel = os.path.basename(datasetsFile.split('.')[0].split('/')[-1])                             # Label to keep track of the tuple version (is taken from the name of the above input file)
outDir          = '/user/' + os.environ['USER'] + '/public/heavyNeutrino'                                 # Output directory in case of local submission
datasets        = [dataset.strip() for dataset in open(datasetsFile)]                                     # Get list of datasets from file given as first argument
datasets        = [dataset.split()[0] for dataset in datasets if dataset and not dataset.startswith('#')] # Clean empty and comment lines
groupFiles      = 1                                                                                       # Group files together when running locally

#check if call asked for local submission
submitLocal     = sys.argv[2]
#Use third argument to specify the number of jobs per file
filesPerJob     = sys.argv[3]

for dataset in datasets:
  outputName, dataset = dataset.split(':')

  if 'pnfs' in dataset or 'user' in dataset or submitLocal: 
      dir        = os.getcwd()
      outputFile = os.path.join(outDir, datasetName, 'local_' + productionLabel, outputName + '_' + str(i) + '.root')
      outputDir = outDir + dataset.split('/')[-1]      
      outputFile = 
      #find way to give skim conditon (determined by outPutName) to bash script
      os.system('bash runLocal.sh ' + dataset + ' ' + outputDir + ' ' + filesPerJob + ' ' + outputName)
  else: # use crab
    print 'Submitting ' + dataset + ' using crab:'
    os.environ['CRAB_PRODUCTIONLABEL'] = productionLabel
    os.environ['CRAB_DATASET']         = dataset
    os.environ['CRAB_OUTPUTFILE']      = outputName + '.root'
    os.system('crab submit -c crab.py')

