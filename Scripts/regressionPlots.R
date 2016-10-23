library("ggplot2")
library(stringr)

#Sample
input<-read.csv(sampleFile, header = TRUE, sep = ",")
i = 1
sample = c()
sampleNum = length(input[, 2])
for(i in c(1: sampleNum)){
	sample = c(sample, rep(as.character(input[i, 2]), 2))
}
i = 1
type = c("Correlation", "Spearman")
type = rep(type, sampleNum) 
value = rep(0.0, 2 * sampleNum)
for(i in c(1: sampleNum)){
	value[1 + (i - 1 ) * 2] = input[i, 3]
	value[2 + (i - 1 ) * 2] = input[i, 5]
	#value[3 + (i - 1 ) * sampleNum] = input[i, 7]
}
data = data.frame(Sample = sample, Type = type, Value = value)

plot <- ggplot2::ggplot(data, aes(x = Sample, y = Value)) +
	geom_bar(aes(fill = Type), stat = "identity", position = "dodge") +
	#geom_errorbar( aes( yddmin = Correlation - CorVar, ymax = Correlation + CorVar ), size = .3, width = .5,position = position_dodge( .9 ) ) +
	theme_bw(16) +
	#scale_x_discrete(labels = function(x) str_wrap(x, width = 5)) +
	scale_y_continuous(breaks = seq(0.0, 1.0, 0.1)) +
	xlab("") 
	#theme(axis.text.x = element_text(angle = 45, hjust = 1))

fileName = "Sample_overview.png"
png(fileName, width = 1200, height = 800)
print(plot)
dev.off()
performanceFile = paste0(outDir, "/", fileName)
file.copy(fileName, performanceFile, overwrite = TRUE)
unlink(fileName)
