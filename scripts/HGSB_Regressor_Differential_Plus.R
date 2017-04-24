args <- commandArgs(TRUE)
library('methods')
ggplotAvailable<-require("ggplot2")
if(length(args) < 1) {
  args <- c("--help")
}
 
if("--help" %in% args) {
  cat("
      Arguments:
      --outDir= Output path (required)
      --dataDir= Data directory (required)
      --out_var= Name of the response variable (required)
      --cores= Number of the cores to use (1 as default)
      --alpha= Alpha parameter stepsize (0.01 as default)
      --testsize= Size of test data (0.2 as default)
      --Ofolds= Number of outer folds for model validation (10 as default)
")      
  q(save="no")
}

#Processing command line arguments
parseArgs <- function(x) strsplit(sub("^--", "", x), "=")
argsDF <- as.data.frame(do.call("rbind", parseArgs(args)))
argsL <- as.list(as.character(argsDF$V2))
names(argsL) <- argsDF$V1

#Checking required arguments
if(is.null(argsL$outDir)) {
 cat("Error!\n\n  Please specify an output directory \n\n ")
q(save="no")
}
 
if(is.null(argsL$dataDir)) {
 cat("Error!\n\n  Please specify the data directory \n\n ")
q(save="no")
}

if(is.null(argsL$out_var)) {
 cat("Error!\n\n Please enter the name of the response variable \n\n ")
q(save="no")
}

#Checking for optional arguments
if(is.null(argsL$cores)) {
 argsL$cores<-20
}
if(is.null(argsL$testsize)){
argsL$testsize<-0.2
}

if(is.null(argsL$Ofolds)){
argsL$Ofolds<-10
}

if(is.null(argsL$alpha)) {
argsL$alpha <-0.01
}

#Creating output directory if necessary
dir.create(argsL$outDir,showWarning=FALSE)

#Loading required packages and initialising index variables
require(glmnet)
library("doMC")
i<-0
k<-0
counter<-0
registerDoMC(argsL$cores)
#Checking the total number of samples
FileList<-list.files(path=argsL$dataDir)
print(paste("Samples to analyse:",as.character(length(FileList)),sep=" "))
for(Sample in FileList){
	counter<-counter+1
	print(paste(as.character(counter),unlist(unlist(strsplit(Sample,".txt")))))
	}

#Creating the header for the overview table
SampleOverview<-c("Name","Mean_TestAcc","Var_TestAcc","Mean_TrainAcc","Var_TrainAcc")

#Declare elastic net functions
elaBinomial<-function(a,x,y){
	elasticnet<-cv.glmnet(x, y, alpha=a,family="binomial",type.measure="class",parallel=TRUE)
	min(elasticnet$cvm)
	}
elaMultinomial<-function(a,x,y){
	elasticnet<-cv.glmnet(x, y, alpha=a,family="multinomial",type.measure="class",parallel=TRUE)
	min(elasticnet$cvm)
	}

# Data Preprocessing 
for(Sample in FileList){
	# Process file names for plot title
	name<-strsplit(Sample, ".",fixed=TRUE)[[1]][1]
	print(name)
	i<-i+1
	#Loading the data matrix
	M<-read.table(paste(argsL$dataDir,Sample,sep="/"),header=TRUE,stringsAsFactors=FALSE,row.names=1)
	#Removing features with standard deviation zero
	SD<-apply(M,2,sd)
	Feature_zero_SD<-as.vector(which(SD==0))
	if(length(Feature_zero_SD)>0){
		print("Warning! The following features are constant and will be removed from the feature matrix")
		print(colnames(M)[Feature_zero_SD])
		M<-M[,-c(Feature_zero_SD)]
	}
	#Initialising FeatureNames, Test and Training Accuracy vectors and retrieving the column containing the response variable
	FeatureName<-colnames(M)
	Response_Variable_location<- grep(argsL$out_var,FeatureName)
	TestAcc<-c(1:argsL$Ofolds)
	TrainAcc<-c(1:argsL$Ofolds)
	F1_1<-c(1:argsL$Ofolds)
	F1_2<-c(1:argsL$Ofolds)
	alphas=seq(0.0,1.0,as.numeric(argsL$alpha))
	#Normalising the data matrix
	M[,-Response_Variable_location]<-log2(M[,-Response_Variable_location]+1)
	M[,-Response_Variable_location]<-scale(M[,-Response_Variable_location],center=TRUE, scale=TRUE)
	#Balancing the data set
	subM<-list(list())
	bM<-c()
#	bM<-M
	index=0
	for (i in unique(M[,Response_Variable_location])){
		index<-index+1
		subM[[index]]<-M[which(M[,Response_Variable_location]==i),]
	}
	mSize=min(sapply(subM,dim)[1,])
	print(mSize)
	test_size<-1/as.numeric(argsL$testsize)
	print(test_size)
	for (i in 1:length(subM)){
		rndselect=sample(x=nrow(subM[[i]]),size=mSize)
		subM[[i]]=subM[[i]][rndselect,]
		bM<-rbind(bM,subM[[i]])
	}
	#Loop through the outer folds
	for (k in 1:argsL$Ofolds){
		print(paste("Iteration: ",as.character(k),sep=" "))
		#Balanced selection of test and training data
		Test_Data<-c()
		Train_Data<-c()
		for (i in 1:length(subM)){
			rndselect=sample(x=nrow(subM[[i]]), size=mSize/test_size)
			Test_Data<-rbind(Test_Data,subM[[i]][rndselect,])
			Train_Data<-rbind(Train_Data,subM[[i]][-rndselect,])
#			rndselect=sample(x=nrow(M),size=as.numeric(argsL$testsize)*nrow(M))
#			Test_Data<-M[rndselect,]
#			Train_Data<-M[-rndselect,]
		}
		#Split the features from response
		x_train<-as.matrix(Train_Data[,-Response_Variable_location])
		x_test<-as.matrix(Test_Data[,-Response_Variable_location])
		y_train<-as.vector(unlist(Train_Data[,Response_Variable_location,drop=FALSE]))
		y_test<-as.vector(unlist(Test_Data[,Response_Variable_location]))
		#Training model parameters in the inner cross validation
		if (length(unique(M[,Response_Variable_location]))==2){
			aError<-sapply(alphas,elaBinomial,x_train,y_train)
		}else{
			aError<-sapply(alphas,elaMultinomial,x_train,y_train)
		}
		#Determine best model and retrain it
		index<-which(aError==min(aError))
		if (length(unique(M[,Response_Variable_location]))==2){
			elasticnet<-cv.glmnet(x_train, y_train,alpha=alphas[index],family="binomial",type.measure="class",parallel=TRUE)
		}else{
			elasticnet<-cv.glmnet(x_train, y_train,alpha=alphas[index],family="multinomial",type.measure="class",parallel=TRUE)
		}
		#Generating a plot visualising the model selection
		png(paste(paste(paste(argsL$outDir,name,sep="/"),k,sep="-"),"png",sep="."))
		plot(elasticnet)
		dev.off()
		#Applying the selected  model to the test data
		predict_test<-predict(elasticnet, x_test, s="lambda.min",type="class")
		predict_train<-predict(elasticnet, x_train, s="lambda.min",type="class")
		#Printing and storing the performance table
		print("Performance on test data:")
		tTest<-table(y_test,predict_test)
		print(tTest)
		write.table(tTest,file=paste(argsL$outDir,"/Table_",k,"_",name,".txt",sep=""),quote=FALSE,sep="\t",row.names=FALSE)
		tTrain<-table(y_train,predict_train)
		#Calculating Accuracy measures
		TestAcc[k]<-0
		TrainAcc[k]<-0
		F1_1[k]<-0
		F1_2[k]<-0
		for (index in 1:dim(tTest)[1]){
			TestAcc[k]<-TestAcc[k]+tTest[(index-1)*dim(tTest)[1]+index]
			TrainAcc[k]<-TrainAcc[k]+tTrain[(index-1)*dim(tTest)[1]+index]
			}
		F1_1[k]<-(2*tTest[1])/(2*tTest[1]+tTest[2]+tTest[3])
		F1_2[k]<-(2*tTest[4])/(2*tTest[4]+tTest[2]+tTest[3])
		print(paste0("F1-Measure: ",F1_1[k]," ",F1_2[k]))
		TestAcc[k]<-TestAcc[k]/sum(tTest)
		print(paste0("Accuracy: ",TestAcc[k]))
		TrainAcc[k]<-TrainAcc[k]/sum(tTrain)
		}
	
	#Storing the mean performance values
	sampleResult<-c(name,mean(TestAcc),var(TestAcc),mean(F1_1),var(F1_1),mean(F1_2),var(F1_2),mean(TrainAcc),var(TrainAcc))
	print(paste(paste("Test-Acc",mean(TestAcc),sep=" "),var(TestAcc),sep=" "))
	print(paste(paste("Train-Acc",mean(TrainAcc),sep=" "),var(TrainAcc),sep=" "))
	print(paste(paste("F1_1",mean(F1_1),sep=" "),var(F1_1),sep=" "))
	print(paste(paste("F1_2",mean(F1_2),sep=" "),var(F1_2),sep=" "))
	SampleOverview<-rbind(SampleOverview,sampleResult)
	#Learning one model on the full data set for feature analysis	
	print("learning all")
	x_com<-as.matrix(bM[,-Response_Variable_location])
	y_com<-as.vector(unlist(bM[,Response_Variable_location,drop=FALSE]))
	aError=0
	if (length(unique(M[,Response_Variable_location]))==2){
		aError<-sapply(alphas,elaBinomial,x_com,y_com)
	}else{
		aError<-sapply(alphas,elaMultinomial,x_com,y_com)
	}
	index<-which(aError==min(aError))
	if (length(unique(M[,Response_Variable_location]))==2){
		elasticnet<-cv.glmnet(x_com, y_com,alpha=alphas[index],family="binomial",type.measure="class",parallel=TRUE)
	}else{
		elasticnet<-cv.glmnet(x_com, y_com,alpha=alphas[index],family="multinomial",type.measure="class",parallel=TRUE)
	}

	#Store the feature values
	if (length(unique(bM[,Response_Variable_location]))>2){
		coefO<-coef(elasticnet,s="lambda.min")
		for (i in names(coefO)){
			nf<-(coefO[i][[1]][,1])[-1]
			nf2<-nf/max(abs(nf))
			nf3<-t(nf2)
			nf3<-as.data.frame(nf3)
			nf4<-t(rbind(colnames(nf3),nf3))
			colnames(nf4)<-c("TF","value")
			nf4[,2]<-as.numeric(as.character(nf4[,2]))
			nf4<-as.data.frame(nf4)
			nf4[,2]<-as.numeric(as.character(nf4[,2]))
			write.table(nf4,file=paste(argsL$outDir,paste("Class",i,"Features.txt",sep="-"),sep='/'),quote=FALSE,sep="\t",row.names=FALSE)
			nf4<-nf4[which(data$nf4$value >0.05),]
			np<-c(1:length((nf4[,2])))
			np[which(nf4[,2]>0)]<-1
			np[which(nf4[,2]<=0)]<-0
			if (ggplotAvailable){
				ggplot2::ggplot(nf4,aes(x=reorder(TF,value),y=value,width=0.8,fill=np))+
				geom_bar(stat="identity")+
				theme_bw(15)+ylab("Normalised feature weight")+xlab("TF")+
				theme(axis.text.x=element_text(angle=45,hjust=1))+
				theme(strip.background  = element_blank())+
				theme(legend.position="none")
				ggsave(paste0(argsL$outDir,"Feature_Coeffcients_Class",i,"_",name,".png"),width=40,height=10,units=c("cm"))
			}
		}
	}else{
			nf<-coef(elasticnet,s="lambda.min")[,1][-1]
			nf2<-nf/max(abs(nf))
			nf3<-t(nf2)
			nf3<-as.data.frame(nf3)
			nf4<-t(rbind(colnames(nf3),nf3))
			colnames(nf4)<-c("TF","value")
			nf4[,2]<-as.numeric(as.character(nf4[,2]))
			nf4<-as.data.frame(nf4)
			nf4[,2]<-as.numeric(as.character(nf4[,2]))
			write.table(nf4,file=paste(argsL$outDir,paste(name,"Features.txt",sep="-"),sep='/'),quote=FALSE,sep="\t",row.names=FALSE)
			nf4<-nf4[which(data$nf4$value >0.05),]
			np<-c(1:length((nf4[,2])))
			np[which(nf4[,2]>0)]<-1
			np[which(nf4[,2]<=0)]<-0
			if (ggplotAvailable){
				ggplot2::ggplot(nf4,aes(x=reorder(TF,value),y=value,width=0.8,fill=np))+
				geom_bar(stat="identity")+
				theme_bw(15)+ylab("Normalised feature weight")+xlab("TF")+
				theme(axis.text.x=element_text(angle=45,hjust=1))+
				theme(strip.background  = element_blank())+
				theme(legend.position="none")
				ggsave(paste0(argsL$outDir,"Feature_Coeffcients_",name,".png"),width=40,height=10,units=c("cm"))
		}
	}	
}
#Generating summary output table
colnames(SampleOverview)<-SampleOverview[1,]
SampleOverview<-SampleOverview[-1,]
if(class(SampleOverview)=="matrix"){
	ggplotSampleOverview<-as.data.frame(rbind(cbind(SampleOverview[,1:3],rep("Test",length(SampleOverview[,1]))),cbind(SampleOverview[,c(1,8,9)],rep("Training",length(SampleOverview[,1]))),cbind(SampleOverview[,c(1,4,5)],rep("F1_1",length(SampleOverview[,1]))),cbind(SampleOverview[,c(1,6,7)],rep("F1_2",length(SampleOverview[,1])))))
}else{
	ggplotSampleOverview<-as.data.frame(rbind(c(SampleOverview[1:3],"Test"),c(SampleOverview[c(1,8,9)],"Training"),c(SampleOverview[c(1,4,5)],"F1_1"),c(SampleOverview[c(1,6,7)],"F1_2")))
}
colnames(ggplotSampleOverview)<-c("Name","Mean","Variance","Measure")
row.names(ggplotSampleOverview)<-c(1:length(row.names(ggplotSampleOverview)))
ggplotSampleOverview[,2]<-as.numeric(as.character(ggplotSampleOverview[,2]))
ggplotSampleOverview[,3]<-as.numeric(as.character(ggplotSampleOverview[,3]))
write.table(ggplotSampleOverview,file=paste0(argsL$outDir,"/Performance_overview.txt"),quote=FALSE,sep='\t',row.names=FALSE)

if (ggplotAvailable){
	ggplot2::ggplot(ggplotSampleOverview,aes(x=Name,y=Mean,width=0.8,fill=Measure,group=Measure))+
	geom_bar(stat="identity",position="dodge")+
	theme_bw(22)+ylab("Mean accuracy")+xlab("Error type")+
	theme(axis.text.x=element_text(angle=45,hjust=1))+
	scale_y_continuous(breaks=seq(0.0,1.0,0.05))+
	scale_fill_manual(values=c("red","blue"))+
	coord_cartesian(ylim=c(0.0,1.0))+
	geom_errorbar(aes(ymin=Mean-sqrt(Variance),ymax=Mean+sqrt(Variance)),position=position_dodge(0.8),width=.4,size=.5)+
	theme(strip.background  = element_blank())
	ggsave(paste0(argsL$outDir,"/Performance_Barplots.png"),width=20,height=20,units=c("cm"))
	cat("generate png")
}
