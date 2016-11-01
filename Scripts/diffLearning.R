## Collect arguments
args <- commandArgs(TRUE)
 
## Default setting when no arguments passed
if(length(args) < 1){
	args <- c("--no input file")
}

#Get filelist from two folders
inputFileName1 = list.files(args[1])
inputFileName2 = list.files(args[2])
outputName = args[3]
print("Start preprocessing")
inputList1 = list()
inputList2 = list()

nameList = list()
#Read data from each sample
for(i in c(1 : length(inputFileName1))){
	data = read.table(paste0(args[1], "/", inputFileName1[i]), header = TRUE)
	rownames(data) = data[, 1]
	nameList[[length(nameList) + 1]] = data[, 1]
	inputList1[[i]] = data
}
for(i in c(1 : length(inputFileName2))){
	data = read.table(paste0(args[2], "/", inputFileName2[i]), header = TRUE)
	rownames(data) = data[, 1]
	nameList[[length(nameList) + 1]] = data[, 1]
	inputList2[[i]] = data
}
commonRow = Reduce(intersect, nameList)
for(i in c(1 : length(inputFileName1))){
	inputList1[[i]] = inputList1[[i]][commonRow,]
}
for(i in c(1 : length(inputFileName2))){
	inputList2[[i]] = inputList2[[i]][commonRow,]
}

#Calculate the avg gene expression and TF affinities
colLen = ncol(inputList1[[1]])
rowLen = nrow(inputList1[[1]])
data1 = as.table(matrix(rep(0, (colLen - 1) * rowLen), ncol = colLen - 1, byrow = TRUE))
data2 = as.table(matrix(rep(0, (colLen - 1) * rowLen), ncol = colLen - 1, byrow = TRUE))

for(k in c(1 : length(inputFileName1))){
	data1 = data1 + inputList1[[k]][,-1]
}
data1 = data1 / length(inputFileName1)

for(k in c(1 :length(inputFileName2))){
	data2 = data2 + inputList2[[k]][,-1]
}
data2 = data2 / length(inputFileName2)

colLen1 = ncol(data1)
colLen2 = ncol(data2)
if(colLen1 != colLen2){
	args <- c("column numbers are different")
}

rowLen1 = nrow(data1)
rowLen2 = nrow(data2)

if(rowLen1 != rowLen2){
	args <- c("row numbers are different")
}

#Add small value to avoid division by zero
data1 = data1 + 0.0000001
data2 = data2 + 0.0000001

#Calculate the fold change between two classes
outData = as.data.frame(matrix(rep(0, colLen1 * rowLen1), ncol = colLen1, byrow = TRUE))
outData = data1 / data2
outData = cbind(inputList1[[1]][,1], outData)
rownames(outData) = rownames(inputList1[[1]])
colnames(outData) = colnames(inputList1[[1]])

#Calculate log2 of gene expression fold change
outData[, 2] = log2(outData[ , 2 ])

#Assing binary class to gene expression
for(i in c(1 : rowLen)){
	if(outData[i, 2] <= 0){
		outData[i, 2] = 0
	}
	else{
		outData[i, 2] = 1
	}
}

dir = "tfRatio"
if(file.exists(dir)){
	unlink(dir, recursive = TRUE)
}
dir.create(dir, showWarnings = FALSE)
outVar = colnames(outData)[2]
outName = paste0(dir, "/tfRatio.csv")
write.table(outData, file = outName, row.names = FALSE)
if(!file.exists(outputName)){
	dir.create(outputName, showWarnings = FALSE)
}
print("Preprocessing done")
print("Start differentiate learning")
curDir = getwd()
outPath = paste0(curDir, "/", outputName)
dataDir = paste0(curDir, "/", dir)
cmd = paste0("Rscript learnDifferential.R --outP=", outPath, " --dataDir=", dataDir, " --out_var=", outVar, " --nworkers=10 --Alpha=0.01 --Testsize=0.2 --Nfolds=6 --TestCV=1 --model=C")
system(cmd)

print("Generate report")
library(knitr)
outDir = paste0(cur, "/", outputName)
overviewFile = paste0(outDir, "/Sample_Overview.txt")
TfFile = paste0(outDir, "/tfRatio.csv-Features_.txt")
source("diffPlots.R")

controlDir = args[1]
diseaseDir = args[2]
knit2html("DiscriminatoryReport.Rmd")
htmlFile = paste0(outDir, "/DiscriminatoryReport.html")
file.copy("DiscriminatoryReport.html", htmlFile, overwrite = TRUE)
unlink( "DiscriminatoryReport.html")
#After all result files are generated. We will copy the output dir from outPath to result dir under project dir. This step will be done by GUI.
