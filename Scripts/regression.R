## Collect arguments
args <- commandArgs( TRUE )
 
## Default setting when no arguments passed
if(length(args) < 1){
	args <- c("--no input file")
}

#Get filelist from two folders
inputFileName1 = list.files(args[1])
outputName = args[2]
print("Start preprocessing")
outVar = "FPKM"
if(!file.exists(outputName)){
	dir.create(outputName, showWarnings = FALSE)
}
print("Preprocessing done")
print("Start regression")
homePath = path.expand("~")
outPath = paste0(homePath, "/EpigeneticsTools/", outputName)
cmd = paste0("Rscript HGSB_Regressor.R --outP=", outPath, " --dataDir=", args[1], " --out_var=", outVar, " --nworkers=10 --Alpha=0.01 --Testsize=0.2 --Nfolds=6 --TestCV=2 --model=C" )
system(cmd)

print("Generate report")
library(knitr)
outDir = paste0(homePath, "/EpigeneticsTools/", outputName)
sampleFile = paste0(outDir, "/Your_Regression_Result/Sample_View.csv")
source("regressionPlots.R")


knit2html("KeyTFsReport.Rmd")
htmlFile = paste0(outDir, "/KeyTFsReport.html")
file.copy("KeyTFsReport.html", htmlFile, overwrite = TRUE)
unlink("KeyTFsReport.html")
#After all result files are generated. We will copy the output dir from outPath to result dir under project dir. This step will be done by GUI.
