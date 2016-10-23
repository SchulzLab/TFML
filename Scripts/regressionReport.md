# Regression report

This is the report from regression result, and it is generated at 2016-10-18 11:48:37.

## Regression performance
This figure shows the result of Correlation, Spearman for each sample.

![result](/home/thsieh/EpigeneticsTools/RegressionTest2/Sample_overview.png)

## Result table
This table shows the result of Correlation, Spearman for each sample.


|Sample_Name                                  |Correlation  |CorrelationVar  |Spearman   |SpearmanVar  |
|:--------------------------------------------|:------------|:---------------|:----------|:------------|
|41_Hf01_NewScaling_TFA__2016.08.09_10.26.09  |0.6351514    |0.0000237582    |0.6826016  |2.67597e-05  |
|41_Hf02_NewScaling_TFA__2016.08.09_01.11.50  |0.5714844    |0.0000395503    |0.6255849  |6.73167e-05  |
|41_Hf03_NewScaling_TFA__2016.08.12_16.59.49  |0.6171135    |0.0001367972    |0.6581553  |4.97353e-05  |

## Command 
The command we used is as followed.<br />
*Rscript HGSB_Regressor.R -outP=/home/thsieh/EpigeneticsTools/RegressionTest2 -dataDir=/home/thsieh/Epigenetics_project/Test/Result/ct -out_var=FPKM -nworkers=10 -Alpha=0.01 -Testsize=0.2 -Nfolds=6 -TestCV=2 -model=C*<br />
