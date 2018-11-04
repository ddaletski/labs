library(dendextend)
library(cluster)
data("votes.repub")

dendrogram = as.dendrogram(agnes(votes.repub))
# color dendrogram branches according to 5-clusters split
dendrogram = set(dendrogram, "branches_k_color", k = 5)
plot(dendrogram)


# data generator
N = 500
x1 = runif(N, 0.1, 2)
y1 = log(1 + -0.2 * x1 + rnorm(N, 0, 0.15))

y2 = runif(N, 0.1, 2)
x2 = log(1 + -0.2 * y2 + rnorm(N, 0, 0.15))

x = c(x1, x2)
y = c(y1, y2)
mat = matrix(c(x, y), ncol=2)


# default
cl = clara(mat, k = 2)
plot(x, y, col=cl$clustering)

# 1 sample
cl = clara(mat, k = 2, samples = 1, sampsize = 100, rngR = TRUE)
plot(x, y, col=cl$clustering)

# many small samples
cl = clara(mat, k = 2, samples = 100, sampsize = 3, rngR = TRUE)
plot(x, y, col=cl$clustering)

# default (4 clusters)
cl = clara(mat, k = 4)
plot(x, y, col=cl$clustering)
