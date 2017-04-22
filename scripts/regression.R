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
curDir = getwd()
outPath = paste0(curDir, "/", outputName, "/")
cmd = paste0("Rscript HGSB_Regressor_Plus_RegulatorTrail.R --outDir=", outPath, " --dataDir=", args[1], "/ --response=", outVar)
system(cmd)

print("Generate report")
outDir = paste0(curDir, "/", outputName)
sampleFile = paste0(outDir, "/Performance_Overview.txt")
#tfFile = paste0(outDir, "/", list.files(path=outDir, pattern = "Regression_Coefficients_Entire_DataSet"))
source("regressionPlots.R")
library(knitr)
library(Matrix)
knit2html("KeyTFsReport.Rmd")
htmlFile = paste0(outDir, "/KeyTFsReport.html")
file.copy("KeyTFsReport.html", htmlFile, overwrite = TRUE)
unlink("KeyTFsReport.html")
#After all result files are generated. We will copy the output dir from outPath to result dir under project dir. This step will be done by GUI.
