library("ggplot2")
library(stringr)
library(grid)

#Sample
input<-read.csv(sampleFile, header = TRUE, sep = "\t")
	i = 1
sample = c()
sampleNum = length(input[, 2])
for(i in c(1: sampleNum)){
	sample = c(sample, rep(as.character(input[i, 1]), 2))
}
i = 1
type = c("Correlation", "Spearman")
type = rep(type, sampleNum) 
value = rep(0.0, 2 * sampleNum)
for(i in c(1: sampleNum)){
	value[1 + (i - 1 ) * 2] = input[i, 2]
	value[2 + (i - 1 ) * 2] = input[i, 4]
}
data = data.frame(Sample = sample, Type = type, Value = value)

plot <- ggplot2::ggplot(data, aes(x = Sample, y = Value)) +
	geom_bar(aes(fill = Type), stat = "identity", position = "dodge") +
	theme_bw(16) +
	theme(text = element_text(size = 14)) +
	scale_y_continuous(breaks = seq(0.0, 1.0, 0.1)) +
	xlab("") 

fileName = "Sample_overview.png"
png(fileName, width = 1200, height = 800)
print(plot)
dev.off()
performanceFile = paste0(outDir, "/", fileName)
file.copy(fileName, performanceFile, overwrite = TRUE)
unlink(fileName)
