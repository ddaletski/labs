mtcars
attach(mtcars)

# count of cars with autogear
sum(am==0)

# min and max 1/4 mile times
min(qsec)
max(qsec)

# min and max weights
min(wt)
max(wt)

# 3 most economic cars
mtcars[order(-mpg),][1:3,]

# basic statistics of horsepower 
mean(hp)
var(hp)
sd(hp)
quantile(hp, seq(0.0, 1.0, 0.1))


# basic statistics of 1/4 mile time
mean(qsec)
var(qsec)
sd(qsec)
quantile(qsec, seq(0.0, 1.0, 0.1))

# correlation between horsepower and 1/4 mile time
cor(hp, qsec)
plot(hp, qsec)
l = line(qsec ~ hp)
abline(l, col='red')

# summary
summary(mtcars)


# histogram of carburators count
h = hist(carb, right = FALSE)

# frequency table of carburators count
intervals = c()
for (i in (2:length(h$breaks))) {
  interval = paste(h$breaks[i-1], "-", h$breaks[i])
  intervals = c(intervals, interval)
}

df = data.frame(intervals, h$counts)
colnames(df) = c('interval', 'frequency')
df
