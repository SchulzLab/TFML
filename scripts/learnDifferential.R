args <- commandArgs(TRUE)
library('methods')

if(length(args) < 1) {
  args <- c("--help")
}
 
## Help 
if("--help" %in% args) {
  cat("
      Beta version of HGSB_Regressor contains Lasso, ELastic Net, Lasso with Negative and postive constraints, ENET with Negative and postive constraints and model feature analysis

      How to run HGSB_Regressor:
 
      Arguments:
      --outP= Path to directory that results should saved
      --dataDir= Data directory path to learn from it
      --out_var= Response varable name
      --nworkers= Number of the cores to use
      --Alpha= Aplha parameter stepsize
      --Testsize= Size of test data. Please specify it as 0.X for X% of whole data to be used for testing. 
      --model= please enter L for lasso and E for Elastic net
      --Nfolds= Number of folds for cross-valdation
      --TestCV= Number of iterations with different test data.
      --constrint= Specify constraint on the coefficents, please enter N for negative and P for positive constraint
      --F_test= Compute the adjasuted pvalue for the features of the model. Please put TRUE if you want to have this analysis
      --outputFolderName= Specify folder names which you should be create upon running and resutls will be there (NOT WORKING!)
      --help=print this text
      
      Example:
      Rscript HGSB_Regressor.R --arg1=/MMCI/MS/DEEP/Result --arg2=/MMCI/MS/DEEP/Data --out_var=Gene_expr --nworkers=15 --Alpha= 0.03  model= E,F_test=TRUE --Testsize=0.2 --Nfolds=6 ,--outputFolderName==Avatar, --constrint= N \n\n 

Contact: azim.dehghani@mpi-inf.mpg.de")


  q(save="no")
}

# Process arguments

parseArgs <- function(x) strsplit(sub("^--", "", x), "=")
argsDF <- as.data.frame(do.call("rbind", parseArgs(args)))
argsL <- as.list(as.character(argsDF$V2))
names(argsL) <- argsDF$V1
argsL$TestCV <- as.numeric(argsL$TestCV )

# Argument Defults

if(is.null(argsL$outP)) {
 cat("Error!\n\n  Please inter the path to to directory that results should saved \n\n ")
q(save="no")
}
 
if(is.null(argsL$dataDir)) {
 cat("Error!\n\n  Please inter the path to directory path to learn from it \n\n ")
q(save="no")
}

if(is.null(argsL$out_var)) {
 cat("Error!\n\n Please inter response variable name \n\n ")
q(save="no")
}

if(is.null(argsL$nworkers)) {
 argsL$nworkers <-15
}
if(is.null(argsL$Testsize)){

argsL$Testsize<-0.2
}

if(is.null(argsL$Nfolds)){
argsL$Nfolds<-6
}

if(is.null(argsL$TestCV)){
argsL$TestCV<-10
}

if(is.null(argsL$Alpha)) {
argsL$Alpha <-0.003
}

if(is.null(argsL$constrint)){
lower_bound<-NULL
upper_bound<-NULL

}else if(argsL$constrint=="P"){
lower_bound<-0
}else if(argsL$constrint=="N"){
upper_bound<-0
 }

if(is.null(argsL$F_test)){
argsL$F_test<-"FALSE"
}

if(is.null(argsL$outputFolderName)){
argsL$outputFolderName<-"Your_Regression_Result"
}



#====================================================================

Where<-argsL$outP
setwd(Where)
Data_Directory <- argsL$dataDir
require(glmnet)
require(doMC)
library("parallel")




# creat the lists which I need later on ==================================================
FileList<-list.files(path=Data_Directory)
setwd(Data_Directory)
print(paste("Total number of samples:",as.character(length(FileList)),sep=" "))
counter<-0
SampleOverview<-c("Name","Mean(TestAcc)","Var(TestAcc)","Mean(TrainAcc)","Var(TrainAcc)")
for(Sample in FileList){
	counter<-counter+1
	print(paste(as.character(counter),unlist(unlist(strsplit(Sample,".txt")))))
	}
# Data Preporcessing 
i<-0
k<-0
registerDoMC(cores=argsL$nworkers)
for(Sample in FileList){
	i<-i+1
	M<-read.csv(Sample,header=TRUE,sep="")
	M<-M[!duplicated(M[,1]),]
	rownames(M)<-as.vector(M[,1])
	M<-M[,-1]
	M<-unique(M)
	M<-data.frame(M)
	FeatureName<-colnames(M)

	Response_Variable_location<- grep(argsL$out_var,FeatureName)
	SD<-apply(M,2,sd)
	Feature_zero_SD<-as.vector(which(SD==0))
	if(length(Feature_zero_SD)>0){M<-M[,-c(Feature_zero_SD)]}
	M[,-Response_Variable_location]<-log2(M[,-Response_Variable_location]+1)
	M[,-Response_Variable_location]<-data.frame(scale(M[,-Response_Variable_location]),center=TRUE, scale=TRUE)

	# Process file names for plot title
	Sample_name<-unlist(strsplit(Sample, ".txt"))
	name<-unlist(Sample_name)
	TestAcc<-c(1:argsL$TestCV)
	TrainAcc<-c(1:argsL$TestCV)

	for (k in 1:argsL$TestCV){
		print(paste("Iteration: ",as.character(k),sep=" "))
		# Partition data into test and train and put them in list for later usage.
		test_size<-1/as.numeric(argsL$Testsize)
		Test_size<-round(nrow(M)/test_size)
		rndselect<-sample(x=nrow(M), size= Test_size)
		Test_Data<-M[rndselect,]
		Train_Data<-M[-rndselect,]
	
		# Split the features from response
		x_train<-as.matrix(Train_Data[,-Response_Variable_location])
		x_test<-as.matrix(Test_Data[,-Response_Variable_location])
		y_train<-as.vector(unlist(Train_Data[,Response_Variable_location,drop=FALSE]))
		y_test<-as.vector(unlist(Test_Data[,Response_Variable_location]))
	
		alphas=seq(0.0,1.0,as.numeric(argsL$Alpha))
		elaA<-function(a){
			elasticnet<-cv.glmnet(x_train, y_train,alpha=a,family="binomial",type.measure="class",parallel=TRUE)
			min(elasticnet$cvm)
		}
		aError<-sapply(alphas,elaA)
		index<-which(aError==min(aError))
		elasticnet<-cv.glmnet(x_train, y_train,alpha=alphas[index],family="binomial",type.measure="class",parallel=TRUE)
		png(paste(paste(paste(Where,Sample_name,sep="/"),k,sep="-"),"png",sep="."))
		plot(elasticnet)
		dev.off()
		predict_test<-predict(elasticnet, x_test, s="lambda.min",type="class")
		predict_train<-predict(elasticnet, x_train, s="lambda.min",type="class")
		tTest<-table(y_test,predict_test)
		tTrain<-table(y_train,predict_train)
		TestAcc[k]<-((tTest[1]+tTest[4])/sum(tTest))
		TrainAcc[k]<-((tTrain[1]+tTrain[4])/sum(tTrain))
		}
	sampleResult<-c(Sample_name,mean(TestAcc),var(TestAcc),mean(TrainAcc),var(TrainAcc))
	print(paste(paste("Test-Acc",mean(TestAcc),sep=" "),var(TestAcc),sep=" "))
	print(paste(paste("Train-Acc",mean(TrainAcc),sep=" "),var(TrainAcc),sep=" "))
	SampleOverview<-rbind(SampleOverview,sampleResult)


	x_com<-as.matrix(M[,-Response_Variable_location])
	y_com<-as.vector(unlist(M[,Response_Variable_location,drop=FALSE]))
	elaA<-function(a){
		elasticnet<-cv.glmnet(x_com,y_com,alpha=a,family="binomial",type.measure="class",parallel=TRUE)
		min(elasticnet$cvm)
		}
	aError<-sapply(alphas,elaA)
	index<-which(aError==min(aError))
	elasticnet<-cv.glmnet(x_train, y_train,alpha=alphas[index],family="binomial",type.measure="class",parallel=TRUE)
	write.table(coef(elasticnet,s="lambda.min")[,1],file=paste(Where,paste(Sample_name,"Features_.txt",sep="-"),sep='/'),quote=FALSE,sep="\t")
	}	

colnames(SampleOverview)<-SampleOverview[1,]
SampleOverview<-SampleOverview[-1,]
write.table(SampleOverview,file=paste(Where,"Sample_Overview.txt",sep='/'),quote=FALSE,sep='\t',row.names=FALSE)

