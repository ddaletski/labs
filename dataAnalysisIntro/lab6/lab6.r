library('arules')

tr = read.transactions("trans.csv", format = 'basket', sep = ";", skip = 0)
mat = as(tr, 'matrix') + 0
heatmap(mat, Rowv=NA,Colv=NA,col=paste("gray",100:0,sep=""))

rules = apriori(tr)
inspect(rules)

itemFrequencyPlot(tr, support = 0.2)
