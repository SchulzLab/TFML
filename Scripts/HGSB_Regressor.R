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

if(is.null(argsL$model)){
argsL$model<-c("E")

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
dir.create(argsL$outputFolderName) 
Data_Directory <- argsL$dataDir
require(glmnet)
require(doMC)
library("parallel")




# creat the lists which I need later on ==================================================
 FileList<-list.files(path=Data_Directory)
 setwd(Data_Directory)

Gene_model_ENET <- vector("list", length(FileList)*argsL$TestCV)
Gene_best_model_correlation<-vector("list", length(FileList)*argsL$TestCV)
Gene_best_model_correlation_Spearman<-vector("list", length(FileList)*argsL$TestCV)
Best_Gene_model_coefficients<-vector("list", length(FileList)*argsL$TestCV)
Sample_Specific_Test_Data<-vector("list", length(FileList)*argsL$TestCV)
Sample_Specific_Train_Data<-vector("list", length(FileList)*argsL$TestCV)
Alpha_prameters<-vector("list", length(FileList)*argsL$TestCV)
Model_Statistics<-vector("list", length(FileList)*argsL$TestCV)
Scatter_plot_Data<-vector("list", length(FileList)*argsL$TestCV)
Sample_View<-vector("list",length(FileList))
print(paste("Total number of samples:",as.character(length(FileList)),sep=" "))
counter<-0
for(Sample in FileList){
	counter<-counter+1
	print(paste(as.character(counter),unlist(unlist(strsplit(Sample,".txt")))))
	}
# Data Preporcessing 
i<-0
k<-0
Plot_save<-paste(Where,"Gene_model_correlation_plot_ENET.pdf", sep="/")
pdf(Plot_save)
for(Sample in FileList){

	i<-i+1
	#M<-read.table(Sample,header=TRUE,sep="")
	M<-read.csv(Sample,header=TRUE,sep="")
	print(paste("Learning Sample no. ",as.character(i),sep=" "))	
	M<-M[!duplicated(M[,1]),]
	rownames(M)<-as.vector(M[,1])
	M<-M[,-1]
	M<-unique(M)
	M<-data.frame(M)
	FeatureName<-colnames(M)
	
	SD<-apply(M,2,sd)
	Feature_zero_SD<-as.vector(which(SD==0))
	if(length(Feature_zero_SD)>0){M<-M[,-c(Feature_zero_SD)]}
	M<-log2(M+1)
	M<-data.frame(scale(M),center=TRUE, scale=TRUE)
	# Process file names for plot title

	Sample_name<-unlist(strsplit(Sample, ".txt"))
	name<-unlist(Sample_name)
	print(name)
	for (k in 1:argsL$TestCV){
		
		print(paste("Iteration: ",as.character(k),sep=" "))
		# Partition data into test and train and put them in list for later usage.
		test_size<-1/as.numeric(argsL$Testsize)
		Test_size<-round(nrow(M)/test_size)
		rndselect<-sample(x=nrow(M), size= Test_size)
		Test_Data<-M[rndselect,]
		Train_Data<-M[-rndselect,]
		Sample_Specific_Test_Data[[((i-1)*argsL$TestCV)+k]]<-Test_Data
		names(Sample_Specific_Test_Data)[((i-1)*argsL$TestCV)+k]<-paste(Sample,as.character(k),sep="_")
		
		Sample_Specific_Train_Data[[((i-1)*argsL$TestCV)+k]]<-Train_Data
		names(Sample_Specific_Train_Data)[((i-1)*argsL$TestCV)+k]<-paste(Sample,as.character(k),sep="_")

		# Split the features from response
	
		Response_Variable_location<- grep(argsL$out_var,FeatureName)
		x_train<-as.matrix(Train_Data[,-Response_Variable_location])
		#print(x_train)
		x_test<-as.matrix(Test_Data[,-Response_Variable_location])
		y_train<-as.vector(unlist(Train_Data[,Response_Variable_location,drop=FALSE]))
		#print(y_train)
		y_test<-as.vector(unlist(Test_Data[,Response_Variable_location]))
	 	A<-c()
		if(length(argsL$model)>0 & argsL$model=="L"){
			alphaslist <-c(1)
			registerDoMC(cores = argsL$nworkers)
			}
		else{
		alphaslist<-seq(0,1,by=as.numeric(argsL$Alpha))
		}
		if(is.null(argsL$constrint)){
			elasticnet<-try(mclapply(alphaslist, function(x){cv.glmnet(x_train, y_train,alpha=x,nfolds=as.numeric(argsL$Nfolds))}, mc.cores=argsL$nworkers))}
		else 
			if(argsL$constrint=="P"){
				elasticnet<-try(mclapply(alphaslist, function(x){cv.glmnet(x_train, y_train,alpha=x,lower=0,nfolds=as.numeric(argsL$Nfolds))}, mc.cores=argsL$nworkers))
			}
		else
			{
			if(argsL$constrint=="N"){
				elasticnet<-try(mclapply(alphaslist, function(x){cv.glmnet(x_train, y_train,alpha=x,upper=0,nfolds=as.numeric(argsL$Nfolds))}, mc.cores=argsL$nworkers))
				}
			}
           

		#if(class(elasticnet) == "try-error") next;
		for (j in 1:length(alphaslist)) {
			A[j]<-min(elasticnet[[j]]$cvm)
			}
	
		index<-which(A==min(A), arr.ind=TRUE)
		#Alpha<- alphaslist[index]
		Gene_model_ENET[[(i-1)*argsL$TestCV+k]]<- elasticnet[[index]]

		names(Gene_model_ENET)[(i-1)*argsL$TestCV+k]<-paste(Sample,as.character(k),sep="_")
		Best_alpha<-alphaslist[index]
		Alpha_prameters[[(i-1)*argsL$TestCV+k]]<-Best_alpha
		names(Alpha_prameters)[(i-1)*argsL$TestCV+k]<-Sample
	
		predict_fit<-predict(Gene_model_ENET[[(i-1)*argsL$TestCV+k]], x_test,s="lambda.min")
		predict_fit_train<-predict(Gene_model_ENET[[(i-1)*argsL$TestCV+k]], x_train,s="lambda.min")
		Best_Gene_model_coefficients[[(i-1)*argsL$TestCV+k]]<-coef(Gene_model_ENET[[(i-1)*argsL$TestCV+k]], s = "lambda.min")
		names(Best_Gene_model_coefficients)[(i-1)*argsL$TestCV+k]<-Sample
		Gene_best_model_correlation[[(i-1)*argsL$TestCV+k]]<-cor(predict_fit,y_test)
		Gene_best_model_correlation_Spearman[[(i-1)*argsL$TestCV+k]]<-cor(predict_fit,y_test,method='spearman')
		Test_error<-sum((y_test- predict_fit)^2)/length(y_test)
		Train_error<-sum((y_train - predict_fit_train)^2)/length(y_train)
		names(Gene_best_model_correlation)[(i-1)*argsL$TestCV+k]<-Sample 
		plot(predict_fit,y_test) 
		title(main=name)
		Scatter_plot_Data[[(i-1)*argsL$TestCV+k]]<-data.frame(Prediction=predict_fit,Test_Data=y_test)
		names(Scatter_plot_Data)[[(i-1)*argsL$TestCV+k]]<-Sample 
		Model_Statistics[[(i-1)*argsL$TestCV+k]]<-data.frame(Sample_name=name,Training_Error=Train_error, Testing_Error=Test_error, Correlation=Gene_best_model_correlation[[(i-1)*argsL$TestCV+k]],Spearman=Gene_best_model_correlation_Spearman[[(i-1)*argsL$TestCV+k]],Alpha=Best_alpha, Number_TrainigData=length(y_train))
		if(class(elasticnet) == "try-error") next;
		}
	}	
dev.off()

# save the objects 

Where_to_Save<-paste(Where,"Your_Regression_Result", sep="/")
setwd(Where_to_Save)
save(Best_Gene_model_coefficients, file="Gene_Best_model_coefficeint_ENET.rda")	
#save(Gene_model_ENET , file="CV.GLment.Gene_model_ENET.rda")
save(Gene_best_model_correlation, file="Gene_models_ENET_correlation_test_data_ENET.rda")
#save(Sample_Specific_Test_Data, file="sample_Specific_Test_Data.rda")
#save(Sample_Specific_Train_Data, file="sample_Specific_Train_Data.rda")
#save(Alpha_prameters, file="Alpha_Parameres.rda")
#save(Scatter_plot_Data, file="Scatter_plotData.rda")
FinalModels_statistics<-do.call("rbind", Model_Statistics)

#Sample_Correlation[[i]]<-data.frame(Mean=mean(),Variance=var())
for (i in 1:length(FileList)){
	cm<-mean(FinalModels_statistics$Correlation[(((i-1)*argsL$TestCV)+1):(i*argsL$TestCV)])
	csd<-var(FinalModels_statistics$Correlation[((i-1)*argsL$TestCV+1):(i*argsL$TestCV)])
	cms<-mean(FinalModels_statistics$Spearman[(((i-1)*argsL$TestCV)+1):(i*argsL$TestCV)])
	csds<-var(FinalModels_statistics$Spearman[((i-1)*argsL$TestCV+1):(i*argsL$TestCV)])
	erm<-mean(FinalModels_statistics$Testing_Error[(((i-1)*argsL$TestCV)+1):(i*argsL$TestCV)])
	ersd<-var(FinalModels_statistics$Testing_Error[(((i-1)*argsL$TestCV)+1):(i*argsL$TestCV)])
	Sample_View[[i]]<-data.frame(Sample_Name=FinalModels_statistics$Sample_name[((i-1)*argsL$TestCV)+1],Correlation=cm,CorrelationVar=csd,Spearman=cms,SpearmanVar=csds,Error=erm,ErrorVar=ersd)
}
save(FinalModels_statistics, file="finalModels_Statistics.rda")
write.csv(FinalModels_statistics, file="Model_Statistics.csv")
Sample_ViewF<-do.call("rbind",Sample_View)
write.csv(Sample_ViewF,file="Sample_View.csv")
print("Learning Finished!")
corleation<-as.vector(unlist(Gene_best_model_correlation))
png("Gene_model_prediction_correlation_ENET")
barplot(corleation, main="Correlation between test and predicted data", col="green")
dev.off()


#==========================================================================================DO Feature Analysis===================================================================
if(argsL$F_test=="TRUE"){
	cat("Started to analyze features! \n\n")
	interactios_Fscore<-vector("list", length(Gene_model_ENET))
	for (j in 1:length(Gene_model_ENET)){
		Data<-Sample_Specific_Train_Data[[j]]
		Sample_Name<-names(Sample_Specific_Train_Data[[j]])
	
		FeatureName<-colnames(Data)
		Where_is_Response<- grep(argsL$out_var,FeatureName)

		y_test<- Data[,Where_is_Response]  
		output<- y_test
		x_test<-Data[,-Where_is_Response]


		coef_matrix<-coef(Gene_model_ENET[[j]], s="lambda.min")
		a<-coef_matrix[,1]
		Coef<- data.frame(a, drop=FALSE)


		index<-which(Coef[,1]!=0)
		features<-rownames(Coef[index,])
		features<- features[-1]   

		feat.stats<-vector("list", length(features))


		if(length(features)>=1){
			for(i in 1:length(features)) {
				temp_expr<-x_test
				temp_expr[,features[i]]<-0
				input<-as.matrix(temp_expr) 
				x_test<-as.matrix(x_test)
		
				# do prediction with leaving out one feature every time.
				pred1 <- predict(Gene_model_ENET[[j]], input, s="lambda.min")
				pred2 <- predict(Gene_model_ENET[[j]], x_test, s="lambda.min")
				# compute the RSS. 
				rss1 <- sum((pred1 - output)^2)	
				rss2 <- sum((pred2 - output)^2)
	
				rss1 <- rss1/ncol(x_test)		
				rss2 <- rss2/ncol(x_test)
				df2 <- (nrow(x_test)) - length(features) + 1	
	
				fstats <- (rss1 - rss2)/(rss2/df2)
				feat.stats[[i]]<-data.frame(feature=features[i], fstats=fstats, pval=pf(fstats, 1, df2, lower.tail=FALSE),coefficient=Coef[features[i],1])
				}

			statistics<-do.call("rbind", feat.stats)
			statistics$FDR <- p.adjust(statistics$pval, "fdr")
			targetname<- names(Gene_model_ENET[j])
		
			for(p in 1:nrow(statistics)){
				statistics[p,6]<- targetname
				if(statistics[p,c("coefficient")]>0){
					statistics[p,7]<-"Positive"
					}
				else{
					statistics[p,7]<-"Negative"
					}
				}


			statistics<-statistics[order(statistics[,5]),]
			colnames(statistics)[6:7]<-c("SampleName","Coef_Sign")
			Name<-paste("Regulator_Sign", targetname, sep="")
			statistics<-statistics[,c("feature","fstats","pval","FDR","coefficient","Coef_Sign","SampleName")]
			write.csv(statistics, file=Name)
			interactios_Fscore[[j]]<-statistics
			}
		else{
			print("UPSS!")
			}
		cat("Analysis finished for sample number:") 
		print(j) 
		}
	Features_Fscore<-do.call("rbind",interactios_Fscore)
	save(Features_Fscore,file="Interaction_Matrix.rda")
	save(interactios_Fscore, file="Interaction_scores.rda")
	}
