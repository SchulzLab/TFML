## Collect arguments
args <- commandArgs( TRUE )
 
## Default setting when no arguments passed
if( length( args ) < 1 ) {
	args <- c( "--no input file" )
}

print( args[ 1 ] )
#Get filelist from two folders
inputFileName1 = list.files( args[ 1 ] )
inputFileName2 = list.files( args[ 2 ] )

inputList1 = list()
inputList2 = list()

#Read data from each sample
for( i in c( 1 : length( inputFileName1 ) ) ){
	data = read.table( paste0( args[ 1 ], "/", inputFileName1[ i ] ), header = TRUE )
	inputList1[[i]] = data
}
for( i in c( 1 : length( inputFileName2 ) ) ){
	data = read.table( paste0( args[ 2 ], "/", inputFileName2[ i ] ), header = TRUE )
	inputList2[[i]] = data
}
print(inputList1[[1]][1:4,1:4])
#Calculate the avg gene expression and TF affinities
colLen = ncol( inputList1[[1]] )
rowLen = nrow( inputList1[[1]] )
data1 = as.table( matrix( rep( 0, colLen * rowLen ), ncol = colLen, byrow = TRUE ) )
data2 = as.table( matrix( rep( 0, colLen * rowLen ), ncol = colLen, byrow = TRUE ) )

for( i in c( 1 : rowLen ) ){
	for( j in c( 2 : colLen ) ) {
		sum = 0
		for( k in c( 1 : length( inputFileName1 ) ) ){
			sum = sum + as.numeric( inputList1[[k]][ i, j ])
		}
		data1[ i, j ] = sum / length( inputFileName1 )
	}
}

for( i in c( 1 : rowLen ) ){
	for( j in c( 2 : colLen ) ) {
		sum = 0
		for( k in c( 1 : length( inputFileName2 ) ) ){
			sum = sum + as.numeric( inputList2[[k]][ i, j ])
		}
		data2[ i, j ] = sum / length( inputFileName2 )
	}
}
rownames( data1 ) = rownames( inputList1[[1]] )
colnames( data1 ) = colnames( inputList1[[1]] )
rownames( data2 ) = rownames( inputList1[[1]] )
colnames( data2 ) = colnames( inputList1[[1]] )

colLen1 = ncol( data1 )
colLen2 = ncol( data2 )
if( colLen1 != colLen2 ){
	args <- c( "column numbers are different" )
}

rowLen1 = nrow( data1 )
rowLen2 = nrow( data2 )

if( rowLen1 != rowLen2 ){
	args <- c( "row numbers are different" )
}

#Add small value to avoid division by zero
data1 = data1 + 0.0000001
data2 = data2 + 0.0000001

#Calculate the fold change between two classes
outData = as.data.frame( matrix( rep( 0, colLen1 * rowLen1 ), ncol = colLen1, byrow = TRUE ) )
for( i in c( 1 : rowLen1 ) ){
	for( j in c( 2 : colLen1 ) ) {
		outData[ i, j ] = as.numeric( data1[ i, j ] ) / as.numeric( data2[ i, j ] )
	}
}
rownames( outData ) = rownames( data1 )
colnames( outData ) = colnames( data1 )

#Calculate log2 of gene expression fold change
outData[ , 2 ] = log2( outData[ , 2 ] )

#Assing binary class to gene expression
for( i in c( 1 : rowLen ) ){
	if( outData[ i, 2 ] <= 0 ){
		outData[ i, 2 ] = 0
	}
	else{
		outData[ i, 2 ] = 1
	}
}
outData[,1] = inputList1[[1]][, 1]
print(inputList1[[1]][,1])
print(outData[,1])
#dir = paste0( "analysis_", fileName )
#dir.create( dir, showWarnings = FALSE )

#outName = paste0( dir, "/", "detail_", fileName )
outName = paste0( "ratio.csv" )
write.table(outData, file = outName, row.names=FALSE )
