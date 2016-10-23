library("ggplot2")

input<-read.table(overviewFile,header=TRUE)
input=input[-1,]
accIndex=c(1,3)
varIndex=c(2,4)
Accuracy=suppressWarnings(as.numeric(levels(input)))[input[accIndex]]
var = suppressWarnings(as.numeric(levels(input)))[input[varIndex]]
Sample<-c("Testing set", "Training set")
performance<-data.frame(Sample)
performance$Accuracy<- Accuracy
plot<-ggplot2::ggplot(performance,aes(x=Sample, y=Accuracy))+
	geom_bar(stat="identity", position="dodge")+
	geom_errorbar(aes(ymin=Accuracy-var,ymax=Accuracy+var),size=.5,width=.5,position=position_dodge(.9))+
	theme_bw(24)+
	scale_y_continuous(breaks=seq(0.0,1.0,0.1))+
	scale_fill_manual(values=c("black","grey"))+
	xlab("")
fileName="Classification_Performance.png"
png(fileName,width=600,height=800)
print(plot)
dev.off()
performanceFile = paste0(outDir, "/", fileName)
file.copy(fileName, performanceFile, overwrite=TRUE)
unlink(fileName)

coefficients<-read.table(TfFile,header=TRUE)
coefficients$TF<-rownames(coefficients)
coefficients<-coefficients[which(coefficients$x != 0),]
coefficients<-coefficients[-1,]
coefficients$Feature<-abs(coefficients$x)

coefficients$Feature<-coefficients$Feature/max(coefficients$Feature)
coefficients=coefficients[order(coefficients[,3],decreasing=TRUE)[1:20],]
coefficients$TF<-factor(coefficients$TF,levels=coefficients$TF[order(coefficients[,3],decreasing=TRUE)])
fileName="Feature_Values.png"
png(fileName,width=1600,height=600)
plot2<-ggplot2::ggplot(coefficients,aes(x=TF,y=Feature))+
	geom_bar(stat="identity",position="dodge")+
	theme_bw(24)+
	theme(axis.text.x=element_text(angle=45,hjust=1))+
	ylab("Normalised Feature Coefficient")
print(plot2)
dev.off()
FeatureFile = paste0(outDir, "/", fileName)
file.copy(fileName, FeatureFile, overwrite = TRUE)
unlink(fileName)

