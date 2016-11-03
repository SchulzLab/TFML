## Collect arguments
args <- commandArgs( TRUE )
 
## Default setting when no arguments passed
if( length( args ) < 1 ) {
	  args <- c( "--no input file" )
}

print( args[ 1 ] )

inputFileName = args[ 1 ]
data = read.table( inputFileName )
splitFileName = unlist( strsplit( inputFileName, "/") )
fileName = splitFileName[ length( splitFileName ) ]
meanSignal = mean( data[ , 5 ] )
maxSignal = max( data[ , 5 ] )
minSignal = min( data[ , 5 ] )

numPeaks = dim( data[ 1 ] )[1]
start = data[ , 2 ]
end = data[ ,3 ]
length = data[ , 3 ] - data[ , 2 ]
meanLen = mean( length )
maxLen = max( length )
minLen = min( length )

#chr = c( "chr1", "chr2", "chr3", "chr4", "chr5", "chr6", "chr7", "chr8", "chr9", "chr10", "chr11", "chr12", "chr13", "chr14", "chr15", "chr16", "chr17", "chr18", "chr19", "chr20", "chr21")
#for( i in 1)


#geneTable = read.table( "reduce_gene_table.txt" )
#tssNum = dim(geneTable)[ 1 ] 
#tssCount = 0
#j = 1
#
#
#for( i in 1 : numPeaks ){
#	for( j in 1 : tssNum ){
#		if( data[ i, 1] == geneTable[ j, 1] ){
#			if( data[ i, 2] >= geneTable[ j, 2] && data[ i, 3] <= geneTable[ j, 3] ){
#				tssCount = tssCount + 1
#				break
#			}
#		}
#	}
#}

dir = paste0( "analysis_", fileName )
dir.create( dir, showWarnings = FALSE )

outName = paste0( dir, "/", "detail_", fileName )
sink( outName, append = FALSE )
cat( "File:", fileName, '\n' )
cat( "Number of open regions:", numPeaks, '\n' )
cat( "Average signal:", meanSignal, '\n' )
cat( "Maximal signal:", maxSignal, '\n' )
cat( "Minimal signal:", minSignal, '\n' )
cat( "Average width:", meanLen, '\n' )
cat( "Maximal width:", maxLen, '\n' )
cat( "Minimal width:", minLen, '\n' )
##cat( "\n" )
#cat( "Top 10 peak:", "\n" )
#for( i in 1:10 ) {
#	cat( paste( data[ i,] ), "\n" )
#}
##sink()
##sData = data[ order( data[, 2 ] ), ]
##outName = paste0( dir, "/", "visual_", fileName, ".jpg" )
##jpeg( outName )
# Plot all chromosome in one jpg file
#jpeg( outName, quality=100,
#     width=1024, height=768)
#	 op <- par(mfcol=c(5,2))
#plot 1
##plot( data[ , 2 ], data[ , 5 ], type='h' )
#par(op)
##dev.off()
