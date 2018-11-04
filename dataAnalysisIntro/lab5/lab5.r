x <- rbind(matrix(rnorm(100, sd = 0.3), ncol = 2), matrix(rnorm(100, mean = 1, sd = 0.3), ncol = 2))
colnames(x) <- c("x", "y")
cl <- kmeans(x, 2)
plot(x, col = cl$cluster)
points(cl$centers, col = 1:2, pch = 8, cex=2)


library(cluster)
cl <- clara(ruspini, 4)
plot(ruspini, col = cl$clustering, xlab = "x", ylab = "y")


data(agriculture)
plot(agnes(agriculture))
